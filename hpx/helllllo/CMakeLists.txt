cmake_minimum_required(VERSION 3.18)
project(hpx_hello CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(HPX REQUIRED)

add_executable(hpx_hello main.cpp)
target_link_libraries(hpx_hello HPX::hpx)
