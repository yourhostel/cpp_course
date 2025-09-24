# III_course/2025-09-04-sqrt/CMakeLists.txt
project(2025-09-04-sqrt)

set(CMAKE_CXX_STANDARD 23)

# 1) Програма для sqrt (main + root)
add_executable(sqrt_2025_09_04
        main.cpp
        root.cpp
)

# 2) Друкує ім'я
add_executable(name_2025_09_04
        name.cpp
)

# 3) Рахує вік у днях
add_executable(age_2025_09_04
        age.cpp
)

# lecture3.cpp
add_executable(lecture3_2025_09_04
        lecture3.cpp
)