#pragma once

#include <boost/log/expressions.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>

#define LOGTRACE BOOST_LOG_SEV(logger::get(), boost::log::trivial::trace)
#define LOGDEBUG BOOST_LOG_SEV(logger::get(), boost::log::trivial::debug)
#define LOGINFO  BOOST_LOG_SEV(logger::get(), boost::log::trivial::info)
#define LOGWARN  BOOST_LOG_SEV(logger::get(), boost::log::trivial::warning)
#define LOGERROR BOOST_LOG_SEV(logger::get(), boost::log::trivial::error)
#define LOGFATAL BOOST_LOG_SEV(logger::get(), boost::log::trivial::fatal)

//Narrow-char thread-safe logger.
typedef boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level> logger_t;

//declares a global logger with a custom initialization
BOOST_LOG_GLOBAL_LOGGER(logger, logger_t)
