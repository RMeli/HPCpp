#ifndef UTILS_RANDOM_H
#define UTILS_RANDOM_H

#include <memory>
#include <type_traits>

namespace utils{
namespace random{

template <typename T>
auto make_random_array_raw(size_t n) -> std::unique_ptr<T[]>{
    static_assert(std::is_floating_point_v<T>);
    auto ptr = std::make_unique<T[]>(n);
    return ptr;
}

} // random
} // utils

#endif // UTILS_RANDOM_H
