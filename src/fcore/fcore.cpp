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
#include <fstream>

#include "fcore.hpp"
#include "capnproto/fcore.capnp.h"


char* readFile(std::string path) {
    using namespace std;

    streampos size;
    char* memblock;

    ifstream file(path, ios::in | ios::binary | ios::ate);

    if (file.is_open()) {
        size = file.tellg();
        memblock = new char [size];
        file.seekg (0, ios::beg);
        file.read (memblock, size);
        file.close();

//        cout << "the entire file content is in memory" << std::endl;
        return memblock;

//        delete[] memblock;
        }

    else cout << "Unable to open file";

    return 0;
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
                FCoreMessages::LoadFileReq::Reader reqReader = famr.getRoot<FCoreMessages::LoadFileReq>();

                std::string path = reqReader.getPath().cStr();
                std::cout << "path: " << path << std::endl;


                // load file
                std::string text = "<html>test text</html>";
                std::cout << "file reading" << std::endl;
                char* fileText = readFile(path);
//                std::cout << "fileText: " << fileText << std::endl;


                // write new capnproto struct
                capnp::MallocMessageBuilder cpMessageBuilder;

                FCoreMessages::LoadFileRep::Builder replyBuilder = cpMessageBuilder.initRoot<FCoreMessages::LoadFileRep>();
                replyBuilder.setText(fileText);


                // send message
                kj::Array<capnp::word> words = messageToFlatArray(cpMessageBuilder);
                kj::ArrayPtr<kj::byte> bytes = words.asBytes();

                void* msgReplyPtr = (void*) bytes.begin();
                size_t msgReplySize = bytes.size();

                zmq::message_t msgReply (msgReplySize);
                memcpy ((void *) msgReply.data (), msgReplyPtr, msgReplySize);

                socket.send (msgReply);
                std::cout << "Sended message" << std::endl;

                delete[] fileText;
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
