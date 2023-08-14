#include "exec/static_thread_pool.hpp"
#include "stdexec/execution.hpp"

#include <array>
#include <iostream>
#include <algorithm>

int main() {
  constexpr size_t n_threads = 6;

  exec::static_thread_pool pool(n_threads);
  auto sched = pool.get_scheduler();

  std::array<int, n_threads> results;
  std::fill(std::begin(results), std::end(results), -1);

  auto fun = [](int i) { return i * i; };
  auto work =
      stdexec::when_all(
          stdexec::on(sched, stdexec::just(1) | stdexec::then(fun)), // 1 to the power of 2
          stdexec::on(sched, stdexec::just(2) | stdexec::then(fun))) | // 2 to the powrt of 2
      stdexec::transfer(sched) | // Not necessary...
      stdexec::bulk(n_threads, [r = results.data()](std::size_t tid,
                                                    const int i, const int j) {
        r[tid] = tid * i * j;
      }); // Fill results for each thread with tid * i (= 1) * j (= 4)

  stdexec::sync_wait(std::move(work));

  std::for_each(std::cbegin(results), std::cend(results),
                [](const int r) { std::cout << r << ' '; });
  std::cout << '\n';
}
