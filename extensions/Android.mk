LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := CrossApp_extension_static

LOCAL_MODULE_FILENAME := libextension

LOCAL_SRC_FILES += video/CAVideoPlayerControlView.cpp \
                   video/CAVideoPlayerDecoder.cpp \
                   video/CAVideoPlayerRender.cpp \
                   video/CAVideoPlayerView.cpp \
		    video/jni/Java_org_CrossApp_lib_CrossAppSDL.cpp \


LOCAL_WHOLE_STATIC_LIBRARIES := CrossApp_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

LOCAL_WHOLE_STATIC_LIBRARIES += CrossApp_libsdl_static
LOCAL_WHOLE_STATIC_LIBRARIES += CrossApp_avcodec_static
LOCAL_WHOLE_STATIC_LIBRARIES += CrossApp_avformat_static
LOCAL_WHOLE_STATIC_LIBRARIES += CrossApp_avresample_static
LOCAL_WHOLE_STATIC_LIBRARIES += CrossApp_avutil_static
LOCAL_WHOLE_STATIC_LIBRARIES += CrossApp_swresample_static
LOCAL_WHOLE_STATIC_LIBRARIES += CrossApp_swscale_static


LOCAL_CFLAGS += -DCC_ENABLE_CHIPMUNK_INTEGRATION=1
LOCAL_EXPORT_CFLAGS += -DCC_ENABLE_CHIPMUNK_INTEGRATION=1
LOCAL_CPPFLAGS += -DCC_ENABLE_CHIPMUNK_INTEGRATION=1
LOCAL_EXPORT_CPPFLAGS += -DCC_ENABLE_CHIPMUNK_INTEGRATION=1

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \



LOCAL_CFLAGS := -fexceptions

include $(BUILD_STATIC_LIBRARY)

$(call import-module,CrossApp)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions/video/ffmpeg/prebuilt/android)
$(call import-module,extensions/video/SDL/prebuilt/android)