#include <iostream>
#include <dlfcn.h>

#include "handle.h"

plugin_t PLUGIN;

auto main(int argc, char* argv[]) -> int {

    // -----
    // Load shared libarary
    // This automatically calls the constructor function in lib.cpp
    // PLUGIN is populated by the constructor
    // -----

    auto handle = dlopen("build/liblib.so", RTLD_LAZY);

    if(!handle) {
        std::cerr << "Cannot open library: " << dlerror() << '\n';
        return 1;
    }
    dlerror(); // Reset errors
    

    // -----
    // Manually load symbol 'add' from the shared library
    // PLUGIN is not used here
    // -----
    using add_t = int(*)(int, int);
    auto add = reinterpret_cast<add_t>(dlsym(handle, "add"));

    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol 'add': " << dlsym_error << '\n';
        dlclose(handle);
        return 1;
    }

    int result = add(1, 2);
    std::cout << "MANUALLY LOADED SYMBOL:\n";
    std::cout << "1 + 2 = " << result << '\n';
    
    // -----
    // Use the automatically registered plugin from the shared library
    // -----
    std::cout << "\nAUTOMATICALLY REGISTERED PLUGIN:\n";
    std::cout << "plugin.name: " << PLUGIN.name << '\n';
    std::cout << "plugin.add(3, 4) = " << PLUGIN.add(3, 4) << '\n';

    // -----
    // Cleanup
    // -----

    dlclose(handle);

    return 0;
}