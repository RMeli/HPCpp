# HPX Test

```bash
module load hpx
mkdir build && cd build
cmake ..
./hpx_hello
```

## HPX Installation

HPX has been installed with the following CMake command (from source, on macOS):

```bash
cmake .. -DHPX_WITH_APEX=TRUE -DHPX_WITH_EXAMPLES=TRUE -DHPX_WITH_TESTS=TRUE -DCMAKE_INSTALL_PREFIX=/Users/rmeli/Documents/software/hpx/ -DCMAKE_CXX_COMPILER=g++-11
```

where `g++-11` is the GCC compiler installed with Homebrew.

## HPX Module

In order to compile HPX applications, the same compiler used to compile HPX is required:

```text
CMake Error at /Users/rmeli/software/hpx/lib/cmake/HPX/HPX_Message.cmake:51 (message):
  ERROR: Compilers do not match.  In order to compile HPX application it is
  recommended to use the same compiler as you did for HPX.
  HPX_CXX_COMPILER=/usr/local/bin/g++-11,
  CMAKE_CXX_COMPILER=/Library/Developer/CommandLineTools/usr/bin/c++.
  HPX_CXX_COMPILER_ID=GNU, CMAKE_CXX_COMPILER_ID=AppleClang.
  HPX_CXX_COMPILER_VERSION=11.3.0,
  CMAKE_CXX_COMPILER_VERSION=13.1.6.13160021.  To disable this message set
  HPX_IGNORE_COMPILER_COMPATIBILITY to On.
```

In order to simplify the use of HPX with the correct compiler, a module can be created as follows:

```
proc ModulesHelp { } {
    puts stderr "HPX C++ library."
}

set modName [module-info name]

if { [ module-info mode load ] } {
    puts stderr "'$modName' module"
}

set HPX_ROOT            /Users/rmeli/software/hpx/

prepend-path PATH       $HPX_ROOT
setenv CC               gcc-11
setenv CXX              g++-11
```

Loading the HPX module with

```bash
module load hpx
```

prepends the HPX installation location to `PATH` and sets the `CC` and `CXX` variables to the compiler used to install HPX.
