#include <string>
#include <sndfile.hh>

class AudioFile {
    public:
        AudioFile(const char * fname, bool open=true);
        AudioFile(const char * fname, int format, int channels, int samplerate);
        ~AudioFile();
        void swap_mode(std::string m);
        bool is_open() { return open; };
    private:
        std::string mode;
        std::string name;
        bool open;
        SndfileHandle file;
};

class AnalysedAudioFile : public AudioFile {
    public:
    private:
};
