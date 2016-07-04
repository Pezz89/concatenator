cmake_minimum_required(VERSION 3.5.2)
set(CMAKE_CXX_STANDARD 11)
# Set the project name
project (concatenator)

###############################################################################
### Boost Settings
find_package(Boost 1.60.0 COMPONENTS program_options log log_setup thread date_time filesystem system REQUIRED) 

if (NOT FO_BOOST_STATIC_LINK)
add_definitions(-DBOOST_ALL_NO_LIB -DBOOST_ALL_DYN_LINK -DBOOST_LOG_DYN_LINK)
endif()

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
###############################################################################

# Set build flags
set(CMAKE_CXX_FLAGS "-g -Wall ")
# Set cmake to output executable to the bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find all included header files.
include_directories(include)
include_directories(${Boost_INCLUDE_DIRS}) 
add_subdirectory(external)

# Build the executable from the source files found


set(CONCATENATOR_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(CONCATENATOR_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(CONCATENATOR_TEST_DIR ${PROJECT_SOURCE_DIR}/tests)

set(CONCATENATOR_SOURCE_FILES
    ${CONCATENATOR_SOURCE_DIR}/Concatenator.cpp
)
set(CONCATENATOR_HEADER_FILES
    ${CONCATENATOR_INCLUDE_DIR}/config.hpp
)
set(CONCATENATOR_TEST_SOURCES
    ${CONCATENATOR_TEST_DIR}/Concatenator_Basic_Tests.cpp
)

add_executable(concatenator ${CONCATENATOR_SOURCE_DIR}/concatenator.cpp)

target_link_libraries(concatenator ${Boost_LIBRARIES})
# Test build options (this code adapted from: https://github.com/ComicSansMS/GhulbusBase/blob/master/CMakeLists.txt)
option(BUILD_TESTS "Determines whether to build tests." ON)
if(BUILD_TESTS)
    enable_testing()

    if(NOT TARGET Catch)
        include(ExternalProject)
        if(WIN32)
            set(FETCH_EXTERNAL_CATCH
                URL https://github.com/philsquared/Catch/archive/v1.2.1-develop.12.zip
                URL_HASH MD5=cda228922a1c9248364c99a3ff9cd9fa)
        else()
            set(FETCH_EXTERNAL_CATCH
                URL https://github.com/philsquared/Catch/archive/v1.2.1-develop.12.tar.gz
                URL_HASH MD5=a8dfb7be899a6e7fb30bd55d53426122)
        endif()
        ExternalProject_Add(Catch-External
            PREFIX ${CMAKE_BINARY_DIR}/external/Catch
            ${FETCH_EXTERNAL_CATCH}
            CONFIGURE_COMMAND ""
            BUILD_COMMAND ""
            INSTALL_COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/external/Catch/src/Catch-External/single_include/catch.hpp
                                                     ${CMAKE_BINARY_DIR}/external/Catch/include/catch.hpp
        )
        add_library(Catch INTERFACE)
        add_dependencies(Catch Catch-External)
        target_include_directories(Catch INTERFACE ${CMAKE_BINARY_DIR}/external/Catch/include)
    endif()

    add_executable(Concatenator_Base_Test ${CONCATENATOR_TEST_SOURCES})
    add_test(NAME TestBase COMMAND Concatenator_Base_Test)
endif()
