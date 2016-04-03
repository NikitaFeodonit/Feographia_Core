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

#ifndef FCORE_SQLMODULE_H
#define FCORE_SQLMODULE_H

#include "fcore/utils/SharedPointers.h"
#include "fcore/library/text/Module.h"
#include "fcore/library/text/words/sql/SqlFragmentText.h"


namespace fcore
{
  class SqlModule
      : public Module
  {
  public:
    explicit SqlModule(SharedString pModulePath);

    SharedSQLiteDatabase createDatabase();
    const SharedSQLiteDatabase openDatabase(bool readwrite);
    const SharedSQLiteDatabase getDatabase() const;
    bool isReadwriteDatabase() const;

    virtual void createTables();
    virtual void setTablesDatabase() const;
    virtual const int insertWord(
        const WordIdInt wordId,
        const SharedString preSigns,
        const SharedString wordText,
        const SharedString postSigns) const;
    virtual const SharedFragmentText getFragmentText() const;
    void createTestSqlModule();


  protected:
    virtual const SharedSQLiteStatement createWordInsertStatement();
    virtual const SharedSQLiteStatement getWordInsertStatement() const;

  private:
    SharedString mpModulePath;
    bool mReadwriteDatabase;
    SharedSqlFragmentText mpText;

    SharedSQLiteDatabase mpDatabase;
    SharedSQLiteStatement mpWordInsertStatement;
  };


  inline const SharedSQLiteDatabase SqlModule::getDatabase() const
  {
    return (mpDatabase);
  }


  inline bool SqlModule::isReadwriteDatabase() const
  {
    return (mReadwriteDatabase);
  }


  inline const SharedSQLiteStatement SqlModule::getWordInsertStatement() const
  {
    return (mpWordInsertStatement);
  }
}  // namespace fcore

#endif  // FCORE_SQLMODULE_H
