#include <deque>
#include <tuple>
#include <utility>
#include <unordered_map>
#include <optional>

template <typename Result, typename... Args>
auto lru_cache(Result (*f)(Args...), std::optional<size_t> cache_size = std::nullopt) {
    // Cache maps arguments to results
    using cache_t = std::deque<std::pair<Args..., Result>>;
    cache_t cache;

    // Maps keys to elements in the cache
    // Provides O(1) access to the cache
    std::unordered_map<Args..., typename cache_t::iterator> cache_map;

    // Capture function pointer and cache
    // Lambda is mutable in order to modify members (cache)
    return [f, cache, cache_map, cache_size](Args... args) mutable -> Result {
        const auto cached_map_it = cache_map.find(args...);

        if(cached_map_it == cache_map.end()){ // Not found in cache
            if(cache_size && cache.size() == *cache_size){ // Cache is full
                cache_map.erase(cache.front().first); // Remove oldest element from map
                cache.pop_front(); // Remove oldest element from cache
            }
            const auto result = f(args...);
            cache.emplace_back(std::make_pair(args..., result));
            cache_map.emplace(args..., cache.end() - 1); // End iterator points after last element
            return result;
        }

        return cached_map_it->second->second;
    };
}