# math/III_course/lib/CMakeLists.txt
add_library(math_iii_lib INTERFACE)

target_include_directories(math_iii_lib
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(math_iii_lib
        INTERFACE
        cxx_std_23
)

find_package(Qt6 REQUIRED COMPONENTS Widgets Charts)

target_link_libraries(math_iii_lib INTERFACE Qt6::Widgets Qt6::Charts)