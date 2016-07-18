#include <iostream>
#include <string>
#include <vector>
#include "boost/program_options.hpp"

using std::vector;
using std::string;
namespace po = boost::program_options;

class ArgumentParser {
    public:
        ArgumentParser();
        ~ArgumentParser() {};
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
        po::options_description desc;
};

class ConcatenatorArgParse : public ArgumentParser {
    public:
       vector<string> get_analyses() { return (*this)["analyses"].as<vector<string>>(); }
       string get_source_db() { return (*this)["source"].as<string>(); }
       string get_target_db() { return (*this)["target"].as<string>(); }
       string get_tar_audio_dir() { return ((*this)["tar_db"].empty() ? (*this)["target"].as<string>() : (*this)["tar_db"].as<string>()); }
       string get_src_audio_dir() { return ((*this)["src_db"].empty() ? (*this)["source"].as<string>() : (*this)["src_db"].as<string>()); }
};
