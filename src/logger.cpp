#include <boost/log/common.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
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
#include <ostream>
#include <fstream>

#include "Logger.h"

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

//BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", int)

Logger::Logger() {

    boost::log::register_simple_formatter_factory< boost::log::trivial::severity_level, char >("Severity");
    Logger::console_sink = boost::make_shared<console_backend>();

    Logger::file_sink =
        boost::make_shared<file_backend>(
            keywords::file_name = "concatenator_log_%N.log",
            keywords::rotation_size = 5 * 1024 * 1024
        );


    Logger::file_sink->set_formatter(
        expr::stream << 
        "[" << 
        expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S") <<
        "] [" <<
        logging::trivial::severity <<
        "] --- " <<
        expr::smessage
    );

    Logger::console_sink->set_formatter(
        expr::stream << 
        "[" << 
        expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S") <<
        "] [" <<
        logging::trivial::severity <<
        "] --- " <<
        expr::smessage
    );

    boost::shared_ptr<std::ostream> stdout_stream{&std::clog, boost::null_deleter{}};
    Logger::console_sink->locked_backend()->add_stream(stdout_stream);

    Logger::console_sink->locked_backend()->auto_flush(true);
    Logger::file_sink->locked_backend()->auto_flush(true);

    //Logger::sink->set_filter(severity > 0);

    logging::core::get()->add_sink(Logger::file_sink);
    logging::core::get()->add_sink(Logger::console_sink);

    logging::add_common_attributes();

};

Logger::~Logger() {
    Logger::file_sink->flush();
    Logger::console_sink->flush();
}
void Logger::trace(std::string str) {
    BOOST_LOG_SEV(lg, logging::trivial::trace) << str;
}

void Logger::debug(std::string str) {
    BOOST_LOG_SEV(lg, logging::trivial::debug) << str;
}

void Logger::info(std::string str) {
    BOOST_LOG_SEV(lg, logging::trivial::info) << str;
}

void Logger::warning(std::string str) {
    BOOST_LOG_SEV(lg, logging::trivial::warning) << str;
}

void Logger::error(std::string str) {
    BOOST_LOG_SEV(lg, logging::trivial::error) << str;
    Logger::file_sink->flush();
    Logger::console_sink->flush();
}

void Logger::fatal(std::string str) {
    BOOST_LOG_SEV(lg, logging::trivial::fatal) << str;
    Logger::file_sink->flush();
    Logger::console_sink->flush();
}
