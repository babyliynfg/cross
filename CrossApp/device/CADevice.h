//
//  CADevice.h
//  CrossApp
//
//  Created by 秦乐 on 2017/2/21.
//  Copyright © 2017年 CrossApp. All rights reserved.
//

#ifndef CADevice_h
#define CADevice_h

#include "basics/CAObject.h"
NS_CC_BEGIN

namespace CADevice
{
    enum class NetWorkData : int
    {
        Wifi=0,
        ReachableViaWWAN,
        None,
    };
    
    struct WifiDate
    {
        std::string ssid{""};
        int level{0};
        std::string mac{""};
    };
    
    enum class VolumeData : int
    {
        Music = 0,
        System,
        Ring,
        VoicCall,
        Alarm,
        Notification
    };
        
    enum class PlatForm : int
    {
        ios,
        android,
    };
        
    struct SystemVersion
    {
        PlatForm platform;
        std::string version{""};
    };
        
    CADevice::SystemVersion getSystemVersion();

    const char* getAppVersion();
        
    void setScreenBrightness(float brightness);
    
    float getScreenBrightness();
        
    CADevice::NetWorkData getNetWorkType();
    
    bool isNetWorkAvailble();
        
    void setVolume(float sender, CADevice::VolumeData type);
    
    float getVolume(CADevice::VolumeData type);
    
    float getBatteryLevel();
        
    void sendLocalNotification(const char* title, const char* content,int time);
        
    void openUrl(const std::string &url);
        
    void setIdleTimerDisabled(bool isIdleTimerDisabled);
};

NS_CC_END

#endif /* CADevice_h */
