#include <iostream>
#include <string>
#include <list>

using std::string;
using std::cout;
using std::endl;

class AudioDatabase {
    public:
        template<typename Iter>
        AudioDatabase(std::string audio_dir, std::string database_dir, Iter it, Iter end);
    private:
        std::string database_dir = "";
        std::string audio_dir = "";
};

template<typename container>
bool in_array(const string &value, const container &array)
{
    cout <<"Test: " << value << endl;
    return std::find(array.begin(), array.end(), value) != array.end();
}

template<typename Iter>
bool check_analyses_valid(Iter iterator, Iter end)
{
    static std::list<string> valid_analyses = {"f0", "RMS"};

    while(iterator != end)
    {
        if(!in_array(*iterator, valid_analyses)) {
            cout << "Nope!" << endl;
            return false;
        }
        ++iterator;
    }
    return true;
}

template<typename Iter>
AudioDatabase::AudioDatabase(string audio_dir, string database_dir, Iter it, Iter end) {
    cout << "HELLO?!?" << endl;
    check_analyses_valid(it, end);
}
