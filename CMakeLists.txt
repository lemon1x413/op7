cmake_minimum_required(VERSION 3.29)
project(op7 C)

set(CMAKE_C_STANDARD 99)

add_executable(op7 main.c
        function.h
        color.h)
