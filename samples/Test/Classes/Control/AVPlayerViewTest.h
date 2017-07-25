
#ifndef __Test__AVPlayerViewTest__
#define __Test__AVPlayerViewTest__

#include <iostream>
#include "RootWindow.h"

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
