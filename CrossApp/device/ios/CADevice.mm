//
//  CADevice.cpp
//  CrossApp
//
//  Created by 秦乐 on 2017/2/21.
//  Copyright © 2017年 CossApp-x. All rights reserved.
//

#include "CADevice.h"
#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <AddressBook/AddressBook.h>
#import <AddressBookUI/AddressBookUI.h>
#import "Reachability.h"
#import <SystemConfiguration/CaptiveNetwork.h>
#import <MediaPlayer/MPMusicPlayerController.h>
#import <MediaPlayer/MediaPlayer.h>

NS_CC_BEGIN

namespace CADevice
{
    CADevice::SystemVersion getSystemVersion()
    {
        CADevice::SystemVersion systemVersion;
        systemVersion.platform = PlatForm::ios;
        systemVersion.version = [[[UIDevice currentDevice]systemVersion] UTF8String];
        return systemVersion;
    }
    
    const char* getAppVersion()
    {
        NSDictionary *infoDictionary = [[NSBundle mainBundle] infoDictionary];
        NSString *app_Version = [infoDictionary objectForKey:@"CFBundleVersion"];
        return [app_Version UTF8String];
    }
    
    void setScreenBrightness(float brightness)
    {
        float brightnessPer = MIN(brightness, 1.0);
        [[UIScreen mainScreen] setBrightness:brightnessPer];
    }
    
    float getScreenBrightness()
    {
        float percent = [[UIScreen mainScreen] brightness];
        return percent;
    }
    
    CADevice::NetWorkData getNetWorkType()
    {
        CADevice::NetWorkData networkType = CADevice::NetWorkData::None;
        Reachability *reach = [Reachability reachabilityWithHostname:@"www.baidu.com"];
        switch ([reach currentReachabilityStatus])
        {
            case NotReachable:
                networkType = CADevice::NetWorkData::None;
                break;
            case ReachableViaWWAN:
                networkType = CADevice::NetWorkData::ReachableViaWWAN;
                break;
            case ReachableViaWiFi:
                networkType = CADevice::NetWorkData::Wifi;
                break;
        }
        return networkType;
    }
    
    bool isNetWorkAvailble()
    {
        Reachability *reach = [Reachability reachabilityWithHostname:@"www.baidu.com"];
        return [reach isReachable];
    }
    
    CADevice::WifiDate getWifiConnectionInfo()
    {
        NSArray *array = (id)CNCopySupportedInterfaces();
        id info = nil;
        for (NSString *ifnam in array) {
            info = (id)CNCopyCurrentNetworkInfo((CFStringRef)ifnam);
            if (info && [info count]) {
                
                break;
            }
            [info release];
        }
        [array release];
        NSDictionary *dic = info;
        NSString *ssid = [[dic objectForKey:@"SSID"] lowercaseString];
        NSString *mac = [[dic objectForKey:@"BSSID"] lowercaseString];
        
        CADevice::WifiDate wifiInfo;
        wifiInfo.ssid = [ssid cStringUsingEncoding:NSUTF8StringEncoding];
        wifiInfo.mac = [mac cStringUsingEncoding:NSUTF8StringEncoding];
        wifiInfo.level = 0;
        return wifiInfo;
    }
    
    void setVolume(float sender, CADevice::VolumeData type)
    {
        [MPMusicPlayerController applicationMusicPlayer].volume = sender;
    }
    
    float getVolume(CADevice::VolumeData type)
    {
        return [MPMusicPlayerController applicationMusicPlayer].volume;
    }
    
    float getBatteryLevel()
    {
        [UIDevice currentDevice].batteryMonitoringEnabled = YES;
        return [UIDevice currentDevice].batteryLevel;
    }
    
    void sendLocalNotification(const char* title, const char* content,int time)
    {
        if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 8.0) {
            
            UIUserNotificationType myTypes = UIRemoteNotificationTypeBadge | UIRemoteNotificationTypeAlert | UIRemoteNotificationTypeSound;
            
            UIUserNotificationSettings *settings = [UIUserNotificationSettings settingsForTypes:myTypes categories:nil];
            
            [[UIApplication sharedApplication] registerUserNotificationSettings:settings];
            
        }
        else
        {
            
            UIRemoteNotificationType myTypes = UIRemoteNotificationTypeBadge|UIRemoteNotificationTypeAlert|UIRemoteNotificationTypeSound;
            
            [[UIApplication sharedApplication] registerForRemoteNotificationTypes:myTypes];
            
        }
        
        UILocalNotification *notification = [[[UILocalNotification alloc] init] autorelease];
        NSDate *pushDate = [NSDate dateWithTimeIntervalSinceNow:time];
        if (notification != nil)
        {
            notification.fireDate = pushDate;
            notification.timeZone = [NSTimeZone defaultTimeZone];
            notification.repeatInterval = kCFCalendarUnitDay;
            notification.soundName = UILocalNotificationDefaultSoundName;
            notification.alertTitle = [NSString stringWithCString:title encoding:NSUTF8StringEncoding];
            notification.alertBody = [NSString stringWithCString:content encoding:NSUTF8StringEncoding];
            notification.applicationIconBadgeNumber = 1;
            NSDictionary *info = [NSDictionary dictionaryWithObject:@"name" forKey:@"key"];
            notification.userInfo = info;
            UIApplication *app = [UIApplication sharedApplication];
            [app scheduleLocalNotification:notification];
            
        }
    }
    
    void openUrl(const std::string &url)
    {
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:[NSString stringWithUTF8String:url.c_str()]]];
            
    #elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:[NSString stringWithUTF8String:url.c_str()]]];
            
    #endif
    }
    
    void setIdleTimerDisabled(bool isIdleTimerDisabled)
    {
        [[UIApplication sharedApplication] setIdleTimerDisabled:isIdleTimerDisabled];
    }
};

NS_CC_END
