#include "catch.hpp"
#include <boost/filesystem.hpp>
#include "H5Cpp.h"
#include "hdf5helper.h"
#include "logger.h"

#include "AudioFile.h"
namespace fs = boost::filesystem;
using namespace H5;

SCENARIO("HDF5 groups are handled correctly in the AnalysedAudioFile class", "[HDF5][AnalysedAudioFile]") {
   GIVEN("An AnalysedAudioFile and a HDF5 file") {
        H5File data_file = H5File("./.test_data.hdf5", H5F_ACC_TRUNC);
        AnalysedAudioFile test_audio = AnalysedAudioFile(fs::path(".test_audio.wav"));

        WHEN("open_data is called using a H5File object") {
            test_audio.open_data(data_file);

            THEN("a group is created using the name of the audio file") {
                REQUIRE(hdf5helper::exists(data_file, test_audio.name()));
            }
        
        }
    }
}
