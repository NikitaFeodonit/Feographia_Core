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
#include "capnproto/FcMsg.capnp.h"
#include "capnproto/FcConst.capnp.h"


const char* INPROC_FCORE = "inproc://fcore";

const int32_t MSG_TYPE_GET_FILE_TEXT = 9999;


class FcoreMain
{
public:
    void operator()(zmq::context_t* zmqContext)
    {
        // Prepare zmq socket
        zmq::socket_t socket (*zmqContext, ZMQ_PAIR);
        socket.bind(INPROC_FCORE);

        while (true) {
            // receive the query
            zmq::message_t zmqQuery;
            socket.recv(&zmqQuery);


            // zmq query to the capnp query
            capnp::word* queryWords = (capnp::word*) zmqQuery.data();
            size_t querySize = zmqQuery.size() / sizeof(capnp::word);

            kj::DestructorOnlyArrayDisposer adp;
            kj::Array<capnp::word> msgArray(queryWords, querySize, adp);
            kj::ArrayPtr<capnp::word> queryArrayP = msgArray.asPtr();
            capnp::FlatArrayMessageReader cpnQuery(queryArrayP);


            // read the capnproto struct
            FcMsg::Message::Reader message = cpnQuery.getRoot<FcMsg::Message>();
            boost::shared_ptr<capnp::MallocMessageBuilder> cpnReply;

            // work the query by the query type
            switch (message.getType()) {

                case MSG_TYPE_GET_FILE_TEXT: {
                    capnp::AnyPointer::Reader dataPointer = message.getDataPointer();
                    cpnReply = sendGetFileTextR(dataPointer.getAs<FcMsg::GetFileTextQ>());
                    break;
                }

                default:
                    // TODO: send error msg
                    cpnReply = nullptr;
                    ;
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
                std::cout << (result ? "Sended message" : "Send message failed") << std::endl;
            }
        }
    }


protected:
    boost::shared_ptr<capnp::MallocMessageBuilder> sendGetFileTextR(FcMsg::GetFileTextQ::Reader queryData) {
        // get the query data
        std::string path = queryData.getFilePath().cStr();
        std::cout << "filePath: " << path << std::endl;


        // make the reply data
        // read file
        std::cout << "file reading" << std::endl;
        auto fileText = getFileText(path);


        // the new capnproto reply
        auto cpnReply = boost::make_shared<capnp::MallocMessageBuilder>();
        FcMsg::GetFileTextR::Builder replyData = cpnReply->initRoot<FcMsg::GetFileTextR>();


        // set the reply data
        // TODO: work Ex
        if (nullptr != fileText) {
            replyData.setFileText(fileText.get());
        } else {
            replyData.setFileText(""); // TODO: setText(Ex.getText())
            replyData.setIsError(true);
        }

        return cpnReply;
    }


    boost::shared_ptr<char[]> getFileText(std::string filePath) {
        auto file = boost::make_shared<std::ifstream>(filePath, std::ios::in | std::ios::binary | std::ios::ate);

        if (file->is_open()) {
            std::streampos fileSize = file->tellg();
            size_t bufferSize = fileSize;

            auto buffer = boost::make_shared<char[]>(++bufferSize);

            file->seekg(0, std::ios::beg);
            file->read(buffer.get(), fileSize);
            buffer[fileSize] = 0; // terminate C-string by 0

            return buffer;
        }

        else {
            std::string error = "Unable to open file, path: " + filePath;
            std::cout << error << std::endl;
            return nullptr; // TODO: throw Ex(error)
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
