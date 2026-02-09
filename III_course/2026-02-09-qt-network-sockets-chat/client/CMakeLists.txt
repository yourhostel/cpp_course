# cpp_course/III_course/2026-02-09-qt-network-sockets-chat/client/CMakeLists.txt

project(chat_client)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(chat_client
        main.cpp
        client.cpp
        client.h
        client.ui
)

target_include_directories(chat_client PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}/chat_client_autogen/include
)

target_link_libraries(chat_client PRIVATE
        Qt6::Widgets
        Qt6::Network
)