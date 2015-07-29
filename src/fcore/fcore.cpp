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

#include <boost/thread.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/smart_ptr/make_shared_array.hpp>
#include <boost/exception/all.hpp>

#include <zmq.hpp>

#include <capnp/common.h>
#include <capnp/message.h>
#include <capnp/serialize.h>

#include <kj/common.h>
#include <kj/memory.h>
#include <kj/mutex.h>
#include <kj/array.h>

#include <string>
#include <iostream>
#include <fstream>

#include "fcore/capnproto/FcMsg.capnp.h"
#include "fcore/capnproto/FcConst.capnp.h"

#include "fcore/message/SendErrorMsg.hpp"
#include "fcore/message/SendFileTextMsg.hpp"
#include "fcore/Fcore.hpp"


class FcoreMain
{
public:
    void operator()(zmq::context_t* zmqContext)
    {
        // Prepare zmq socket
        zmq::socket_t socket (*zmqContext, ZMQ_PAIR);
        socket.bind(FcConst::INPROC_FCORE->cStr());

        while (true) {
            // receive the query
            zmq::message_t zmqQuery;
            socket.recv(&zmqQuery);


            // zmq query to the capnp query
            capnp::word* queryWords = (capnp::word*) zmqQuery.data();
            size_t querySize = zmqQuery.size() / sizeof(capnp::word);

            kj::DestructorOnlyArrayDisposer adp;
            kj::Array<capnp::word> msgArray(queryWords, querySize, adp);
            kj::ArrayPtr<capnp::word> arrayPtrQ = msgArray.asPtr();
            capnp::FlatArrayMessageReader cpnQuery(arrayPtrQ);


            // read the capnproto struct
            FcMsg::Message::Reader msgQ = cpnQuery.getRoot<FcMsg::Message>();
            auto msgPtrQ = boost::make_shared<FcMsg::Message::Reader>(msgQ);

            // the new capnproto reply
            boost::shared_ptr<capnp::MallocMessageBuilder> cpnReply;

            // work the query by the query type
            switch (msgPtrQ->getMsgType()) {

                case FcConst::MSG_TYPE_GET_FILE_TEXT: {
                    SendFileTextMsg sendFileTextMsg(msgPtrQ);
                    cpnReply = sendFileTextMsg.msgWorker();
                    break;
                }

                default: {
                    SendErrorMsg sendErrorMsgmsg(msgPtrQ);
                    cpnReply = sendErrorMsgmsg.msgWorker();
                    break;
                }
            }


            // send the reply
            if (nullptr != cpnReply) {
                // capnproto message to the zmq message
                kj::Array<capnp::word> replyWords = messageToFlatArray(*cpnReply);
                kj::ArrayPtr<kj::byte> replyBytes = replyWords.asBytes();

                void* replyBytesPtr = (void*) replyBytes.begin();
                size_t replySize = replyBytes.size();


                // send the zmq reply
                zmq::message_t zmqReply(replySize);
                memcpy ((void *) zmqReply.data (), replyBytesPtr, replySize);

                bool result = socket.send (zmqReply);
                // TODO: boost logger
                std::cout << (result ? "Sended message" : "Send message failed") << std::endl;
            }
        }
    }
};


void* fcoreRunMainThread()
{
    FcoreMain fcoreMain;
    // Prepare zmq context
    zmq::context_t* zmqContext = new zmq::context_t(1);
    boost::thread fcoreMainThread(fcoreMain, zmqContext);

    return *zmqContext; // return zmqContext->ptr;
}
