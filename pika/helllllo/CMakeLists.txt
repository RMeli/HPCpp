cmake_minimum_required(VERSION 3.18)
project(pika_hello CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(pika REQUIRED)

add_executable(pika_hello main.cpp)
target_link_libraries(pika_hello pika::pika)
