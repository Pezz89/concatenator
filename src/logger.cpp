#include <boost/log/common.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/expressions.hpp>
#include <boost/utility/empty_deleter.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>

#include "Logger.h"

using namespace boost::log;

BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", int)

Logger::Logger() {
    Logger::sink = boost::make_shared<text_sink>();

    boost::shared_ptr<std::ostream> stream{&std::clog, boost::empty_deleter{}};
    Logger::sink->locked_backend()->add_stream(stream);
    Logger::sink->set_filter(severity > 0);
    Logger::sink->set_formatter(expressions::stream << severity << ": " <<
    expressions::smessage);

    core::get()->add_sink(Logger::sink);

};

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

