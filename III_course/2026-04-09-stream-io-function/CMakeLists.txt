# III_course/2026-04-09-stream-io-function/CMakeLists.txt
project(stream_io_function)

set(CMAKE_CXX_STANDARD 23)
# Якщо компілятор не підтримує вказаний стандарт C++(тут 23), збірка має впасти.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Код у чистому стандарті C++, без нестандартних розширень компілятора.
# Код збирається однаково в GCC, Clang, MSVC.
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(stream_io_function
        main.cpp
        Function.tpp
        #        <dir>/class.h
        #        <dir>/class.cpp
)

target_include_directories(stream_io_function PRIVATE
        #        ${CMAKE_CURRENT_SOURCE_DIR}
        #        ${CMAKE_CURRENT_SOURCE_DIR}/<dir>
)

set(DATA_FILES
#       sin_cos.txt
#        log_exp.txt
#        square_cube.txt
#       linear_square.txt

#        inv_linear.txt
#       abs_saw.txt
#       diode_sigmoid.txt
#       tanh_gauss.txt
)

foreach(file ${DATA_FILES})
    configure_file(
            ${CMAKE_CURRENT_SOURCE_DIR}/${file}
            ${CMAKE_CURRENT_BINARY_DIR}/${file}
            COPYONLY
    )
endforeach()