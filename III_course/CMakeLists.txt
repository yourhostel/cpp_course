# III_course/CMakeLists.txt
# Автозбірка всіх підкаталогів: у кожному шукаємо .cpp та робимо окремі таргети.

#file(GLOB SUBDIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*")
#
#foreach(dir ${SUBDIRS})
#    if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${dir}")
#        # усі .cpp у підкаталозі
#        file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${dir}/*.cpp")
#        if (SRC_FILES)
#            # Ім'я таргету = назва каталогу (наприклад 2025-09-04-sqrt)
#            add_executable(${dir} ${SRC_FILES})
#            target_compile_features(${dir} PRIVATE cxx_std_23)
#            message(STATUS "III_course: додано таргет ${dir}")
#        endif()
#    endif()
#endforeach()

# III_course/CMakeLists.txt
add_subdirectory(2025-09-04-sqrt)