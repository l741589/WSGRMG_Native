LOCAL_PATH := $(call my-dir)

#include $(CLEAR_VARS)
#LOCAL_MODULE := base
#LOCAL_SRC_FILES := adbi/libbase.a
#LOCAL_EXPORT_C_INCLUDES := adbi
#include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libcocos2dcpp
LOCAL_SRC_FILES := E:\AndroidWS\WSGCrack\warshipgirlsr_cn_2_5_0_base\lib\armeabi\libcocos2dcpp.so
LOCAL_EXPORT_C_INCLUDES := libcocos2dcpp
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := MagicBox
LOCAL_CFLAGS := -w -std=c++11
LOCAL_LDLIBS := -llog -lOpenSLES -landroid
LOCAL_SHARED_LIBRARIES := libcocos2dcpp
#LOCAL_STATIC_LIBRARIES := base
LOCAL_SRC_FILES := com_bigzhao_jianrmagicbox_CppInterface.cpp \
    HookUtils.cpp \
    Listeners.cpp	\
	Hackers.cpp	\
	IO.cpp	\
	util.cpp \
	SoundManager.cpp \
	FakeShip.cpp	\
	audio\AudioEngine.cpp \
	audio\AudioEngine-inl.cpp \
	adbi\base.c\
	adbi\util.c\
	adbi\hook.c\
	ice\IceKey.cpp

include $(BUILD_SHARED_LIBRARY)
