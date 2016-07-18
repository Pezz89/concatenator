#include <iostream>
#include "logger.h"
#include "ArgumentParser.h"
#include "AudioDatabase.h"
#include <list>
#include <string>

using namespace std;

namespace 
{ 
  const size_t ERROR_IN_COMMAND_LINE = 1; 
  const size_t SUCCESS = 0; 
  const size_t ERROR_UNHANDLED_EXCEPTION = 2; 
 
}

int main(int argc, char** argv) {
    // Initialize a logger object to be used for message handeling throughout
    // the program
    Logger log = Logger();
    /*
    try 
    {
    */
        // Initialize object to parse arguments supplied by user from command
        // line
        ConcatenatorArgParse argparse = ConcatenatorArgParse();
        // Parse arguments and exit program if specified (through use of --help
        // or -h flag)
        if(argparse.parseargs(argc, argv)) {
            return SUCCESS;
        }
        
        vector<string> analyses = argparse.get_analyses();

        // Initialize the source audio database object with arguments provided from the command line.
        AudioDatabase source_db = AudioDatabase(
                argparse.get_source_db(), 
                analyses, 
                &log, 
                argparse.get_src_audio_dir()
        );

        // Initialize the target audio database object with arguments provided from the command line.
        AudioDatabase target_db = AudioDatabase(
                argparse.get_target_db(), 
                analyses, 
                &log, 
                argparse.get_tar_audio_dir()
        );

    /*
    }
    catch(std::exception& e) 
    { 
        string error("Unhandled Exception reached the top of main:\n");
        error.append(e.what());

        log.error(error);
        return ERROR_UNHANDLED_EXCEPTION; 
    }   
    */
    return SUCCESS;
}
