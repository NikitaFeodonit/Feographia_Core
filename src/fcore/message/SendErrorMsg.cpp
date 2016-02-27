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

#include <boost/lexical_cast.hpp>

#include <iostream>

#include "fcore/FcoreLog.h"
#include "SendErrorMsg.h"


namespace fcore
{
  void SendErrorMsg::dataWorker(
      boost::shared_ptr <capnp::AnyPointer::Reader> dataPtrQ,
      boost::shared_ptr <FcMsg::Message::Builder>   msgPtrR)
  {
    // make the reply data
    std::string errorMsg = "ERROR: unknown message type: " + boost::lexical_cast <std::string>(
        mMsgPtrQ->getMsgType());
    BOOST_LOG_SEV(FcoreLog::log, debug) << errorMsg;

    // set the reply type and data
    msgPtrR->setMsgType(FcConst::MSG_TYPE_ERROR);
    msgPtrR->setErrorFlag(true);
    msgPtrR->setMsgText(errorMsg);
  }  // SendErrorMsg::dataWorker
}  // namespace fcore
