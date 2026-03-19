# math/III_course/2026-03-19-continuous-random-variable/CMakeLists.txt
project(continuous-random-variable)

set(CMAKE_CXX_STANDARD 23)
# Якщо компілятор не підтримує вказаний стандарт C++(тут 23), збірка має впасти.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Код у чистому стандарті C++, без нестандартних розширень компілятора.
# Код збирається однаково в GCC, Clang, MSVC.
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(continuous-random-variable
        main.cpp
        DistributionRepository.cpp
        DistributionStatistics.tpp
        DistributionStatistics.h
        # ../2026-03-08-probability-combination/Probability.cpp

        # <dir>/class.h
        # <dir>/class.cpp
)

target_include_directories(continuous-random-variable PRIVATE
        # ${CMAKE_CURRENT_SOURCE_DIR}
        # ${CMAKE_CURRENT_SOURCE_DIR}/../2026-03-08-probability-combination
)