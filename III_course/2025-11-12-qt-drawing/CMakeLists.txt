# cpp_course/III_course/2025-11-12-qt-drawing/CMakeLists.txt
project(qt_practical_10_tree_parser)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(qt_drawing
        main.cpp
        drawing.cpp
        drawing.h
        drawing.ui
)

target_link_libraries(qt_drawing PRIVATE Qt6::Widgets Qt6::Gui)