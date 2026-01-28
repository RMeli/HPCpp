cmake_minimum_required(VERSION 3.20)
project(nptest)
set(CMAKE_CXX_STANDARD 20)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

add_executable(nptest main.cpp)

target_link_libraries(nptest PRIVATE Python3::Python)
target_include_directories(nptest PRIVATE ${Python3_INCLUDE_DIRS})
