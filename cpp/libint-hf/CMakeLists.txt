cmake_minimum_required(VERSION 3.20)

project(hfuture LANGUAGES CXX DESCRIPTION "Hartree-Fock with pika and DLA-Future")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(Libint2 REQUIRED) # Libint2::int2

# Hartree-Fock
add_executable(hf.x hf.cpp)
target_link_libraries(hf.x PRIVATE Libint2::int2)
