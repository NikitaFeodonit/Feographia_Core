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

#ifndef FCORE_SQLTEXT_H
#define FCORE_SQLTEXT_H

#include "fcore/utils/SharedPointers.h"
#include "fcore/library/text/words/FragmentText.h"
#include "fcore/library/text/fragments/sql/SqlTable.h"


namespace fcore
{
  class SqlFragmentText
      : public virtual FragmentText
        , public virtual SqlTable
  {
  public:
    explicit SqlFragmentText();

    virtual const SharedWordMap getFragmentText(
        const WordIdInt& fromWordId,
        const WordIdInt& toWordId) const;

  protected:
  public:
    virtual void setDatabase(const SharedSQLiteDatabase pDatabase) override;
    virtual const SharedString getCreateTableSql() const override;

    virtual const SharedSQLiteStatement createFragmentTextQueryStatement();
    const SharedSQLiteStatement getFragmentTextQueryStatement() const;

  private:
    SharedSQLiteStatement mpFragmentTextQueryStatement;
  };


  inline const SharedSQLiteStatement SqlFragmentText::getFragmentTextQueryStatement() const
  {
    return (mpFragmentTextQueryStatement);
  }


  using SharedSqlFragmentText = std::shared_ptr <SqlFragmentText>;


  template <typename ... Args>
  SharedSqlFragmentText makeSharedSqlFragmentText(Args&& ... args)
  {
    return (std::make_shared <SqlFragmentText>(std::forward <Args>(args) ...));
  }
}  // namespace fcore

#endif  // FCORE_SQLTEXT_H
