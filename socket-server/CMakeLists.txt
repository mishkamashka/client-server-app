cmake_minimum_required(VERSION 3.12)
project(socket_server)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(socket_server
        include/file_io.h
        include/functions.h
        include/linked_list.h
        src/file_io.c
        src/functions.c
        src/linked_list.c
        src/main.c
        src/server.c
        makefile)
