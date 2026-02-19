cmake_minimum_required(VERSION 3.20)
project(umpire CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(umpire REQUIRED)
find_package(OpenMP REQUIRED)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE umpire OpenMP::OpenMP_CXX)
target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic)
