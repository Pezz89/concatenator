#include <string>
#include <sndfile.hh>

class AudioFile {
    public:
        AudioFile(const char * &name, const int &mode=SFM_RDWR, const int &format=0, const int &channels=0, const int &samplerate=0);
        int open(const int &mode=SFM_READ, const int &format=0, const int &channels=0, const int &samplerate=0);
    protected:
        SndfileHandle file;
        SF_INFO* file_info;
    private:
        std::string name;
};

class AnalysedAudioFile : public AudioFile {
    public:
    private:
};

