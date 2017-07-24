
#include "ViewAnimationTest.h"

ViewAnimationTest::ViewAnimationTest()
{
    this->setTitle("CAViewAnimation");
}

ViewAnimationTest::~ViewAnimationTest()
{
}

void ViewAnimationTest::viewDidLoad()
{
    this->showIndex(0);
}

void ViewAnimationTest::viewDidUnload()
{
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

void ViewAnimationTest::showIndex(ssize_t index)
{
    this->getView()->removeAllSubviews();

    auto bg = CAImageView::createWithImage(CAImage::create("image/1.jpg"));
    bg->setLayout(DLayoutFill);
    this->getView()->addSubview(bg);
    
    
    if (index == 0)
    {
        auto imageView = CAImageView::createWithLayout(DLayoutZero);
        imageView->setImage(CAImage::create("image/start.jpg"));
        this->getView()->addSubview(imageView);
        
        auto btn = CAButton::createWithLayout(DLayout(DHorizontalLayout_NW_C(0.3, 0.5), DVerticalLayout_B_H(120 ,60)), CAButton::Type::RoundedRect);
        btn->setTitleForState(CAControl::State::Normal, "Start Animation 1");
        this->getView()->addSubview(btn);
        
        btn->addTarget([=]{
            
            imageView->setLayout(DLayoutZero);
            imageView->setAlpha(0);
            
            CAViewAnimation::beginAnimations("");
            CAViewAnimation::setAnimationDuration(1.0f);
            
            imageView->setLayout(DLayoutFill);
            imageView->setAlpha(1.0f);
            
            CAViewAnimation::commitAnimations();
            
        }, CAButton::Event::TouchUpInSide);
    }
    else if (index == 1)
    {
        auto imageView = CAImageView::createWithLayout(DLayout(DHorizontalLayout_W_C(270, 0.3f), DVerticalLayout_H_C(480, 0.4f)));
        imageView->setImage(CAImage::create("image/start.jpg"));
        this->getView()->addSubview(imageView);
        
        auto btn = CAButton::createWithLayout(DLayout(DHorizontalLayout_NW_C(0.3, 0.5), DVerticalLayout_B_H(120 ,60)), CAButton::Type::RoundedRect);
        btn->setTitleForState(CAControl::State::Normal, "Start Animation 2");
        this->getView()->addSubview(btn);
        
        btn->addTarget([=]{
            
            imageView->setLayout(DLayout(DHorizontalLayout_W_C(270, 0.3f), DVerticalLayout_H_C(480, 0.4f)));
            imageView->setRotationY(0);
            
            CAViewAnimation::beginAnimations("");
            CAViewAnimation::setAnimationDuration(1.0f);
            
            imageView->setLayout(DLayout(DHorizontalLayout_W_C(270, 0.7f), DVerticalLayout_H_C(480, 0.4f)));
            
            imageView->setRotationY(720);
            
            CAViewAnimation::commitAnimations();
            
        }, CAButton::Event::TouchUpInSide);
    }
    else
    {
        auto imageView = CAImageView::createWithLayout(DLayoutFill);
        imageView->setImage(CAImage::create("image/start.jpg"));
        this->getView()->addSubview(imageView);
        
        auto btn = CAButton::createWithLayout(DLayout(DHorizontalLayout_NW_C(0.3, 0.5), DVerticalLayout_B_H(120 ,60)), CAButton::Type::RoundedRect);
        btn->setTitleForState(CAControl::State::Normal, "Start Animation 3");
        this->getView()->addSubview(btn);
        
        auto fillRect = DRectZero;
        fillRect.size = imageView->getImage()->getContentSize();
        
        auto zeroRect = DRectZero;
        zeroRect.size.height = fillRect.size.height;
        
        btn->addTarget([=]{
            
            imageView->setLayout(DLayoutFill);
            imageView->setImageRect(fillRect);
            
            CAViewAnimation::beginAnimations("");
            CAViewAnimation::setAnimationDuration(1.0f);
            CAViewAnimation::setAnimationRepeatAutoreverses(true);
            
            imageView->setLayout(DLayout(DHorizontalLayouttZero, DVerticalLayoutFill));
            imageView->setImageRect(zeroRect);
            
            CAViewAnimation::commitAnimations();
            
        }, CAButton::Event::TouchUpInSide);
    }
    
    static ssize_t s_index = 0;
    auto btn = CAButton::createWithLayout(DLayout(DHorizontalLayout_NW_C(0.3,0.5), DVerticalLayout_B_H(20, 60)), CAButton::Type::RoundedRect);
    btn->setTitleForState(CAControl::State::Normal, "Switch Next");
    btn->addTarget([&] {
                  
        if (++s_index > 2)
        {
            s_index = 0;
        }
        this->showIndex(s_index);
        
    }, CAButton::Event::TouchUpInSide);
    this->getView()->addSubview(btn);
}

