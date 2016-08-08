#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "H5Cpp.h"

using namespace H5;

int main( int argc, char* const argv[] )
{
    // Global setup goes here...
    // Prevent HDF5 library from printing errors that are handeled in try/catch blocks.
    //Exception::dontPrint();

    int result = Catch::Session().run( argc, argv );

    // global clean-up goes here...

    return result;
}

