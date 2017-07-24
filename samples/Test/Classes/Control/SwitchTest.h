
#ifndef __Test__SwitchTest__
#define __Test__SwitchTest__

#include <iostream>
#include "CrossApp.h"

USING_NS_CC;

class SwitchTest: public CAViewController
{
    
public:

	SwitchTest();
    
	virtual ~SwitchTest();
    
    CREATE_FUNC(SwitchTest);
    
protected:
    
    void viewDidLoad();
    
    void viewDidUnload();
    
};


#endif /* defined(__HelloCpp__ViewController__) */
