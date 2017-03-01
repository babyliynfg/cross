//
//  CheckboxTest.cpp
//  Test
//
//  Created by ly≤     on 2017/3/1.
//
//

#include "CheckboxTest.h"

CheckboxTest::CheckboxTest()
{
    CADrawerController* drawer = (CADrawerController*)CAApplication::getApplication()->getRootWindow()->getRootViewController();
    drawer->setTouchMoved(false);
}

CheckboxTest::~CheckboxTest()
{
    CADrawerController* drawer = (CADrawerController*)CAApplication::getApplication()->getRootWindow()->getRootViewController();
    drawer->setTouchMoved(true);
}

void CheckboxTest::viewDidLoad()
{
    this->getView()->setColor(CAColor_gray);
    
    CACheckbox* box = CACheckbox::createWithLayout(DLayout(DHorizontalLayout_W_C(54, 0.5), DVerticalLayout_H_C(54, 0.25f)));
    this->getView()->addSubview(box);
    box->setTarget([](bool var)
    {
        CCLog("box: %d", var);
    });
    
    CACheckbox* box1 = CACheckbox::createWithLayout(DLayout(DHorizontalLayout_W_C(240, 0.5), DVerticalLayout_H_C(54, 0.55f)));
    box1->setImageStateNormal(CAImage::create("source_material/switch_on.png"));
    box1->setImageStateSelected(CAImage::create("source_material/switch_off.png"));
    box1->setTitleStateNormal("未选中");
    box1->setTitleStateSelected("选中");
    this->getView()->addSubview(box1);
    box1->setTarget([](bool var)
    {
        CCLog("box: %d", var);
    });
}

void CheckboxTest::viewDidUnload()
{
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}
