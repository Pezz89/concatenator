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

BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", int)

Logger::Logger() {

    boost::log::register_simple_formatter_factory< boost::log::trivial::severity_level, char >("Severity");
    Logger::sink = boost::make_shared<text_sink>();

    Logger::sink->set_formatter
    (
        expr::stream << 
        "[" << 
        expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S") <<
        "] [" <<
        logging::trivial::severity <<
        "] --- " <<
        expr::smessage
    );


    boost::shared_ptr<std::ostream> stdout_stream{&std::clog, boost::null_deleter{}};
    Logger::sink->locked_backend()->add_stream(stdout_stream);
    Logger::sink->locked_backend()->add_stream(boost::make_shared< std::ofstream >("sample.log"));

    //Logger::sink->set_filter(severity > 0);

    logging::core::get()->add_sink(Logger::sink);

    logging::add_common_attributes();

};

void Logger::trace(std::string str) {
    BOOST_LOG_SEV(lg, logging::trivial::trace) << str;
    Logger::sink->flush(); 
}

void Logger::debug(std::string str) {
    BOOST_LOG_SEV(lg, logging::trivial::debug) << str;
    Logger::sink->flush(); 
}

void Logger::info(std::string str) {
    BOOST_LOG_SEV(lg, logging::trivial::info) << str;
    Logger::sink->flush(); 
}

void Logger::warning(std::string str) {
    BOOST_LOG_SEV(lg, logging::trivial::warning) << str;
    Logger::sink->flush(); 
}

void Logger::error(std::string str) {
    BOOST_LOG_SEV(lg, logging::trivial::error) << str;
    Logger::sink->flush(); 
}

void Logger::fatal(std::string str) {
    BOOST_LOG_SEV(lg, logging::trivial::fatal) << str;
    Logger::sink->flush(); 
}
