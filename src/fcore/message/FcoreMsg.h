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

#ifndef FCORE_FCOREMSG_H
#define FCORE_FCOREMSG_H

#include <boost/smart_ptr/make_shared.hpp>
#include <boost/exception/all.hpp>

#include <capnp/message.h>

#include "fcore/capnproto/FcMsg.capnp.h"
#include "fcore/capnproto/FcConst.capnp.h"


typedef boost::error_info <struct errInfoMsg_, std::string> FcoreErrInfo;
struct FcoreErrEx
  : virtual boost::exception {};


namespace fcore
{
  class FcoreMsg
  {
  public:
    explicit FcoreMsg(boost::shared_ptr <FcMsg::Message::Reader> msgPtrQ);

    boost::shared_ptr <capnp::MallocMessageBuilder> msgWorker();

  protected:
    virtual void dataWorker(
        boost::shared_ptr <capnp::AnyPointer::Reader> dataPtrQ,
        boost::shared_ptr <FcMsg::Message::Builder>   msgPtrR) = 0;

    boost::shared_ptr <FcMsg::Message::Reader> mMsgPtrQ;
  };
}  // namespace fcore

#endif  // FCORE_FCOREMSG_H
