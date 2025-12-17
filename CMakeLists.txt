cmake_minimum_required(VERSION 3.29)
project(CLib C)

set(CMAKE_C_STANDARD 11)

include_directories(. array matrix)

set(LIB_SOURCES
        array/array.c
        array/array.h
        array/array_math.c
        array/array_math.h

        matrix/matrix.c
        matrix/matrix.h
        matrix/matrix_math.c
        matrix/matrix_math.h

        errors.h
)

file(GLOB NN_SOURCES "nn/*.c")
list(APPEND LIB_SOURCES ${NN_SOURCES})

add_executable(CLib
        main.c
        ${LIB_SOURCES}
)

file(GLOB EXAMPLES "examples/*.c")
foreach(EXAMPLE_FILE ${EXAMPLES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_FILE} NAME_WE)
    add_executable(${EXAMPLE_NAME}
            ${EXAMPLE_FILE}
            ${LIB_SOURCES}
    )
endforeach()

file(GLOB EXAMPLES "nn/*.c")
foreach(EXAMPLE_FILE ${EXAMPLES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_FILE} NAME_WE)
    add_executable(${EXAMPLE_NAME}
            ${EXAMPLE_FILE}
            ${LIB_SOURCES}
    )
endforeach()
