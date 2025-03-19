cmake_minimum_required(VERSION 3.10)
project(PicoDBTests)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

set(GTEST_ROOT "/opt/homebrew/Cellar/googletest/1.16.0")
include_directories(${GTEST_ROOT}/include)
link_directories(${GTEST_ROOT}/lib)

# Add Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Collect all source files
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/core/*.cpp"
    "src/storage/*.cpp"
    "src/utils/*.cpp"
)

# Add the test executable
add_executable(runTests test/test_create_table.cpp ${SOURCES})

# Link Google Test libraries
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)