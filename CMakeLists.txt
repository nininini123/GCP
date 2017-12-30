cmake_minimum_required(VERSION 3.9)
project(GraphColor)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_BUILD_TYPE RELEASE)

add_executable(GraphColor main.cpp readCSV.cpp tabuSearch.cpp tabuSearch.h readCSV.h)