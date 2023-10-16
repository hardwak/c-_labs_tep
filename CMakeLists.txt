cmake_minimum_required(VERSION 3.26)
project(tepLaby)

set(CMAKE_CXX_STANDARD 17)

add_executable(tepLaby memoryAllocation/main.cpp
        memoryAllocation/main.h
        memoryAllocation/CTable.cpp
        memoryAllocation/CTable.h)
