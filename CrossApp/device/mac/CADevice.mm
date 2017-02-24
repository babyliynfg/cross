//
//  CADevice.cpp
//  CrossApp
//
//  Created by 秦乐 on 2017/2/21.
//  Copyright © 2017年 cocos2d-x. All rights reserved.
//

#include "CADevice.h"
#import <Foundation/Foundation.h>
#import <AddressBook/AddressBook.h>
#import "Reachability.h"
#import <SystemConfiguration/CaptiveNetwork.h>
#import <MediaPlayer/MediaPlayer.h>
#import <AppKit/AppKit.h>

NS_CC_BEGIN

namespace CADevice
{
    const char* getSystemVersionWithIOS()
    {
        return "";
    }
    
    const char* getAppVersion()
    {
        return "";
    }
    
    void setScreenBrightness(float brightness)
    {
     
    }
    
    float getScreenBrightness()
    {
        return 0;
    }
    
    CADevice::NetWorkData getNetWorkType()
    {
        return CADevice::NetWorkData::None;
    }
    
    bool isNetWorkAvailble()
    {
        return true;
    }
    
    CADevice::WifiDate getWifiConnectionInfo()
    {
        CADevice::WifiDate wifiInfo;

        return wifiInfo;
    }
    
    void setVolume(float sender, CADevice::VolumeData type)
    {
    }
    
    float getVolume(CADevice::VolumeData type)
    {
        return 0;
    }
    
    float getBatteryLevel()
    {
        return 0;
    }
    
    void sendLocalNotification(const char* title, const char* content,int time)
    {
            }
    
    void OpenURL(const std::string &url)
    {
        [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:[NSString stringWithUTF8String:url.c_str()]]];
    }
    
    void setIdleTimerDisabled(bool isIdleTimerDisabled)
    {
    }
};

NS_CC_END
