#include <string>
#include <list>
#include "AudioDatabase.h"
#include "AudioFile.h"
#include <stdexcept>
#include <set>
#include <algorithm>
#include <boost/algorithm/string/join.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include "H5Cpp.h"

namespace fs = boost::filesystem;

using namespace std;
using namespace H5;
using namespace AudioFile;

AudioDatabase::AudioDatabase(
        const string database_dir, 
        vector<string> analyses
    ) : analyses(analyses)
{

    LOGINFO << "Database directory: " << database_dir;

    // Remove duplicate strings from vector of analyses.
    std::vector<string>::iterator it;
    it = std::unique (this->analyses.begin(), this->analyses.end());
    analyses.resize(std::distance(this->analyses.begin(),it));
    
    validate_analysis_list(this->analyses);

    database_dirs.insert({"root", fs::path(database_dir)});
    this->audio_dir = fs::path(audio_dir);

}

void AudioDatabase::validate_analysis_list(vector<string>& analyses)
{
    // Check that all analysis strings supplied refer to valid analyses.
    list<string> invalid = check_analyses_valid(analyses.begin(), analyses.end());
    if(!invalid.empty()) {
        string err = "The following analysis string(s) supplied to the AudioDatabase constructor are not valid: ";
        string invalid_strings = boost::algorithm::join(invalid, " "); 
        throw std::runtime_error(err + invalid_strings);
    }
}

void AudioDatabase::load_database(fs::path source_dir)
{
    // Make sure the database root directory exists.
    try
    {
        if(create_directory(database_dirs["root"])) 
        {
            LOGDEBUG << "Database directory created: " << database_dir.string();
        }
        else if(exists(database_dirs["root"]))
        {
            LOGDEBUG << "Database directory already exists: " << database_dir.string();
        }
    } 
    catch(boost::filesystem::filesystem_error &e)
    {
        throw std::runtime_error("Database directory could not be created: " + database_dir.string());
    }


    // Create a folder hierachy used to store audio and analysis data used by the database.
    create_subdirs();

    if(source_dir.empty()) {
        source_dir = database_dirs["audio"];
        LOGDEBUG << "Source directory not provided. Setting to:" << source_dir.string();
    }

    if(!exists(source_dir)) {
        throw std::runtime_error("Source audio directory does not exist: " + source_dir.string());
    }

    // Only organise audio if new audio is to be added from a new location.
    if(source_dir != database_dirs["audio"]) {
        // Copy/create links to audio files that are to be used as part of the database.
        organise_audio(source_dir);
    }

    // Find all audio in the database and store references for use later...
    register_audio();

    //Find/create HDF5 file for storage of analysis data.
    register_data();

}

void AudioDatabase::analyse_database(const bool& reanalyse)
{
    for(auto afile_path : audio_files)
    {
        AnalysedAudioFile afile = AnalysedAudioFile(afile_path);
        afile.open_data(data_file);
        afile.analyse(analyses.begin(), analyses.end(), reanalyse);
    }
}

void AudioDatabase::register_data()
{
    fs::path data_path = database_dirs["data"]/fs::path("data.hdf5");
    try
    {
        data_file = H5File(data_path.string(), H5F_ACC_RDWR);
        LOGINFO << "Reading database data from: " <<  (database_dirs["data"]/fs::path("data.hdf5")).string();
    }
    catch(FileIException &e)
    {
        if(!fs::exists(data_path.string()))
        {
            data_file = H5File(data_path.string(), H5F_ACC_TRUNC);
            LOGINFO << "Creating new database file at: " <<  (database_dirs["data"]/fs::path("data.hdf5")).string();
        }
        else
        {
            LOGINFO << "Data file exists but cannot be read: " <<  data_path.string();
            throw;
        }
    }
}

void AudioDatabase::create_subdirs()
{
    static array<fs::path, 2> directory_names = {{ 
        fs::path("audio"), 
        fs::path("data") 
    }};
    
    for(const auto& name : directory_names) {
        fs::path subdir = database_dirs["root"]/name;
        try
        {
            if(create_directory(subdir)) {
                LOGINFO << "Subdirectory created: " <<  subdir.string();
            }
            else if(exists(database_dirs["root"]))
            {
                LOGINFO << "Subdirectory already exists: " <<  subdir.string();
            }
        }
        catch(boost::filesystem::filesystem_error &e)
        {
            throw std::runtime_error("Subdirectory could not be created: " + database_dirs["root"].string());
        }
        database_dirs.insert({name.string(), subdir});
    }
}

bool AudioDatabase::validate_filetype(const fs::path& filepath)
{
    // Define patterns to validate files found based on their file extensions.
    static array<string, 4> valid_filetypes = {{
        ".wav",
        ".aif", 
        ".aiff", 
        ".flac"
    }};

    for(const auto& filetype : valid_filetypes)
    {
        // compare file extension with valid extension strings to find match.
        bool valid = (filetype.compare(filepath.extension().string()) == 0);
        if(valid) {
            return true;
        }
    }
    return false;
}

void AudioDatabase::organise_audio(fs::path source_dir, bool symlink)
{

    LOGINFO << "Organising audio directory at: " <<  database_dirs["audio"].string();
    // Define the destination for copying/linking all valid audio files found.
    for(fs::recursive_directory_iterator iter(source_dir), end; iter != end; ++iter)
    {
        // Don't search the audio directory of the database if this is a subdirectory of the source directory provided.
        if (iter->path() == database_dirs["audio"])
        {
            iter.disable_recursion_pending();
        }

        if(!validate_filetype(iter->path())) {
            LOGINFO << "File: " <<  iter->path().string() <<  " isn't a supported audiofile. Skipping...";
            continue;
        }

        
        fs::path destination_file = database_dirs["audio"]/iter->path().filename();
        
        if(symlink) {
            // Try to symlink the file to the audio directory of the database.
            try {
            fs::create_symlink(iter->path(), destination_file);
            LOGINFO << "Linked: " <<  iter->path().string() << " to: " <<  destination_file.string();
            }
            catch(boost::filesystem::filesystem_error &e){
                // If symbolic linking fails then the file probably already exists at the location.
                LOGINFO << "Failed to link: " <<  iter->path().string() << " to " << destination_file.string() << " File may already exists.";
            }
        }
        else {
        // If it is in the database as a symlink, but a full copy is required
            if(fs::exists(destination_file) && !fs::is_symlink(destination_file)) {
                LOGINFO << "File already exists: " <<  iter->path().string();
                continue;
            }

            // Copy file, overwriting any previously created symbolic links.
            try {
                fs::remove(destination_file);
                fs::copy_file(iter->path(), destination_file, fs::copy_option::overwrite_if_exists);
                LOGDEBUG << "Copied: " <<  iter->path().string() << " to: " << destination_file.string();
            }
            catch(boost::filesystem::filesystem_error &e){
                // If symbolic linking fails then the file probably already exists at the location.
                LOGDEBUG << "Failed to copy source file to: " <<  destination_file.string() << " File may already exists.";
            }
        }
    }
}

void AudioDatabase::register_audio()
{
    // Clear any previous entries from set.
    audio_files.clear();
    for(auto& entry : boost::make_iterator_range(fs::directory_iterator(database_dirs["audio"]), {})) 
    {
        if(validate_filetype(entry.path())) {
            LOGINFO << "Registered audio file: " <<  entry.path().string();
            audio_files.insert(entry.path());
        }
    }
}
