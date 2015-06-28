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
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/smart_ptr/make_shared_array.hpp>

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

#include "fcore.hpp"
#include "capnproto/fcore.capnp.h"


boost::shared_ptr<char[]> readFile(std::string path) {
    using namespace std;

    auto file = boost::make_shared<ifstream>(path, ios::in | ios::binary | ios::ate);

    if (file->is_open()) {
        streampos fileSize = file->tellg();
        size_t bufferSize = fileSize;

        auto buffer = boost::make_shared<char[]>(++bufferSize);

        file->seekg(0, ios::beg);
        file->read(buffer.get(), fileSize);
        buffer[fileSize] = 0; // terminate C-string by 0

//        cout << "buffer: " << *buffer << std::endl;
//        cout << "bufferSize: " << bufferSize << std::endl;

        return buffer;
        }

    else {
        cout << "Unable to open file, path: " << path;
        return nullptr;
        }
}


class FcoreMain
{
public:
        void operator()(zmq::context_t* zmqContext)
        {
            //  Prepare our context and socket
            zmq::socket_t socket (*zmqContext, ZMQ_PAIR);
            socket.bind ("inproc://fcore");

            while (true) {
                // receive the message
                zmq::message_t zmqMsgRequest;
                socket.recv (&zmqMsgRequest);


                // zmq message to capnp message
                capnp::word* msgWords = (capnp::word*) zmqMsgRequest.data();
                size_t msgSize = zmqMsgRequest.size() / sizeof(capnp::word);

                kj::DestructorOnlyArrayDisposer adp;
                kj::Array<capnp::word> msgArray(msgWords, msgSize, adp);
                kj::ArrayPtr<capnp::word> msgArrayP = msgArray.asPtr();
                capnp::FlatArrayMessageReader famr(msgArrayP);


                // read capnproto struct
                FCoreMessages::LoadFileReq::Reader reqReader = famr.getRoot<FCoreMessages::LoadFileReq>();

                std::string path = reqReader.getPath().cStr();
                std::cout << "path: " << path << std::endl;


                // read file
                std::cout << "file reading" << std::endl;
                auto fileText = readFile(path);


                // write new capnproto message
                capnp::MallocMessageBuilder capnpMsgBuilder;
                FCoreMessages::LoadFileRep::Builder replyBuilder = capnpMsgBuilder.initRoot<FCoreMessages::LoadFileRep>();
                replyBuilder.setText(nullptr == fileText ? "" : fileText.get());


                // capnproto message to zmq message
                kj::Array<capnp::word> words = messageToFlatArray(capnpMsgBuilder);
                kj::ArrayPtr<kj::byte> bytes = words.asBytes();

                void* msgReplyPtr = (void*) bytes.begin();
                size_t msgReplySize = bytes.size();


                // send zmq message
                zmq::message_t zmqMsgReply(msgReplySize);
                memcpy ((void *) zmqMsgReply.data (), msgReplyPtr, msgReplySize);

                socket.send (zmqMsgReply);
                std::cout << "Sended message" << std::endl;
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
