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

#ifndef FCORE_TEXTDEFS_H
#define FCORE_TEXTDEFS_H

#include <string>
#include <cstdint>

#include "boost/smart_ptr/shared_ptr.hpp"
#include "boost/smart_ptr/make_shared_object.hpp"
#include "fcore/capnproto/FcConst.capnp.h"


namespace fcore
{
  using WordInVerseIdInt = std::uint8_t;    // max  90 per verse
  using VerseIdInt = std::uint8_t;          // max 176 per chapter
  using ChapterIdInt = std::uint8_t;        // max 150 per book
  using BookIdInt = std::uint8_t;           // max  77 per module
  using WordIdInt = std::uint32_t;
  using FragmentIdInt = std::uint64_t;      // BookIdInt must be < 128 for cast to signed INTEGER of sqlite


  class TextId
  {
  public:
    static const std::uint8_t UNKNOWN_ID = FcConst::UNKNOWN_ID;

    static const WordInVerseIdInt getWordInVerseId(WordIdInt wordId);
    static const VerseIdInt getVerseId(WordIdInt wordId);
    static const ChapterIdInt getChapterId(WordIdInt wordId);
    static const BookIdInt getBookId(WordIdInt wordId);

    static const WordIdInt getFromWordId(FragmentIdInt fragmentId);
    static const WordIdInt getToWordId(FragmentIdInt fragmentId);

    static const WordIdInt getWordId(
        BookIdInt        bookId,
        ChapterIdInt     chapterId,
        VerseIdInt       verseId,
        WordInVerseIdInt wordInVerseId);

    static const FragmentIdInt getWordId(
        WordIdInt fromWord,
        WordIdInt toWord);

  private:
    struct SizeOfIdInt
    {
      static const int WORD_IN_VERSE = sizeof(WordInVerseIdInt) * 8;
      static const int VERSE = sizeof(VerseIdInt) * 8;
      static const int CHAPTER = sizeof(ChapterIdInt) * 8;
      static const int BOOK = sizeof(BookIdInt) * 8;

      static const int WORD = sizeof(WordIdInt) * 8;
      static const int FRAGMENT = sizeof(FragmentIdInt) * 8;
    };


    struct IdMask
    {
      static const WordIdInt WORD_IN_VERSE = ~(~0u << SizeOfIdInt::WORD_IN_VERSE);
      static const WordIdInt VERSE = ~(~0u << SizeOfIdInt::VERSE) << SizeOfIdInt::WORD_IN_VERSE;
      static const WordIdInt CHAPTER = (~(~0u << (SizeOfIdInt::CHAPTER)))
          << (SizeOfIdInt::VERSE + SizeOfIdInt::WORD_IN_VERSE);
      static const WordIdInt BOOK = (~(~0u << (SizeOfIdInt::BOOK)))
          << (SizeOfIdInt::CHAPTER + SizeOfIdInt::VERSE + SizeOfIdInt::WORD_IN_VERSE);

      static const FragmentIdInt FROM_WORD = ~0u >> SizeOfIdInt::WORD;
      static const FragmentIdInt TO_WORD = ~0u << SizeOfIdInt::WORD;
    };
  };


  inline const WordInVerseIdInt TextId::getWordInVerseId(WordIdInt wordId)
  {
    return (static_cast <WordInVerseIdInt>(wordId & IdMask::WORD_IN_VERSE));
  }


  inline const VerseIdInt TextId::getVerseId(WordIdInt wordId)
  {
    return (static_cast <VerseIdInt>((wordId& IdMask::VERSE) >> SizeOfIdInt::WORD_IN_VERSE));
  }


  inline const ChapterIdInt TextId::getChapterId(WordIdInt wordId)
  {
    return (static_cast <ChapterIdInt>((wordId& IdMask::CHAPTER)
        >> (SizeOfIdInt::VERSE + SizeOfIdInt::WORD_IN_VERSE)));
  }


  inline const BookIdInt TextId::getBookId(WordIdInt wordId)
  {
    return (static_cast <BookIdInt>((wordId& IdMask::BOOK)
        >> (SizeOfIdInt::CHAPTER + SizeOfIdInt::VERSE + SizeOfIdInt::WORD_IN_VERSE)));
  }


  inline const WordIdInt TextId::getFromWordId(FragmentIdInt fragmentId)
  {
    return (static_cast <WordIdInt>(fragmentId & IdMask::FROM_WORD));
  }


  inline const WordIdInt TextId::getToWordId(FragmentIdInt fragmentId)
  {
    return (static_cast <WordIdInt>((fragmentId& IdMask::TO_WORD) >> SizeOfIdInt::WORD));
  }


  inline const WordIdInt TextId::getWordId(
      BookIdInt        bookId,
      ChapterIdInt     chapterId,
      VerseIdInt       verseId,
      WordInVerseIdInt wordInVerseId)
  {
    WordIdInt wordId = bookId;
    wordId = (wordId << SizeOfIdInt::BOOK) + chapterId;
    wordId = (wordId << SizeOfIdInt::CHAPTER) + verseId;
    wordId = (wordId << SizeOfIdInt::VERSE) + wordInVerseId;
    return (wordId);
  }


  inline const FragmentIdInt TextId::getWordId(
      WordIdInt fromWord,
      WordIdInt toWord)
  {
    FragmentIdInt fragmentId = toWord;
    fragmentId = (fragmentId << SizeOfIdInt::WORD) + fromWord;
    return (fragmentId);
  }
}  // namespace fcore


#endif  // FCORE_TEXTDEFS_H
