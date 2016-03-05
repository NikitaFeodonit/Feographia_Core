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

#include "fcore/message/CreateTestModuleMsg.h"

#include "fcore/FcoreLog.h"
#include "fcore/utils/SharedPointers.h"
#include "fcore/library/text/sql/SqlModule.h"


namespace fcore
{
  CreateTestModuleMsg::CreateTestModuleMsg(const boost::shared_ptr <FcMsg::Message::Reader> msgPtrQ)
    : FcoreMsg(msgPtrQ)
  {}


  SharedString createTestModule(const std::string& modulePath)
  {
    SqlModule module;
    module.createTestSqlModule();
    return (makeSharedString("Test sql module is created."));
  }


  void CreateTestModuleMsg::dataWorker(
      boost::shared_ptr <capnp::AnyPointer::Reader> dataPtrQ,
      boost::shared_ptr <FcMsg::Message::Builder>   msgPtrR)
  {
    // get the query data
    FcMsg::CreateTestModuleQ::Reader dataQ = dataPtrQ->getAs <FcMsg::CreateTestModuleQ>();
    std::string                      modulePath = dataQ.getModulePath().cStr();
    BOOST_LOG_SEV(FcoreLog::log, debug) << "modulePath: " << modulePath;

    // make the reply data
    // read file
    BOOST_LOG_SEV(FcoreLog::log, debug) << "create test module";
    auto reportText = createTestModule(modulePath);

    // set the reply data
    if (reportText) {
      capnp::AnyPointer::Builder        dataPtrR = msgPtrR->initDataPointer();
      FcMsg::CreateTestModuleR::Builder dataR = dataPtrR.initAs <FcMsg::CreateTestModuleR>();
      dataR.setReportText(*reportText);
    }
    else {
      throw FcoreErrEx() << FcoreErrInfo("createTestModule() error, nullptr == reportText");
    }
  }  // CreateTestModuleMsg::dataWorker
}  // namespace fcore
