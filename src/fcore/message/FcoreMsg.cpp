#include <string>
#include <iostream>
#include <fstream>

#include <kj/common.h>
#include <kj/memory.h>
#include <kj/mutex.h>
#include <kj/array.h>

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
        std::string errorMsg;
        if (std::string const* errMsgPtr = boost::get_error_info<ErrInfoMsg>(ex) ) {
            errorMsg += *errMsgPtr;
        }

        // TODO:
//        if (std::string const* filePathPtr = boost::get_error_info<ErrInfoFilePath>(ex) ) {
//            errorMsg += *filePathPtr;
//        }

        msgPtrR->setErrorFlag(true);
        msgPtrR->setMsgText(errorMsg);
    }

    return cpnPtrR;
}
