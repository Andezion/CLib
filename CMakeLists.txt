cmake_minimum_required(VERSION 3.29)
project(CLib C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(CLib
    main.c
        array_1d.c
        array_1d.h
        array_2d.c
        array_2d.h)
