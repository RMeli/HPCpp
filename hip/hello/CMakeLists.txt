cmake_minimum_required(VERSION 3.21)
cmake_policy(VERSION 3.21.3...3.27)
project(hello LANGUAGES CXX HIP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_HIP_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-Wall")

set(AMDGPU_TARGETS "gfx90a")

add_executable(hello hello.hip)
