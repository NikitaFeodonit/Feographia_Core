#ifndef SENDERRORMSG_HPP
#define SENDERRORMSG_HPP

#include "fcore/message/FcoreMsg.hpp"


class SendErrorMsg : public FcoreMsg
{
public:
    explicit SendErrorMsg(boost::shared_ptr<FcMsg::Message::Reader> msgPtrQ) : FcoreMsg(msgPtrQ) {};

protected:
    boost::shared_ptr<capnp::AnyPointer::Builder> dataWorker(
            boost::shared_ptr<capnp::AnyPointer::Reader> dataPtrQ,
            boost::shared_ptr<FcMsg::Message::Builder> msgPtrR);

};

#endif // SENDERRORMSG_HPP
