#include "ArgumentParser.h"
#include <vector>
#include <iostream>

using namespace std;

ArgumentParser::ArgumentParser() : desc("Allowed options") {
    // Add positional arguments to specify source, target and output database locations.
    positionalOptions.add("source", 1); 
    positionalOptions.add("target", 1); 
    positionalOptions.add("output", 1); 

    // Add optional arguments to allow control over application settings from the command line.
    desc.add_options()
        ("help,h", "produce help message")
        ("source", po::value<string>()->required(), "Source location")
        ("target", po::value<string>()->required(), "Target location")
        ("output", po::value<string>()->required(), "Output location")
        ("analyses,a", po::value<vector<string>>()->multitoken(), "Analysis "
         "strings specifying analyses to use for database comparison.")
        ("src_audio", po::value<string>(), "Specifies the "
         "directory to create the source database and store analyses in. If "
         "not specified then the " "source directory will be used directly.")
        ("tar_audio", po::value<string>(), "Specifies the "
         "directory to create the target database and store analyses in. If "
         "not specified then the target directory will be used directly.")
    ;
}

int ArgumentParser::parseargs(int argc, char** argv) {
    po::store(po::command_line_parser(argc, argv).options(desc).positional(positionalOptions).run(), vm);

    // If help option is specified then output help message
    if (vm.count("help")) {
        cout << desc << "\n";
        return 1;
    }

    po::notify(vm);  

    if (vm["analyses"].empty()) {
        throw runtime_error("No analysis strings provided as arguments.");
    }
    return 0;
}

const po::variable_value& ArgumentParser::operator [](char const *b) const {
    return vm[b];
}

po::variables_map::size_type ArgumentParser::count(char const *ref) {
    return vm.count(ref);
}
