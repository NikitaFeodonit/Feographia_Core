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

#include <string>
#include <iostream>
#include <fstream>

#include <capnp/message.h>

#include "fcore/message/FcoreMsg.hpp"


FcoreMsg::FcoreMsg(boost::shared_ptr<FcMsg::Message::Reader> msgPtrQ)
{
    mMsgPtrQ = msgPtrQ;
}


boost::shared_ptr<capnp::MallocMessageBuilder> FcoreMsg::msgWorker()
{
    // the new capnproto reply
    auto cpnPtrR = boost::make_shared<capnp::MallocMessageBuilder>();
    auto msgPtrR = boost::make_shared<FcMsg::Message::Builder>(cpnPtrR->initRoot<FcMsg::Message>());

    // set the reply type
    msgPtrR->setMsgType(mMsgPtrQ->getMsgType());

    try {
        // get the query data
        auto dataPtrQ = boost::make_shared<capnp::AnyPointer::Reader>(mMsgPtrQ->getDataPointer());
        // make and set the reply data
        dataWorker(dataPtrQ, msgPtrR);

    } catch (boost::exception& ex) {
        // set the error reply data
        std::string errInfo;
        if (std::string const* errInfoPtr = boost::get_error_info<FcoreErrInfo>(ex) ) {
            errInfo += *errInfoPtr;
        }

        msgPtrR->setErrorFlag(true);
        msgPtrR->setMsgText(errInfo);
    }

    return cpnPtrR;
}
