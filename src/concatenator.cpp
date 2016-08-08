#include <iostream>
#include "Logger.h"
#include "ArgumentParser.h"
#include "AudioDatabase.h"
#include <list>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include "H5Cpp.h"

using namespace std;

namespace pt = boost::property_tree;

namespace 
{ 
  const size_t ERROR_IN_COMMAND_LINE = 1; 
  const size_t SUCCESS = 0; 
  const size_t ERROR_UNHANDLED_EXCEPTION = 2; 
 
}

int main(int argc, char** argv) {
    // Prevent HDF5 library from printing errors that are handeled in try/catch blocks.
    H5::Exception::dontPrint();
    //
    // Initialize object to parse arguments supplied by user from command
    // line
    ConcatenatorArgParse argparse = ConcatenatorArgParse();
    // Parse arguments and exit program if specified (through use of --help
    // or -h flag)
    if(argparse.parseargs(argc, argv)) {
        return SUCCESS;
    }

    fs::path config_filepath = argparse.get_config_path();
    if(config_filepath.empty()) {
        config_filepath = fs::path("./config.json");
    }
    vector<string> analyses = argparse.get_analyses();

    // Initialize the source audio database object with arguments provided from the command line.
    AudioDatabase source_db = AudioDatabase(
            argparse.get_source_db(), 
            analyses
    );
    source_db.load_database(argparse.get_src_audio_dir());
    source_db.analyse_database();

    /*
    // Initialize the target audio database object with arguments provided from the command line.
    AudioDatabase target_db = AudioDatabase(
            argparse.get_target_db(), 
            analyses, 
            &log
    );
    target_db.load_database(argparse.get_tar_audio_dir());

    }
    */
    return SUCCESS;

}
