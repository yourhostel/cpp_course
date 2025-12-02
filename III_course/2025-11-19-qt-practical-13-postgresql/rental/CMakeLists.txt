# cpp_course/III_course/2025-11-19-qt-practical-13-postgresql/rental/CMakeLists.txt

project(rental)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Sql)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(rental
        main.cpp
        rental.cpp
        db/sql_helper.cpp
        delegates/combo_delegate.cpp
        delegates/no_edit_delegate.cpp
        tabs/visual_components.cpp
        tabs/view_tables.cpp
        tabs/records_view.cpp
        tabs/relations_view.cpp
)

target_include_directories(rental PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/db
        ${CMAKE_CURRENT_SOURCE_DIR}/delegates
        ${CMAKE_CURRENT_SOURCE_DIR}/tabs
)

target_link_libraries(rental PRIVATE
        Qt6::Widgets
        Qt6::Gui
        Qt6::Sql)