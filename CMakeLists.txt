cmake_minimum_required(VERSION 3.12)
project(TaskMasterPlusPlus C CXX)  # Renamed here to avoid potential ++ issues

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/libs/json/single_include  # Key path for <nlohmann/json.hpp>
    ${CMAKE_SOURCE_DIR}/libs/Bcrypt.cpp/include
)

# Source files
set(CPP_SOURCES
    src/main.cpp
    src/taskmanager.cpp
    src/usermanager.cpp
    libs/Bcrypt.cpp/src/bcrypt.cpp
    libs/Bcrypt.cpp/src/blowfish.cpp
)

# Executable
add_executable(tsm ${CPP_SOURCES})
