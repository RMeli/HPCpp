cmake_minimum_required(VERSION 3.25)
project(kokkos_pytorch CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(Kokkos REQUIRED CONFIG)
find_package(Torch REQUIRED CONFIG)

add_executable(kpt main.cpp)
target_link_libraries(kpt Kokkos::kokkos ${TORCH_LIBRARIES})
