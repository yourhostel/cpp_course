# cpp_course/III_course/2025-11-01-qt-tabulation/CMakeLists.txt
project(qt_tabulation)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Charts)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB MODEL_SRC "models/*.cpp")
file(GLOB MODEL_HDR "models/*.h")

file(GLOB CTRL_SRC "controllers/*.cpp")
file(GLOB CTRL_HDR "controllers/*.h")

file(GLOB VIEW_SRC "views/*.cpp")
file(GLOB VIEW_HDR "views/*.h")

add_executable(qt_tabulation
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

        ${MODEL_SRC} ${MODEL_HDR}
        ${CTRL_SRC} ${CTRL_HDR}
        ${VIEW_SRC} ${VIEW_HDR}
)

target_include_directories(qt_tabulation PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/models
        ${CMAKE_CURRENT_SOURCE_DIR}/controllers
        ${CMAKE_CURRENT_SOURCE_DIR}/views
)

target_link_libraries(qt_tabulation PRIVATE Qt6::Widgets Qt6::Charts)