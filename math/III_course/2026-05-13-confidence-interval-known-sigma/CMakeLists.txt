# math/III_course/2026-05-13-confidence-interval-known-sigma/CMakeLists.txt
project(confidence_interval_known_sigma)

set(CMAKE_CXX_STANDARD 23)
# Якщо компілятор не підтримує вказаний стандарт C++(тут 23), збірка має впасти.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Код у чистому стандарті C++, без нестандартних розширень компілятора.
# Код збирається однаково в GCC, Clang, MSVC.
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(confidence_interval_known_sigma
        main.cpp
)

target_link_libraries(confidence_interval_known_sigma PRIVATE math_iii_lib)

