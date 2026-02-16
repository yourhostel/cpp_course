# III_course/2026-02-15-creating-own-components/CMakeLists.txt
project(creating_own_components LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
# Якщо компілятор не підтримує вказаний стандарт C++(тут 23), збірка має впасти.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Код у чистому стандарті C++, без нестандартних розширень компілятора.
# Код збирається однаково в GCC, Clang, MSVC.
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(creating_own_components
        main.cpp
        Components.cpp
        Components.h
        components.ui
        tabs/CounterTab.cpp
        tabs/CounterTab.h
        tabs/GridTab.cpp
        tabs/GridTab.h
)

target_include_directories(creating_own_components PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/tabs
)

target_link_libraries(creating_own_components PRIVATE
        Qt6::Widgets
)