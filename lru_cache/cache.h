#include <map>
#include <tuple>

template <typename Result, typename... Args>
auto lru_cache(Result (*f)(Args...)){
    // Cache maps arguments to results
    // TODO: Better data structure
    std::map<std::tuple<Args...>, Result> cache;

    // Capture function pointer and cache
    // Lambda is mutable in order to modify members (cache)
    return [f, cache](Args... args) mutable -> Result {
        const auto args_tuple = std::make_tuple(args...);
        const auto cached = cache.find(args_tuple);

        if(cached == cache.end()){
            const auto result = f(args...);
            cache[args_tuple] = result;  // Cache  uncached result
            return result;
        }
        return cached->second; // chached is an iterator to a pair<args, result>
    };
}