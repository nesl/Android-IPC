LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := edu_ucla_nesl_android_ashmem_datareceiver_nativelib_NativeLib.c
LOCAL_MODULE := edu_ucla_nesl_android_ashmem_datareceiver_nativelib_NativeLib
LOCAL_LDLIBS += -llog
include $(BUILD_SHARED_LIBRARY)