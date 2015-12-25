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

# http://developer.android.com/intl/ru/ndk/guides/application_mk.html

#APP_ABI := all
APP_ABI := armeabi-v7a

APP_PLATFORM := android-9
NDK_TOOLCHAIN_VERSION := 4.9

APP_BUILD_SCRIPT := ../src/Android.mk

#APP_CFLAGS :=
#APP_CPPFLAGS :=
#APP_LDFLAGS :=


# http://developer.android.com/ndk/guides/cpp-support.html#runtimes
# file:///<path to ndk>/docs/Programmers_Guide/html/md_3__key__topics__building__a_p_p_l_i_c_a_t_i_o_n-_m_k.html
APP_STL := gnustl_shared # default. CrystaX uses gnustl_shared for prebuilded boost and others.

APP_CPPFLAGS += -std=c++11
APP_CPPFLAGS += -fexceptions
APP_CPPFLAGS += -frtti



# This optional variable can be defined to either 'release' or 'debug'.
# This is used to alter the optimization level when building your application's modules.
# A 'release' mode is the default, and will generate highly optimized binaries.
# The 'debug' mode will generate un-optimized binaries which are much easier to debug.
# Note that if your application is debuggable (i.e. if your manifest sets the android:debuggable attribute to "`true`" in its <application> tag),
# the default will be 'debug' instead of 'release'. This can be overridden by setting APP_OPTIM to 'release'.
# Note that it is possible to debug both 'release' and 'debug' binaries,
# but the 'release' builds tend to provide less information during debugging sessions:
# some variables are optimized out and can't be inspected, code re-ordering can make stepping through the code difficult, stack traces may not be reliable, etc...
#APP_OPTIM := release
#APP_OPTIM := debug


# Set this variable to 'true' when your module has a very high number of sources and/or dependent static or shared libraries.
# This forces the build system to use an intermediate list file, and use it with the library archiver or static linker with the @ syntax.
# This can be useful on Windows, where the command-line only accepts a maximum of 8191 characters, which can be too small for complex projects.
# This also impacts the compilation of individual source files, placing nearly all compiler flags inside list files too.
# NOTE: We do not recommend enabling this feature by default, since it makes the build slower.
#APP_SHORT_COMMANDS := true
