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

#include "fcore/library/text/sql/SqlModule.h"

#include "fcore/library/text/util/SqlTextConstants.h"
#include "fcore/library/text/util/PathConstants.h"


namespace fcore
{
  SqlModule::SqlModule()
  {
    std::stringstream dbPath;
    dbPath << PathConstants::MODULES_PATH << "/" << "testmodule";
    mpText = makeSharedSqlFragmentText(makeSharedString(dbPath.str()));
  }


  const SharedFragmentText SqlModule::getFragmentText() const
  {
    return (std::static_pointer_cast <FragmentText>(mpText));
  }


  void SqlModule::createTestSqlModule()
  {
    mpText->createTable();

    SQLite::Database db(mpText->getDbPath()->c_str(), SQLITE_OPEN_READWRITE);

    std::stringstream sql;
    int               cnt = 0;

    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 22, 1) << ", NULL, 'Потому', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 22, 2) << ", NULL, 'и', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 22, 3) << ", NULL, 'вменилось', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 22, 4) << ", NULL, 'ему', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 22, 5) << ", NULL, 'в', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 22, 6) << ", NULL, 'праведность', '.')";
    cnt = db.exec(sql.str());
    sql.str(std::string());

    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 23, 1) << ", NULL, 'А', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 23, 2) << ", NULL, 'впрочем', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 23, 3) << ", NULL, 'не', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 23, 4) << ", NULL, 'в', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 23, 5) << ", NULL, 'отношении', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 23, 6) << ", NULL, 'к', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 23, 7) << ", NULL, 'нему', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 23, 8) << ", NULL, 'одному', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 23, 9) << ", NULL, 'написано', ',')";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 23, 10) << ", NULL, 'что', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 23, 11) << ", NULL, 'вменилось', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 23, 12) << ", NULL, 'ему', ',')";
    cnt = db.exec(sql.str());
    sql.str(std::string());

    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 24, 1) << ", NULL, 'но', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 24, 2) << ", NULL, 'и', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 24, 3) << ", NULL, 'в', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 24, 4) << ", NULL, 'отношении', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 24, 5) << ", NULL, 'к', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 24, 6) << ", NULL, 'нам', ';')";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 24, 7) << ", NULL, 'вменится', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 24, 8) << ", NULL, 'и', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 24, 9) << ", NULL, 'нам', ',')";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 24, 10) << ", NULL, 'верующим', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 24, 11) << ", NULL, 'в', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 24, 12) << ", NULL, 'Того', ',')";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 24, 13) << ", NULL, 'Кто', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 24, 14) << ", NULL, 'воскресил', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 24, 15) << ", NULL, 'из', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 24, 16) << ", NULL, 'мертвых', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 24, 17) << ", NULL, 'Иисуса', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 24, 18) << ", NULL, 'Христа', ',')";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 24, 19) << ", NULL, 'Господа', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 24, 20) << ", NULL, 'нашего', ',')";
    cnt = db.exec(sql.str());
    sql.str(std::string());

    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 25, 1) << ", NULL, 'Который', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 25, 2) << ", NULL, 'предан', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 25, 3) << ", NULL, 'за', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 25, 4) << ", NULL, 'грехи', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 25, 5) << ", NULL, 'наши', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 25, 6) << ", NULL, 'и', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 25, 7) << ", NULL, 'воскрес', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 25, 8) << ", NULL, 'для', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 25, 9) << ", NULL, 'оправдания', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 4, 25, 10) << ", NULL, 'нашего', '.')";
    cnt = db.exec(sql.str());
    sql.str(std::string());

    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 1, 1) << ", NULL, 'Итак', ',')";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 1, 2) << ", NULL, 'оправдавшись', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 1, 3) << ", NULL, 'верою', ',')";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 1, 4) << ", NULL, 'мы', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 1, 5) << ", NULL, 'имеем', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 1, 6) << ", NULL, 'мир', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 1, 7) << ", NULL, 'с', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 1, 8) << ", NULL, 'Богом', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 1, 9) << ", NULL, 'через', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 1, 10) << ", NULL, 'Господа', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 1, 11) << ", NULL, 'нашего', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 1, 12) << ", NULL, 'Иисуса', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 1, 13) << ", NULL, 'Христа', ',')";
    cnt = db.exec(sql.str());
    sql.str(std::string());

    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 2, 1) << ", NULL, 'через', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 2, 2) << ", NULL, 'Которого', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 2, 3) << ", NULL, 'верою', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 2, 4) << ", NULL, 'и', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 2, 5) << ", NULL, 'получили', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 2, 6) << ", NULL, 'мы', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 2, 7) << ", NULL, 'доступ', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 2, 8) << ", NULL, 'к', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 2, 9) << ", NULL, 'той', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 2, 10) << ", NULL, 'благодати', ',')";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 2, 11) << ", NULL, 'в', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 2, 12) << ", NULL, 'которой', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 2, 13) << ", NULL, 'стоим', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 2, 14) << ", NULL, 'и', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 2, 15) << ", NULL, 'хвалимся', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 2, 16) << ", NULL, 'надеждою', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 2, 17) << ", NULL, 'славы', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 2, 18) << ", NULL, 'Божией', '.')";
    cnt = db.exec(sql.str());
    sql.str(std::string());

    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 3, 1) << ", NULL, 'И', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 3, 2) << ", NULL, 'не', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 3, 3) << ", NULL, 'сим', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 3, 4) << ", NULL, 'только', ',')";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 3, 5) << ", NULL, 'но', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 3, 6) << ", NULL, 'хвалимся', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 3, 7) << ", NULL, 'и', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 3, 8) << ", NULL, 'скорбями', ',')";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 3, 9) << ", NULL, 'зная', ',')";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 3, 10) << ", NULL, 'что', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 3, 11) << ", NULL, 'от', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 3, 12) << ", NULL, 'скорби', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 3, 13) << ", NULL, 'происходит', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 3, 14) << ", NULL, 'терпение', ',')";
    cnt = db.exec(sql.str());
    sql.str(std::string());

    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 4, 1) << ", NULL, 'от', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 4, 2) << ", NULL, 'терпения', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 4, 3) << ", NULL, 'опытность', ',')";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 4, 4) << ", NULL, 'от', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 4, 5) << ", NULL, 'опытности', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 4, 6) << ", NULL, 'надежда', ',')";
    cnt = db.exec(sql.str());
    sql.str(std::string());

    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 5, 1) << ", NULL, 'а', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 5, 2) << ", NULL, 'надежда', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 5, 3) << ", NULL, 'не', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 5, 4) << ", NULL, 'постыжает', ',')";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 5, 5) << ", NULL, 'потому', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 5, 6) << ", NULL, 'что', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 5, 7) << ", NULL, 'любовь', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 5, 8) << ", NULL, 'Божия', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 5, 9) << ", NULL, 'излилась', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 5, 10) << ", NULL, 'в', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 5, 11) << ", NULL, 'сердца', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 5, 12) << ", NULL, 'наши', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 5, 13) << ", NULL, 'Духом', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 5, 14) << ", NULL, 'Святым', ',')";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 5, 15) << ", NULL, 'данным', NULL)";
    cnt = db.exec(sql.str());
    sql.str(std::string());
    sql << "INSERT INTO " << SqlTextConstants::TABLE_TEXT << " VALUES (";
    sql << TextId::getWordId(52, 5, 5, 16) << ", NULL, 'нам', '.')";
    cnt = db.exec(sql.str());
    sql.str(std::string());
  }  // SqlModule::createTestSqlModule
}  // namespace fcore
