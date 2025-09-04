# II_course/CMakeLists.txt

# Тут ми автоматично шукаємо всі каталоги виду Practical_*
# і створюємо для кожного окремий executable без зайвих CMakeLists.txt

file(GLOB CHILD_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "Practical_*")

foreach(dir ${CHILD_DIRS})
    # Знайдемо всі .cpp файли у каталозі
    file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${dir}/*.cpp")

    if (SRC_FILES)
        # Назву таргету робимо таку ж, як назва каталогу (наприклад Practical_2_15)
        add_executable(${dir} ${SRC_FILES})
        message(STATUS "Added target ${dir} with sources: ${SRC_FILES}")
    else()
        message(WARNING "No .cpp files found in ${dir}, skipping")
    endif()
endforeach()
