cmake_minimum_required(VERSION 3.26)
project(M2AP)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(main
        main.cpp
        DataList.h)
