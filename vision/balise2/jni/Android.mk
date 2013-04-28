LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)


include /home/vins/local/OpenCV-2.4.5-android-sdk/sdk/native/jni/OpenCV.mk

#LOCAL_C_INCLUDES += /home/vins/local/android-ndk-r8e/platforms/android-8/arch-arm/usr/include
LOCAL_MODULE    := bougiesjni
LOCAL_C_INCLUDES += $(LOCAL_PATH)
# for file in $(ls *.cpp *.h); do echo -n $file ; done;
LOCAL_SRC_FILES := candlecolors.cpp candlecolors.h computefeaturepoints.cpp computefeaturepoints.h computehomography.cpp computehomography.h main.cpp matchdescriptors.cpp matchdescriptors.h
LOCAL_LDLIBS +=  -llog -ldl
#LOCAL_LDLIBS += -L/home/vins/local/android-ndk-r8e/platforms/android-8/arch-arm/usr/lib
#LOCAL_LDLIBS += -landroid

include $(BUILD_SHARED_LIBRARY)
