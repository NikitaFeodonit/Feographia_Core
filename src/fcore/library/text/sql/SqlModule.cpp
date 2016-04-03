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

#include "fcore/library/text/sql/SqlModule.h"

#include "fcore/library/text/util/SqlTextConstants.h"
#include "fcore/FcoreLog.h"


namespace fcore
{
  SqlModule::SqlModule(SharedString pModulePath)
      : mpModulePath{pModulePath}
      , mReadwriteDatabase{false}
      , mpText{makeSharedSqlFragmentText()}
  { }


  SharedSQLiteDatabase SqlModule::createDatabase()
  {
    mReadwriteDatabase = true;
    mpDatabase =
        makeSharedSQLiteDatabase(*mpModulePath, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
    return (mpDatabase);
  }


  const SharedSQLiteDatabase SqlModule::openDatabase(bool readwrite)
  {
    mReadwriteDatabase = readwrite;
    mpDatabase = makeSharedSQLiteDatabase(*mpModulePath,
        readwrite ? SQLITE_OPEN_READWRITE : SQLITE_OPEN_READONLY);
    setTablesDatabase();
    return (mpDatabase);
  }


  void SqlModule::createTables()
  {
    try {
      std::string sql;
      sql += "DROP TABLE IF EXISTS ";
      sql += SqlTextConstants::TABLE_TEXT;

//      BOOST_LOG_SEV(FcoreLog::log, debug) << "Drop module table: " << sql;
      getDatabase()->exec(sql);

//      sql = *mpText->getCreateTableSql();
//      BOOST_LOG_SEV(FcoreLog::log, debug) << "Create module table: " << sql;
//      getDatabase()->exec(sql);
      getDatabase()->exec(*mpText->getCreateTableSql());

      setTablesDatabase();
      createWordInsertStatement();

    } catch (std::exception& e) {
      std::string errMsg = "SQLite exception: " + std::string(e.what());
      BOOST_LOG_SEV(FcoreLog::log, debug) << errMsg;
//        throw FcoreErrEx() << FcoreErrInfo(errMsg);
    }
  }


  void SqlModule::setTablesDatabase() const
  {
    mpText->setDatabase(getDatabase());
  }


  const SharedSQLiteStatement SqlModule::createWordInsertStatement()
  {
    std::string sql;
    sql += "INSERT INTO ";
    sql += SqlTextConstants::TABLE_TEXT;
    sql += " VALUES (?1, ?2, ?3, ?4)"; // TODO: named constants of indexes

    return (mpWordInsertStatement = makeSharedSQLiteStatement(*getDatabase(), sql));
  }


  const int SqlModule::insertWord(
      const WordIdInt wordId,
      const SharedString preSigns,
      const SharedString wordText,
      const SharedString postSigns) const
  {
    SharedSQLiteStatement pInsert = getWordInsertStatement();
    pInsert->reset();
    pInsert->clearBindings();

    pInsert->bind(1, static_cast<sqlite3_int64> (wordId));

    if (preSigns) {
      pInsert->bind(2, *preSigns);
    }
    if (wordText) {
      pInsert->bind(3, *wordText);
    }
    if (postSigns) {
      pInsert->bind(4, *postSigns);
    }

    return (pInsert->exec());
  }


  const SharedFragmentText SqlModule::getFragmentText() const
  {
    return (std::static_pointer_cast <FragmentText>(mpText));
  }


  void SqlModule::createTestSqlModule()
  {
    // TODO: for multiply inserts see https://www.sqlite.org/faq.html#q19

    SQLite::Transaction transaction(*createDatabase());
    createTables();

    int cnt = 0;

    cnt += insertWord(TextId::getWordId(52, 4, 22, 1), nullptr, makeSharedString("Потому"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 22, 2), nullptr, makeSharedString("и"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 22, 3), nullptr, makeSharedString("вменилось"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 22, 4), nullptr, makeSharedString("ему"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 22, 5), nullptr, makeSharedString("в"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 22, 6), nullptr, makeSharedString("праведность"), makeSharedString("."));

    cnt += insertWord(TextId::getWordId(52, 4, 23, 1), nullptr, makeSharedString("А"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 23, 2), nullptr, makeSharedString("впрочем"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 23, 3), nullptr, makeSharedString("не"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 23, 4), nullptr, makeSharedString("в"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 23, 5), nullptr, makeSharedString("отношении"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 23, 6), nullptr, makeSharedString("к"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 23, 7), nullptr, makeSharedString("нему"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 23, 8), nullptr, makeSharedString("одному"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 23, 9), nullptr, makeSharedString("написано"), makeSharedString(","));
    cnt += insertWord(TextId::getWordId(52, 4, 23, 10), nullptr, makeSharedString("что"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 23, 11), nullptr, makeSharedString("вменилось"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 23, 12), nullptr, makeSharedString("ему"), makeSharedString(","));

    cnt += insertWord(TextId::getWordId(52, 4, 24, 1), nullptr, makeSharedString("но"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 24, 2), nullptr, makeSharedString("и"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 24, 3), nullptr, makeSharedString("в"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 24, 4), nullptr, makeSharedString("отношении"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 24, 5), nullptr, makeSharedString("к"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 24, 6), nullptr, makeSharedString("нам"), makeSharedString(";"));
    cnt += insertWord(TextId::getWordId(52, 4, 24, 7), nullptr, makeSharedString("вменится"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 24, 8), nullptr, makeSharedString("и"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 24, 9), nullptr, makeSharedString("нам"), makeSharedString(","));
    cnt += insertWord(TextId::getWordId(52, 4, 24, 10), nullptr, makeSharedString("верующим"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 24, 11), nullptr, makeSharedString("в"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 24, 12), nullptr, makeSharedString("Того"), makeSharedString(","));
    cnt += insertWord(TextId::getWordId(52, 4, 24, 13), nullptr, makeSharedString("Кто"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 24, 14), nullptr, makeSharedString("воскресил"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 24, 15), nullptr, makeSharedString("из"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 24, 16), nullptr, makeSharedString("мертвых"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 24, 17), nullptr, makeSharedString("Иисуса"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 24, 18), nullptr, makeSharedString("Христа"), makeSharedString(","));
    cnt += insertWord(TextId::getWordId(52, 4, 24, 19), nullptr, makeSharedString("Господа"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 24, 20), nullptr, makeSharedString("нашего"), makeSharedString(","));

    cnt += insertWord(TextId::getWordId(52, 4, 25, 1), nullptr, makeSharedString("Который"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 25, 2), nullptr, makeSharedString("предан"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 25, 3), nullptr, makeSharedString("за"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 25, 4), nullptr, makeSharedString("грехи"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 25, 5), nullptr, makeSharedString("наши"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 25, 6), nullptr, makeSharedString("и"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 25, 7), nullptr, makeSharedString("воскрес"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 25, 8), nullptr, makeSharedString("для"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 25, 9), nullptr, makeSharedString("оправдания"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 4, 25, 10), nullptr, makeSharedString("нашего"), makeSharedString("."));

    cnt += insertWord(TextId::getWordId(52, 5, 1, 1), nullptr, makeSharedString("Итак"), makeSharedString(","));
    cnt += insertWord(TextId::getWordId(52, 5, 1, 2), nullptr, makeSharedString("оправдавшись"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 1, 3), nullptr, makeSharedString("верою"), makeSharedString(","));
    cnt += insertWord(TextId::getWordId(52, 5, 1, 4), nullptr, makeSharedString("мы"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 1, 5), nullptr, makeSharedString("имеем"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 1, 6), nullptr, makeSharedString("мир"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 1, 7), nullptr, makeSharedString("с"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 1, 8), nullptr, makeSharedString("Богом"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 1, 9), nullptr, makeSharedString("через"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 1, 10), nullptr, makeSharedString("Господа"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 1, 11), nullptr, makeSharedString("нашего"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 1, 12), nullptr, makeSharedString("Иисуса"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 1, 13), nullptr, makeSharedString("Христа"), makeSharedString(","));

    cnt += insertWord(TextId::getWordId(52, 5, 2, 1), nullptr, makeSharedString("через"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 2, 2), nullptr, makeSharedString("Которого"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 2, 3), nullptr, makeSharedString("верою"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 2, 4), nullptr, makeSharedString("и"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 2, 5), nullptr, makeSharedString("получили"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 2, 6), nullptr, makeSharedString("мы"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 2, 7), nullptr, makeSharedString("доступ"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 2, 8), nullptr, makeSharedString("к"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 2, 9), nullptr, makeSharedString("той"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 2, 10), nullptr, makeSharedString("благодати"), makeSharedString(","));
    cnt += insertWord(TextId::getWordId(52, 5, 2, 11), nullptr, makeSharedString("в"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 2, 12), nullptr, makeSharedString("которой"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 2, 13), nullptr, makeSharedString("стоим"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 2, 14), nullptr, makeSharedString("и"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 2, 15), nullptr, makeSharedString("хвалимся"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 2, 16), nullptr, makeSharedString("надеждою"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 2, 17), nullptr, makeSharedString("славы"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 2, 18), nullptr, makeSharedString("Божией"), makeSharedString("."));

    cnt += insertWord(TextId::getWordId(52, 5, 3, 1), nullptr, makeSharedString("И"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 3, 2), nullptr, makeSharedString("не"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 3, 3), nullptr, makeSharedString("сим"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 3, 4), nullptr, makeSharedString("только"), makeSharedString(","));
    cnt += insertWord(TextId::getWordId(52, 5, 3, 5), nullptr, makeSharedString("но"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 3, 6), nullptr, makeSharedString("хвалимся"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 3, 7), nullptr, makeSharedString("и"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 3, 8), nullptr, makeSharedString("скорбями"), makeSharedString(","));
    cnt += insertWord(TextId::getWordId(52, 5, 3, 9), nullptr, makeSharedString("зная"), makeSharedString(","));
    cnt += insertWord(TextId::getWordId(52, 5, 3, 10), nullptr, makeSharedString("что"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 3, 11), nullptr, makeSharedString("от"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 3, 12), nullptr, makeSharedString("скорби"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 3, 13), nullptr, makeSharedString("происходит"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 3, 14), nullptr, makeSharedString("терпение"), makeSharedString(","));

    cnt += insertWord(TextId::getWordId(52, 5, 4, 1), nullptr, makeSharedString("от"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 4, 2), nullptr, makeSharedString("терпения"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 4, 3), nullptr, makeSharedString("опытность"), makeSharedString(","));
    cnt += insertWord(TextId::getWordId(52, 5, 4, 4), nullptr, makeSharedString("от"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 4, 5), nullptr, makeSharedString("опытности"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 4, 6), nullptr, makeSharedString("надежда"), makeSharedString(","));

    cnt += insertWord(TextId::getWordId(52, 5, 5, 1), nullptr, makeSharedString("а"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 5, 2), nullptr, makeSharedString("надежда"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 5, 3), nullptr, makeSharedString("не"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 5, 4), nullptr, makeSharedString("постыжает"), makeSharedString(","));
    cnt += insertWord(TextId::getWordId(52, 5, 5, 5), nullptr, makeSharedString("потому"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 5, 6), nullptr, makeSharedString("что"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 5, 7), nullptr, makeSharedString("любовь"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 5, 8), nullptr, makeSharedString("Божия"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 5, 9), nullptr, makeSharedString("излилась"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 5, 10), nullptr, makeSharedString("в"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 5, 11), nullptr, makeSharedString("сердца"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 5, 12), nullptr, makeSharedString("наши"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 5, 13), nullptr, makeSharedString("Духом"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 5, 14), nullptr, makeSharedString("Святым"), makeSharedString(","));
    cnt += insertWord(TextId::getWordId(52, 5, 5, 15), nullptr, makeSharedString("данным"), nullptr);
    cnt += insertWord(TextId::getWordId(52, 5, 5, 16), nullptr, makeSharedString("нам"), makeSharedString("."));

    transaction.commit();

    BOOST_LOG_SEV(FcoreLog::log, debug) << "createTestSqlModule(), inserted words: " << cnt;
  }
}  // namespace fcore
