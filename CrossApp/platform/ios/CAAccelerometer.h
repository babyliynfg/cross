
#ifndef __PLATFORM_IPHONE_CAACCELEROMETER_H__
#define __PLATFORM_IPHONE_CAACCELEROMETER_H__

#include "platform/CAAccelerometerDelegate.h"

NS_CC_BEGIN

class CC_DLL CAAccelerometer
{
public:
    CAAccelerometer();
        
    void setDelegate(CAAccelerometerDelegate* pDelegate);
    
    void setAccelerometerInterval(float interval);
};

NS_CC_END

#endif
