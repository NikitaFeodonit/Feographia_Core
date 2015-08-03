#ifndef FCORELOG_HPP
#define FCORELOG_HPP

#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>


namespace logsrc = boost::log::sources;

enum severity_level
{
    trace,
    debug,
    info,
    warning,
    error,
    fatal
};


class FcoreLog : public logsrc::severity_logger_mt< severity_level >
{
public:
    static void initFcoreLog();
    static FcoreLog log;
};


#endif // FCORELOG_HPP
