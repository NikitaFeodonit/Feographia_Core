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

#ifndef FCORE_SQLTABLE_H
#define FCORE_SQLTABLE_H

#include <string>
#include "fcore/utils/SharedPointers.h"


namespace fcore
{
  class SqlTable
  {
  public:
    explicit SqlTable();
    virtual ~SqlTable();

    virtual void setDatabase(const SharedSQLiteDatabase pDatabase);
    const SharedSQLiteDatabase getDatabase() const;

  protected:
    virtual const SharedString getCreateTableSql() const = 0;

  private:
    SharedSQLiteDatabase mpDatabase;
  };


  inline const SharedSQLiteDatabase SqlTable::getDatabase() const
  {
    return (mpDatabase);
  }


  inline void SqlTable::setDatabase(const SharedSQLiteDatabase pDatabase)
  {
    mpDatabase = pDatabase;
  }
}  // namespace fcore

#endif  // FCORE_SQLTABLE_H
