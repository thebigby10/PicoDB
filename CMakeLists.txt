cmake_minimum_required(VERSION 3.10)
project(SingleFile LANGUAGES CXX)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Collect all source files
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/core/*.cpp"
    "src/storage/*.cpp"
    "src/utils/*.cpp"
)

# Compile only `example_usage.cpp`
add_executable(example_usage examples/example_usage.cpp ${SOURCES})
