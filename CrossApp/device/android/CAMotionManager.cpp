//
//  CAGyroscope.cpp
//  CrossApp
//
//  Created by 秦乐 on 2017/2/20.
//  Copyright © 2017年 . All rights reserved.
//

#include "../CAMotionManager.h"
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
            jmi.env->DeleteLocalRef(jmi.classID);
        }
    }
    
    void JAVASetGyroscope(float interval)
    {
        JniMethodInfo jmi;
        if (JniHelper::getStaticMethodInfo(jmi, "org/CrossApp/lib/CrossAppDevice", "setGyroscopeInterval", "(F)V"))
        {
            jmi.env->CallStaticVoidMethod(jmi.classID, jmi.methodID, interval);
            jmi.env->DeleteLocalRef(jmi.classID);
        }
    }
    
    void JAVAStopGyroscope()
    {
        JniMethodInfo jmi;
        if (JniHelper::getStaticMethodInfo(jmi, "org/CrossApp/lib/CrossAppDevice", "disableGyroscope", "()V"))
        {
            jmi.env->CallStaticVoidMethod(jmi.classID, jmi.methodID);
            jmi.env->DeleteLocalRef(jmi.classID);
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

void CAMotionManager::startGyroscope(const std::function<void(const CAMotionManager::Date&)>& callback)
{
    _callBack = callback;
    
    JAVAStartGyroscope();
}

void CAMotionManager::setGyroInterval(float interval)
{
    JAVASetGyroscope(interval);
}

void CAMotionManager::stopGyroscope()
{
    JAVAStopGyroscope();
}

extern "C"
{
    JNIEXPORT void JNICALL Java_org_CrossApp_lib_CrossAppGyroscope_onGyroSensorChanged(                             JNIEnv *env,jobject obj,jfloat px,jfloat py,jfloat pz,jfloat pTime)
    {
        CAMotionManager::Date data;
        data.x = px;
        data.y = py;
        data.z = pz;
        data.timestamp = pTime;
        _callBack(&data);
    }
}

NS_CC_END

