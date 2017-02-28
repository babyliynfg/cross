//
//  CADevice.cpp
//  CrossApp
//
//  Created by 秦乐 on 2017/2/21.
//  Copyright © 2017年 cocos2d-x. All rights reserved.
//

#include "../CADevice.h"

NS_CC_BEGIN
namespace CADevice
{
    const char* getAppVersion()
    {
        return "";
    }

    void setScreenBrightness(float brightness)
    {
    }

    float getScreenBrightness()
    {
        return 0.f;
    }

    CADevice::NetWorkData getNetWorkType()
    {
		return NetWorkData::Wifi;
    }

    bool isNetWorkAvailble()
    {
        return true;
    }

    void setVolume(float sender, CADevice::VolumeData type)
	{
    }

    float getVolume(CADevice::VolumeData type)
    {
		return 0.0f;
    }

    float getBatteryLevel()
    {
        return 0.f;
    }

    void sendLocalNotification(const char* title, const char* content,int time)
    {
    }

    void OpenURL(const std::string &url)
    {
		::ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOW);
    }

    void setIdleTimerDisabled(bool isIdleTimerDisabled)
    {

    }
};
NS_CC_END
