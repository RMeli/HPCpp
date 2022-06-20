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
        auto cached_map_it = cache_map.find(args...);

        if(cached_map_it == cache_map.end()){ // Not found in cache
            if(cache_size && cache.size() == *cache_size){ // Cache is full
                // Remove oldest element, at the front of the queue
                // Remove first from unordered_map, using the argument as key
                // Then remove from the front of the queue
                cache_map.erase(cache.front().first);
                cache.pop_front();
            }
            // Compute element and add it to the cache
            const auto result = f(args...);
            cache.emplace_back(std::make_pair(args..., result));
            cache_map.emplace(args..., cache.end() - 1); // End iterator points after last element
            return result;
        }
        else{ // Found in cache
            // Move cached element to the end of the queue
            // It is now the most recently used element
            auto cached_it = cached_map_it->second;
            cache.push_back(*cached_it);
            cache.erase(cached_it);
            cached_map_it->second = cache.end() - 1;

            return cache.back().second;
        }
    };
}