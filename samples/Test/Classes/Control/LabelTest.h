
#ifndef __Test__LabelTest__
#define __Test__LabelTest__

#include <iostream>
#include "CrossApp.h"

USING_NS_CC;

class LabelTest: public CAViewController
{
    
public:

	LabelTest();
    
	virtual ~LabelTest();
    
    CREATE_FUNC(LabelTest);
    
protected:
    
    void viewDidLoad();
    
    void viewDidUnload();
    
    void showIndex(ssize_t index);
};


#endif /* defined(__HelloCpp__ViewController__) */
