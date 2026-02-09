# cpp_course/III_course/2026-02-09-qt-network-sockets-chat/server/CMakeLists.txt

project(chat_server)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(chat_server
        main.cpp
        server.cpp
        server.h
        server.ui
)

target_include_directories(chat_server PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}/chat_server_autogen/include
)

target_link_libraries(chat_server PRIVATE
        Qt6::Widgets
        Qt6::Network
)
