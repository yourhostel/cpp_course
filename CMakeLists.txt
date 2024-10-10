cmake_minimum_required(VERSION 3.29)
project(cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(Practical_3/Tasks)

add_executable(cpp
    Practical_2/MyFirstProgram/MyFirstProgram.cpp
    Practical_3/Tasks/console_utils.cpp
    Practical_3/Tasks/console_utils.h
    Practical_3/Tasks/Task1.cpp
    Practical_3/Tasks/Task2.cpp
    Practical_3/Tasks/Task3.cpp
    Practical_3/Tasks/Task4.cpp)
