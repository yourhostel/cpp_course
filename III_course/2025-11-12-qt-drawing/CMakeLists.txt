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

        canvas/canvas.cpp
        canvas/canvas.h

        modules/astroid_math.h

        tabs/pixel_pen_tab.cpp
        tabs/pixel_pen_tab.h
        tabs/shapes_tab.cpp
        tabs/shapes_tab.h
        tabs/lines_tab.cpp
        tabs/lines_tab.h

        widgets/analog_clock.h
)

target_include_directories(qt_drawing PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/canvas
        ${CMAKE_CURRENT_SOURCE_DIR}/tabs
        ${CMAKE_CURRENT_SOURCE_DIR}/modules
        ${CMAKE_CURRENT_SOURCE_DIR}/widgets
)

target_link_libraries(qt_drawing PRIVATE Qt6::Widgets Qt6::Gui)