#include <iostream>
#include <string>
#include <list>
#include <set>
#include <boost/algorithm/string.hpp>
#include "logger.h"

using std::string;
using std::cout;
using std::endl;
using std::list;

/*!
 * A class that encapsulates a collection of AudioFile objects in order to
 * perform analysis and synthesis operations on batches of audio files.
*/

class AudioDatabase {
    public:
        AudioDatabase(const std::string audio_dir, const std::string database_dir, list<string>& analyses, Logger* log);
    private:
        std::string database_dir = "";
        std::string audio_dir = "";
        // Define a set that stores the locations of audiofiles in the database.
        std::set<string> audio_file_set;
        Logger* log;

};


/*! A function that determines whether a string value is found in the container.
*/
template<typename container>
bool in_array(string &value, const container &array)
{
    boost::algorithm::to_upper(value);
    return std::find(array.begin(), array.end(), value) != array.end();
}

/*! Check that analysis strings provided are supported by the database object

  \param iterator - An iterator pointing to where to begin checking strings are valid.
  \param end - An iterator pointing to the point at which to stop analysing strings.
*/
template<typename Iter>
Iter check_analyses_valid(Iter iterator, Iter end)
{
    static std::list<string> valid_analyses = {
        "RMS",
        "ZEROX",
        "FFT",
        "SPCCNTR",
        "SPCSPRD",
        "SPCFLUX",
        "SPCCF",
        "SPCFLATNESS",
        "F0",
        "PEAK",
        "CENTROID",
        "VARIANCE",
        "KURTOSIS",
        "SKEWNESS",
        "HARM_RATIO"
    };

    while(iterator != end)
    {
        if(!in_array(*iterator, valid_analyses)) {
            return iterator;
        }
        ++iterator;
    }
    return iterator;
}
