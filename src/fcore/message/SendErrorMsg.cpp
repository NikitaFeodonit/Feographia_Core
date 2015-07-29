#include <boost/lexical_cast.hpp>

#include <string>
#include <iostream>
#include <fstream>

#include <kj/common.h>
#include <kj/memory.h>
#include <kj/mutex.h>
#include <kj/array.h>

#include "fcore/message/SendErrorMsg.hpp"


boost::shared_ptr<capnp::AnyPointer::Builder> SendErrorMsg::dataWorker(
        boost::shared_ptr<capnp::AnyPointer::Reader> dataPtrQ,
        boost::shared_ptr<FcMsg::Message::Builder> msgPtrR)
{
    // make the reply data
    std::string errorMsg = "ERROR: unknown message type: " + boost::lexical_cast<std::string>(mMsgPtrQ->getMsgType());
    // TODO: boost logger
    std::cout << errorMsg << std::endl;

    // set the reply type and data
    msgPtrR->setMsgType(FcConst::MSG_TYPE_ERROR);
    msgPtrR->setErrorFlag(true);
    msgPtrR->setMsgText(errorMsg);
}
