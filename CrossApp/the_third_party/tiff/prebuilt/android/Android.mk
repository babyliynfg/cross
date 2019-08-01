LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := tiff_static
LOCAL_MODULE_FILENAME := CrossApp_tiff_static
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libtiff.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include/android
include $(PREBUILT_STATIC_LIBRARY)
