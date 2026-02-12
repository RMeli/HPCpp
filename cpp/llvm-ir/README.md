# LLVM IR

With `clang++` it is possible to inspect LLVM IR, after optimization or after each optimization pass.

After optimization:
```bash
clang++ -O2 -emit-llvm -S main.cpp -o main.ll
```

After each optimization pass:
```bash
clang++ -O2 -mllvm -print-after-all main.cpp
```

## Build

```bash
cmake -S . -B build -DCMAKE_CXX_COMPILER=clang++ -DOPT_LEVEL=O0
cmake --build build --target ir
cmake --build build --target asm
cmake --build build
```