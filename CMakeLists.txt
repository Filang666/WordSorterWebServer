cmake_minimum_required(VERSION 3.20)
# Set the project name
project(WordSorterWebServer)

# Find the Boost library
find_package(Boost REQUIRED COMPONENTS program_options filesystem)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the sources for the WordSorter class
add_library(WordSorter
    src/WordSorter.cpp
    src/WordSorter.h
)

# Define the executable for the WebServer
add_executable(WordSorterWebServer
    src/main.cpp
    src/WebServer.cpp
)

# Link the Boost libraries with the WebServer executable
target_link_libraries(WordSorterWebServer
    PRIVATE
    WordSorter
    Boost::filesystem
)

# Include directories for header files
target_include_directories(WordSorterWebServer
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
