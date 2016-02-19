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

#ifndef FCORE_TEXT_H
#define FCORE_TEXT_H

#include <map>
#include <memory>
#include "fcore/library/text/words/Word.h"


namespace fcore
{
  using SharedWord = std::shared_ptr <Word>;
  using PairIdWord = std::pair <WordIdInt, SharedWord>;
  using SharedWordMap = std::shared_ptr <std::map <WordIdInt, SharedWord> >;


  // http://stackoverflow.com/a/13196986
  template <typename ... Args>
  SharedWord makeSharedWord(Args&& ... args)
  {
    return (std::make_shared <Word>(std::forward <Args>(args) ...));
  }


  template <typename ... Args>
  SharedWordMap makeSharedWordMap(Args&& ... args)
  {
    return (std::make_shared <std::map <WordIdInt, SharedWord> >(std::forward <Args>(args) ...));
  }


  class FragmentText
  {
  public:
    explicit FragmentText();

    virtual const SharedWordMap getFragmentText(
        WordIdInt fromWordId,
        WordIdInt toWordId) const = 0;
  };
}  // namespace fcore

#endif  // FCORE_TEXT_H
