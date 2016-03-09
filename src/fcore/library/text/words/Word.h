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

#ifndef FCORE_WORD_H
#define FCORE_WORD_H

#include <string>

#include "fcore/library/text/util/TextId.h"
#include "fcore/utils/SharedPointers.h"


namespace fcore
{
  class Word
  {
  public:
    Word();
    Word(const Word& other);

    explicit Word(
        const WordIdInt id,
        const SharedString preSigns = nullptr,
        const SharedString word = nullptr,
        const SharedString postSigns = nullptr);

    virtual ~Word();

    const WordIdInt getId() const;
    const WordInVerseIdInt getWordInVerceId() const;
    const VerseIdInt getVerseId() const;
    const ChapterIdInt getChapterId() const;
    const BookIdInt getBookId() const;

    const SharedString getPreSigns() const;
    const SharedString getWordText() const;
    const SharedString getPostSigns() const;

  private:
    WordIdInt mId;
    SharedString mPreSigns;
    SharedString mWordText;
    SharedString mPostSigns;
  };


  using SharedWord = std::shared_ptr <Word>;


  template <typename ... Args>
  SharedWord makeSharedWord(Args&& ... args)
  {
    return (std::make_shared <Word>(std::forward <Args>(args) ...));
  }


  inline const WordIdInt Word::getId() const
  {
    return (mId);
  }


  inline const WordInVerseIdInt Word::getWordInVerceId() const
  {
    return (TextId::getWordInVerseId(getId()));
  }


  inline const VerseIdInt Word::getVerseId() const
  {
    return (TextId::getVerseId(getId()));
  }


  inline const ChapterIdInt Word::getChapterId() const
  {
    return (TextId::getChapterId(getId()));
  }


  inline const BookIdInt Word::getBookId() const
  {
    return (TextId::getBookId(getId()));
  }


  inline const SharedString Word::getPreSigns() const
  {
    return (mPreSigns);
  }


  inline const SharedString Word::getWordText() const
  {
    return (mWordText);
  }


  inline const SharedString Word::getPostSigns() const
  {
    return (mPostSigns);
  }
}  // namespace fcore

#endif  // FCORE_WORD_H
