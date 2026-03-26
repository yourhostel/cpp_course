# math/III_course/2026-03-26-anova/CMakeLists.txt
project(anova)

set(CMAKE_CXX_STANDARD 23)
# Якщо компілятор не підтримує вказаний стандарт C++(тут 23), збірка має впасти.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Код у чистому стандарті C++, без нестандартних розширень компілятора.
# Код збирається однаково в GCC, Clang, MSVC.
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(anova
        main.cpp
        # <dir>/class.h
        # <dir>/class.cpp
)

find_package(PostgreSQL REQUIRED)

target_include_directories(anova PRIVATE
        ${PostgreSQL_INCLUDE_DIRS}
        # ${CMAKE_CURRENT_SOURCE_DIR}/<dir>
)

target_link_libraries(anova PRIVATE
        ${PostgreSQL_LIBRARIES}
)