#include "cache.h"

#include "timer.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <cassert>

constexpr size_t cache_size = 2;
constexpr int r = 42;

int slow_calculation(size_t n){
  using namespace std::chrono_literals; // ms
  std::this_thread::sleep_for(500ms);
  return r;
}

int main(){
    Timer t;

    auto f = lru_cache(slow_calculation, cache_size);
    std::cout << "LRU cache size: " << cache_size << '\n';

    // Calling the first time executes the function
    auto arg = 1;
    t.start();
    auto result =f(arg);
    auto elapsed = t.stop();
    assert(result == r);
    std::cout << "Time f(" << arg << "): " << elapsed.count() << " ms\n";

    // Calling the second time with same argument reads the cache
    arg = 1;
    t.start();
    result = f(arg);
    elapsed = t.stop();
    assert(result == r);
    std::cout << "Time f(" << arg << "): " << elapsed.count() << " ms\n";

    // Calling with a different argument executes the function again
    arg = 2;
    t.start();
    result = f(arg);
    elapsed = t.stop();
    assert(result == r);
    std::cout << "Time f(" << arg << "): " << elapsed.count() << " ms\n";

    // Calling with the previous argument brings it back to the front
    arg = 1;
    t.start();
    result = f(arg);
    elapsed = t.stop();
    assert(result == r);
    std::cout << "Time f(" << arg << "): " << elapsed.count() << " ms\n";

    // Calling with a different argument executes the function again
    // First element of the cache gets evicted since cache size is limited to 2
    arg = 3;
    t.start();
    result = f(arg);
    elapsed = t.stop();
    assert(result == r);
    std::cout << "Time f(" << arg << "): " << elapsed.count() << " ms\n";

    // Latest element is now in cache
    arg = 3;
    t.start();
    result = f(arg);
    elapsed = t.stop();
    assert(result == r);
    std::cout << "Time f(" << arg << "): " << elapsed.count() << " ms\n";

    // Second element was evicted from the cache
    arg = 2;
    t.start();
    result = f(arg);
    elapsed = t.stop();
    assert(result == r);
    std::cout << "Time f(" << arg << "): " << elapsed.count() << " ms\n";

    arg = 2;
    t.start();
    result = f(arg);
    elapsed = t.stop();
    assert(result == r);
    std::cout << "Time f(" << arg << "): " << elapsed.count() << " ms\n";

    arg = 3;
    t.start();
    result = f(arg);
    elapsed = t.stop();
    assert(result == r);
    std::cout << "Time f(" << arg << "): " << elapsed.count() << " ms\n";

    // First argument was evicted from the cache, needs to recompute
    arg = 1;
    t.start();
    result = f(arg);
    elapsed = t.stop();
    assert(result == r);
    std::cout << "Time f(" << arg << "): " << elapsed.count() << " ms\n";

    return 0;
}