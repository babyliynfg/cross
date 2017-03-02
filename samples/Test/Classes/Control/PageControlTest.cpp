//
//  PageControlTest.cpp
//  Test
//
//  Created by ly on 2017/3/2.
//
//

#include "PageControlTest.h"

PageControlTest::PageControlTest()
{
    CADrawerController* drawer = (CADrawerController*)CAApplication::getApplication()->getRootWindow()->getRootViewController();
    drawer->setTouchMoved(false);
}

PageControlTest::~PageControlTest()
{
    CADrawerController* drawer = (CADrawerController*)CAApplication::getApplication()->getRootWindow()->getRootViewController();
    drawer->setTouchMoved(true);
}

void PageControlTest::viewDidLoad()
{
    this->getView()->setColor(CAColor_gray);
    
    CAPageControl* pageControl = CAPageControl::createWithLayout(DLayout(DHorizontalLayout_L_R(100, 100), DVerticalLayout_H_C(54, 0.25f)));
    pageControl->setNumberOfPages(5);
    pageControl->setPageIndicatorTintColor(CAColor_white);
    pageControl->setCurrentPageIndicatorTintColor(CAColor_green);
    pageControl->setTarget([=](int index)
    {
        CCLog("btn_tag===%d",pageControl->getCurrentPage());
    });
    this->getView()->addSubview(pageControl);
}

void PageControlTest::viewDidUnload()
{
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}