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

#include "fcore/message/GetFragmentTextMsg.h"

#include "fcore/FcoreLog.hpp"
#include "fcore/library/text/util/SharedPointers.h"
#include "fcore/library/text/util/TextId.h"
#include "fcore/library/text/sql/SqlModule.h"


namespace fcore
{
  GetFragmentTextMsg::GetFragmentTextMsg(const boost::shared_ptr <FcMsg::Message::Reader> msgPtrQ)
    : FcoreMsg(msgPtrQ)
  {}


  SharedString getFragmentText(
      const WordIdInt fromWordId,
      const WordIdInt toWordId)
  {
    SqlModule module;
    return (module.getHtmlText(fromWordId, toWordId));
  }


  void GetFragmentTextMsg::dataWorker(
      boost::shared_ptr <capnp::AnyPointer::Reader> dataPtrQ,
      boost::shared_ptr <FcMsg::Message::Builder>   msgPtrR)
  {
    // get the query data
    FcMsg::GetFragmentTextQ::Reader dataQ = dataPtrQ->getAs <FcMsg::GetFragmentTextQ>();

    FcMsg::Reference::Reader fromReference = dataQ.getFromReference();
    std::string              fromOsisBookIdStr(fromReference.getBookId().cStr());
    SharedString             fromOsisBookId = makeSharedString(fromOsisBookIdStr);
//      SharedString fromOsisBookId = makeSharedString(fromReference.getBookId().cStr());
    ChapterIdInt     fromChapterId = fromReference.getChapterId();
    VerseIdInt       fromVerseId = fromReference.getVerseId();
    WordInVerseIdInt fromWordInVerseId = fromReference.getWordInVerseId();
    // TODO: get fromBookId from fromOsisBookId
    WordIdInt fromWordId = TextId::getWordId(52, fromChapterId, fromVerseId, fromWordInVerseId);

    FcMsg::Reference::Reader toReference = dataQ.getToReference();
    std::string              toOsisBookIdStr(toReference.getBookId().cStr());
    SharedString             toOsisBookId = makeSharedString(toOsisBookIdStr);
//      SharedString toOsisBookId = makeSharedString(toReference.getBookId().cStr());
    ChapterIdInt     toChapterId = toReference.getChapterId();
    VerseIdInt       toVerseId = toReference.getVerseId();
    WordInVerseIdInt toWordInVerseId = toReference.getWordInVerseId();
    // TODO: get toBookId from toOsisBookId
    WordIdInt toWordId = TextId::getWordId(52, toChapterId, toVerseId, toWordInVerseId);

    BOOST_LOG_SEV(FcoreLog::log,
        debug) << "from reference - bookId: " << fromOsisBookIdStr << ", chapterId: "
               << fromChapterId << ", verseId: " << fromVerseId << ", wordId: "
               << fromWordInVerseId;
    BOOST_LOG_SEV(FcoreLog::log,
        debug) << "to reference - bookId: " << toOsisBookIdStr << ", chapterId: " << toChapterId
               << ", verseId: " << toVerseId << ", wordId: " << toWordInVerseId;

    // make the reply data
    // read file
    BOOST_LOG_SEV(FcoreLog::log, debug) << "get fragment text";
    auto pFragmentText = getFragmentText(fromWordId, toWordId);

    // set the reply data
    if (pFragmentText) {
      BOOST_LOG_SEV(FcoreLog::log, debug) << "pFragmentText: " << *pFragmentText;
      capnp::AnyPointer::Builder       dataPtrR = msgPtrR->initDataPointer();
      FcMsg::GetFragmentTextR::Builder dataR = dataPtrR.initAs <FcMsg::GetFragmentTextR>();
      dataR.setFragmentText(*pFragmentText);
    }
    else {
      throw FcoreErrEx() << FcoreErrInfo("getFragmentText() error, nullptr == pFragmentText");
    }
  }  // GetFragmentTextMsg::dataWorker
}  // namespace fcore
