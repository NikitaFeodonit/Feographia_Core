/*
 * Project:  Feographia
 * Purpose:  Mobile application to work with the biblical text
 * Authors:  NikitaFeodonit, nfeodonit@yandex.com
 * ****************************************************************************
 * Copyright (C) 2015 NikitaFeodonit
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

#ifndef FCOREMSG_HPP
#define FCOREMSG_HPP

// TODO: place it
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/smart_ptr/make_shared_array.hpp>
#include <boost/exception/all.hpp>

#include <capnp/common.h>
#include <capnp/message.h>
#include <capnp/serialize.h>

#include "fcore/capnproto/FcMsg.capnp.h"
#include "fcore/capnproto/FcConst.capnp.h"


// TODO: place it
typedef boost::error_info<struct errInfoMsg_, std::string> ErrInfoMsg;
typedef boost::error_info<struct errInfoFilePath_,std::string> ErrInfoFilePath;
struct FileOpenError: virtual boost::exception { };
struct GetFileTextError: virtual boost::exception { };


class FcoreMsg
{
public:
    explicit FcoreMsg(boost::shared_ptr<FcMsg::Message::Reader> msgPtrQ);

    boost::shared_ptr<capnp::MallocMessageBuilder> msgWorker();

protected:
    virtual boost::shared_ptr<capnp::AnyPointer::Builder> dataWorker(
            boost::shared_ptr<capnp::AnyPointer::Reader> dataPtrQ,
            boost::shared_ptr<FcMsg::Message::Builder> msgPtrR) = 0;

    boost::shared_ptr<FcMsg::Message::Reader> mMsgPtrQ;
};

#endif // FCOREMSG_HPP
