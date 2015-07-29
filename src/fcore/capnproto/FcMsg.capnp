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

@0xd53496402d81854c;

using Cxx = import "/capnp/c++.capnp";
$Cxx.namespace("FcMsg");

using Java = import "/capnp/java.capnp";
$Java.package("ru.feographia.capnproto");
$Java.outerClassname("FcMsg");


struct Message
{
  errorFlag @0 :Bool = false;
  msgType @1 :Int32;
  msgText @2 :Text;
  dataPointer @3 :AnyPointer;
}


struct Reference
{
  bookId @0 :Text;
  chapterId @1 :Int32;
  fromVerseId @2 :Int32;
  toVerseId @3 :Int32;
}


struct GetChapterQ
{
  reference @0 :Reference;
}
struct GetChapterR
{
  chapterText @0 :Text;
}


# for test
struct GetFileTextQ
{
  filePath @0 :Text;
}
struct GetFileTextR
{
  fileText @0 :Text;
}
