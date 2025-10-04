cmake_minimum_required(VERSION 3.29)
project(CLib C)

set(CMAKE_C_STANDARD 11)

include_directories(. array matrix)

add_executable(CLib
        main.c

        array/array.c
        array/array.h

        matrix/matrix.c
        matrix/matrix.h

        matrix/matrix_math.c
        matrix/matrix_math.h

        errors.h
        array/array_math.c
        array/array_math.h)
