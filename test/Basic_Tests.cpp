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
                REQUIRE(hdf5helper::groupExists(data_file, test_audio.name()));

                AND_WHEN("open_data is called again to read a group that now already exists") {
                    test_audio.open_data(data_file);
                    THEN("The group should be loaded without error")
                    {
                        //TODO: Add check that group still contains data created in previous test.
                    }
                }
            }
        }
   }
   if(fs::exists("./.test_data.hdf5")) {
       fs::remove("./.test_data.hdf5");
   }
   if(fs::exists(".test_audio.wav")) {
       fs::remove(".test_audio.wav");
   }
}
