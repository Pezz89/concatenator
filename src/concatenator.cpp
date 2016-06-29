#include <iostream>
#include "argument_parser.h"

using namespace std;

int main(int argc, char** argv) {

    // Declare the supported options.
    ArgumentParser argparse = ArgumentParser();
    argparse.parseargs(argc, argv);
    cout << "Hello world!" << endl;
    return 0;
}
