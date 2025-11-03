# cpp_course/III_course/2025-11-03-qt-gui-basics/exchange_form/CMakeLists.txt
project(exchange_form)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Network)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(exchange_form
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

target_link_libraries(exchange_form PRIVATE Qt6::Widgets Qt6::Gui Qt6::Network)