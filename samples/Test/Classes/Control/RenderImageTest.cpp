
#include "RenderImageTest.h"


RenderImageTest::RenderImageTest()
{
    CADrawerController* drawer = (CADrawerController*)CAApplication::getApplication()->getRootWindow()->getRootViewController();
    drawer->setTouchMoved(false);
}

RenderImageTest::~RenderImageTest()
{
    CADrawerController* drawer = (CADrawerController*)CAApplication::getApplication()->getRootWindow()->getRootViewController();
    drawer->setTouchMoved(true);
}

void RenderImageTest::viewDidLoad()
{
    winSize = this->getView()->getBounds().size;
    this->getView()->setColor(CAColor_gray);
    
    dle_ren_index = 0;
    
    CAButton* btn = CAButton::create(CAButton::Type::SquareRect);
    btn->setLayout(DLayout(DHorizontalLayout_W_C(240, 0.5), DVerticalLayout_B_H(50, 54)));
    btn->setTitleForState(CAControl::State::Normal, "Click");
    btn->setTitleColorForState(CAControl::State::Normal, ccc4(51,204,255,255));
    btn->setTag(1);
    btn->addTarget([=]()
    {
        CADevice::openAlbum(this);
    }, CAButton::Event::TouchUpInSide);
    this->getView()->addSubview(btn);
}

void RenderImageTest::viewDidUnload()
{
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

CADrawView* getStencil(const DSize& size, int index)
{
    if (index == 0)
    {
        DPoint ver[4];
        ver[0] = DPoint(0, 0);
        ver[1] = DPoint(0, size.height);
        ver[2] = DPoint(size.width, size.height);
        ver[3] = DPoint(size.width, 0);
        CADrawView* stencil = CADrawView::create();
        stencil->drawPolygon(ver, 4, ccc4(255, 0, 0, 0), 2, ccc4(255, 0, 0, 0));
        stencil->setFrameOrigin(DPoint(0, size.height));
        return stencil;
    }
    else if (index == 1)
    {
        DPoint cir[720];
        for (int i=0; i<720; i++)
        {
            float x = cosf(i * M_PI/180.f) * size.width/2;
            float y = sinf(i * M_PI/180.f) * size.width/2;
            cir[i] = DPoint(x, y);
        }
        CADrawView* stencil = CADrawView::create();
        stencil->drawPolygon(cir, 720, ccc4(255, 255, 255, 127), 0, ccc4(255, 255, 255, 0));
        stencil->setCenterOrigin(DPoint(size.width/2, size.height/2));
        return stencil;
    }
    return NULL;
}

void RenderImageTest::getSelectedImage(CAImage *image)
{
    int index = 0;
    
    DRect scrollRect;
    scrollRect.origin.x = 100;
    scrollRect.origin.y = 50;
    scrollRect.size.width = winSize.width - 200;
    scrollRect.size.height = winSize.height - 200;
    
    m_clvImage = CAClippingView::create();
    m_clvImage->setStencil(getStencil(scrollRect.size, index));
    m_clvImage->setFrame(scrollRect);
    m_clvImage->setClippingEnabled(false);
    this->getView()->addSubview(m_clvImage);
    
    float temp_mini = 0;
    if (image->getContentSize().width>image->getContentSize().height)
    {
        temp_mini = scrollRect.size.height/image->getContentSize().height;
    }
    else
    {
        temp_mini = scrollRect.size.width/image->getContentSize().width;
    }
    CAScrollView* scrollView = CAScrollView::createWithFrame(m_clvImage->getBounds());
    scrollView->setViewSize(image->getContentSize());
    scrollView->setContentOffset(DPointZero, false);
    scrollView->setMinimumZoomScale(temp_mini);
    scrollView->setMaximumZoomScale(2.5f);
    scrollView->setBackgroundColor(CAColor_clear);
    scrollView->setShowsScrollIndicators(false);
    scrollView->setScrollViewDelegate(this);
    scrollView->setDisplayRange(true);
    scrollView->enabledTopShadow(true);
    scrollView->enabledBottomShadow(true);
    scrollView->enabledLeftShadow(true);
    scrollView->enabledRightShadow(true);
    m_clvImage->addSubview(scrollView);
    
    CAImageView* imv = CAImageView::createWithImage(image);
    imv->setLayout(DLayoutFill);
    imv->setScaleType(CAImageView::ScaleType::FitImageInside);
    scrollView->addSubview(imv);
    
    m_clv = CAClippingView::create();
    m_clv->setStencil(getStencil(scrollRect.size, index));
    m_clv->setFrame(scrollRect);
    m_clv->setTouchEnabled(false);
    m_clv->setInverted(false);
    m_clv->setClippingEnabled(true);
    this->getView()->addSubview(m_clv);
    
    DRect ivRect;
    ivRect.size = winSize;
    ivRect.origin = ccpMult(scrollRect.origin, -1);
    CAView* iv = CAView::createWithColor(ccc4(0,0,0,128));
    iv->setFrame(ivRect);
    m_clv->addSubview(iv);
    
    render_btn = CAButton::create(CAButton::Type::SquareRect);
    render_btn->setLayout(DLayout(DHorizontalLayout_W_C(240, 0.5), DVerticalLayout_B_H(50, 54)));
    render_btn->setTitleForState(CAControl::State::Normal, "Click");
    render_btn->setTitleColorForState(CAControl::State::Normal, ccc4(51,204,255,255));
    render_btn->setTag(2);
    render_btn->addTarget([=]()
    {
        m_clvImage->setClippingEnabled(true);
        CARenderImage* rm = CARenderImage::create(winSize.width-200, winSize.height-200);
        rm->printscreenWithView(m_clvImage);
        
        renderImage = CAView::createWithLayout(DLayout(DHorizontalLayout_L_R(100, 100), DVerticalLayout_T_B(50, 150)));
        this->getView()->addSubview(renderImage);
        
        m_clvImage->setClippingEnabled(false);
        
        if (m_clv!=NULL)
        {
            this->getView()->removeSubview(m_clv);
            m_clv = NULL;
            this->getView()->removeSubview(m_clvImage);
            m_clvImage = NULL;
            this->getView()->removeSubview(render_btn);
            render_btn = NULL;
        }
        
        CAImageView* imageView = CAImageView::createWithLayout(DLayoutFill);
        imageView->setImage(rm->getImageView()->getImage());
        renderImage->addSubview(imageView);
        
        CAScheduler::getScheduler()->schedule(schedule_selector(RenderImageTest::scheduleFuck), this, 3);
    }, CAButton::Event::TouchUpInSide);
    this->getView()->addSubview(render_btn);
}

void RenderImageTest::scheduleFuck(float dt)
{
    if (dle_ren_index>=1) {
        CAScheduler::getScheduler()->unschedule(schedule_selector(RenderImageTest::scheduleFuck), this);
        if (renderImage!=NULL)
        {
            this->getView()->removeSubview(renderImage);
            renderImage = NULL;
        }
        dle_ren_index = 0;
    }else{
        dle_ren_index++;
    }
}
