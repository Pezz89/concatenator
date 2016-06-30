#include <boost/log/common.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/log/trivial.hpp>
#include <iostream>

#include "Logger.h"

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", int)

Logger::Logger() {
    Logger::sink = boost::make_shared<text_sink>();

    boost::shared_ptr<std::ostream> stdout_stream{&std::clog, boost::null_deleter{}};
    Logger::sink->locked_backend()->add_stream(stdout_stream);

    /*
    add_file_log
    (
        keywords::file_name = "concatenator_%N.log",
        keywords::rotation_size = 10 * 1024 * 1024,
        keywords::format = (
            expr::stream << 
            "[" << 
            expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S") <<
            "] [" <<
            Logger::severity_levels[severity] <<
            "] --- "
        )
    );
    */
    Logger::sink->set_formatter(&Logger::formatter);

    logging::add_common_attributes();
    Logger::sink->set_filter(severity > 0);

    logging::core::get()->add_sink(Logger::sink);

};

void Logger::formatter(logging::record_view const& rec, logging::formatting_ostream& strm)
{
    // Get the LineID attribute value and put it into the stream
    strm << logging::extract< unsigned int >("LineID", rec) << ": ";

    // The same for the severity level.
    // The simplified syntax is possible if attribute keywords are used.
    strm << "<" << rec[logging::trivial::severity] << "> ";

    // Finally, put the record message to the stream
    strm << rec[expr::smessage];
}

void Logger::error(std::string str) {
    BOOST_LOG_SEV(lg, 2) << str;
    Logger::sink->flush(); 
}

void Logger::info(std::string str) {
    BOOST_LOG_SEV(lg, 0) << str;
    Logger::sink->flush(); 
}

void Logger::warning(std::string str) {
    BOOST_LOG_SEV(lg, 1) << str;
    Logger::sink->flush(); 
}

