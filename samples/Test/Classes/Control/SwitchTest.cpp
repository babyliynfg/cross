
#include "SwitchTest.h"

SwitchTest::SwitchTest()
{
    CADrawerController* drawer = (CADrawerController*)CAApplication::getApplication()->getRootWindow()->getRootViewController();
    drawer->setTouchMoved(false);
}

SwitchTest::~SwitchTest()
{
    CADrawerController* drawer = (CADrawerController*)CAApplication::getApplication()->getRootWindow()->getRootViewController();
    drawer->setTouchMoved(true);
}

void SwitchTest::viewDidLoad()
{
    this->getView()->setColor(CAColor_gray);
    
    CASwitch* customSwitch1 = CASwitch::createWithLayout(DLayout(DHorizontalLayout_L_W(150, 100), DVerticalLayout_T_H(350, 20)), CASwitch::Type::RoundedRect);
    customSwitch1->setTag(100);
    customSwitch1->setIsOn(true, false);
    customSwitch1->setTarget([=](bool on)
    {
        if (!on)
        {
            CCLog("switchStateChange false");
        }
        else
        {
            CCLog("switchStateChange true");
        }
    });
    this->getView()->addSubview(customSwitch1);
    
    CASwitch* customSwitch2 = CASwitch::createWithLayout(DLayout(DHorizontalLayout_R_W(150, 100), DVerticalLayout_T_H(350, 20)), CASwitch::Type::SquareRect);
    customSwitch2->setTag(101);
    customSwitch2->setIsOn(true, false);
    customSwitch2->setOnImage(CAImage::create("image/Switch_on.png"));
    customSwitch2->setOffImage(CAImage::create("image/Switch_off.png"));
    customSwitch2->setTarget([=](bool on)
    {
        if (!on)
        {
            CCLog("switchStateChange false");
        }
        else
        {
            CCLog("switchStateChange true");
        }
    });
    this->getView()->addSubview(customSwitch2);
}

void SwitchTest::viewDidUnload()
{
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


