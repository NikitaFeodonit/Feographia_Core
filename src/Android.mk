#
# Project:  Feographia
# Purpose:  Mobile application to work with the biblical text
# Authors:  NikitaFeodonit, nfeodonit@yandex.com
# ****************************************************************************
# Copyright (C) 2015 NikitaFeodonit
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)


LOCAL_MODULE := fcore
#LOCAL_MODULE_FILENAME := libfcore


LOCAL_CPP_EXTENSION := .cpp .c++

LOCAL_SRC_FILES :=

LOCAL_SRC_FILES += fcore/capnproto/FcMsg.capnp.c++
LOCAL_SRC_FILES += fcore/capnproto/FcConst.capnp.c++

LOCAL_SRC_FILES += fcore/message/FcoreMsg.cpp
LOCAL_SRC_FILES += fcore/message/SendErrorMsg.cpp
LOCAL_SRC_FILES += fcore/message/SendFileTextMsg.cpp

LOCAL_SRC_FILES += fcore/Fcore.cpp
LOCAL_SRC_FILES += fcore/platform/android/FcoreAndroid.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)


TARGET_PLATFORM := android-9

#LOCAL_CPP_FEATURES := rtti
#LOCAL_CPP_FEATURES += exceptions
LOCAL_CPPFLAGS += -fexceptions
LOCAL_CPPFLAGS += -frtti
LOCAL_CPPFLAGS += -std=c++11

#LOCAL_EXPORT_CFLAGS := -DFOO=1
#LOCAL_EXPORT_CPPFLAGS := -DFOO=1

LOCAL_LDLIBS := -llog

LOCAL_STATIC_LIBRARIES :=
LOCAL_STATIC_LIBRARIES += zmq-prebuilt
LOCAL_STATIC_LIBRARIES += capnp-prebuilt
LOCAL_STATIC_LIBRARIES += kj-prebuilt
LOCAL_STATIC_LIBRARIES += boost_thread_static
LOCAL_STATIC_LIBRARIES += boost_system_static

LOCAL_WHOLE_STATIC_LIBRARIES :=
LOCAL_WHOLE_STATIC_LIBRARIES += jzmq-prebuilt

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path,$(LOCAL_PATH)/..)
$(call import-module,prebuild-libs/zeromq)
$(call import-module,prebuild-libs/capnproto-cpp)
$(call import-module,boost/1.58.0)
