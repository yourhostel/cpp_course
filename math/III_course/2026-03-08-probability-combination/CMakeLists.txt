# math/III_course/2026-03-08-probability-combination/CMakeLists.txt
project(probability-combination)

set(CMAKE_CXX_STANDARD 23)
# Якщо компілятор не підтримує вказаний стандарт C++(тут 23), збірка має впасти.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Код у чистому стандарті C++, без нестандартних розширень компілятора.
# Код збирається однаково в GCC, Clang, MSVC.
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(probability-combination
        main.cpp
        Validator.h
        Validator.tpp

        # <dir>/class.h
        # <dir>/class.cpp
)

target_include_directories(probability-combination PRIVATE
        # ${CMAKE_CURRENT_SOURCE_DIR}
        # ${CMAKE_CURRENT_SOURCE_DIR}/<dir>
)