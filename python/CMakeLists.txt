cmake_minimum_required(VERSION 3.15)
project(mm LANGUAGES C)

find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)

# Python 3.10 limited API
set(PYTHON_LIMITED_API 0x030A0000)

add_library(mm MODULE mmmodule.c)

# Compile with limited ABI
target_compile_definitions(mm PRIVATE Py_LIMITED_API=${PYTHON_LIMITED_API})

target_link_libraries(mm PRIVATE Python::Module)

# Set the output name to remove the "lib" prefix
set_target_properties(mm PROPERTIES PREFIX "")

# Install the module
install(TARGETS mm DESTINATION .)