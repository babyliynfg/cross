
#ifndef __Test__ScrollViewTest__
#define __Test__ScrollViewTest__

#include <iostream>
#include "CrossApp.h"

USING_NS_CC;

class ScrollViewTest: public CAViewController
{
    
public:

	ScrollViewTest();
    
	virtual ~ScrollViewTest();
    
    CREATE_FUNC(ScrollViewTest);
    
protected:
    
    void viewDidLoad();
    
    void viewDidUnload();

};


#endif /* defined(__HelloCpp__ViewController__) */
