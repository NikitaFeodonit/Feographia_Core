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

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += \
    $$PWD \

HEADERS += \
#    $$PWD/fcore/capnproto/FcMsg.capnp.h \
#    $$PWD/fcore/capnproto/FcConst.capnp.h \
    $$PWD/fcore/message/FcoreMsg.hpp \
    $$PWD/fcore/message/SendErrorMsg.hpp \
    $$PWD/fcore/message/SendFileTextMsg.hpp \
    $$PWD/fcore/FcoreLog.hpp \
    $$PWD/fcore/Fcore.hpp \

SOURCES += \
#    $$PWD/fcore/capnproto/FcMsg.capnp.c++ \
#    $$PWD/fcore/capnproto/FcConst.capnp.c++ \
    $$PWD/fcore/message/FcoreMsg.cpp \
    $$PWD/fcore/message/SendErrorMsg.cpp \
    $$PWD/fcore/message/SendFileTextMsg.cpp \
    $$PWD/fcore/FcoreLog.cpp \
    $$PWD/fcore/Fcore.cpp \

OTHER_FILES += \
    $$PWD/fcore/capnproto/capnp-compile.cmd \
    $$PWD/fcore/capnproto/capnp-main.cmd \
    \
    $$PWD/fcore/capnproto/FcMsg.capnp \
    $$PWD/fcore/capnproto/FcConst.capnp \


include(../prebuild-libs/zeromq/zeromq.pri)
include(../prebuild-libs/capnproto-cpp/capnproto-cpp.pri)
include(../libs/sqlite/sqlite.pri)
include(../libs/SQLiteCpp/SQLiteCpp.pri)
