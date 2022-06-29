cmake_minimum_required(VERSION 3.18)
project(lru_cache LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-Wall")

add_executable(lru_cache
    main.cpp
    ../../_utils/timer.cpp
)
target_include_directories(lru_cache PRIVATE "../../_utils/")

