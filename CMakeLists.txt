cmake_minimum_required(VERSION 3.30)
project(xpath C)

set(CMAKE_C_STANDARD 11)

include_directories(code)

add_executable(xpath
    code/helper.c
    code/helper.h
    code/path_element.h
    code/path_element.c)
