#include <dlfcn.h>
#include <iostream>

#include "handle.h"

plugin_t PLUGIN;

auto main(int argc, char *argv[]) -> int {

  // -----
  // Load shared libarary
  // This automatically calls the constructor function in lib.cpp
  // PLUGIN is populated by the constructor
  // -----
  
  std::cout << ">>> Started main.cpp\n";

  auto handle = dlopen("build/liblib.so", RTLD_LAZY);

  if (!handle) {
    std::cerr << "Cannot open library: " << dlerror() << '\n';
    return 1;
  }
  dlerror(); // Reset errors

  // -----
  // Use the automatically registered plugin from the shared library
  // -----
  std::cout << "AUTOMATICALLY REGISTERED PLUGIN:\n";
  std::cout << "plugin.name: " << PLUGIN.name << '\n';
  std::cout << "plugin.add(3, 4) = " << PLUGIN.add(3, 4) << '\n';

  // -----
  // Cleanup
  // -----

  dlclose(handle);

  return 0;
}
