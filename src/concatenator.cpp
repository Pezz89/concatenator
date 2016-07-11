#include <iostream>
#include "logger.h"
#include "ArgumentParser.h"
#include "AudioDatabase.h"
#include <vector>

using namespace std;

int main(int argc, char** argv) {
    Logger log = Logger();
    ArgumentParser argparse = ArgumentParser();
    //argparse.parseargs(argc, argv);
    log.error("My pretty little error!");

    vector<string> analyses = {"BLARGH"};
    AudioDatabase db = AudioDatabase("./", "./", analyses.begin(), analyses.end());
    return 0;
}
