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

#include "fcore/Fcore.h"

#include <boost/thread.hpp>
#include <boost/smart_ptr/make_shared.hpp>

#include <capnp/serialize.h>

#include "fcore/capnproto/FcMsg.capnp.h"
#include "fcore/capnproto/FcConst.capnp.h"

#include "fcore/message/SendErrorMsg.h"
#include "fcore/message/SendFileTextMsg.h"
#include "fcore/message/CreateTestModuleMsg.h"
#include "fcore/message/GetFragmentTextMsg.h"
#include "fcore/message/GetTestTextMsg.h"


namespace fcore
{
  Fcore::Fcore() {}


  void Fcore::fcoreInit()
  {
    std::cout << "logger initialization" << std::endl;
    FcoreLog::initFcoreLog();
    BOOST_LOG_SEV(FcoreLog::log, info) << "logger is initialized";
  }


  kj::Array <capnp::word> Fcore::messageWorker(
      void*         segmentsPtrsQ,
      long long int segmentsSizesQ)
  {
    // to the capnp query
    capnp::word* queryWords = static_cast <capnp::word*>(segmentsPtrsQ);
    size_t       querySize = segmentsSizesQ / sizeof(capnp::word);

    kj::DestructorOnlyArrayDisposer adp;
    kj::Array <capnp::word>         msgArray(queryWords, querySize, adp);
    kj::ArrayPtr <capnp::word>      arrayPtrQ = msgArray.asPtr();
    capnp::FlatArrayMessageReader   cpnQuery(arrayPtrQ);


    // read the capnproto struct
    FcMsg::Message::Reader msgQ = cpnQuery.getRoot <FcMsg::Message>();
    auto                   msgPtrQ = boost::make_shared <FcMsg::Message::Reader>(msgQ);

    // the new capnproto reply
    boost::shared_ptr <capnp::MallocMessageBuilder> cpnReply;

    // work the query by the query type
    switch (msgPtrQ->getMsgType()) {
        case FcConst::MSG_TYPE_GET_FRAGMENT_TEXT: {
          GetFragmentTextMsg msg(msgPtrQ);
          cpnReply = msg.msgWorker();
          break;
        }

        case FcConst::MSG_TYPE_CREATE_TEST_MODULE: {
          CreateTestModuleMsg msg(msgPtrQ);
          cpnReply = msg.msgWorker();
          break;
        }

        case FcConst::MSG_TYPE_GET_FILE_TEXT: {
          SendFileTextMsg msg(msgPtrQ);
          cpnReply = msg.msgWorker();
          break;
        }

        case FcConst::MSG_TYPE_GET_TEST_TEXT: {
          GetTestTextMsg msg(msgPtrQ);
          cpnReply = msg.msgWorker();
          break;
        }

        default: {
          SendErrorMsg msg(msgPtrQ);
          cpnReply = msg.msgWorker();
          break;
        }
    }  // switch


    // send the reply
    if (nullptr != cpnReply) {
      // capnproto message to the serialization
      kj::Array <capnp::word> replyWords = messageToFlatArray(*cpnReply);
      return (kj::mv(replyWords));
    }

    kj::Array <capnp::word> empty = kj::heapArray <capnp::word>(0);
    return (kj::mv(empty));
  }  // Fcore::messageWorker
}  // namespace fcore
