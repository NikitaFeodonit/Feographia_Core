#ifndef SENDFILETEXTMSG_HPP
#define SENDFILETEXTMSG_HPP

#include "fcore/message/FcoreMsg.hpp"


class SendFileTextMsg : public FcoreMsg
{
public:
    explicit SendFileTextMsg(boost::shared_ptr<FcMsg::Message::Reader> msgPtrQ) : FcoreMsg(msgPtrQ) {};

protected:
    boost::shared_ptr<capnp::AnyPointer::Builder> dataWorker(
            boost::shared_ptr<capnp::AnyPointer::Reader> dataPtrQ,
            boost::shared_ptr<FcMsg::Message::Builder> msgPtrR);
};

#endif // SENDFILETEXTMSG_HPP
