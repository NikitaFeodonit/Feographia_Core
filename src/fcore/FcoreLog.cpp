#include <boost/core/null_deleter.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/expressions/formatters/date_time.hpp>
#include <boost/log/expressions/keyword.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>


#include "fcore/FcoreLog.hpp"


namespace boostlog = boost::log;
namespace logsrc = boost::log::sources;
namespace logexpr = boost::log::expressions;
namespace logsinks = boost::log::sinks;
namespace logkeys = boost::log::keywords;
namespace logattrs = boost::log::attributes;

BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", severity_level)
BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "TimeStamp", boost::posix_time::ptime)


FcoreLog FcoreLog::log;


// The operator puts a human-friendly representation of the severity level to the stream
std::ostream& operator<< (std::ostream& strm, severity_level level)
{
    static const char* strings[] =
    {
        "TRACE",
        "DEBUG",
        "INFO",
        "WARNING",
        "ERROR",
        "FATAL"
    };

    if (static_cast< std::size_t >(level) < sizeof(strings) / sizeof(*strings))
        strm << strings[level];
    else
        strm << static_cast< int >(level);

    return strm;
}


void FcoreLog::initFcoreLog()
{
    boostlog::add_common_attributes();

    // Construct the sink
    typedef logsinks::synchronous_sink< logsinks::text_ostream_backend > text_sink;
    boost::shared_ptr< text_sink > sink = boost::make_shared< text_sink >();

    // We have to provide an empty deleter to avoid destroying the global stream object
    boost::shared_ptr< std::ostream > stream(&std::cout, boost::null_deleter());
    sink->locked_backend()->add_stream(stream);

                         sink->set_formatter(
                             logexpr::format("FC: %1% [%2%] %3%")
                             % timestamp
                             % severity
                             % logexpr::smessage
                             );

    // Register the sink in the logging core
    boostlog::core::get()->add_sink(sink);
}
