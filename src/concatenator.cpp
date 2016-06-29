#include <iostream>
#include "ArgumentParser.h"
#include "AudioDatabase.h"

using namespace std;

int main(int argc, char** argv) {

    ArgumentParser argparse = ArgumentParser();
    argparse.parseargs(argc, argv);
    cout << "Hello world!" << endl;
    return 0;
}
