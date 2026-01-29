#ifndef HANDLE_H
#define HANDLE_H

#include <string>
#include <functional>
#include <iostream>

struct plugin_t {
    std::string name;
    // Use raw function pointer to avoid issues with std::function
    // holding state that may become invalid when the shared library is unloaded
    int(*add)(int, int);
};

extern plugin_t PLUGIN;

inline void register_plugin(plugin_t plugin){
    PLUGIN = plugin;
}

#endif
