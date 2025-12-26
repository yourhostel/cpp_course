# cpp_course/III_course/2025-12-26-semester-assessments/CMakeLists.txt
project(semester_assessments LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
# Якщо компілятор не підтримує вказаний стандарт C++(тут 23), збірка має впасти.
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Код у чистому стандарті C++, без нестандартних розширень компілятора.
# Код збирається однаково в GCC, Clang, MSVC.
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(semester_assessments
        main.cpp
        classes/University.cpp
        classes/SolidOfRevolution.cpp
)

target_include_directories(semester_assessments PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/classes
)