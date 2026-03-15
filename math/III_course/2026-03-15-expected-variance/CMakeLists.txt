# math/III_course/2026-03-15-expected-variance/CMakeLists.txt
project(expected-variance)

set(CMAKE_CXX_STANDARD 23)
# Якщо компілятор не підтримує вказаний стандарт C++(тут 23), збірка має впасти.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Код у чистому стандарті C++, без нестандартних розширень компілятора.
# Код збирається однаково в GCC, Clang, MSVC.
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(expected-variance
        main.cpp
        # ../2026-03-08-probability-combination/Probability.cpp

        # <dir>/class.h
        # <dir>/class.cpp
)

target_include_directories(expected-variance PRIVATE
        # ${CMAKE_CURRENT_SOURCE_DIR}
        # ${CMAKE_CURRENT_SOURCE_DIR}/../2026-03-08-probability-combination
)