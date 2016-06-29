#include "argument_parser.h"
#include <iostream>

using namespace std;

ArgumentParser::ArgumentParser() : desc("Allowed options") {
    positionalOptions.add("input_db", 1); 
    positionalOptions.add("output_db", 1); 

    
    desc.add_options()
        ("help,h", "produce help message")
        ("compression", po::value<int>(), "set compression level")
    ;
}

int ArgumentParser::parseargs(int argc, char** argv) {
    po::store(po::command_line_parser(argc, argv).options(desc).positional(positionalOptions).run(), vm);
    po::notify(vm);  

    // If help option is specified then output help message
    if (vm.count("help")) {
        cout << desc << "\n";
        return 1;
    }
    return 0;
}
