#ifndef AUDIOFILE_H
#define AUDIOFILE_H

#include <string>
#include <sndfile.hh>
#include <boost/filesystem.hpp>
#include <map>
#include "analyses/analysis.h"
#include "logger.h"
#include "H5Cpp.h"
#include "DataHandler.h"

namespace fs = boost::filesystem;
namespace aa = AudioAnalysis;
namespace dh = DataHandling;


namespace AudioFile {
    class AnalysedAudioFile {
        public:
            AnalysedAudioFile(fs::path filepath) : filepath(filepath) {}

            int open_data(unique_ptr<dh::DataHandler>& data)
            {
                try {
                    data->create_group(name());
                
                    LOGDEBUG << "Created data group for audio file: " <<  name();
                }
                catch(H5::FileIException& e){
                    filegroup = data->open_group(name());
                    LOGDEBUG << "Loaded data group for audio file: " <<  name();
                }
                return 0;
            }

            template <typename Iter>
            int analyse(Iter it, Iter end, const bool reanalyse)
            {
                LOGDEBUG << "Creating analyses for audio file: " <<  name();
                // Initialize a factory object for creating analysis objects.
                aa::AnalysisFactory factory = aa::AnalysisFactory(reanalyse);

                for(; it != end; ++it) {
                    unique_ptr<analysis> a = factory.create(aa::analysis_index_from_string(*it));
                    a->create_analysis();
                }
                return 0;
            }
        
            int open(const int &mode, const int &format, const int &channels, const int &samplerate)
            {
                switch(mode){
                    case SFM_READ: 
                        file = SndfileHandle(filepath.string());
                        break;
                    case SFM_WRITE: 
                        file = SndfileHandle(filepath.string(), SFM_WRITE, format, channels, samplerate);
                        break;
                    case SFM_RDWR: 
                        file = SndfileHandle(filepath.string(), SFM_RDWR, format, channels, samplerate);
                        break;
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
            unique_ptr<dh::GroupHandler> filegroup;
        };
}
#endif
