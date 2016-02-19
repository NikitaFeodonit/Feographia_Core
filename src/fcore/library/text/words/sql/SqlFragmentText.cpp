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

#include "fcore/library/text/words/sql/SqlFragmentText.h"

#include "fcore/library/text/util/SqlTextConstants.h"


namespace fcore
{
  SqlFragmentText::SqlFragmentText(SharedString pDbPath)
    : SqlTable{pDbPath} {}


  const SharedString SqlFragmentText::getCreateTableSql() const
  {
    std::stringstream sql;
    sql << "CREATE TABLE IF NOT EXISTS " << SqlTextConstants::TABLE_TEXT << " (";
    sql << SqlTextConstants::FIELD_ID << " INTEGER PRIMARY KEY, ";
    sql << SqlTextConstants::FIELD_PRESIGNS << " TEXT, ";
    sql << SqlTextConstants::FIELD_WORD << " TEXT, ";
    sql << SqlTextConstants::FIELD_POSTSIGNS << " TEXT)";
    return (makeSharedString(sql.str()));
  }  // SqlFragmentText::getCreateTableSql


  const SharedWordMap SqlFragmentText::getFragmentText(
      WordIdInt fromWordId,
      WordIdInt toWordId) const
  {
    SharedWordMap wordMap = makeSharedWordMap();

    std::stringstream sql;
    sql << "SELECT ";
    sql << SqlTextConstants::FIELD_ID << ", ";
    sql << SqlTextConstants::FIELD_PRESIGNS << ", ";
    sql << SqlTextConstants::FIELD_WORD << ", ";
    sql << SqlTextConstants::FIELD_POSTSIGNS;
    sql << " FROM " << SqlTextConstants::TABLE_TEXT << " WHERE ";
    sql << SqlTextConstants::FIELD_ID << " >= " << fromWordId << " AND ";
    sql << SqlTextConstants::FIELD_ID << " < " << toWordId;
    sql << " ORDER BY " << SqlTextConstants::FIELD_ID << " ASC";

    SQLite::Database db {
      *getDbPath(), SQLITE_OPEN_READONLY
    };
    SQLite::Statement query {
      db, sql.str()
    };

    while (query.executeStep()) {
      WordIdInt id = static_cast <WordIdInt>(query.getColumn(0).getInt());

      std::string preSigns(query.getColumn(1).getText(""));
      SharedString sharedPreSigns = makeSharedString(preSigns);

      std::string wordText(query.getColumn(2).getText(""));
      SharedString sharedWordText = makeSharedString(wordText);

      std::string postSigns(query.getColumn(3).getText(""));
      SharedString sharedPostSigns = makeSharedString(postSigns);

      SharedWord word = makeSharedWord(id, sharedPreSigns, sharedWordText, sharedPostSigns);
      wordMap->insert(PairIdWord(id, word));
    }

    return (wordMap);
  }  // SqlFragmentText::getFragmentText
}  // namespace fcore
