
#include "platform/CAFontProcesstor.h"
#include "images/CAImage.h"
#include "platform/CAFileUtils.h"
#include "jni/JniHelper.h"
#include <jni.h>
#include <string.h>
#include <vector>
#include <stdio.h>

NS_CC_BEGIN

std::vector<CAData*> s_gDataVec;
DSize s_gDimensions;

extern "C"
{
    /**
     * this method is called by java code to init width, height and pixels data
     */
    JNIEXPORT void JNICALL Java_org_CrossApp_lib_CrossAppBitmap_nativeInitBitmapDC(JNIEnv*  env, jobject thiz, int width, int height, jbyteArray pixels)
    {
        s_gDimensions = DSize(width, height);
        CCLog("xxxxxxxxxxxxxxxx:  width %d, height %d", width, height);
        ssize_t length = width * height * 4;
        unsigned char *bytes = (unsigned char*)malloc(sizeof(unsigned char) * length);
        env->GetByteArrayRegion(pixels, 0, length, (jbyte*)bytes);
        
        CAData* data = new CAData();
        data->fastSet(bytes, length);
        s_gDataVec.push_back(data);
    }
};

int getTextAlign(CATextAlignment align)
{
    int a = 0x31 ;
    switch (align) {
        case CATextAlignment::Left:
            0x31 ;
            break;
        case CATextAlignment::Center:
            0x33 ;
            break ;
        case CATextAlignment::Right :
            0x32 ;
            break ;
        default:
            break;
    }
    return  a ;
}

CAImage* CAFontProcesstor::imageForText(const std::string& text, const CAFont& font, DSize& dimensions)
{
    CAImage* ret = nullptr;
    
    do
    {
        CC_BREAK_IF(text.empty());
        
        
        
        JniMethodInfo methodInfo;
        if (! JniHelper::getStaticMethodInfo(methodInfo, "org/CrossApp/lib/CrossAppBitmap", "createTextBitmapShadowStroke", "(Ljava/lang/String;Ljava/lang/String;IIIIIIIIIFFFFIIIIIF)Z"))
        {
            break ;
        }
        // Do a full lookup for the font path using FileUtils in case the given font name is a relative path to a font file asset,
        // or the path has been mapped to a different location in the app package:
        std::string fullPathOrFontName = font.fontName;
        if(FileUtils::getInstance()->isFileExist(fullPathOrFontName)) {
            fullPathOrFontName = FileUtils::getInstance()->fullPathForFilename(font.fontName);
            // If the path name returned includes the 'assets' dir then that needs to be removed, because the android.content.Context
            // requires this portion of the path to be omitted for assets inside the app package.
            if (fullPathOrFontName.find("assets/") == 0)
            {
                fullPathOrFontName = fullPathOrFontName.substr(strlen("assets/"));   // Chop out the 'assets/' portion of the path.
            }
        }
        
        
        //            int count = text.length();
        //            jbyteArray strArray = methodInfo.env->NewByteArray(count);
        //            methodInfo.env->SetByteArrayRegion(strArray, 0, count, reinterpret_cast<const jbyte*>(&text[0]));
        //            jstring jstrFont = methodInfo.env->NewStringUTF(fullPathOrFontName.c_str());
        
        jstring jstrFont = methodInfo.env->NewStringUTF(fullPathOrFontName.c_str());
        jstring jsStr = methodInfo.env->NewStringUTF(text.c_str());

        if(!methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID,
                                                    jsStr,
                                                    jstrFont,
                                                    (int)font.fontSize,
                                                    font.color.r,
                                                    font.color.g,
                                                    font.color.b,
                                                    font.color.a,
                                                    getTextAlign(font.textAlignment),
                                                    (int)dimensions.width,
                                                    (int)dimensions.height,
                                                    (int)font.shadow.shadowEnabled,
                                                    font.shadow.shadowOffset.width,
                                                    font.shadow.shadowOffset.height,
                                                    font.shadow.shadowBlur,
                                                    font.shadow.shadowOpacity,
                                                    (int)font.stroke.strokeEnabled,
                                                    font.stroke.strokeColor.r,
                                                    font.stroke.strokeColor.g,
                                                    font.stroke.strokeColor.b,
                                                    font.stroke.strokeColor.a,
                                                    font.stroke.strokeSize
                                                    ))
        {
            break ;
        }
        
        //            methodInfo.env->DeleteLocalRef(strArray);
        methodInfo.env->DeleteLocalRef(jsStr);
        methodInfo.env->DeleteLocalRef(jstrFont);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
        dimensions = s_gDimensions;
        
        
        
        CAData* data = s_gDataVec.front();
        s_gDataVec.clear();
        ret = CAImage::createWithRawDataNoCache(data, CAImage::PixelFormat::RGBA8888, dimensions.width, dimensions.height);
        data->release();
    } while (0);
    
    
    return ret;
}

float CAFontProcesstor::heightForFont(const CAFont& font)
{
    //public static float heightForFont(int fontSize)
    float ret = 0 ;
    JniMethodInfo jni;
    if (JniHelper::getStaticMethodInfo(jni, "org/CrossApp/lib/CrossAppBitmap", "heightForFont", "(I)F"))
    {
        int fontSize = (int)font.fontSize;
        ret = (float)(jfloat)jni.env->CallStaticFloatMethod(jni.classID, jni.methodID, fontSize);
        jni.env->DeleteLocalRef(jni.classID);
        
    }
    
    
    return ret;
}

float CAFontProcesstor::heightForTextAtWidth(const std::string& text, const CAFont& font, float width)
{
    float ret = 0;
    CCLog("xxxxxxxxxxxxxxxx:  width %f, fontSize %f", width, font.fontSize);
    JniMethodInfo jni;
    if (JniHelper::getStaticMethodInfo(jni, "org/CrossApp/lib/CrossAppBitmap", "heightForTextAtWidth", "(Ljava/lang/String;II)F"))
    {
        jstring string = jni.env->NewStringUTF(text.c_str());
        int w = (int)width;
        int fontSize = (int)font.fontSize;
        ret = (float)(jfloat)jni.env->CallStaticFloatMethod(jni.classID, jni.methodID, string, w, fontSize);
        jni.env->DeleteLocalRef(jni.classID);
        
    }
    return ret;
}

float CAFontProcesstor::widthForTextAtOneLine(const std::string& text, const CAFont& font)
{
    //public static float widthForTextAtOneLine(String string ,  int fontSize)
    float ret = 0 ;
    JniMethodInfo jni;
    if (JniHelper::getStaticMethodInfo(jni, "org/CrossApp/lib/CrossAppBitmap", "widthForTextAtOneLine", "(Ljava/lang/String;I)F"))
    {
        
        jstring string = jni.env->NewStringUTF(text.c_str());
        int fontSize = (int)font.fontSize;
        ret = (float)(jfloat)jni.env->CallStaticFloatMethod(jni.classID, jni.methodID, string, fontSize);
        jni.env->DeleteLocalRef(jni.classID);
        
    }
    
    return ret;
}



NS_CC_END


