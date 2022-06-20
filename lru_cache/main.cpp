#include "cache.h"

#include "timer.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <cassert>

constexpr size_t cache_size = 3;

size_t slow_calculation(size_t n){
  using namespace std::chrono_literals; // ms
  std::this_thread::sleep_for(500ms);
  return n;
}

int main(){
    Timer t;

    auto f = lru_cache(slow_calculation, cache_size);
    std::cout << "LRU cache size: " << cache_size << '\n';

    for (size_t i = 0; i < cache_size; i++) {
      auto arg = i;

      t.start();
      auto result = f(arg);
      auto elapsed = t.stop();
      assert(result == arg);
      std::cout << "Time f(" << arg << "): " << elapsed.count() << " ms\n";

      t.start();
      result = f(arg);
      elapsed = t.stop();
      assert(result == arg);
      std::cout << "Time f(" << arg << "): " << elapsed.count() << " ms\n";
    }

    // Bring 1 in front of the cache
    auto arg = 1;
    t.start();
    auto result = f(arg);
    auto elapsed = t.stop();
    assert(result == arg);
    std::cout << "Time f(" << arg << "): " << elapsed.count() << " ms\n";

    // Cache now contains: 0, 2, 1

    // Evict 0 from cache
    arg = 3;
    t.start();
    result = f(arg);
    elapsed = t.stop();
    assert(result == arg);
    std::cout << "Time f(" << arg << "): " << elapsed.count() << " ms\n";

    // Evict 2 from cache
    arg = 4;
    t.start();
    result = f(arg);
    elapsed = t.stop();
    assert(result == arg);
    std::cout << "Time f(" << arg << "): " << elapsed.count() << " ms\n";

    // 1 still cached
    arg = 1;
    t.start();
    result = f(arg);
    elapsed = t.stop();
    assert(result == arg);
    std::cout << "Time f(" << arg << "): " << elapsed.count() << " ms\n";

    return 0;
}