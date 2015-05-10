LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := test-boost
LOCAL_SRC_FILES := test.cpp gps.cpp
LOCAL_STATIC_LIBRARIES := boost_serialization_static
LOCAL_LDLIBS    := -llog

include $(BUILD_SHARED_LIBRARY)

$(call import-module,boost/1.57.0)
