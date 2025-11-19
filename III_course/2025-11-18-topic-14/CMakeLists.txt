# cpp_course/III_course/2025-11-18-topic-14/CMakeLists.txt
project(topic_14)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(topic_14
        main.cpp
        Accountant.cpp
        Accountant.h
        Employee.cpp
        Employee.h
        Employer.cpp
        Employee.h
        Person.cpp
        Person.h
        Position.cpp
        Position.h
        Calc.h
)
