cmake_minimum_required(VERSION 3.12)
project(TaskMaster++ C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)

set(CPP_SOURCES
    src/main.cpp
    src/taskmanager.cpp
    src/usermanager.cpp
    src/bcrypt/bcrypt.cpp
    src/bcrypt/blowfish.cpp
)

add_executable(tsm ${CPP_SOURCES} )