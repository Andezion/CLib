cmake_minimum_required(VERSION 3.29)
project(CLib C)

set(CMAKE_C_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR})

file(GLOB ARRAY_SOURCES "${CMAKE_SOURCE_DIR}/array/*.c")
file(GLOB MATRIX_SOURCES "${CMAKE_SOURCE_DIR}/matrix/*.c")
file(GLOB NN_SOURCES "${CMAKE_SOURCE_DIR}/nn/*.c")

add_library(array_lib STATIC ${ARRAY_SOURCES})
target_include_directories(array_lib PUBLIC ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/array)

add_library(matrix_lib STATIC ${MATRIX_SOURCES})
target_include_directories(matrix_lib PUBLIC ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/matrix)

add_library(nn_lib STATIC ${NN_SOURCES})
target_include_directories(nn_lib PUBLIC ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/nn)

target_link_libraries(nn_lib PUBLIC matrix_lib array_lib)

if(EXISTS "${CMAKE_SOURCE_DIR}/main.c")
        add_executable(CLib main.c)
        target_link_libraries(CLib PRIVATE array_lib matrix_lib nn_lib)
endif()

file(GLOB EXAMPLES "${CMAKE_SOURCE_DIR}/examples/*.c")
foreach(EXAMPLE_FILE ${EXAMPLES})
        get_filename_component(EXAMPLE_NAME ${EXAMPLE_FILE} NAME_WE)
        add_executable(${EXAMPLE_NAME} ${EXAMPLE_FILE})

        target_link_libraries(${EXAMPLE_NAME} PRIVATE nn_lib matrix_lib array_lib)
endforeach()

