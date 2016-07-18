#include <string>
#include <vector>
#include "AudioDatabase.h"
#include <stdexcept>
#include <set>
#include <algorithm>

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
    it = std::unique (analyses.begin(), analyses.end());   // 10 20 30 20 10 ?  ?  ?  ?
    analyses.resize(std::distance(analyses.begin(),it));
    
    // Check that all analysis strings supplied refer to valid analyses.
    vector<string>::const_iterator valid = check_analyses_valid(analyses.begin(), analyses.end());
    if(valid != analyses.end()) {
        string err = "The analysis string supplied to the AudioDatabase constructor is not valid: " + *valid;
        throw std::runtime_error(err);
    }

    this->database_dir = database_dir;
    this->audio_dir = audio_dir;
}
