#include <iostream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include "logger.h"

using std::vector;
using std::string;

namespace po = boost::program_options;
namespace fs = boost::filesystem;
namespace pt = boost::property_tree;

class ArgumentParser {
    public:
        ArgumentParser();
        ArgumentParser(const ArgumentParser&);
        ArgumentParser& operator=(const ArgumentParser&);
        int parseargs(int argc, char** argv);
        po::variables_map::size_type count(char const *ref);

        const po::variable_value& operator [](char const *b) const;
        //std::string& operator [](char const *b);
    
    private:
        // Stores values for arguments parsed from the command line
        po::variables_map vm;
        //Create a positional options object for parsing input, output etc
        //positional arguments from command line.
        po::positional_options_description positionalOptions; 
        po::options_description generic;
        po::options_description config;
};

class ConcatenatorArgParse : public ArgumentParser {
    public:
       vector<string> get_analyses() { return (*this)["active_analyses"].as<vector<string>>(); }
       string get_source_db() { return (*this)["source"].as<string>(); }
       string get_target_db() { return (*this)["target"].as<string>(); }
       fs::path get_tar_audio_dir() { return ((*this)["tar_audio"].empty() ? fs::path("") : fs::path((*this)["tar_audio"].as<string>())); }
       fs::path get_src_audio_dir() { return ((*this)["src_audio"].empty() ? fs::path("") : fs::path((*this)["src_audio"].as<string>())); }
       fs::path get_config_path() { return fs::path((*this)["config"].as<string>()); }
};

