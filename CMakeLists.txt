cmake_minimum_required(VERSION 3.5.2)
# Set the project name
project (concatenator)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.60.0 COMPONENTS program_options) 


# Set build flags
set(CMAKE_CXX_FLAGS "-g -Wall")
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
