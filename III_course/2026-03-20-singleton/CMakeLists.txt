# III_course/2026-03-20-singleton/CMakeLists.txt
project(singleton)

set(CMAKE_CXX_STANDARD 23)
# Якщо компілятор не підтримує вказаний стандарт C++(тут 23), збірка має впасти.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Код у чистому стандарті C++, без нестандартних розширень компілятора.
# Код збирається однаково в GCC, Clang, MSVC.
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(singleton
        main.cpp
        #        <dir>/class.h
        #        <dir>/class.cpp
)

target_include_directories(singleton PRIVATE
#        ${CMAKE_CURRENT_SOURCE_DIR}
        #        ${CMAKE_CURRENT_SOURCE_DIR}/<dir>
)