# cpp_course/III_course/2025-11-19-qt-practical-13-postgresql/rental/CMakeLists.txt

project(rental)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(rental
        main.cpp
        rental.cpp
        rental.h
        rental.ui
)

target_link_libraries(student_form PRIVATE Qt6::Widgets Qt6::Gui)