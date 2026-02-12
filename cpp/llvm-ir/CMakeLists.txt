cmake_minimum_required(VERSION 3.20)
project(llvm_ir_explorer CXX)

if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(FATAL_ERROR
        "This project must be configured with clang++.\n"
        "Re-run CMake with:  -DCMAKE_CXX_COMPILER=clang++")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(main main.cpp)

set(OPT_LEVEL "O2" CACHE STRING "Optimization level.")

set(IR_DIR       "${CMAKE_CURRENT_BINARY_DIR}/ir")
set(ASM_DIR      "${CMAKE_CURRENT_BINARY_DIR}/asm")
file(MAKE_DIRECTORY "${IR_DIR}" "${ASM_DIR}")

set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

# Emit LLVM IR
add_custom_target(ir
    COMMAND "${CMAKE_CXX_COMPILER}"
        -${OPT_LEVEL} -emit-llvm -S -std=c++20
        -o "${IR_DIR}/main.ll"
        "${SRC}"
    VERBATIM
)

# Emit ASM
add_custom_target(asm
    COMMAND "${CMAKE_CXX_COMPILER}"
        -${OPT_LEVEL} -S -fverbose-asm -std=c++20
        -o "${ASM_DIR}/main.s"
        "${SRC}"
    VERBATIM
)