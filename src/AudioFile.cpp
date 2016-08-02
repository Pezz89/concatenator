#include "AudioFile.h"
#include <string>
#include <vector>
#include <iostream>
#include "logger.h"
#include "H5Cpp.h"

using namespace std;
using namespace H5;

AnalysedAudioFile::AnalysedAudioFile(fs::path filepath, Group& filegroup, Logger& log) : filepath(filepath), filegroup(filegroup), log(log)
{

}

AnalysedAudioFile::~AnalysedAudioFile()
{
}

int AnalysedAudioFile::open(const int &mode, const int &format, const int &channels, const int &samplerate)
{
    switch(mode){
        case SFM_READ: file = SndfileHandle(filepath.string());
        case SFM_WRITE: file = SndfileHandle(filepath.string(), SFM_WRITE, format, channels, samplerate);
        case SFM_RDWR: file = SndfileHandle(filepath.string(), SFM_RDWR, format, channels, samplerate);
    }

    return 0;
}

int AnalysedAudioFile::open()
{
    file = SndfileHandle(filepath.string());
    return 0;
}

std::string AnalysedAudioFile::name()
{
    return filepath.stem().string();
}
