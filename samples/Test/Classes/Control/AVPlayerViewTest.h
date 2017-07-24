
#ifndef __Test__AVPlayerViewTest__
#define __Test__AVPlayerViewTest__

#include <iostream>
#include "CrossApp.h"

USING_NS_CC;

class AVPlayerViewTest: public CAViewController
{
    
public:

	AVPlayerViewTest();
    
	virtual ~AVPlayerViewTest();
    
    CREATE_FUNC(AVPlayerViewTest);
    
protected:
    
    void viewDidLoad();
    
    void viewDidUnload();
    
};


#endif /* defined(__Test__AVPlayerViewTest__) */
