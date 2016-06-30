#include <boost/shared_ptr.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/severity_logger.hpp>

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
        typedef boost::log::sinks::asynchronous_sink<boost::log::sinks::text_ostream_backend> text_sink;
        boost::log::sources::severity_logger<int> lg;
        boost::shared_ptr<text_sink> sink;
};
