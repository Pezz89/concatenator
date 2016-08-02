#include <iostream>
#include <string>
#include <list>
#include <set>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <H5Cpp.h>
#include "logger.h"

using std::string;
using std::cout;
using std::endl;
using std::list;
using std::vector;

/*!
 * A class that encapsulates a collection of AudioFile objects in order to
 * perform analysis and synthesis operations on batches of audio files.
*/

class AudioDatabase {
    public:
        AudioDatabase(
                const std::string database_dir, 
                vector<string>& analyses, 
                Logger& log
        );
        void load_database(boost::filesystem::path source_dir, bool reanalyse=false);

    private:
        boost::filesystem::path database_dir;
        boost::filesystem::path audio_dir;
        // Define a set that stores the locations of audiofiles in the database.
        std::set<boost::filesystem::path> audio_file_set;
        std::map<string, boost::filesystem::path> database_dirs;
        Logger log;

        void validate_analysis_list(vector<string>& analyses);
        bool validate_filetype(const boost::filesystem::path& filepath);
        void create_subdirs();
        void organise_audio(boost::filesystem::path source_dir, bool symlink=true);
        // Used to find and store paths to all audio that is part of the current database
        void register_audio();

        // Declare a HDF5 file object to be used for storing analysis data.
        H5::H5File data_file;

        void register_data();

        void analyse_database();
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
std::list<string> check_analyses_valid(Iter iterator, Iter end)
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
    std::list<string> invalid;

    while(iterator != end)
    {
        if(!in_array(*iterator, valid_analyses)) {
            invalid.push_back(*iterator);
        }
        ++iterator;
    }
    return invalid;
}
