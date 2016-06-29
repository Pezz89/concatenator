#include <iostream>
#include "boost/program_options.hpp"

namespace po = boost::program_options;

class ArgumentParser {
    public:
        ArgumentParser();
        ~ArgumentParser() {};
        ArgumentParser(const ArgumentParser&);
        ArgumentParser& operator=(const ArgumentParser&);
        int parseargs(int argc, char** argv);
    
    private:
        //Create a positional options object for parsing input, output etc
        //positional arguments from command line.
        po::positional_options_description positionalOptions; 
        //
        po::variables_map vm;
        po::options_description desc;
};
