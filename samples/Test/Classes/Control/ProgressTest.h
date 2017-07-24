
#ifndef __Test__ProgressTest__
#define __Test__ProgressTest__

#include <iostream>
#include "CrossApp.h"

USING_NS_CC;

class ProgressTest: public CAViewController
{
    
public:

	ProgressTest();
    
	virtual ~ProgressTest();
    
    CREATE_FUNC(ProgressTest);
    
protected:
    
    void viewDidLoad();
    
    void viewDidUnload();
};


#endif /* defined(__HelloCpp__ViewController__) */
