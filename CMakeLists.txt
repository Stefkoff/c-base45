cmake_minimum_required(VERSION 3.26)
project(base45 C)

set(CMAKE_C_STANDARD 11)

add_executable(base45 main.c base45.h)
