cmake_minimum_required(VERSION 2.8)
project(project4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Graph.cpp Graph.h)
add_executable(project4 ${SOURCE_FILES} Edges.cpp Edges.h)