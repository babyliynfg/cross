//
//  CAGyroscope.cpp
//  CrossApp
//
//  Created by 秦乐 on 2017/2/20.
//  Copyright © 2017年 . All rights reserved.
//

#include "CAMotionManager.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include "basics/CAApplication.h"


NS_CC_BEGIN

extern "C"
{
    void JAVAStartGyroscope()
    {
        JniMethodInfo jmi;
        if (JniHelper::getStaticMethodInfo(jmi, "org/CrossApp/lib/CrossAppDevice", "enableGyroscope", "()V"))
        {
            jmi.env->CallStaticVoidMethod(jmi.classID, jmi.methodID);
        }
    }
    
    void JAVASetGyroscope(float interval)
    {
        JniMethodInfo jmi;
        if (JniHelper::getStaticMethodInfo(jmi, "org/CrossApp/lib/CrossAppDevice", "setGyroscopeInterval", "(F)V"))
        {
            jmi.env->CallStaticVoidMethod(jmi.classID, jmi.methodID, interval);
        }
    }
    
    void JAVAStopGyroscope()
    {
        JniMethodInfo jmi;
        if (JniHelper::getStaticMethodInfo(jmi, "org/CrossApp/lib/CrossAppDevice", "disableGyroscope", "()V"))
        {
            jmi.env->CallStaticVoidMethod(jmi.classID, jmi.methodID);
        }
    }
}



CAMotionManager::CAMotionManager()
{
}

CAMotionManager::~CAMotionManager()
{
}


std::function<void(const CAMotionManager::Date&)> _callBack;

void startGyroscope(const std::function<void(const CAMotionManager::Date&)>& callback)
{
    _callBack = callback;
    
    JAVAStartGyroscope();
}

void setGyroInterval(float interval)
{
    JAVASetGyroscope(interval);
}

void stopGyroscope()
{
    JAVAStopGyroscope();
}

extern "C"
{
    JNIEXPORT void JNICALL Java_org_CrossApp_lib_CrossAppGyroscope_onGyroSensorChanged(                             JNIEnv *env,jobject obj,jfloat px,jfloat py,jfloat pz,jfloat pTime)
    {
        m_obData.x = px;
        m_obData.y = py;
        m_obData.z = pz;
        m_obData.timestamp = pTime;
        _callBack(m_obData);
    }
}

NS_CC_END

