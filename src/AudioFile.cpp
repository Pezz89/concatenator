#include "AudioFile.h"
#include <string>
using namespace std;

AudioFile::AudioFile(const char * fname, bool open)
{
    if(open) {
        file = SndfileHandle(fname);
    }
    name = fname;
}

AudioFile::AudioFile(const char * fname, const int format, const int channels, const int samplerate)
{

}

void AudioFile::swap_mode(string m)
{
    
}

