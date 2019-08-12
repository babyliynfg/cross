
#include "cocoa/CCSet.h"
#include "basics/CAApplication.h"
#include "dispatcher/CAKeypadDispatcher.h"
#include "dispatcher/CATouch.h"
#include "dispatcher/CATouchDispatcher.h"
#include <android/log.h>
#include <jni.h>
#include "platform/android/CCEGLView.h"

using namespace CrossApp;

extern "C" {
    JNIEXPORT void JNICALL Java_org_CrossApp_lib_CrossAppRenderer_nativeTouchesBegin(JNIEnv * env, jobject thiz, jint id, jfloat x, jfloat y)
    {
        CrossApp::CAEvent* theEvent = new CrossApp::CAEvent();
        theEvent->setEventType(CrossApp::EventType::androidEvent);
        intptr_t* id_ptr;
        *id_ptr = id;
        float* x_f; float* y_f;
        *x_f = x;
        *y_f = y;

        CAApplication::getApplication()->getOpenGLView()->handleTouchesBegin(1, id_ptr, x_f, y_f, theEvent);
        theEvent->release();
    }

    JNIEXPORT void JNICALL Java_org_CrossApp_lib_CrossAppRenderer_nativeTouchesEnd(JNIEnv * env, jobject thiz, jint id, jfloat x, jfloat y)
    {
        CrossApp::CAEvent* theEvent = new CrossApp::CAEvent();
        theEvent->setEventType(CrossApp::EventType::androidEvent);
        
        intptr_t* id_ptr;
        *id_ptr = id;
        float* x_f; float* y_f;
        *x_f = x;
        *y_f = y;
        
        CAApplication::getApplication()->getOpenGLView()->handleTouchesEnd(1, id_ptr, x_f, y_f, theEvent);
        theEvent->release();
    }

    JNIEXPORT void JNICALL Java_org_CrossApp_lib_CrossAppRenderer_nativeTouchesMove(JNIEnv * env, jobject thiz, jintArray ids, jfloatArray xs, jfloatArray ys) {
        int size = env->GetArrayLength(ids);
        jint id[size];
        jfloat x[size];
        jfloat y[size];

        env->GetIntArrayRegion(ids, 0, size, id);
        env->GetFloatArrayRegion(xs, 0, size, x);
        env->GetFloatArrayRegion(ys, 0, size, y);

        intptr_t* id_ptr = new intptr_t(size);
        for (int i=0; i<size; i++)
        {
            id_ptr[i] = id[i];
        }
        
        CrossApp::CAEvent* theEvent = new CrossApp::CAEvent();
        theEvent->setEventType(CrossApp::EventType::androidEvent);
        CAApplication::getApplication()->getOpenGLView()->handleTouchesMove(size, id_ptr, x, y, theEvent);
        theEvent->release();
        
        delete id_ptr;
    }

    JNIEXPORT void JNICALL Java_org_CrossApp_lib_CrossAppRenderer_nativeTouchesCancel(JNIEnv * env, jobject thiz, jintArray ids, jfloatArray xs, jfloatArray ys) {
        int size = env->GetArrayLength(ids);
        jint id[size];
        jfloat x[size];
        jfloat y[size];

        env->GetIntArrayRegion(ids, 0, size, id);
        env->GetFloatArrayRegion(xs, 0, size, x);
        env->GetFloatArrayRegion(ys, 0, size, y);

        intptr_t* id_ptr = new intptr_t(size);
        for (int i=0; i<size; i++)
        {
            id_ptr[i] = id[i];
        }
        
        CrossApp::CAEvent* theEvent = new CrossApp::CAEvent();
        theEvent->setEventType(CrossApp::EventType::androidEvent);
        CAApplication::getApplication()->getOpenGLView()->handleTouchesCancel(size, id_ptr, x, y, theEvent);
        theEvent->release();
        
        delete id_ptr;
    }

    #define KEYCODE_BACK 0x04
    #define KEYCODE_MENU 0x52

    JNIEXPORT jboolean JNICALL Java_org_CrossApp_lib_CrossAppRenderer_nativeKeyDown(JNIEnv * env, jobject thiz, jint keyCode) {
        CAApplication* application = CAApplication::getApplication();
        switch (keyCode) {
            case KEYCODE_BACK:
                if (application->getKeypadDispatcher()->dispatchKeypadMSG(CAKeypadDispatcher::KeypadMSGType::BackClicked))
                    return JNI_TRUE;
                break;
            case KEYCODE_MENU:
                if (application->getKeypadDispatcher()->dispatchKeypadMSG(CAKeypadDispatcher::KeypadMSGType::MenuClicked))
                    return JNI_TRUE;
                break;
            default:
                return JNI_FALSE;
        }
        return JNI_FALSE;
    }
}
