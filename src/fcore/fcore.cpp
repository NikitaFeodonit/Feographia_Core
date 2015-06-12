/*******************************************************************************
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
 ******************************************************************************/

#include <boost/thread.hpp>
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

#include "fcore.hpp"
#include "capnproto/test.capnp.h"


class FcoreMain
{
public:
        void operator()(zmq::context_t* zmqContext)
        {
            //  Prepare our context and socket
            zmq::socket_t socket (*zmqContext, ZMQ_PAIR);
            socket.bind ("inproc://step3");

            while (true) {
                // receive the message
                zmq::message_t msgRequest;
                socket.recv (&msgRequest);


                // decompose message
                capnp::word* msgWords = (capnp::word*) msgRequest.data();
                size_t msgSize = msgRequest.size() / sizeof(capnp::word);

                kj::DestructorOnlyArrayDisposer adp;
                kj::Array<capnp::word> msgArray(msgWords, msgSize, adp);
                kj::ArrayPtr<capnp::word> msgArrayP = msgArray.asPtr();
                capnp::FlatArrayMessageReader famr(msgArrayP);


                // read capnproto struct
                Request::Reader reqReader = famr.getRoot<Request>();

                uint32_t id = reqReader.getId();
//                std::cout << "id " << id << std::endl;
                std::string name = reqReader.getName().cStr();
//                std::cout << "name " << name << std::endl;


                // write new capnproto struct
                capnp::MallocMessageBuilder cpMessageBuilder;

                Reply::Builder replyBuilder = cpMessageBuilder.initRoot<Reply>();
                replyBuilder.setIdReply(/*id +*/ 12);
                replyBuilder.setNameReply(/*name +*/ "FamilieMy");


                // send message
                kj::Array<capnp::word> words = messageToFlatArray(cpMessageBuilder);
                kj::ArrayPtr<kj::byte> bytes = words.asBytes();

                void* msgReplyPtr = (void*) bytes.begin();
                size_t msgReplySize = bytes.size();

                zmq::message_t msgReply (msgReplySize);
                memcpy ((void *) msgReply.data (), msgReplyPtr, msgReplySize);

                socket.send (msgReply);
//                std::cout << "Sended message" << std::endl;
                }
        }
};


void* fcoreRunMainThread()
{
    FcoreMain fcoreMain;
    zmq::context_t* zmqContext = new zmq::context_t(1);
    boost::thread fcoreMainThread(fcoreMain, zmqContext);

    return *zmqContext; // return zmqContext->ptr;
}
