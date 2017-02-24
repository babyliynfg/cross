//
//  CAImagePickerController.h
//  CrossApp
//
//  Created by 秦乐 on 2017/2/21.
//  Copyright © 2017年 cocos2d-x. All rights reserved.
//

#include "CAImagePickerController.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include "basics/CAApplication.h"

NS_CC_BEGIN

extern "C"
{
    void JAVAOpenCamera(int type)
    {
        JniMethodInfo jmi;
        if(JniHelper::getStaticMethodInfo(jmi , "org/CrossApp/lib/CrossAppDevice" , "CAImageCapture" , "(I)V"))
        {
            jmi.env->CallStaticVoidMethod(jmi.classID , jmi.methodID,type);
            jmi.env->DeleteLocalRef(jmi.classID);
        }
    }
    
    void JAVAOpenAlbum(int type)
    {
        JniMethodInfo jmi;
        if(JniHelper::getStaticMethodInfo(jmi , "org/CrossApp/lib/CrossAppNativeTool" , "CAImageAlbum" , "(I)V"))
        {
            jmi.env->CallStaticVoidMethod(jmi.classID , jmi.methodID,type);
            jmi.env->DeleteLocalRef(jmi.classID);
        }
    }
    
    void JAVAwriteImageToPhoto(CAImage* image, const std::string &imageName)
    {
        JniMethodInfo jmi;
        const char* path;
        std::string savePath;
        if (JniHelper::getStaticMethodInfo(jmi, "org/CrossApp/lib/CrossAppDevice", "getSaveImagePath", "()Ljava/lang/String;"))
        {
            jstring a = (jstring)jmi.env->CallStaticObjectMethod(jmi.classID, jmi.methodID);
            path = jmi.env->GetStringUTFChars(a, 0);
        }
        savePath = path;
        savePath = savePath + imageName + ".jpg";
        image->saveToFile(savePath);
        
        if (JniHelper::getStaticMethodInfo(jmi, "org/CrossApp/lib/CrossAppDevice", "UpdateCamera", "(Ljava/lang/String;)V"))
        {
            jmi.env->CallStaticVoidMethod(jmi.classID, jmi.methodID, jmi.env->NewStringUTF(savePath.c_str()));
        }
    }
}

std::function<void(CrossApp::CAImage*)> _callBack;

CAImagePickerController::CAImagePickerController(SourceType type)
: m_eSourceType(type)
{
    
}

CAImagePickerController::~CAImagePickerController()
{
    
}

CAImagePickerController* CAImagePickerController::create(SourceType type)
{
    CAImagePickerController* var = new CAImagePickerController(type);
    if (var && var->init())
    {
        var->autorelease();
        return var;
    }
    CC_SAFE_DELETE(var);
    return nullptr;
}

bool init()
{
    return true;
}

void open(const std::function<void(CrossApp::CAImage*)>& callback)
{
    _callBack = callback;
    
    switch (m_eSourceType)
    {
        case SourceType::PhotoLibrary:
        {
            JAVAOpenAlbum(1);
        }
            break;
        case SourceType::CameraDeviceRear:
        {
            JAVAOpenCamera(int type);
        }
            break;
        case SourceType::CameraDeviceFront:
        {
            JAVAOpenCamera(int type);
        }
            break;
        case SourceType::SavedPhotosAlbum:
        {
            CCAssert(false, "");
            return;
        }
            break;
        default:
            break;
    }
}

void writeImageToPhoto(CAImage* image, const std::function<void(bool)>& finishCallback, const std::string &imageName)
{
    JAVAwriteImageToPhoto(image, imageName);
}

extern "C"
{
    
}

NS_CC_END
