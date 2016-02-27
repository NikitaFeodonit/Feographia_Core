/*
 * Project:  Feographia
 * Purpose:  Mobile application to work with the biblical text
 * Authors:  NikitaFeodonit, nfeodonit@yandex.com
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

#include "fcore/library/text/fragments/sql/SqlTable.h"

#include <sstream>
#include "fcore/FcoreLog.h"


namespace fcore
{
  SqlTable::SqlTable(SharedString pDbPath)
    : mpDbPath{pDbPath} {}


  SqlTable::~SqlTable() {}


  void SqlTable::createTable() const
  {
    try {
      SharedString pCreateTableSql = getCreateTableSql();
      BOOST_LOG_SEV(FcoreLog::log, debug) << "Create module table: " << *pCreateTableSql;

      SQLite::Database db(*getDbPath(), SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
      db.exec(*pCreateTableSql);
    }
    catch (std::exception& e) {
      std::string errMsg = "SQLite exception: " + std::string(e.what());
      BOOST_LOG_SEV(FcoreLog::log, debug) << errMsg;
//        throw FcoreErrEx() << FcoreErrInfo(errMsg);
    }
  }  // SqlTable::createTable
}  // namespace fcore
