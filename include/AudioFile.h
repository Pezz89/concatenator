#include <string>
#include <sndfile.hh>
#include <boost/filesystem.hpp>
#include "logger.h"
#include "H5Cpp.h"

namespace fs = boost::filesystem;

class AnalysedAudioFile {
    public:
        AnalysedAudioFile(fs::path name, H5::Group& filegroup, Logger& log);
        ~AnalysedAudioFile();
        void analyse();
        int open(const int &mode, const int &format, const int &channels, const int &samplerate);
        int open();
        int open_data(const H5::H5File& data_file);
        std::string name();

        template <typename T>
        int open_data(const T& data)
        {
            try {
                filegroup = data.createGroup(name());
                log.debug("Created data group for audio file: " + filepath.filename().string());
            }
            catch(H5::GroupIException e){
                filegroup = data.openGroup(name());
                log.debug("Loaded data group for audio file: " + filepath.filename().string());
            }
            return 0;
        }
    
    private:
        SndfileHandle file;
        fs::path filepath;
        H5::Group filegroup;
        Logger log;
};

