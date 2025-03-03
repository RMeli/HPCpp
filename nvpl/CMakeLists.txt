cmake_minimum_required(VERSION 3.12)

project(nvpl_test LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if(NOT NVPL_MPI_TYPE)
	set(NVPL_MPI_TYPE "mpich")
endif()

find_package("custom-blas" REQUIRED)
find_package("custom-lapack" REQUIRED)
find_package("custom-scalapack" REQUIRED)

add_executable(main main.cpp)
target_compile_options(main PRIVATE -Wall -Wextra)
target_link_libraries(main PUBLIC BLAS::BLAS LAPACK::LAPACK SCALAPACK::SCALAPACK)
