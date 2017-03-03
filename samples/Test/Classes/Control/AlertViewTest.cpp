
#include "AlertViewTest.h"

AlertViewTest::AlertViewTest()
{
    CADrawerController* drawer = (CADrawerController*)CAApplication::getApplication()->getRootWindow()->getRootViewController();
    drawer->setTouchMoved(false);

}

AlertViewTest::~AlertViewTest()
{
    CADrawerController* drawer = (CADrawerController*)CAApplication::getApplication()->getRootWindow()->getRootViewController();
    drawer->setTouchMoved(true);

}


void AlertViewTest::viewDidLoad()
{
    this->getView()->setColor(CAColor4B::GRAY);
    
    //初始化viewList
    CAButton* btn1 = CAButton::create(CAButton::Type::RoundedRect);
    btn1->setLayout(DLayout(DHorizontalLayout_W_C(240, 0.5), DVerticalLayout_H_C(54, 0.25)));
    btn1->setTag(100);
    btn1->setTitleForState(CAControl::State::Normal, "Click-1");
    btn1->addTarget([=]()
    {
        
        CAAlertView* alert = CAAlertView::create("Alert", "this is a alert!", "close", nullptr);
        alert->show([=](int index)
        {
            this->alertCallBack(index);
        });
        

    }, CAButton::Event::TouchUpInSide);
    this->getView()->addSubview(btn1);
    
    CAButton* btn2 = CAButton::create(CAButton::Type::RoundedRect);
    btn2->setLayout(DLayout(DHorizontalLayout_W_C(240, 0.5), DVerticalLayout_H_C(54, 0.5)));
    btn2->setTag(200);
    btn2->setTitleForState(CAControl::State::Normal, "Click-2");
    btn2->addTarget([=]()
    {
        
        CAAlertView::create("Alert", "this is a alert!", {"ok", "close"})->show([=](int index)
        {
            this->alertCallBack(index);
        });
        
        
    }, CAButton::Event::TouchUpInSide);
    this->getView()->addSubview(btn2);
    
    CAButton* btn3 = CAButton::create(CAButton::Type::RoundedRect);
    btn3->setLayout(DLayout(DHorizontalLayout_W_C(240, 0.5), DVerticalLayout_H_C(54, 0.75)));
    btn3->setTag(300);
    btn3->setTitleForState(CAControl::State::Normal, "Click-3");
    btn3->addTarget([=]()
    {
        
        std::string message = "This message is very long, a lot of buttons, which is a shortcut to use a multi button case.This message is very long, a lot of buttons, which is a shortcut to use a multi button case.This message is very long, a lot of buttons, which is a shortcut to use a multi button case.This message is very long, a lot of buttons, which is a shortcut to use a multi button case.";
        
        CAAlertView::create("Alert", message.c_str(), "button1", "button2", "button3", "button4", "button5", "button6", "button7", "button8", "button9", "button10", nullptr)->show([=](int index)
        {
            this->alertCallBack(index);
        });
        
        
    }, CAButton::Event::TouchUpInSide);
    this->getView()->addSubview(btn3);
    
}

void AlertViewTest::viewDidUnload()
{
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

void AlertViewTest::alertCallBack(int btnIndex)
{
    CCLog("btnIndex==%d",btnIndex);
}



