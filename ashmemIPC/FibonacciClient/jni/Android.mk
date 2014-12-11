# Defines the root to all other relative paths
# The macro function my-dir, provided by the build system,
# specifies the path of the current directory (i.e. the 
# directory containing the Android.mk file itself)
LOCAL_PATH := $(call my-dir)

# Clear all LOCAL_XXX variables with the exception of 
# LOCAL_PATH (this is needed because all variables are global)
include $(CLEAR_VARS)


#ANDROID_INCLUDE := $(LOCAL_PATH)/android/include
#ANDROID_LIB := $(LOCAL_PATH)/android/lib

#LOCAL_CFLAGS += -DHAVE_PTHREADS -DHAVE_SYS_UIO_H

#LOCAL_C_INCLUDES += $(ANDROID_INCLUDE)/system/core/include
#LOCAL_C_INCLUDES += $(ANDROID_INCLUDE)/frameworks/native/include

#LOCAL_LDLIBS += -L$(ANDROID_LIB)
#LOCAL_LDLIBS += -llog -lutils -lbinder

# List all of our C/C++ files to be compiled (header file 
# dependencies are automatically computed)
LOCAL_SRC_FILES := com_marakana_android_fibonacciclientnative_FibLibClient.c

# The name of our shared module (this name will be prepended
# by lib and postfixed by .so)
LOCAL_MODULE := com_marakana_android_fibonacciclientnative_FibLibClient

# We need to tell the linker about our use of the liblog.so
LOCAL_LDLIBS += -llog

# Collects all LOCAL_XXX variables since "include $(CLEAR_VARS)"
#  and determines what to build (in this case a shared library)
include $(BUILD_SHARED_LIBRARY)

