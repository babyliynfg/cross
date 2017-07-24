
#ifndef __Test__TabBarTest__
#define __Test__TabBarTest__

#include <iostream>
#include "CrossApp.h"

USING_NS_CC;

class TabBarTest: public CAViewController
{
    
public:

	TabBarTest();
    
	virtual ~TabBarTest();
    
    CREATE_FUNC(TabBarTest);
    
protected:
    
    void viewDidLoad();
    
    void viewDidUnload();
    
};


#endif /* defined(__HelloCpp__ViewController__) */
