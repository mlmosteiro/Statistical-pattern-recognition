cmake_minimum_required(VERSION 3.6)
project(Linear)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Utility.cpp Utility.h Set.cpp Set.h)
add_executable(Linear ${SOURCE_FILES})