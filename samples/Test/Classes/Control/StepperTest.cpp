
#include "StepperTest.h"
#include "CDUIShowAutoCollectionView.h"

int StepperNum = 0;

StepperTest::StepperTest()
{
    CADrawerController* drawer = (CADrawerController*)CAApplication::getApplication()->getRootWindow()->getRootViewController();
    drawer->setTouchMoved(false);
}

StepperTest::~StepperTest()
{
    CADrawerController* drawer = (CADrawerController*)CAApplication::getApplication()->getRootWindow()->getRootViewController();
    drawer->setTouchMoved(true);
    
    StepperNum = 0;
}

void CDUIShowAutoCollectionView::StepperRightBtnRightcallback(CAButton* btn)
{
    if (showStepperNavigationBar >= 1)
    {
        showStepperNavigationBar = 0;
        StepperNum = showStepperNavigationBar;
    }
    else
    {
        StepperNum = ++showStepperNavigationBar;
    }
    CCLog("StepperNum = %d", StepperNum);
    StepperTest* ViewContrllerStepperTest = new StepperTest();
    ViewContrllerStepperTest->init();
    ViewContrllerStepperTest->setNavigationBarItem(StepperNavigationBar);
    ViewContrllerStepperTest->autorelease();
    RootWindow::getInstance()->getRootNavigationController()->replaceViewController(ViewContrllerStepperTest, false);
}

void StepperTest::viewDidLoad()
{
    this->getView()->setColor(CAColor_gray);
    
    if (StepperNum == 0)
    {
        step_value = CALabel::createWithLayout(DLayout(DHorizontalLayout_W_C(300, 0.5), DVerticalLayout_H_C(100, 0.25)));
        step_value->setText("step_value:0");
        step_value->setColor(CAColor_black);
        step_value->setFontSize(28);
        step_value->setTextAlignment(CATextAlignment::Center);
        step_value->setVerticalTextAlignmet(CAVerticalTextAlignment::Center);
        this->getView()->addSubview(step_value);
        
        step = CAStepper::createWithLayout(DLayout(DHorizontalLayout_W_C(360, 0.5), DVerticalLayout_H_C(60, 0.5)), CAStepper::Orientation::Horizontal);
        //step->setWraps(true);//是否循环,默认循环
        step->setMinValue(0);
        step->setMaxValue(50);
        step->setStepValue(1);
        //step->setAutoRepeat(false);
        this->getView()->addSubview(step);
        step->setTarget([=](float value)
        {
            char tem[30];
            sprintf(tem, "step_value:%.0f",value);
            step_value->setText(tem);
            CCLog("step-tag === %f",value);
        });
    }
    else
    {
        step_value = CALabel::createWithLayout(DLayout(DHorizontalLayout_W_C(300, 0.5), DVerticalLayout_H_C(100, 0.25)));
        step_value->setText("step_value:0");
        step_value->setColor(CAColor_black);
        step_value->setFontSize(28);
        step_value->setTextAlignment(CATextAlignment::Center);
        step_value->setVerticalTextAlignmet(CAVerticalTextAlignment::Center);
        this->getView()->addSubview(step_value);
        
        step = CAStepper::createWithLayout(DLayout(DHorizontalLayout_W_C(60, 0.5), DVerticalLayout_H_C(360, 0.5)), CAStepper::Orientation::Vertical);
        //step->setWraps(true);//是否循环,默认循环
        step->setMinValue(0);
        step->setMaxValue(50);
        step->setStepValue(1);
        //step->setAutoRepeat(false);
        this->getView()->addSubview(step);
        step->setTarget([=](float value)
        {
            char tem[30];
            sprintf(tem, "step_value:%.0f",value);
            step_value->setText(tem);
            CCLog("step-tag === %f",value);
        });
    }
}

void StepperTest::viewDidUnload()
{
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}



