# LRU Cache

*Least recently used cache* (LRU cache).

## LRU Cache in Python

Python provides a decorator to wrap a function with a memoizing callable that saves up to the `maxsize` most recent calls:

```python
from functools import lru_cache

@lru_cache(maxsize=100)
def foo():
    pass
```

## LRU Cache in C++

[1] provides an example of general unbounded function cache (similar to Python's `@functools.cache`) implemented using `std::map` (`O(log(N))` insertion and retrieval with `operator[]`).

Since insertion and retrieval of elements (using `operator[]`) is $O(\log n)$ for `std::map`, the implementation in [1] is not the most efficient. Additionally, a `std::map` does not retain the order of insertion which is necessary to implement LRU cache.

An LRU cache can be implemented efficiently using two data structure: a `std::deque` (ordered, with $O(1)$ insertion or removal of elements at the end or beginning), and a `std::unordered_map` (average $O(1)$ insertion and removal). The `std::deque` keeps track of the elements added to cache and allows to easily and efficiently evict old elements when the cache is full and a new element needs to be stored. `std::unordered_map` provides an efficient mapping between the function arguments (stored as keys) and the position of the corresponding cached value (stored as values).

## Source

[1] Functional Programming in C++*, Ivan Čukić, Manning Publications Co., ISBN 9781617293818.
