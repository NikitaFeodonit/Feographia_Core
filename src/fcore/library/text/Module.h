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

#ifndef FCORE_MODULE_H
#define FCORE_MODULE_H

#include "fcore/library/text/words/FragmentText.h"
#include "fcore/library/text/words/sql/SqlFragmentText.h"
#include "fcore/library/text/fragments/Paragraph.h"


namespace fcore
{
  using SharedFragmentText = std::shared_ptr <FragmentText>;


  // http://stackoverflow.com/a/13196986
  template <typename ... Args>
  SharedFragmentText makeSharedFragmentText(Args&& ... args)
  {
    return (std::make_shared <FragmentText>(std::forward <Args>(args) ...));
  }


  class Module
  {
  public:
    explicit Module();

    virtual const SharedFragmentText getFragmentText() const = 0;
    SharedString getHtmlText(
        const WordIdInt fromWordId,
        const WordIdInt toWordId) const;

  private:
    // FragmentText

    // StrongNumbers
    // GreekProperties
    // InterlinearTranslations<Lang,InterlinearTranslation>
    // Versification

    // ParagraphTitles
  };
}  // namespace fcore

#endif  // FCORE_MODULE_H
