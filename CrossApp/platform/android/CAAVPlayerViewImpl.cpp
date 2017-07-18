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


static std::map<int , CAAVPlayerView*> s_map;
static std::map<int , std::function<void(CAImage*)> > s_ImageCallback_map;
static std::map<int , std::function<void(float current, float duratuon)> > s_PeriodicTime_map;
static std::map<int , std::function<void(float current, float duratuon)> > s_LoadedTime_map;
static std::map<int , std::function<void()> > s_DidPlayToEndTime_map;
static std::map<int , std::function<void()> > s_TimeJumped_map;


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
    s_map[m_pPlayerView->m_u__ID] = m_pPlayerView;
    
    s_ImageCallback_map[m_pPlayerView->m_u__ID] = [&](CAImage* image)
    {
        m_pPlayerView->setImage(image);
    };
    
    s_PeriodicTime_map[m_pPlayerView->m_u__ID] = [&](float current, float duratuon)
    {
        if(m_pPlayerView->m_obPeriodicTime)
            m_pPlayerView->m_obPeriodicTime(current,duratuon) ;
    };
    
    s_LoadedTime_map[m_pPlayerView->m_u__ID] = [&](float current, float duratuon)
    {
        if(m_pPlayerView->m_obLoadedTime)
            m_pPlayerView->m_obLoadedTime(current,duratuon) ;
    };
    
    
    s_DidPlayToEndTime_map[m_pPlayerView->m_u__ID] = [&]()
    {
        if(m_pPlayerView->m_obDidPlayToEndTime)
            m_pPlayerView->m_obDidPlayToEndTime() ;
    };
    s_TimeJumped_map[m_pPlayerView->m_u__ID] = [&]()
    {
        if(m_pPlayerView->m_obTimeJumped)
            m_pPlayerView->m_obTimeJumped() ;
    };
    
}

CAAVPlayerViewImpl::~CAAVPlayerViewImpl()
{
    s_map.erase(m_pPlayerView->m_u__ID);
    s_ImageCallback_map.erase(m_pPlayerView->m_u__ID);
    s_PeriodicTime_map.erase(m_pPlayerView->m_u__ID);
    s_LoadedTime_map.erase(m_pPlayerView->m_u__ID);
    s_DidPlayToEndTime_map.erase(m_pPlayerView->m_u__ID);
    s_TimeJumped_map.erase(m_pPlayerView->m_u__ID);
    
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

void CAAVPlayerViewImpl::stop()
{
    JniMethodInfo jni;
    if (JniHelper::getStaticMethodInfo(jni, "org/CrossApp/lib/CrossAppVideoPlayer", "stop4native", "(I)V"))
    {
        jni.env->CallStaticVoidMethod(jni.classID, jni.methodID, (jint)m_pPlayerView->m_u__ID );
        jni.env->DeleteLocalRef(jni.classID);
    }
}

void CAAVPlayerViewImpl::setCurrentTime(float current)
{
    
    JniMethodInfo jni;
    if (JniHelper::getStaticMethodInfo(jni, "org/CrossApp/lib/CrossAppVideoPlayer", "setCurrentTime4native", "(FI)V"))
    {
        jni.env->CallStaticVoidMethod(jni.classID, jni.methodID, (jfloat)current , (jint)m_pPlayerView->m_u__ID );
        jni.env->DeleteLocalRef(jni.classID);
    }
}


const DSize& CAAVPlayerViewImpl::getPresentationSize()
{
    DSize size = DSize(0, 0) ;
    JniMethodInfo jni;
    if (JniHelper::getStaticMethodInfo(jni, "org/CrossApp/lib/CrossAppVideoPlayer", "getPresentationSize4native", "(I)[I"))
    {
        jintArray arr = (jintArray)jni.env->CallStaticObjectMethod(jni.classID, jni.methodID, (jint)m_pPlayerView->m_u__ID );
        
        jint* elems =jni.env-> GetIntArrayElements(arr, 0);
        size.width = (int)elems[0] ;
        size.height = (int)elems[1] ;
        
        jni.env->DeleteLocalRef(jni.classID);
        jni.env->ReleaseIntArrayElements(arr, elems, 0);
    }
    return size ;
    
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
            if (auto& callback = s_ImageCallback_map.at((int)key))
            {
                callback(image);
            }
        }
        
    }
    
    // 监听播放进度
    JNIEXPORT void JNICALL Java_org_CrossApp_lib_CrossAppVideoPlayer_onPeriodicTime(JNIEnv *env, jclass cls, jint key, jfloat current,jfloat duration)
    {
        
        if (s_PeriodicTime_map.count((int)key) > 0)
        {
            if (auto& callback = s_PeriodicTime_map.at((int)key))
            {
                callback((float)current,(float)duration);
            }
        }
        
    }
    
    // 监听缓冲进度
    JNIEXPORT void JNICALL Java_org_CrossApp_lib_CrossAppVideoPlayer_onLoadedTime(JNIEnv *env, jclass cls, jint key, jfloat current,jfloat duration)
    {
        if (s_LoadedTime_map.count((int)key) > 0)
        {
            if (auto& callback = s_LoadedTime_map.at((int)key))
            {
                callback((float)current,(float)duration);
            }
        }
        
    }
    
    // 监听播放完毕
    JNIEXPORT void JNICALL Java_org_CrossApp_lib_CrossAppVideoPlayer_onDidPlayToEndTime(JNIEnv *env, jclass cls, jint key)
    {
        
        if (s_DidPlayToEndTime_map.count((int)key) > 0)
        {
            if (auto& callback = s_DidPlayToEndTime_map.at((int)key))
            {
                callback();
            }
        }
        
    }
    
    // 监听快进或者慢进或者跳过某段播放
    JNIEXPORT void JNICALL Java_org_CrossApp_lib_CrossAppVideoPlayer_onTimeJumped(JNIEnv *env, jclass cls, jint key)
    {
        if (s_TimeJumped_map.count((int)key) > 0)
        {
            if (auto& callback = s_TimeJumped_map.at((int)key))
            {
                callback();
            }
        }
    }
    
    
}


NS_CC_END


