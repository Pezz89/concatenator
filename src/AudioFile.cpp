#include "AudioFile.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

AudioFile::AudioFile(const char * &name, const int &mode, const int &format, const int &channels, const int &samplerate)
{
    this->name = name;
    open(mode, format, channels, samplerate);
}

int AudioFile::open(const int &mode, const int &format, const int &channels, const int &samplerate)
{
    switch(mode){
        case SFM_READ: file = SndfileHandle(name);
        case SFM_WRITE: file = SndfileHandle(name, SFM_WRITE, format, channels, samplerate);
        case SFM_RDWR: file = SndfileHandle(name, SFM_RDWR, format, channels, samplerate);
    }

    return 0;
}

