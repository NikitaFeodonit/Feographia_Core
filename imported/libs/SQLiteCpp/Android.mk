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


LOCAL_MODULE := SQLiteCpp


LOCAL_CPP_EXTENSION := .cpp

LOCAL_SRC_FILES :=
LOCAL_SRC_FILES += src/Backup.cpp
LOCAL_SRC_FILES += src/Column.cpp
LOCAL_SRC_FILES += src/Database.cpp
LOCAL_SRC_FILES += src/Statement.cpp
LOCAL_SRC_FILES += src/Transaction.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/src/include
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/src/include


TARGET_PLATFORM := android-9

LOCAL_STATIC_LIBRARIES :=
LOCAL_STATIC_LIBRARIES += sqlite


include $(BUILD_STATIC_LIBRARY)


$(call import-add-path,$(LOCAL_PATH)/..)
$(call import-module,imported/libs/sqlite)
