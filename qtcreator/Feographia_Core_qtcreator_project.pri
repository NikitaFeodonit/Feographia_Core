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


# Warning: to build the project uses the android-nkd/jni/Android.mk,
#          this pro-file is for the QtCreator itself only
#
# For building from QtCreator make following for project configuration in QtCreator:
#
# in Project -> Build Settings -> Add -> Build -> name "ndk-build"
# Shadow build == true
# Build dir (relative to the main project) == E:\Dev\projects\Android\Feographia_Android\Feographia_Core\android-nkd
#
# Build Steps -- all delete and disable. Add build step -- Custom process step
# Command: (relative to the Crystax NDK) E:\Dev\Tools\Android\crystax-ndk-10.1.0\ndk-build.cmd
# Arguments:
# Working dir: %{buildDir}
#
# Clean steps -- all delete and disable. Add clean step -- Custom process step
# Command: (relative to the Crystax NDK) E:\Dev\Tools\Android\crystax-ndk-10.1.0\ndk-build.cmd
# Arguments: clean
# Working dir: %{buildDir}


TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += \
    $$PWD/../src

HEADERS += \
    $$PWD/../src/Feographia_Core/gps.hpp \

SOURCES += \
    $$PWD/../src/Feographia_Core/gps.cpp \

OTHER_FILES += \
    $$PWD/../android-nkd/jni/Android.mk \
    $$PWD/../android-nkd/jni/Application.mk \

# from Crystax NDK
INCLUDEPATH += \
    $(ANDROID_NDK_ROOT)/sources/boost/1.57.0/include
