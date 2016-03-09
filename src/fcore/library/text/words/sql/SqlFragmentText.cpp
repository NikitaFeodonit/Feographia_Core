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

#include "fcore/FcoreLog.h"
#include "fcore/library/text/words/sql/SqlFragmentText.h"

#include "fcore/library/text/util/SqlTextConstants.h"


namespace fcore
{
  SqlFragmentText::SqlFragmentText()
  { }


  void SqlFragmentText::setDatabase(const SharedSQLiteDatabase pDatabase)
  {
    SqlTable::setDatabase(pDatabase);

    if (pDatabase) {
      createFragmentTextQueryStatement();
    }
  }


  const SharedString SqlFragmentText::getCreateTableSql() const
  {
    SharedString sql = makeSharedString();
    *sql += "CREATE TABLE IF NOT EXISTS ";
    *sql += SqlTextConstants::TABLE_TEXT;
    *sql += " (";
    *sql += SqlTextConstants::FIELD_ID;
    *sql += " INTEGER PRIMARY KEY, ";
    *sql += SqlTextConstants::FIELD_PRESIGNS;
    *sql += " TEXT, ";
    *sql += SqlTextConstants::FIELD_WORD;
    *sql += " TEXT, ";
    *sql += SqlTextConstants::FIELD_POSTSIGNS;
    *sql += " TEXT)";

    return (sql);
  }  // SqlFragmentText::getCreateTableSql


  const SharedSQLiteStatement SqlFragmentText::createFragmentTextQueryStatement()
  {
    std::string sql;
    sql += "SELECT ";
    sql += SqlTextConstants::FIELD_ID;
    sql += ", ";
    sql += SqlTextConstants::FIELD_PRESIGNS;
    sql += ", ";
    sql += SqlTextConstants::FIELD_WORD;
    sql += ", ";
    sql += SqlTextConstants::FIELD_POSTSIGNS;
    sql += " FROM ";
    sql += SqlTextConstants::TABLE_TEXT;
    sql += " WHERE ";
    sql += SqlTextConstants::FIELD_ID;
    sql += " >= ?1 AND "; // TODO: named constants of indexes
    sql += SqlTextConstants::FIELD_ID;
    sql += " < ?2  ORDER BY ";
    sql += SqlTextConstants::FIELD_ID;
    sql += " ASC";

    return (mpFragmentTextQueryStatement = makeSharedSQLiteStatement(*getDatabase(), sql));
  }


  const SharedWordMap SqlFragmentText::getFragmentText(
      const WordIdInt& fromWordId,
      const WordIdInt& toWordId) const
  {
    SharedSQLiteStatement pQuery = getFragmentTextQueryStatement();
    pQuery->reset();
    pQuery->clearBindings();

    pQuery->bind(1, static_cast<sqlite3_int64> (fromWordId));
    pQuery->bind(2, static_cast<sqlite3_int64> (toWordId));

    SharedWordMap wordMap = makeSharedWordMap();

    while (pQuery->executeStep()) {
      WordIdInt id = static_cast <WordIdInt>(pQuery->getColumn(0).getInt());

      // TODO: named constants of columns
      // we must make copy of getText()
      SharedString preSigns = makeSharedString(pQuery->getColumn(1).getText(""));
      SharedString wordText = makeSharedString(pQuery->getColumn(2).getText(""));
      SharedString postSigns = makeSharedString(pQuery->getColumn(3).getText(""));

      SharedWord word = makeSharedWord(id, preSigns, wordText, postSigns);
      wordMap->insert(PairIdWord(id, word));
    }

    return (wordMap);
  }  // SqlFragmentText::getFragmentText
}  // namespace fcore
