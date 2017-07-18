#include "../CAAVPlayerViewImpl.h"
#include "view/CAAVPlayerView.h"
#include "images/CAImage.h"
#include "basics/CAApplication.h"
#include <map>
#include <android/log.h>
#include <stdio.h>
#include <jni.h>
#include "jni/JniHelper.h"


NS_CC_BEGIN

class ImageCallback
{
public:
    ImageCallback(const std::function<void(CAImage*)>& callback)
    :_callback(callback)
    {}
    
    std::function<void(CAImage*)> _callback;
};

static std::map<int , CAAVPlayerViewImpl*> s_map;
static std::map<int , ImageCallback*> s_ImageCallback_map;


void removePlayer(int key)
{
    JniMethodInfo jni;
    if (JniHelper::getStaticMethodInfo(jni, "org/CrossApp/lib/CrossAppVideoPlayer", "removeById", "(I)V"))
    {
        jni.env->CallStaticVoidMethod(jni.classID, jni.methodID , key);
        jni.env->DeleteLocalRef(jni.classID);
    }
}

CAAVPlayerViewImpl::CAAVPlayerViewImpl(CAAVPlayerView* playerView)
: m_pPlayerView(playerView)
{
    s_map[m_pPlayerView->m_u__ID] = this;
    ImageCallback* imageCallback = new ImageCallback([&](CAImage* image)
    {
        m_pPlayerView->setImage(image);
    });
    s_ImageCallback_map[m_pPlayerView->m_u__ID] = imageCallback;
}

CAAVPlayerViewImpl::~CAAVPlayerViewImpl()
{
    s_map.erase(m_pPlayerView->m_u__ID);
    delete s_ImageCallback_map[m_pPlayerView->m_u__ID];
    s_ImageCallback_map.erase(m_pPlayerView->m_u__ID);
    removePlayer(m_pPlayerView->m_u__ID) ;
}


void CAAVPlayerViewImpl::setUrl(const std::string& url)
{
    JniMethodInfo jni;
    if (JniHelper::getStaticMethodInfo(jni, "org/CrossApp/lib/CrossAppVideoPlayer", "setDataSource", "(Ljava/lang/String;I)V"))
    {
        jstring jFilePath = jni.env->NewStringUTF(url.c_str());
        jni.env->CallStaticVoidMethod(jni.classID, jni.methodID , jFilePath , (jint)m_pPlayerView->m_u__ID);
        jni.env->DeleteLocalRef(jni.classID);
    }
    
}

void CAAVPlayerViewImpl::setFilePath(const std::string& filePath)
{
    JniMethodInfo jni;
    if (JniHelper::getStaticMethodInfo(jni, "org/CrossApp/lib/CrossAppVideoPlayer", "setDataSource", "(Ljava/lang/String;I)V"))
    {
        jstring jFilePath = jni.env->NewStringUTF(filePath.c_str());
        jni.env->CallStaticVoidMethod(jni.classID, jni.methodID , jFilePath , (jint)m_pPlayerView->m_u__ID);
        jni.env->DeleteLocalRef(jni.classID);
    }
}
    
void CAAVPlayerViewImpl::play()
{
    JniMethodInfo jni;
    if (JniHelper::getStaticMethodInfo(jni, "org/CrossApp/lib/CrossAppVideoPlayer", "play4native", "(I)V"))
    {
        jni.env->CallStaticVoidMethod(jni.classID, jni.methodID , (jint)m_pPlayerView->m_u__ID);
        jni.env->DeleteLocalRef(jni.classID);
    }
}
    
void CAAVPlayerViewImpl::pause()
{
    JniMethodInfo jni;
    if (JniHelper::getStaticMethodInfo(jni, "org/CrossApp/lib/CrossAppVideoPlayer", "pause4native", "(I)V"))
    {
        jni.env->CallStaticVoidMethod(jni.classID, jni.methodID, (jint)m_pPlayerView->m_u__ID );
        jni.env->DeleteLocalRef(jni.classID);
    }
}

float CAAVPlayerViewImpl::getDuration()
{
    jint duration = 0 ;
    JniMethodInfo jni;
    if (JniHelper::getStaticMethodInfo(jni, "org/CrossApp/lib/CrossAppVideoPlayer", "getDuration", "(I)I"))
    {
        duration = jni.env->CallStaticIntMethod(jni.classID, jni.methodID, (jint)m_pPlayerView->m_u__ID );
        jni.env->DeleteLocalRef(jni.classID);
    }
    
    return (float)duration ;
}

float CAAVPlayerViewImpl::getCurrentTime()
{
    jint current = 0 ;
    JniMethodInfo jni;
    if (JniHelper::getStaticMethodInfo(jni, "org/CrossApp/lib/CrossAppVideoPlayer", "getCurrentTime", "(I)I"))
    {
        current = jni.env->CallStaticIntMethod(jni.classID, jni.methodID, (jint)m_pPlayerView->m_u__ID );
        jni.env->DeleteLocalRef(jni.classID);
    }
    
    return (float)current ;
}


extern "C"
{
    
    JNIEXPORT void JNICALL Java_org_CrossApp_lib_CrossAppVideoPlayer_onFrameAttached(JNIEnv *env, jclass cls, jint key, jbyteArray buf, jint width, jint height)
    {

        ssize_t length = width * height * 4;
        unsigned char* data = (unsigned char*)malloc(sizeof(unsigned char) * length);
        env->GetByteArrayRegion(buf, 0, width * height * 4, (jbyte *)data);
        CrossApp::CAData* ca_data = CrossApp::CAData::create();
        ca_data->fastSet(data, length);
        CAImage* image = CAImage::createWithRawDataNoCache(ca_data, CAImage::PixelFormat::RGBA8888, width, height);
        
        if (s_ImageCallback_map.count((int)key) > 0)
        {
            const std::function<void(CAImage*)>& callback = s_ImageCallback_map.at((int)key)->_callback;
            
            if (callback)
            {
                callback(image);
            }
        }
        
    }
}


NS_CC_END


