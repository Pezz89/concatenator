#include <string>
#include <sndfile.hh>
#include <boost/filesystem.hpp>
#include <map>
#include "analyses/analysis.h"
#include "logger.h"
#include "H5Cpp.h"

namespace fs = boost::filesystem;
namespace aa = AudioAnalysis;

namespace AudioFile {
    static const map<string, aa::valid_analyses> analysis_map = { {"RMS", aa::RMS}, {"F0", aa::F0} };
    
    class AnalysedAudioFile {
        public:
            AnalysedAudioFile(fs::path filepath) : filepath(filepath) {}

            template <typename T>
            int open_data(T& data)
            {
                try {
                    data.createGroup(name());
                
                    LOGDEBUG << "Created data group for audio file: " <<  name();
                }
                catch(H5::Exception& e){
                    filegroup = data.openGroup(name());
                    LOGDEBUG << "Loaded data group for audio file: " <<  name();
                }
                return 0;
            }

            template <typename Iter>
            int analyse(Iter it, Iter end, const bool reanalyse)
            {
                for(; it != end; ++it) {
                    if(reanalyse) {
                    }
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
}
