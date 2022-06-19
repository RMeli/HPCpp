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
  std::this_thread::sleep_for(1000ms);
  return r;
}

int main(){
    Timer t;

    auto f = lru_cache(slow_calculation, cache_size);
    std::cout << "LRU cache size: " << cache_size << '\n';

    // Calling the first time executes the function
    auto arg = 10;
    t.start();
    auto result =f(arg);
    auto elapsed = t.stop();
    assert(result == r);
    std::cout << "Time f(" << arg << "): " << elapsed.count() << " ms\n";

    // Calling the second time with same argument reads the cache
    arg = 10;
    t.start();
    result = f(arg);
    elapsed = t.stop();
    assert(result == r);
    std::cout << "Time f(" << arg << "): " << elapsed.count() << " ms\n";

    // Calling with a different argument executes the function again
    arg = 20;
    t.start();
    result = f(arg);
    elapsed = t.stop();
    assert(result == r);
    std::cout << "Time f(" << arg << "): " << elapsed.count() << " ms\n";

    // Calling with a different argument executes the function again
    // First element of the cache gets evicted since cache size is limited to 2
    arg = 30;
    t.start();
    result = f(arg);
    elapsed = t.stop();
    assert(result == r);
    std::cout << "Time f(" << arg << "): " << elapsed.count() << " ms\n";

    // Latest element is now in cache
    arg = 30;
    t.start();
    result = f(arg);
    elapsed = t.stop();
    assert(result == r);
    std::cout << "Time f(" << arg << "): " << elapsed.count() << " ms\n";

    // Second element is still in cache
    arg = 20;
    t.start();
    result = f(arg);
    elapsed = t.stop();
    assert(result == r);
    std::cout << "Time f(" << arg << "): " << elapsed.count() << " ms\n";

    // First argument was evicted from the cache, needs to recompute
    arg = 10;
    t.start();
    result = f(arg);
    elapsed = t.stop();
    assert(result == r);
    std::cout << "Time f(" << arg << "): " << elapsed.count() << " ms\n";

    return 0;
}