# Shared library lib.cpp and main.cpp target
cmake_minimum_required(VERSION 3.20)
project(dload_example LANGUAGES CXX)

add_library(lib SHARED lib.cpp)

add_executable(main main.cpp)