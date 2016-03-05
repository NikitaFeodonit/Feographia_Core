#
# Project:  Feographia
# Purpose:  Mobile application to work with the biblical text
# Author:   NikitaFeodonit, nfeodonit@yandex.com
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


TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += \
    $$PWD/src/include \

HEADERS += \
    $$PWD/src/include/SQLiteCpp/Assertion.h \
    $$PWD/src/include/SQLiteCpp/Column.h \
    $$PWD/src/include/SQLiteCpp/Database.h \
    $$PWD/src/include/SQLiteCpp/Exception.h \
    $$PWD/src/include/SQLiteCpp/SQLiteCpp.h \
    $$PWD/src/include/SQLiteCpp/Statement.h \
    $$PWD/src/include/SQLiteCpp/Transaction.h \

SOURCES += \
    $$PWD/src/Column.cpp \
    $$PWD/src/Database.cpp \
    $$PWD/src/Statement.cpp \
    $$PWD/src/Transaction.cpp \

OTHER_FILES += \
    $$PWD/Android.mk \
