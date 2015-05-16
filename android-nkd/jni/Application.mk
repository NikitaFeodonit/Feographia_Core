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

#APP_ABI := all
APP_ABI := armeabi-v7a

APP_PLATFORM := android-9
NDK_TOOLCHAIN_VERSION := 4.9

# Set this variable to 'true' when your module has a very high number of sources and/or dependent static or shared libraries.
# This forces the build system to use an intermediate list file, and use it with the library archiver or static linker with the @ syntax.
# This can be useful on Windows, where the command-line only accepts a maximum of 8191 characters, which can be too small for complex projects.
# This also impacts the compilation of individual source files, placing nearly all compiler flags inside list files too.
# NOTE: We do not recommend enabling this feature by default, since it makes the build slower.
#APP_SHORT_COMMANDS := true
