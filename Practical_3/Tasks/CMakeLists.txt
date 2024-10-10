cmake_minimum_required(VERSION 3.29)
project(Tasks)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Tasks
    console_utils.cpp
    console_utils.h
    Task1.cpp
    Task2.cpp
    Task3.cpp
    Task4.cpp)
