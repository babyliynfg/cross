
#ifndef __PLATFORM_WIN32_UIACCELEROMETER_H__
#define __PLATFORM_WIN32_UIACCELEROMETER_H__

#include "platform/CAAccelerometerDelegate.h"

NS_CC_BEGIN

class CC_DLL CAAccelerometer
{
public:
	CAAccelerometer();
	~CAAccelerometer();

    void setDelegate(CAAccelerometerDelegate* pDelegate);
    void setAccelerometerInterval(float interval);
    void update( double x,double y,double z,double timestamp );
private:
    CAAcceleration m_obAccelerationValue;
    CAAccelerometerDelegate* m_pAccelDelegate;
};

NS_CC_END

#endif
