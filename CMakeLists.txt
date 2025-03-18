# Specify the minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(PicoDB VERSION 1.0.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the installation directory for the library
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

# Define the library output directory
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# Define the include directories for the project
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add the source files for the PicoDB library
set(SOURCES
    src/PicoDB.cpp
    src/core/Cell.cpp
    src/core/ConfigManager.cpp
    src/core/Database.cpp
    src/core/Table.cpp
    src/core/UserPermissionManager.cpp
    src/storage/Encryptor.cpp
    src/storage/FileHandler.cpp
    src/utils/Date.cpp
    src/utils/Map.cpp
    src/utils/String.cpp
    src/utils/StringVectorConverter.cpp
    src/utils/Vector.cpp
)

# Define the header files for the project
set(HEADERS
    include/PicoDB/PicoDB.h
    include/PicoDB/Cell.h
    include/PicoDB/ConfigManager.h
    include/PicoDB/Database.h
    include/PicoDB/Table.h
    include/PicoDB/UserPermissionManager.h
    include/PicoDB/Encryptor.h
    include/PicoDB/FileHandler.h
    include/PicoDB/String.h
    include/PicoDB/StringVectorConverter.h
    include/PicoDB/Vector.h
)

# Create a static library
add_library(picoDB STATIC ${SOURCES})

# Set the include directories for the library (public headers)
target_include_directories(picoDB PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Specify the directory for the header files
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

# Specify the installation of the library
install(TARGETS picoDB DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

# Create a basic executable to test the library (optional)
# add_executable(test_picoDB test/test.cpp)
# target_link_libraries(test_picoDB picoDB)

# Enable testing if you have unit tests
# enable_testing()
# add_subdirectory(test)

# Optionally, add CMake modules or dependencies (for example, Google Test for unit testing)
# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})
# target_link_libraries(test_picoDB ${GTEST_LIBRARIES})
