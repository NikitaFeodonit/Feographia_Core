#ifndef FCOREMSG_HPP
#define FCOREMSG_HPP

// TODO: place it
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/smart_ptr/make_shared_array.hpp>
#include <boost/exception/all.hpp>

#include <capnp/common.h>
#include <capnp/message.h>
#include <capnp/serialize.h>

#include "fcore/capnproto/FcMsg.capnp.h"
#include "fcore/capnproto/FcConst.capnp.h"


// TODO: place it
typedef boost::error_info<struct errInfoMsg_, std::string> ErrInfoMsg;
typedef boost::error_info<struct errInfoFilePath_,std::string> ErrInfoFilePath;
struct FileOpenError: virtual boost::exception { };
struct GetFileTextError: virtual boost::exception { };


class FcoreMsg
{
public:
    explicit FcoreMsg(boost::shared_ptr<FcMsg::Message::Reader> msgPtrQ);

    boost::shared_ptr<capnp::MallocMessageBuilder> msgWorker();

protected:
    virtual boost::shared_ptr<capnp::AnyPointer::Builder> dataWorker(
            boost::shared_ptr<capnp::AnyPointer::Reader> dataPtrQ,
            boost::shared_ptr<FcMsg::Message::Builder> msgPtrR) = 0;

    boost::shared_ptr<FcMsg::Message::Reader> mMsgPtrQ;
};

#endif // FCOREMSG_HPP
