cmake_minimum_required(VERSION 3.6)
project(Ass2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    convolution.cpp
    histogram.cpp
    reverse0.cpp
    reverse1.cpp
    reverse2.cpp)

add_executable(Ass2 ${SOURCE_FILES})