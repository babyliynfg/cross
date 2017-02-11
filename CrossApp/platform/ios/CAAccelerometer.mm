

#include "CAAccelerometer.h"
#include "AccelerometerDelegateWrapper.h"

NS_CC_BEGIN


CAAccelerometer::CAAccelerometer()
{
}

void CAAccelerometer::setDelegate(CAAccelerometerDelegate* pDelegate)
{
    if (pDelegate)
    {
        [[AccelerometerDispatcher sharedAccelerometerDispather] addDelegate:pDelegate];
    }
    else
    {
        [[AccelerometerDispatcher sharedAccelerometerDispather] stopAccelerometerInterval];
        [[AccelerometerDispatcher sharedAccelerometerDispather] release];
    }
}

void CAAccelerometer::setAccelerometerInterval(float interval)
{
    [[AccelerometerDispatcher sharedAccelerometerDispather] setAccelerometerInterval:interval];
}

NS_CC_END

