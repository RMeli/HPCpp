# Shared library lib.cpp and main.cpp target
cmake_minimum_required(VERSION 3.20)
project(dload_example LANGUAGES CXX)

add_library(lib SHARED lib.cpp)

add_executable(main main.cpp)
# Link against dl library for dlopen/dlsym/dlclose
target_link_libraries(main PRIVATE ${CMAKE_DL_LIBS})
# Export main's symbols so dlopen'd libraries can find them (e.g., PLUGIN)
set_target_properties(main PROPERTIES ENABLE_EXPORTS TRUE)