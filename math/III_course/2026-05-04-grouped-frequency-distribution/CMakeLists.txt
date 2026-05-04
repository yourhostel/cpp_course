# math/III_course/2026-05-04-grouped-frequency-distribution/CMakeLists.txt
project(grouped_frequency_distribution)

set(CMAKE_CXX_STANDARD 23)
# Якщо компілятор не підтримує вказаний стандарт C++(тут 23), збірка має впасти.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Код у чистому стандарті C++, без нестандартних розширень компілятора.
# Код збирається однаково в GCC, Clang, MSVC.
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(grouped_frequency_distribution
        main.cpp
        # <dir>/class.h
        # <dir>/class.cpp
)

target_link_libraries(grouped_frequency_distribution PRIVATE math_iii_lib)

target_include_directories(grouped_frequency_distribution PRIVATE
        #         ${CMAKE_CURRENT_SOURCE_DIR}
        #         ${CMAKE_CURRENT_SOURCE_DIR}/../lib/math_iii_stats
)

#find_package(Qt6 REQUIRED COMPONENTS Widgets Charts)
#
#target_link_libraries(grouped_frequency_distribution PRIVATE Qt6::Widgets Qt6::Charts)