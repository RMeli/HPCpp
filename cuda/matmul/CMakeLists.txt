cmake_minimum_required(VERSION 3.20)
project(mm LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-Wall")

find_package(CUDA 11.0 REQUIRED)
find_package(benchmark REQUIRED)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)


add_executable(benchmark benchmark.cu mm.cpp mm.cu)
target_include_directories(benchmark PRIVATE "." "../../_utils/")
target_link_libraries(benchmark benchmark::benchmark benchmark::benchmark_main)

enable_testing()
add_executable(tests tests.cu mm.cpp mm.cu)
target_include_directories(tests PRIVATE "." "../../_utils/")
target_link_libraries(tests GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(tests)
