
#ifndef __Test__ImageViewTest__
#define __Test__ImageViewTest__

#include <iostream>
#include "CrossApp.h"

USING_NS_CC;

class ImageViewTest: public CAViewController
{
    
public:

	ImageViewTest();
    
	virtual ~ImageViewTest();
    
    CREATE_FUNC(ImageViewTest);
    
protected:
    
    void viewDidLoad();
    
    void viewDidUnload();
    
    void showIndex(ssize_t index);
    
public:
    
    CAImageView* AnimationImages();
    
};


#endif /* defined(__HelloCpp__ViewController__) */
