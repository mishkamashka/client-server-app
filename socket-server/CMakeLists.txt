cmake_minimum_required(VERSION 3.12)
project(sp_lab4 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(sp_lab4
        linked-list.c
        linked-list.h
        functions.c
        functions.h
        file_io.c
        file_io.h
        main.c)

target_link_libraries(sp_lab4 m)