#include <boost/shared_ptr.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/formatting_ostream.hpp>

class Logger {
    public:
        Logger();
        ~Logger() {};
        void debug(std::string str);
        void info(std::string str);
        void warning(std::string str);
        void error(std::string str);
        void critical(std::string str);

    private:
        static void formatter(boost::log::record_view const& rec, boost::log::formatting_ostream& strm);
        const char* severity_levels[5] = 
        {
            "normal",
            "notification",
            "warning",
            "error",
            "critical"
        };

        typedef boost::log::sinks::asynchronous_sink<boost::log::sinks::text_ostream_backend> text_sink;
        boost::log::sources::severity_logger<int> lg;
        boost::shared_ptr<text_sink> sink;
};
