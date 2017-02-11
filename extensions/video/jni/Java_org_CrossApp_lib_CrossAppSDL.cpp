
#include "SDL_main.h"
#include "CrossApp.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

using namespace CrossApp;

extern "C" {
	
	extern void SDL_Android_Init(JNIEnv* env, jclass cls);
	extern jint SDL_JNI_OnLoad(JavaVM* vm, void* reserved);
	extern int Android_JNI_SetupThread(void);
	
    JNIEXPORT void JNICALL Java_org_CrossApp_lib_CrossAppSDL_nativeInit(JNIEnv* env, jclass cls, jobject obj) {
        int ret = SDL_JNI_OnLoad(JniHelper::getJavaVM(), NULL);
        SDL_Android_Init(env, cls);
    }
}