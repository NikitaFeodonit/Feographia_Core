#
# Project:  Feographia
# Purpose:  Mobile application to work with the biblical text
# Authors:  NikitaFeodonit, nfeodonit@yandex.com
# ****************************************************************************
# Copyright (C) 2015-2016 NikitaFeodonit
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


LOCAL_MODULE := sqlite


LOCAL_SRC_FILES :=
LOCAL_SRC_FILES += src/sqlite3.c


LOCAL_C_INCLUDES := $(LOCAL_PATH)/src
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/src


TARGET_PLATFORM := android-9

## flags from Crystax NDK
#LOCAL_CFLAGS :=
#LOCAL_CFLAGS += -Wall -Wno-unused -Wno-multichar -Wstrict-aliasing=2 -Werror
#case $ABI in
#  x86|x86_64|arm64-v8a)
#    echo 'LOCAL_CFLAGS += -Wno-strict-aliasing'
#    ;;
#esac
#LOCAL_CFLAGS += -fno-exceptions -fmessage-length=0

LOCAL_CFLAGS += -DSQLITE_THREADSAFE=2 # Multi-threaded

## may be used
#SQLITE_ENABLE_FTS3
#SQLITE_ENABLE_FTS3_PARENTHESIS
#SQLITE_ENABLE_FTS4
#SQLITE_ENABLE_ICU


include $(BUILD_STATIC_LIBRARY)
