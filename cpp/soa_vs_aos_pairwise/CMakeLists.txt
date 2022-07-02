cmake_minimum_required(VERSION 3.18)
project(soa_vs_aos_pairwise LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-Wall")

add_executable(soa_vs_aos_pairwise
    main.cpp
    ../../_utils/timer.cpp
)
target_include_directories(soa_vs_aos_pairwise PRIVATE "../../_utils/")
