#include <string>
#include <vector>
#include <list>
#include "AudioDatabase.h"
#include <stdexcept>
#include <set>
#include <algorithm>
#include <boost/algorithm/string/join.hpp>

using namespace std;

AudioDatabase::AudioDatabase(
        const string database_dir, 
        vector<string>& analyses,
        Logger* log,
        const string audio_dir
    ) 
{
    this->log = log;

    log->info("Database directory: " + database_dir);
    log->info("Audio directory: " + audio_dir);
    // Remove duplicate strings from vector of analyses.
    std::vector<string>::iterator it;
    it = std::unique (analyses.begin(), analyses.end());
    analyses.resize(std::distance(analyses.begin(),it));
    
    // Check that all analysis strings supplied refer to valid analyses.
    list<string> invalid = check_analyses_valid(analyses.begin(), analyses.end());
    if(!invalid.empty()) {
        string err = "The following analysis string(s) supplied to the AudioDatabase constructor are not valid: ";
        string invalid_strings = boost::algorithm::join(invalid, " "); 
        throw std::runtime_error(err + invalid_strings);
    }

    this->database_dir = database_dir;
    this->audio_dir = audio_dir;
}
