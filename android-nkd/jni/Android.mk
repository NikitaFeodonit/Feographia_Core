LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := Feographia_Core

#LOCAL_MODULE_FILENAME := libfeographia_core


#LOCAL_SRC_FILES := $(LOCAL_PATH)/../../src/Feographia_Core/gps.cpp \

LOCAL_SRC_FILES := ../../src/Feographia_Core/gps.cpp \

#                   relative/dir/probe.cpp \

#LOCAL_SRC_FILES += relative/dir/probe.cpp


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../src/Feographia_Core

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../src/Feographia_Core

#LOCAL_C_INCLUDES := ../../src/Feographia_Core

#LOCAL_EXPORT_C_INCLUDES := ../../src/Feographia_Core

LOCAL_STATIC_LIBRARIES := boost_serialization_static

TARGET_PLATFORM := android-9

include $(BUILD_STATIC_LIBRARY)

$(call import-module,boost/1.57.0)
