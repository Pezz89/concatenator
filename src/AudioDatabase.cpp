#include <string>
#include <list>
#include "AudioDatabase.h"
#include <stdexcept>
#include <set>

using namespace std;

AudioDatabase::AudioDatabase(
        const string audio_dir, 
        const string database_dir, 
        list<string>& analyses,
        Logger* log
    ) 
{
    this->log = log;

    // Remove duplicate strings from list of analyses.
    analyses.unique();
    
    // Check that all analysis strings supplied refer to valid analyses.
    list<string>::const_iterator valid = check_analyses_valid(analyses.begin(), analyses.end());
    if(valid != analyses.end()) {
        string err = "The analysis string supplied to the AudioDatabase constructor is not valid: " + *valid;
        throw std::runtime_error(err);
    }

    this->database_dir = database_dir;
    this->audio_dir = audio_dir;
}
