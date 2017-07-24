
#include "RenderImageTest.h"
#include "RootWindow.h"

RenderImageTest::RenderImageTest()
{
    this->setTitle("CARenderImage");
}

RenderImageTest::~RenderImageTest()
{
}

void RenderImageTest::viewDidLoad()
{
    CAImageView* imageView = CAImageView::createWithImage(CAImage::create("image/h1.png"));
    imageView->setLayout(DLayout(DHorizontalLayout_W_C(400, 0.5), DVerticalLayout_H_C(500, 0.5)));
    imageView->setScaleType(CAImageView::ScaleType::FitImageInside);
    this->getView()->addSubview(imageView);
    
    CAButton* button = CAButton::createWithLayout(DLayout(DHorizontalLayout_W_C(200, 0.5), DVerticalLayout_B_H(20, 60)) , CAButton::Type::RoundedRect);
    button->setTitleForState(CAControl::State::Normal,"截取");
    this->getView()->addSubview(button);
    button->addTarget([=]
    {
        auto winSize = CAApplication::getApplication()->getWinSize();
        
        CARenderImage* render = CARenderImage::create(winSize.width, winSize.height , CAImage::PixelFormat::RGBA8888);
        render->printscreenWithView(RootWindow::getInstance()->getRootViewController()->getView()) ;

        imageView->setImage(render->getImageView()->getImage()) ;

    }, CAButton::Event::TouchUpInSide);
}

void RenderImageTest::viewDidUnload()
{
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


