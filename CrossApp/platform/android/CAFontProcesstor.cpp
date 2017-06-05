
#include "platform/CAFontProcesstor.h"
#include <vector>


#define CLASS_CAFONTPROCESSOR "org/CrossApp/lib/CrossAppBitmap"
#define GET_CAFONTPROCESSOR_CLASS "(I)Lorg/CrossApp/lib/CrossAppBitmap;"


NS_CC_BEGIN
namespace CAFontProcesstor
{
    std::vector<CAData*> s_gDataVec;
    DSize s_gDimensions;
    
    CAImage* imageForText(const std::string& text, const CAFont& font, DSize& dimensions)
    {
        CAImage* ret = nullptr;
        
        do
        {
            CC_BREAK_IF(text.empty());
            
            
            
            JniMethodInfo methodInfo;
            if (! JniHelper::getStaticMethodInfo(methodInfo, CLASS_CAFONTPROCESSOR, "createTextBitmapShadowStroke","([BLjava/lang/String;IIIIIIIIZFFFFZIIIIF)Z"))
            {
                break ;
            }
            // Do a full lookup for the font path using FileUtils in case the given font name is a relative path to a font file asset,
            // or the path has been mapped to a different location in the app package:
            std::string fullPathOrFontName = font.fontName;
            if(FileUtils::getInstance()->isFileExist(fullPathOrFontName)) {
                fullPathOrFontName = FileUtils::getInstance()->fullPathForFilename(textDefinition._fontName);
                // If the path name returned includes the 'assets' dir then that needs to be removed, because the android.content.Context
                // requires this portion of the path to be omitted for assets inside the app package.
                if (fullPathOrFontName.find("assets/") == 0)
                {
                    fullPathOrFontName = fullPathOrFontName.substr(strlen("assets/"));   // Chop out the 'assets/' portion of the path.
                }
            }
            
            
            int count = strlen(text);
            jbyteArray strArray = methodInfo.env->NewByteArray(count);
            methodInfo.env->SetByteArrayRegion(strArray, 0, count, reinterpret_cast<const jbyte*>(text));
            jstring jstrFont = methodInfo.env->NewStringUTF(fullPathOrFontName.c_str());
            
            
            /**
             *
             * @param string
             * @param fontName
             * @param fontSize
             * @param fontTintR
             * @param fontTintG
             * @param fontTintB
             * @param fontTintA
             * @param alignment
             * @param width
             * @param height
             * @param shadow
             * @param shadowDX
             * @param shadowDY
             * @param shadowBlur
             * @param shadowOpacity
             * @param stroke
             * @param strokeR
             * @param strokeG   
             * @param strokeB    
             * @param strokeA    
             * @param strokeSize  
             * @return
             
             bool        strokeEnabled;
             CAColor4B   strokeColor;
             float       strokeSize;
             
             */
            
            if(!methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID,
                                                        strArray,
                                                        jstrFont,
                                                        font.fontsize,
                                                        font.color.r,
                                                        font.color.g,
                                                        font.color.b,
                                                        font.color.a,
                                                        getTextAlign(font.textAlignment),
                                                        dimensions.width,
                                                        dimensions.height,
                                                        font.shadow.shadowEnabled,
                                                        font.shadow.shadowOffset.width,
                                                        font.shadow.shadowOffset.height,
                                                        font.shadow.shadowBlur,
                                                        font.shadow.shadowOpacity,
                                                        font.stroke.strokeEnabled,
                                                        font.stroke.strokeColor.r,
                                                        font.stroke.strokeColor.g,
                                                        font.stroke.strokeColor.b,
                                                        font.stroke.strokeColor.a,
                                                        font.stroke.strokeSize
                                                        ))
            {
                break ;
            }
            
            methodInfo.env->DeleteLocalRef(strArray);
            methodInfo.env->DeleteLocalRef(jstrFont);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
            
            dimensions = s_gDimensions;
            
            CAData* data = s_gDataVec.front();
            s_gDataVec.clear();
            ret = CAImage::createWithRawDataNoCache(data, CAImage::PixelFormat::RGBA8888, pixelsWide, pixelsHigh);
            data->release();
        } while (0);
        
        
        return ret;
    }
    
    float heightForFont(const CAFont& font)
    {
        //public static float heightForFont(int fontSize)
        float ret = 0 ;
        JniMethodInfo jni;
        if (JniHelper::getStaticMethodInfo(jni, CLASS_CAFONTPROCESSOR, "heightForFont", "(I)F"))
        {
            ret = (float)(jfloat)jni.env->CallStaticFloatMethod(jni.classID, jni.methodID, font.fontsize);
            jni.env->DeleteLocalRef(jni.classID);
            
        }
        
    
        return ret;
    }
    
    
    int getTextAlign(CATextAlignment align)
    {
        int a = 0x31 ;
        switch (align) {
            case Left:
                0x31 ;
                break;
            case Center:
                0x33 ;
                break ;
            case Right :
                0x32 ;
                break ;
            default:
                break;
        }
        return  a ;
    }
    
    
    float heightForTextAtWidth(const std::string& text, const CAFont& font, float width)
    {
        //public static float heightForTextAtWidth(String string , int width , int fontsize)
        float ret = 0 ;
        JniMethodInfo jni;
        if (JniHelper::getStaticMethodInfo(jni, CLASS_CAFONTPROCESSOR, "heightForTextAtWidth", "(Ljava/lang/String;II)F"))
        {
            jstring string = jni.env->NewStringUTF(text.c_str());
            ret = (float)(jfloat)jni.env->CallStaticFloatMethod(jni.classID, jni.methodID, string , width , font.fontsize);
            jni.env->DeleteLocalRef(jni.classID);
            
        }
        
        
        return ret;
    }
    
    float widthForTextAtOneLine(const std::string& text, const CAFont& font)
    {
        //public static float widthForTextAtOneLine(String string ,  int fontSize)
        float ret = 0 ;
        JniMethodInfo jni;
        if (JniHelper::getStaticMethodInfo(jni, CLASS_CAFONTPROCESSOR, "widthForTextAtOneLine", "(Ljava/lang/String;I)F"))
        {
            
            jstring string = jni.env->NewStringUTF(text.c_str());
            
            ret = (float)(jfloat)jni.env->CallStaticFloatMethod(jni.classID, jni.methodID, string , font.fontsize);
            jni.env->DeleteLocalRef(jni.classID);
            
        }
        
        return ret;
    }
    
    
    
}
NS_CC_END




// this method is called by Cocos2dxBitmap
extern "C"
{
    /**
     * this method is called by java code to init width, height and pixels data
     */
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxBitmap_nativeInitBitmapDC(JNIEnv*  env, jobject thiz, int width, int height, jbyteArray pixels)
    {
        unsigned int pixelsWide = width;
        unsigned int pixelsHigh = height;
        
        ssize_t length = width * height * 4;
        unsigned char *bytes = (unsigned char*)malloc(sizeof(unsigned char) * length);
        env->GetByteArrayRegion(pixels, 0, length, (jbyte*)bytes);
        
        s_gDimensions = DSize(pixelsWide, pixelsHigh);
        
        CAData* data = new CAData();
        data->fastSet(bytes, length);
        s_gDataVec.push_back(data);
    }
};

