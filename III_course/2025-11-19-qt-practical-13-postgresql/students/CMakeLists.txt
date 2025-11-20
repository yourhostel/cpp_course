# cpp_course/III_course/2025-11-19-qt-practical-13-postgresql/students/CMakeLists.txt
project(students)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Sql)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(students
        main.cpp
        students.cpp
        students.h
        students.ui
)

target_link_libraries(students PRIVATE
        Qt6::Widgets
        Qt6::Gui
        Qt6::Sql)