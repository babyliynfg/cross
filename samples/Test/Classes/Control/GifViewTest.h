
#ifndef __Test__GifViewTest__
#define __Test__GifViewTest__

#include <iostream>
#include "CrossApp.h"

USING_NS_CC;

class GifViewTest: public CAViewController
{
    
public:

	GifViewTest();
    
	virtual ~GifViewTest();
    
    CREATE_FUNC(GifViewTest);
    
protected:
    
    void viewDidLoad();
    
    void viewDidUnload();
    
};


#endif /* defined(__HelloCpp__ViewController__) */
