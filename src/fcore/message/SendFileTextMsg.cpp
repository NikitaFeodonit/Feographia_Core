#include <string>
#include <iostream>
#include <fstream>

#include <kj/common.h>
#include <kj/memory.h>
#include <kj/mutex.h>
#include <kj/array.h>

#include "fcore/message/SendFileTextMsg.hpp"


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
        // TODO: boost logger
        std::cout << errorMsg << filePath << std::endl;

        // TODO:
        throw FileOpenError()
                << ErrInfoMsg(errorMsg)
                << ErrInfoFilePath(filePath);
    }
}


boost::shared_ptr<capnp::AnyPointer::Builder> SendFileTextMsg::dataWorker(
        boost::shared_ptr<capnp::AnyPointer::Reader> dataPtrQ,
        boost::shared_ptr<FcMsg::Message::Builder> msgPtrR)
{
    // get the query data
    FcMsg::GetFileTextQ::Reader dataQ = dataPtrQ->getAs<FcMsg::GetFileTextQ>();
    std::string path = dataQ.getFilePath().cStr();
    // TODO: boost logger
    std::cout << "filePath: " << path << std::endl;

    // make the reply data
    // read file
    // TODO: boost logger
    std::cout << "file reading" << std::endl;
    auto fileText = getFileText(path);

    // set the reply data
    if (nullptr != fileText) {
        capnp::AnyPointer::Builder dataPtrR = msgPtrR->initDataPointer();
        FcMsg::GetFileTextR::Builder dataR = dataPtrR.initAs<FcMsg::GetFileTextR>();
        dataR.setFileText(fileText.get());
    } else {
        // TODO:
        throw GetFileTextError() << ErrInfoMsg("getFileText() error");
    }
}
