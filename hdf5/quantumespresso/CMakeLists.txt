cmake_minimum_required(VERSION 3.22)
project(hdf5_qe CXX)

find_package(HDF5 REQUIRED)

add_executable(hdf5_qe main.cpp)
target_link_libraries(hdf5_qe hdf5::hdf5)
