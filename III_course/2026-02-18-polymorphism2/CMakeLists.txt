# III_course/2026-02-18-polymorphism2/CMakeLists.txt
project(polymorphism2)

set(CMAKE_CXX_STANDARD 23)
# Якщо компілятор не підтримує вказаний стандарт C++(тут 23), збірка має впасти.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Код у чистому стандарті C++, без нестандартних розширень компілятора.
# Код збирається однаково в GCC, Clang, MSVC.
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(polymorphism2
        main.cpp
        power/PowerStrategy.cpp
        power/PowerStrategy.h
        power/FastPowerStrategy.cpp
        power/FastPowerStrategy.h
)

target_include_directories(polymorphism2 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/power
)
