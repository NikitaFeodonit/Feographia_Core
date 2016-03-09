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

#include "fcore/library/text/fragments/sql/SqlFragment.h"

#include <fcore/library/text/util/SqlTextConstants.h>


namespace fcore
{
  SqlFragment::~SqlFragment() {}


//  const SharedString SqlFragment::getCreateTableSql() const  // TODO: remove it
//  {
//    SharedString sql = makeSharedString();
//    *sql += "CREATE TABLE IF NOT EXISTS ";
//    *sql += *getModuleId();
//    *sql += "(";
//    *sql += SqlTextConstants::FIELD_ID;
//    *sql += " INTEGER PRIMARY KEY)";
//    return (sql);
//  }
}  // namespace fcore
