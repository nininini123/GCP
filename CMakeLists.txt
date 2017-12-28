cmake_minimum_required(VERSION 3.9)
project(GraphColor)

set(CMAKE_CXX_STANDARD 11)

add_executable(GraphColor main.cpp readCSV.cpp tabuSearch.cpp)