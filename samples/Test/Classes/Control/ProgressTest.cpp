
#include "ProgressTest.h"

ProgressTest::ProgressTest()
{
}

ProgressTest::~ProgressTest()
{
}

void ProgressTest::viewDidLoad()
{
    this->getView()->setColor(CAColor4B::GRAY);
    
    progress_value = CALabel::createWithLayout(DLayout(DHorizontalLayout_L_R(100, 100), DVerticalLayout_T_H(300, 50)));
    progress_value->setTag(100);
    progress_value->setText("");
    progress_value->setFontSize(30);
    progress_value->setColor(ccc4(51, 204, 255, 255));
    progress_value->setTextAlignment(CATextAlignment::Center);
    progress_value->setVerticalTextAlignmet(CAVerticalTextAlignment::Center);
    this->getView()->addSubview(progress_value);
    
    progress = CAProgress::create();
    progress->setLayout(DLayout(DHorizontalLayout_L_R(100, 100), DVerticalLayout_T_H(550, 0)));
    CAScheduler::getScheduler()->schedule(schedule_selector(ProgressTest::progressValueChange), this, 0.01, false);
    this->getView()->addSubview(progress);
}

void ProgressTest::viewDidUnload()
{
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

void ProgressTest::progressValueChange(float _t)
{
    char valueText[20] = "";
    float currentValue = progress->getProgress() + 0.001;
    progress->setProgress(currentValue);
    sprintf(valueText,"%.02f%%",currentValue*100-0.1);
    progress_value->setText(valueText);
    
}

