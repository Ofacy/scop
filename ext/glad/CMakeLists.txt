cmake_minimum_required(VERSION 4.1.1)
project(Glad)

add_library(glad include/glad/gl.h src/gl.c)
target_include_directories(glad PUBLIC include/)