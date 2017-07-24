
#include "ImageViewTest.h"
#include "FirstViewController.h"

ImageViewTest::ImageViewTest()
{
    this->setTitle("CAImageView");
}

ImageViewTest::~ImageViewTest()
{

}

void ImageViewTest::viewDidLoad()
{
    this->showIndex(0);
}

void ImageViewTest::viewDidUnload()
{
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

void ImageViewTest::showIndex(ssize_t index)
{
    this->getView()->removeAllSubviews();
    
    CAView* view = CAView::createWithLayout(DLayout(DHorizontalLayout_L_R(50, 50), DVerticalLayout_T_B(50, 80)));
    view->setColor(CAColor4B::GRAY);
    this->getView()->addSubview(view);
    
    if (index == 0)
    {
        CAImageView* image1 = CAImageView::createWithImage(CAImage::create("image/h1.png"));
        image1->setLayout(DLayoutFill);
        view->addSubview(image1);
    }
    else if (index == 1)
    {
        CAImageView* image2 = CAImageView::createWithImage(CAImage::create("image/h1.png"));
        image2->setScaleType(CAImageView::ScaleType::FitImageXY);
        image2->setLayout(DLayoutFill);
        view->addSubview(image2);
    }
    else if (index == 2)
    {
        CAImageView* image3 = CAImageView::createWithImage(CAImage::create("image/h1.png"));
        image3->setScaleType(CAImageView::ScaleType::FitImageCrop);
        image3->setLayout(DLayoutFill);
        view->addSubview(image3);
    }
    else if (index == 3)
    {
        CAImageView* image4 = CAImageView::createWithImage(CAImage::create("image/h1.png"));
        image4->setScaleType(CAImageView::ScaleType::FitImageInside);
        image4->setLayout(DLayoutFill);
        view->addSubview(image4);
    }
    else
    {
        CAVector<CAImage* > img;
        for (int i=0; i<8; i++)
        {
            char temp[50];
            sprintf(temp, "animation/npc_382-%d.png",i+1);
            CAImage* im = CAImage::create(temp);
            img.pushBack(im);
        }
        CAImageView* image7 = CAImageView::createWithLayout(DLayoutFill);
        image7->setAnimationImages(img);
        image7->setAnimationDuration(0.2);
        image7->startAnimating();
        view->addSubview(image7);
    }
    
    
    static ssize_t s_index = 0;
    auto btn = CAButton::createWithLayout(DLayout(DHorizontalLayout_NW_C(0.3,0.5), DVerticalLayout_B_H(20 ,50)), CAButton::Type::RoundedRect);
    btn->setTitleForState(CAControl::State::Normal, "Switch Next");
    btn->addTarget([&]
    {
        if (++s_index > 4)
        {
            s_index = 0;
        }
        this->showIndex(s_index);
        
    }, CAButton::Event::TouchUpInSide);
    this->getView()->addSubview(btn);
}

