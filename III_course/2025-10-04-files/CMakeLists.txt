# III_course/2025-10-04-files/CMakeLists.txt
project(files)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(files
        main.cpp
)

# Копіювати car.csv у директорію збірки поруч із виконуваним файлом
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/car.csv ${CMAKE_CURRENT_BINARY_DIR}/car.csv COPYONLY)