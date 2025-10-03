cmake_minimum_required(VERSION 3.29)
project(CLib C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(CLib
        main.c

        array.c
        array.h

        matrix.c
        matrix.h

        matrix_math.c
        matrix_math.h

        errors.h)
