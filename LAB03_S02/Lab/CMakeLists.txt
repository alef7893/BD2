cmake_minimum_required(VERSION 3.28)
project(Lab)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab
        main.cpp
        Record.h
        Page.h
        B+TreeFile.h)
