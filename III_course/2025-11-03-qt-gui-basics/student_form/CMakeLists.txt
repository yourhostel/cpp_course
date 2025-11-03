# cpp_course/III_course/2025-11-03-qt-gui-basics/student_form/CMakeLists.txt
project(student_form)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(student_form
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        resources.qrc
)

target_link_libraries(student_form PRIVATE Qt6::Widgets Qt6::Gui)