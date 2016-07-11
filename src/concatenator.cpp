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
    try 
    {
        // Initialize object to parse arguments supplied by user from command
        // line
        ArgumentParser argparse = ArgumentParser();
        // Parse arguments and exit program if specified (through use of --help
        // or -h flag)
        if(argparse.parseargs(argc, argv)) {
            return ERROR_IN_COMMAND_LINE;
        }

        list<string> analyses = {"BLARGH"};
        AudioDatabase db = AudioDatabase("./", "./", analyses, &log);
    }
    catch(std::exception& e) 
    { 
        string error("Unhandled Exception reached the top of main:\n");
        error.append(e.what());

        log.error(error);
        return ERROR_UNHANDLED_EXCEPTION; 
    }   
    return SUCCESS;
}
