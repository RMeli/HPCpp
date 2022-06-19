#include "cache.h"

#include "timer.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <cassert>

constexpr int r = 42;

int slow_calculation(size_t n){
  using namespace std::chrono_literals; // ms
  std::this_thread::sleep_for(1000ms);
  return r;
}

int main(){
    Timer t;

    auto f = lru_cache(slow_calculation, 2);

    // Calling the first time executes the function
    t.start();
    auto result =f(10);
    auto elapsed = t.stop();
    assert(result == r);
    std::cout << "Time #1: " << elapsed.count() << " ms" << std::endl;

    // Calling the second time reads the cache
    t.start();
    result = f(10);
    elapsed = t.stop();
    assert(result == r);
    std::cout << "Time #2: " << elapsed.count() << " ms" << std::endl;

    // Calling with a different argument executes the function again
    t.start();
    result = f(20);
    elapsed = t.stop();
    assert(result == r);
    std::cout << "Time #3: " << elapsed.count() << " ms" << std::endl;

    // Calling with a different argument executes the function again
    // First element of the cache gets evicted
    t.start();
    result = f(30);
    elapsed = t.stop();
    assert(result == r);
    std::cout << "Time #4: " << elapsed.count() << " ms" << std::endl;

    // Latest element is now in cache
    t.start();
    result = f(30);
    elapsed = t.stop();
    assert(result == r);
    std::cout << "Time #5: " << elapsed.count() << " ms" << std::endl;

    // First argument was evicted from the cache, needs to recompute
    t.start();
    result = f(10);
    elapsed = t.stop();
    assert(result == r);
    std::cout << "Time #6: " << elapsed.count() << " ms" << std::endl;

    return 0;
}