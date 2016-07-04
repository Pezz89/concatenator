#include <iostream>
#include "Logger.h"
#include "ArgumentParser.h"
#include "AudioDatabase.h"

using namespace std;

int main(int argc, char** argv) {
    Logger log = Logger();

    ArgumentParser argparse = ArgumentParser();
    //argparse.parseargs(argc, argv);
    log.error("My pretty little error!");
    return 0;
}
