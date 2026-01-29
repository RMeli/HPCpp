#include <iostream>
#include <dlfcn.h>

auto main(int argc, char* argv[]) -> int {

    auto handle = dlopen("build/liblib.so", RTLD_LAZY);

    if(!handle) {
        std::cerr << "Cannot open library: " << dlerror() << '\n';
        return 1;
    }
    dlerror(); // Reset errors
    

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
    
    dlclose(handle);

    return 0;
}
