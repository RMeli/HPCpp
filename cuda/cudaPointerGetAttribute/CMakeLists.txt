cmake_minimum_required(VERSION 3.18)
project(cuda_pointer_get_attribute LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

find_package(CUDAToolkit REQUIRED)

add_executable(ptr ptr.cpp)
set_source_files_properties(ptr.cpp PROPERTIES LANGUAGE CUDA)

target_link_libraries(ptr PRIVATE CUDA::cudart)
