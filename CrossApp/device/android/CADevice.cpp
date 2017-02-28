//
//  CADevice.cpp
//  CrossApp
//
//  Created by 秦乐 on 2017/2/21.
//  Copyright © 2017年 cocos2d-x. All rights reserved.
//

#include "../CADevice.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"

NS_CC_BEGIN
namespace CADevice
{
    extern "C"
    {
        const char* JAVAGetSystemVersion()
        {
            JniMethodInfo jmi;
            if(JniHelper::getStaticMethodInfo(jmi , "org/CrossApp/lib/CrossAppDevice" , "getSystemVersion" , "()Ljava/lang/String;"))
            {
                jstring a = (jstring)jmi.env->CallStaticObjectMethod(jmi.classID , jmi.methodID);
                const char* b = jmi.env->GetStringUTFChars( a , 0 );
                jmi.env->DeleteLocalRef(jmi.classID);
                return b;
            }
        }
        
        const char* JAVAGetAppVersion()
        {
            JniMethodInfo jmi;
            if(JniHelper::getStaticMethodInfo(jmi , "org/CrossApp/lib/CrossAppDevice" , "getAppVersion" , "()Ljava/lang/String;"))
            {
                jstring a = (jstring)jmi.env->CallStaticObjectMethod(jmi.classID , jmi.methodID);
                const char* b = jmi.env->GetStringUTFChars( a , 0 );
                jmi.env->DeleteLocalRef(jmi.classID);
                return b;
            }
        }
        
        void JAVASetScreenBrightness(int sender)
        {
            JniMethodInfo jmi;
            if(JniHelper::getStaticMethodInfo(jmi , "org/CrossApp/lib/CrossAppDevice" , "setScreenBrightness" , "(I)V"))
            {
                jmi.env->CallStaticVoidMethod(jmi.classID , jmi.methodID,sender);
                jmi.env->DeleteLocalRef(jmi.classID);
            }
        }
        
        float JAVAgetBrightness()
        {
            JniMethodInfo jmi;
            if(JniHelper::getStaticMethodInfo(jmi , "org/CrossApp/lib/CrossAppDevice" , "getScreenBrightness" , "()I"))
            {
                jint nBrightness = (jint)jmi.env->CallStaticIntMethod(jmi.classID , jmi.methodID);
                int brightness = nBrightness;
                jmi.env->DeleteLocalRef(jmi.classID);
                return (float)brightness / 255.0f;
            }
        }
        
        CADevice::NetWorkData JAVAgetNetWorkType()
        {
            CADevice::NetWorkData networkType = CADevice::NetWorkData::None;
            JniMethodInfo jmi;
            if(JniHelper::getStaticMethodInfo(jmi , "org/CrossApp/lib/CrossAppDevice" , "getAPNType" , "()I"))
            {
                jint a = (jint)jmi.env->CallStaticIntMethod(jmi.classID , jmi.methodID);
                switch (a)
                {
                    case 0:
                        networkType = CADevice::NetWorkData::None;
                        break;
                    case 1:
                        networkType = CADevice::NetWorkData::Wifi;
                        break;
                    case 2:
                    case 3:
                        networkType = CADevice::NetWorkData::ReachableViaWWAN;
                        break;
                }
            }
            jmi.env->DeleteLocalRef(jmi.classID);
            return networkType;
        }
        
        bool JAVAisNetWorkAvailble()
        {
            JniMethodInfo jmi;
            if(JniHelper::getStaticMethodInfo(jmi , "org/CrossApp/lib/CrossAppDevice" , "isNetWorkAvailble" , "()I"))
            {
                jint a = (jint)jmi.env->CallStaticIntMethod(jmi.classID , jmi.methodID);
                int b = (int)a;
                jmi.env->DeleteLocalRef(jmi.classID);
                return (bool)b;
            }
        }
        
        void JAVAsetVolume(float sender,int type)
        {
            JniMethodInfo jmi;
            if(JniHelper::getStaticMethodInfo(jmi , "org/CrossApp/lib/CrossAppDevice" , "setVolum" , "(FI)V"))
            {
                jmi.env->CallStaticVoidMethod(jmi.classID , jmi.methodID,sender,type);
                jmi.env->DeleteLocalRef(jmi.classID);
            }
        }
        
        float JAVAgetVolume(int type)
        {
            JniMethodInfo jmi;
            if(JniHelper::getStaticMethodInfo(jmi , "org/CrossApp/lib/CrossAppDevice" , "getVolum" , "(I)F"))
            {
                jfloat a = (jfloat)jmi.env->CallStaticFloatMethod(jmi.classID , jmi.methodID,type);
                float b = a;
                jmi.env->DeleteLocalRef(jmi.classID);
                return b;
            }
        }
        
        float JAVAgetBattery()
        {
            JniMethodInfo jmi;
            if(JniHelper::getStaticMethodInfo(jmi , "org/CrossApp/lib/CrossAppDevice" , "getBatteryLevel" , "()I"))
            {
                jint a = (jint)jmi.env->CallStaticIntMethod(jmi.classID , jmi.methodID);
                int b = a;
                jmi.env->DeleteLocalRef(jmi.classID);
                return (float)b/100.0f;
            }
        }
        
        void JAVAsendLocalNotification(const char* title, const char* content, int time)
        {
            JniMethodInfo jmi;
            if(JniHelper::getStaticMethodInfo(jmi , "org/CrossApp/lib/CrossAppDevice" , "sendLocalNotification" , "(Ljava/lang/String;Ljava/lang/String;I)V"))
            {
                jmi.env->CallStaticVoidMethod(jmi.classID , jmi.methodID,jmi.env->NewStringUTF(title),jmi.env->NewStringUTF(content),time);
                jmi.env->DeleteLocalRef(jmi.classID);
            }
        }
        
        void JAVAOpenURL(const std::string &url)
        {
            JniMethodInfo jmi;
            if(JniHelper::getStaticMethodInfo(jmi , "org/CrossApp/lib/CrossAppDevice" , "browserOpenURL" , "(Ljava/lang/String;)V"))
            {
                jmi.env->CallStaticVoidMethod(jmi.classID , jmi.methodID,jmi.env->NewStringUTF(url.c_str()));
                jmi.env->DeleteLocalRef(jmi.classID);
            }
        }
        
        void JAVASetIdleTimerDisabled(int type)
        {
            JniMethodInfo jmi;
            if(JniHelper::getStaticMethodInfo(jmi , "org/CrossApp/lib/CrossAppDevice" , "setIdleTimerDisabled" , "(I)V"))
            {
                jmi.env->CallStaticVoidMethod(jmi.classID , jmi.methodID,type);
                jmi.env->DeleteLocalRef(jmi.classID);
            }
        }
    }

    #endif

    CADevice::SystemVersion getSystemVersion()
    {
        CADevice::SystemVersion systemVersion;
        systemVersion.platform = PlatForm::android;
        systemVersion.version = JAVAGetSystemVersion();
        return systemVersion;
    }
    
    const char* getAppVersion()
    {
        return JAVAGetAppVersion();
    }

    void setScreenBrightness(float brightness)
    {
        int sender = (int)(brightness*255.0f);
        
        JAVASetScreenBrightness(sender);
    }

    float getScreenBrightness()
    {
        return JAVAgetBrightness();
    }

    CADevice::NetWorkData getNetWorkType()
    {
        return JAVAgetNetWorkType();
    }

    bool isNetWorkAvailble()
    {
        return JAVAisNetWorkAvailble();
    }

    void setVolume(float sender, CADevice::VolumeData type)
    {
        int mType = (int)type;
        JAVAsetVolume(sender, mType);
    }

    float getVolume(CADevice::VolumeData type)
    {
        int mType = (int)type;
        JAVAgetVolume(mType);
    }

    float getBatteryLevel()
    {
        return JAVAgetBattery();
    }

    void sendLocalNotification(const char* title, const char* content,int time)
    {
        JAVAsendLocalNotification(title,content,time);
    }

    void OpenURL(const std::string &url)
    {
        JAVAOpenURL(url);
    }

    void setIdleTimerDisabled(bool isIdleTimerDisabled)
    {
        int type = isIdleTimerDisabled ? 1 : 0;
        JAVASetIdleTimerDisabled(type);
    }
};
NS_CC_END
