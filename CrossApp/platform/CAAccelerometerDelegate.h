

#ifndef __CAACCELEROMETER_DELEGATE_H__
#define __CAACCELEROMETER_DELEGATE_H__

#include "CACommon.h"

NS_CC_BEGIN
/**
@brief The device accelerometer reports values for each axis in units of g-force 
*/
class CAAcceleration
{
public:
    double x;
    double y;
    double z;

    float timestamp;
    
    CAAcceleration(): x(0), y(0), z(0), timestamp(0) {}
};

/**
@brief 
The CAAccelerometerDelegate defines a single method for
receiving acceleration-related data from the system.
@js NA
@lua NA
*/
class CC_DLL CAAccelerometerDelegate
{
public:
    virtual ~CAAccelerometerDelegate() {}
    
    virtual void didAccelerate(CAAcceleration* pAccelerationValue) {CC_UNUSED_PARAM(pAccelerationValue);}
};

NS_CC_END

#endif
