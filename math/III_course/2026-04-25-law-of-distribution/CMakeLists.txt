# math/III_course/2026-04-20-bernoulli-laplace-poisson-review/CMakeLists.txt
project(law_of_distribution)

set(CMAKE_CXX_STANDARD 23)
# Якщо компілятор не підтримує вказаний стандарт C++(тут 23), збірка має впасти.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Код у чистому стандарті C++, без нестандартних розширень компілятора.
# Код збирається однаково в GCC, Clang, MSVC.
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(law_of_distribution
        main.cpp
        # <dir>/class.h
        # <dir>/class.cpp
)

target_link_libraries(law_of_distribution PRIVATE math_iii_lib)

target_include_directories(law_of_distribution PRIVATE
#         ${CMAKE_CURRENT_SOURCE_DIR}
#         ${CMAKE_CURRENT_SOURCE_DIR}/../lib/math_iii_stats
)