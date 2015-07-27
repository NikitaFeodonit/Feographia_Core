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

#include "fcore.hpp"
#include "capnproto/FcMsg.capnp.h"
#include "capnproto/FcConst.capnp.h"


typedef boost::error_info<struct errInfoMsg_, std::string> ErrInfoMsg;
typedef boost::error_info<struct errInfoFilePath_,std::string> ErrInfoFilePath;
struct FileOpenError: virtual boost::exception { };
struct GetFileTextError: virtual boost::exception { };


class FcoreMain
{
public:
    void operator()(zmq::context_t* zmqContext)
    {
        // Prepare zmq socket
        zmq::socket_t socket (*zmqContext, ZMQ_PAIR);
        socket.bind(FcConst::INPROC_FCORE.get().cStr());

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
            boost::shared_ptr<capnp::MallocMessageBuilder> cpnReply;

            // work the query by the query type
            switch (msgQ.getMsgType()) {

                case FcConst::MSG_TYPE_GET_FILE_TEXT: {
                    capnp::AnyPointer::Reader dataPtrQ = msgQ.getDataPointer();
                    cpnReply = sendGetFileTextR(dataPtrQ.getAs<FcMsg::GetFileTextQ>());
                    break;
                }

                default:
                    std::string errorMsg = "ERROR: unknown message type: " + msgQ.getMsgType();
                    std::cout << errorMsg << std::endl;
                    cpnReply = sendErrorMsgR(errorMsg);
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
    boost::shared_ptr<capnp::MallocMessageBuilder> sendErrorMsgR(std::string errorMsg)
    {
        // the new capnproto reply
        auto cpnReply = boost::make_shared<capnp::MallocMessageBuilder>();
        FcMsg::Message::Builder msgR = cpnReply->initRoot<FcMsg::Message>();

        // set the reply type
        msgR.setMsgType(FcConst::MSG_TYPE_ERROR);
        msgR.setErrorFlag(true);
        msgR.setMsgText(errorMsg);

        return cpnReply;
    }


    boost::shared_ptr<capnp::MallocMessageBuilder> sendGetFileTextR(FcMsg::GetFileTextQ::Reader dataQ)
    {
        // get the query data
        std::string path = dataQ.getFilePath().cStr();
        std::cout << "filePath: " << path << std::endl;

        // the new capnproto reply
        auto cpnReply = boost::make_shared<capnp::MallocMessageBuilder>();
        FcMsg::Message::Builder msgR = cpnReply->initRoot<FcMsg::Message>();

        // set the reply type
        msgR.setMsgType(FcConst::MSG_TYPE_GET_FILE_TEXT);

        try {
            // make the reply data
            // read file
            std::cout << "file reading" << std::endl;
            auto fileText = getFileText(path);

            // set the reply data
            if (nullptr != fileText) {
                capnp::AnyPointer::Builder dataPtrR = msgR.initDataPointer();
                FcMsg::GetFileTextR::Builder dataR = dataPtrR.initAs<FcMsg::GetFileTextR>();
                dataR.setFileText(fileText.get());
            } else {
                throw GetFileTextError() << ErrInfoMsg("getFileText() error");
            }

        } catch (boost::exception& ex) {
            // set the error reply data
            std::string errorMsg;
            if (std::string const* errMsgPtr = boost::get_error_info<ErrInfoMsg>(ex) ) {
                errorMsg += *errMsgPtr;
            }
            if (std::string const* filePathPtr = boost::get_error_info<ErrInfoFilePath>(ex) ) {
                errorMsg += *filePathPtr;
            }
            msgR.setErrorFlag(true);
            msgR.setMsgText(errorMsg);
        }

        return cpnReply;
    }


    boost::shared_ptr<char[]> getFileText(std::string filePath)
    {
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
            std::string errorMsg = "Unable to open file, file path: ";
            std::cout << errorMsg << filePath << std::endl;
            throw FileOpenError()
                    << ErrInfoMsg(errorMsg)
                    << ErrInfoFilePath(filePath);
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
