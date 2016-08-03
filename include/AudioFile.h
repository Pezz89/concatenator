#include <string>
#include <sndfile.hh>
#include <boost/filesystem.hpp>
#include "logger.h"
#include "H5Cpp.h"

namespace fs = boost::filesystem;

class AnalysedAudioFile {
    public:
        AnalysedAudioFile(fs::path filepath) : filepath(filepath) {}
        void analyse();

        template <typename T>
        int open_data(const T& data)
        {
            try {
                filegroup = data.createGroup(name());
                DEBUG << "Created data group for audio file: " <<  filepath.filename().string();
            }
            catch(H5::GroupIException e){
                filegroup = data.openGroup(name());
                DEBUG << "Loaded data group for audio file: " <<  filepath.filename().string();
            }
            return 0;
        }
    
        int open(const int &mode, const int &format, const int &channels, const int &samplerate)
        {
            switch(mode){
                case SFM_READ: file = SndfileHandle(filepath.string());
                case SFM_WRITE: file = SndfileHandle(filepath.string(), SFM_WRITE, format, channels, samplerate);
                case SFM_RDWR: file = SndfileHandle(filepath.string(), SFM_RDWR, format, channels, samplerate);
            }

            return 0;
        }

        int open()
        {
            file = SndfileHandle(filepath.string());
            return 0;
        }

        std::string name()
        {
            return filepath.stem().string();
        }
        private:
            SndfileHandle file;
            fs::path filepath;
            H5::Group filegroup;
    };

