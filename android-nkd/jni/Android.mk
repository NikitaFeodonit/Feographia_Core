#*******************************************************************************
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
#*******************************************************************************

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := fcore
#LOCAL_MODULE_FILENAME := libfcore

LOCAL_SRC_FILES := ../../src/fcore/fcore.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../src
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../src

TARGET_PLATFORM := android-9

LOCAL_STATIC_LIBRARIES := boost_thread_static
LOCAL_STATIC_LIBRARIES += boost_system_static
LOCAL_STATIC_LIBRARIES += zeromq-prebuilt

include $(BUILD_STATIC_LIBRARY)

$(call import-module,boost/1.57.0)

$(call import-add-path,$(LOCAL_PATH)/../../..)
$(call import-module,libs/zeromq/android-nkd/jni)
