
#ifndef __Test__VideoPlayerControlViewTest__
#define __Test__VideoPlayerControlViewTest__

#include <iostream>
#include "CrossAppExt.h"

USING_NS_CC_EXT;

class VideoPlayerControlViewTest: public CAViewController, public CAVideoPlayerControlViewDelegate
{
    
public:

	VideoPlayerControlViewTest();
    
	virtual ~VideoPlayerControlViewTest();
    
protected:
    
    void viewDidLoad();
    
    void viewDidUnload();
    
public:
    
    void onBackButtonClicked(CAVideoPlayerControlView *playerControlView);
    
};


#endif /* defined(__HelloCpp__ViewController__) */
