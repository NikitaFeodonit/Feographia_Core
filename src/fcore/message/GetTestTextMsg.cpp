/*
 * Project:  Feographia
 * Purpose:  Mobile application to work with the biblical text
 * Authors:  NikitaFeodonit, nfeodonit@yandex.com
 * ****************************************************************************
 * Copyright (C) 2015-2016 NikitaFeodonit
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
 */

#include "fcore/message/GetTestTextMsg.h"

#include "fcore/FcoreLog.hpp"
#include "fcore/library/text/util/SharedPointers.h"


std::string* bigStr = nullptr;

std::string* getBigStr()
{
    std::string* src = new std::string("abcdefghi "); // 10 chars
    std::string* dst = new std::string();

    for (int i = 0; i < 100000; ++i) { // 10 * 100 000 = 1 000 000 chars
        *dst += *src;
    }

    return dst;
}


void Deleter(std::string* ptr)
{}


fcore::SharedString getBigTestText(const std::string& testPath)
{
    if (nullptr == bigStr) {
        bigStr = getBigStr();
        BOOST_LOG_SEV(FcoreLog::log, debug) << "big str created.";
    }
    std::shared_ptr<std::string> str(bigStr, Deleter);

    return str;
}


fcore::SharedString getTestText(const std::string& testPath)
{
    auto str = fcore::makeSharedString("test text");
    return str;
}


void GetTestTextMsg::dataWorker(
        boost::shared_ptr<capnp::AnyPointer::Reader> dataPtrQ,
        boost::shared_ptr<FcMsg::Message::Builder> msgPtrR)
{
    // get the query data
    FcMsg::GetTestTextQ::Reader dataQ = dataPtrQ->getAs<FcMsg::GetTestTextQ>();
    std::string testPath = dataQ.getTestPath().cStr();
//    BOOST_LOG_SEV(FcoreLog::log, debug) << "testPath: " << testPath;

    // make the reply data
    // get test text
//    BOOST_LOG_SEV(FcoreLog::log, debug) << "get test text";

//    auto testText = getTestText(testPath);
    auto testText = getBigTestText(testPath);

//    BOOST_LOG_SEV(FcoreLog::log, debug) << "test text: " << testText->c_str();
//    BOOST_LOG_SEV(FcoreLog::log, debug) << "c++ byte size: " << testText->size();

    // set the reply data
    if (nullptr != testText) {
        capnp::AnyPointer::Builder dataPtrR = msgPtrR->initDataPointer();
        FcMsg::GetTestTextR::Builder dataR = dataPtrR.initAs<FcMsg::GetTestTextR>();
        dataR.setTestText(testText->c_str());
    } else {
        throw FcoreErrEx() << FcoreErrInfo("getTestText() error, nullptr == testText");
    }
}
