LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := jpeg_static
LOCAL_MODULE_FILENAME := CrossApp_jpeg_static
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libjpeg.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include/android
include $(PREBUILT_STATIC_LIBRARY)
