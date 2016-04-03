/*
 * Project:  Feographia
 * Purpose:  Mobile application to work with the biblical text
 * Author:   NikitaFeodonit, nfeodonit@yandex.com
 * ****************************************************************************
 * Copyright (C) 2015-2016 NikitaFeodonit
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "fcore/utils/FileUtils.h"

#include <fstream>
#include <cerrno>


namespace fcore
{
  const char* FileUtils::FILE_SEPARATOR = "/";


  SharedString FileUtils::getFileContents(SharedString pFilePath)
  {
    // http://insanecoding.blogspot.ru/2011/11/how-to-read-in-file-in-c.html
    // http://insanecoding.blogspot.ru/2011/11/reading-in-entire-file-at-once-in-c.html
    // http://stackoverflow.com/a/525103
    std::ifstream in(*pFilePath, std::ios::in | std::ios::binary);
    if (in) {
      SharedString contents = makeSharedString();
      in.seekg(0, std::ios::end);
      contents->resize(in.tellg());
      in.seekg(0, std::ios::beg);
      in.read(&(*contents)[0], contents->size());
      in.close();
      return (contents);
    }
    throw (errno);
  }
}
