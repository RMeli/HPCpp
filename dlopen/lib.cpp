#include <iostream>

#include "handle.h"

// extern "C" disables C++ name mangling
//
// Without extern "C", the function name is mangled:
//     $ nm -gD build/liblib.so | grep add
//     00000000000010f9 T _Z3addii
//
// With extern "C", the function name is not mangled:
//     $ nm -gD build/liblib.so | grep add
//     00000000000010f9 T add
extern "C" auto add(int a, int b) -> int {
    return a + b;
}

// Automatic plugin registration
__attribute__((constructor))
void register_plugin(){
    std::cout << "Registering plugin... ";
    plugin_t plugin;
    plugin.name = "add";
    plugin.add = add;
    register_plugin(plugin);
    std::cout << "OK" << std::endl;
}