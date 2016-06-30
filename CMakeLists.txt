cmake_minimum_required(VERSION 3.5.2)
set(CMAKE_CXX_STANDARD 11)
# Set the project name
project (concatenator)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.60.0 COMPONENTS program_options log log_setup thread date_time filesystem system) 

if (NOT FO_BOOST_STATIC_LINK)
add_definitions(-DBOOST_ALL_NO_LIB -DBOOST_ALL_DYN_LINK -DBOOST_LOG_DYN_LINK)
endif()

# Set build flags
set(CMAKE_CXX_FLAGS "-g -Wall ")
# Set cmake to output executable to the bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)

# Find all the source fies in the src directory
file(GLOB SOURCES "src/*.cpp")

# Build the executable from the source files found
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(concatenator ${SOURCES})
    target_link_libraries(concatenator ${Boost_LIBRARIES})
endif()
