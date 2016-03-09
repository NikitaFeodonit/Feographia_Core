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

#ifndef FCORE_SHAREDPOINTERS_H
#define FCORE_SHAREDPOINTERS_H

#include <memory>
#include <string>
#include "SQLiteCpp/SQLiteCpp.h"


namespace fcore
{
  // SharedString
  using SharedString = std::shared_ptr <std::string>;


  // http://stackoverflow.com/a/13196986
  template <typename ... Args>
  SharedString makeSharedString(Args&& ... args)
  {
    return (std::make_shared <std::string>(std::forward <Args>(args) ...));
  }


  // SharedSQLiteDatabase
  using SharedSQLiteDatabase = std::shared_ptr <SQLite::Database>;


  template <typename ... Args>
  SharedSQLiteDatabase makeSharedSQLiteDatabase(Args&& ... args)
  {
    return (std::make_shared <SQLite::Database>(std::forward <Args>(args) ...));
  }


  // SharedSQLiteStatement
  using SharedSQLiteStatement = std::shared_ptr <SQLite::Statement>;


  template <typename ... Args>
  SharedSQLiteStatement makeSharedSQLiteStatement(Args&& ... args)
  {
    return (std::make_shared <SQLite::Statement>(std::forward <Args>(args) ...));
  }
}  // namespace fcore


#endif  // FCORE_SHAREDPOINTERS_H
