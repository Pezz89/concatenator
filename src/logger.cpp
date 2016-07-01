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

    boost::log::register_simple_formatter_factory< boost::log::trivial::severity_level, char >("Severity");
    Logger::sink = boost::make_shared<text_sink>();

    boost::shared_ptr<std::ostream> stdout_stream{&std::clog, boost::null_deleter{}};
    Logger::sink->locked_backend()->add_stream(stdout_stream);

    add_file_log
    (
        keywords::file_name = "concatenator_%N.log",
        keywords::rotation_size = 10 * 1024 * 1024,
        keywords::format = (
            expr::stream << 
            "[" << 
            expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S") <<
            "] [" <<
            logging::trivial::severity <<
            "] --- " <<
            expr::smessage
        )
    );

    logging::add_common_attributes();
    Logger::sink->set_filter(severity > 0);

    logging::core::get()->add_sink(Logger::sink);

};

void Logger::error(std::string str) {
    BOOST_LOG_SEV(lg, logging::trivial::error) << str;
    Logger::sink->flush(); 
}

void Logger::info(std::string str) {
    BOOST_LOG_SEV(lg, logging::trivial::error) << str;
    Logger::sink->flush(); 
}

void Logger::warning(std::string str) {
    BOOST_LOG_SEV(lg, logging::trivial::error) << str;
    Logger::sink->flush(); 
}

