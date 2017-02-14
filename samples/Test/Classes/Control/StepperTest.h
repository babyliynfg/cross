
#ifndef __Test__StepperTest__
#define __Test__StepperTest__

#include <iostream>
#include "CrossApp.h"

USING_NS_CC;

class StepperTest: public CAViewController
{
    
public:

	StepperTest();
    
	virtual ~StepperTest();
    
protected:
    
    void viewDidLoad();
    
    void viewDidUnload();
    
public:
    
    CAStepper* step;
    CALabel* step_value;
    
};


#endif /* defined(__HelloCpp__ViewController__) */
