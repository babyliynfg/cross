
#ifndef __Test__SliderTest__
#define __Test__SliderTest__

#include <iostream>
#include "CrossApp.h"

USING_NS_CC;

class SliderTest: public CAViewController 
{
    
public:

	SliderTest();
    
	virtual ~SliderTest();
    
protected:
    
    void viewDidLoad();
    
    void viewDidUnload();
    
public:
    
    CALabel* sliderValue1;
    CALabel* sliderValue2;
    CASlider* slider;
    
public:
    
    void sliderValueChange(CAControl* btn, DPoint point);
    
};


#endif /* defined(__HelloCpp__ViewController__) */
