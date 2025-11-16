# cpp_course/III_course/2025-11-15-qt-practical-11-tree-parser-2/CMakeLists.txt
project(qt_practical_11_tree_parser_2)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(qt_practical_11_tree_parser_2
        main.cpp
        calculation.cpp
        calculation.h
        calculation.ui
        expressiontree.h
        parser.h
)

target_link_libraries(qt_practical_11_tree_parser_2 PRIVATE Qt6::Widgets Qt6::Gui)