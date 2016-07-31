#include "ArgumentParser.h"
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;

namespace fs = boost::filesystem;
namespace pt = boost::property_tree;

ArgumentParser::ArgumentParser() : generic("Command line options"), config("Configuration") {
    // Add positional arguments to specify source, target and output database locations.
    positionalOptions.add("source", 1); 
    positionalOptions.add("target", 1); 
    positionalOptions.add("output", 1); 

    // Add optional arguments to allow control over application settings from the command line.
    generic.add_options()
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
        ("config,c", po::value<string>()->default_value("config.json"), 
         "Specifies the location of a config file to be used for configuring "
         "the program. If no config is specified, the default ./config.json "
         "file found in the concatenator project directory, will be used.")
    ;

    config.add_options()
        ("analysis.active_analyses", po::value<vector<string>>()->multitoken(), "Analysis "
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

    po::options_description cmdline_options;
    cmdline_options.add(generic).add(config);

    po::options_description config_file_options;
    config_file_options.add(config);

    std::ifstream settings_file("config.ini");

    po::store(po::command_line_parser(argc, argv).options(generic).positional(positionalOptions).run(), vm);;
    po::store(po::parse_config_file(settings_file, config), vm);

    // If help option is specified then output help message
    if (vm.count("help")) {
        cout << generic << "\n";
        return 1;
    }

    po::notify(vm);  

    if (vm["analyses"].empty()) {
        vector<string> v = vm["analysis.active_analyses"].as<vector<string>>();
        for(std::vector<string>::iterator it = v.begin(); it != v.end(); ++it) {
            std::cout << *it;
        }

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

