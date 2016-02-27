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

#include "fcore/library/text/Module.h"

#include "fcore/FcoreLog.h"


namespace fcore
{
  Module::Module() {}


  SharedString Module::getHtmlText(
      const WordIdInt fromWordId,
      const WordIdInt toWordId) const
  {
    SharedWordMap     pTextMap = getFragmentText()->getFragmentText(fromWordId, toWordId);
    int               currVerseId = 0;
    std::stringstream htmlText;

    for (auto it = pTextMap->begin(); it != pTextMap->end(); ++it) {
      // WordIdInt wordId = it->first;
      SharedWord   pWord = it->second;
      SharedString pPreSigns = pWord->getPreSigns();
      SharedString pWordText = pWord->getWordText();
      SharedString pPostSigns = pWord->getPostSigns();
      int          chapterId = pWord->getChapterId();
      int          verseId = pWord->getVerseId();
      int          wordInVerseId = pWord->getWordInVerceId();

      if (pWordText) {
        if (!currVerseId || (1 == wordInVerseId)) {
          if (currVerseId) {
            htmlText << "</div>\n";
          }
          currVerseId = verseId;
          htmlText << "<div id=\"verse_" << verseId << "\" class=\"verse\">";
          htmlText << "<b>" << chapterId << ":" << verseId << "</b>";
        }

        htmlText << " ";
        if (pPreSigns) {
          htmlText << *pPreSigns;
        }
        htmlText << *pWordText;
        if (pPostSigns) {
          htmlText << *pPostSigns;
        }
      }
    }

    if (currVerseId) {
      htmlText << "</div>\n";
    }

    BOOST_LOG_SEV(FcoreLog::log, debug) << "htmlText: " << htmlText.str();
    return (makeSharedString(htmlText.str()));
  }  // Module::getHtmlText
}  // namespace fcore
