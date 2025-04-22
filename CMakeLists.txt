# CMakeLists.txt
cmake_minimum_required(VERSION 3.12)
project(TaskMaseter++ CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include header files from current and include directories
include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)

# Add all source files
file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(tsm ${SOURCES})