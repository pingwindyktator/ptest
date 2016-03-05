cmake_minimum_required(VERSION 3.3)
#set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
#set(CMAKE_C_COMPILER "/usr/bin/clang")

project(ptest_demo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weffc++ -msse2 -std=c++14 -Ofast -pipe -Wall -Wextra -Wpedantic -pedantic-errors -Wcast-qual -Wmissing-include-dirs -Waddress -Wno-unused-parameter -Wconversion -pthread")

file(GLOB PTEST ../*cpp)

set(SOURCE_FILES demo.cpp)
add_executable(ptest_demo ${SOURCE_FILES} ${PTEST})
