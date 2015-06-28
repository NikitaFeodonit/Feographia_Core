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

@0xddd08a9a8cb53659;

using Cxx = import "/capnp/c++.capnp";
$Cxx.namespace("FCoreMessages");

using Java = import "/capnp/java.capnp";
$Java.package("ru.feographia.capnproto");
$Java.outerClassname("FCoreMessages");


struct LoadFileReq {
  path @0 :Text;
}

struct LoadFileRep {
  text @0 :Text;
}
