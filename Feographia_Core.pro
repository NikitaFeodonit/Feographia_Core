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


# Make following for project configuration:
#
# in Project -> Build Settings -> Add -> Build -> name "ndk-build"
# Shadow build == true
# Build dir (relative to the main project) == E:\Dev\projects\Android\Feographia_Android\Feographia_Core\src\main
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

HEADERS += $$PWD/src/main/jni/gps.hpp \

SOURCES += $$PWD/src/main/jni/gps.cpp \
           $$PWD/src/main/jni/test.cpp

OTHER_FILES += $$PWD/src/main/jni/Android.mk \
               $$PWD/src/main/jni/Application.mk

# only for Qt Creator self
INCLUDEPATH += E:/Dev/Tools/Android/crystax-ndk-10.1.0/sources/boost/1.57.0/include

#include(deployment.pri)
#qtcAddDeployment()
