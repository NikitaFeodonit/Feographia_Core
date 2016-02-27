#ifndef FCORE_FCORELOG_H
#define FCORE_FCORELOG_H

#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>


namespace fcore
{
namespace logsrc = boost::log::sources;

  enum severity_level
  {
    trace, debug, info, warning, error, fatal
  };


  class FcoreLog
    : public logsrc::severity_logger_mt <severity_level>
  {
  public:
    static void initFcoreLog();

    static FcoreLog log;
  };
}  // namespace fcore


#endif  // FCORE_FCORELOG_H
