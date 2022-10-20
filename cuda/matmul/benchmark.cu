#include <benchmark/benchmark.h>

#include "random.h"

#include "mm_serial.h"
#include "mm_cu.h"

constexpr size_t n_rows = 10;
constexpr size_t n = 20;
constexpr size_t n_cols = 50;

static auto BM_mm_serial(benchmark::State &state) -> void {
  auto a = utils::random::make_random_array_raw<double>(n_rows * n);
  auto b = utils::random::make_random_array_raw<double>(n * n_cols);
  auto c = utils::random::make_random_array_raw<double>(n_rows * n_cols);

  for (auto _ : state) {
    serial::mm(a, b, c, n_rows, n, n_cols);
  }
}
BENCHMARK(BM_mm_serial);

static auto BM_mm_cuda(benchmark::State &state) -> void {
  auto a = utils::random::make_random_array_raw<double>(n_rows * n);
  auto b = utils::random::make_random_array_raw<double>(n * n_cols);
  auto c = utils::random::make_random_array_raw<double>(n_rows * n_cols);

  constexpr size_t num_threads_per_block = 16;
  constexpr size_t num_blocks = n_rows * n_cols / num_threads_per_block + 1;

  for (auto _ : state) {
    cuda::mm(a.get(), b.get(), c.get(), n_rows, n, n_cols, num_threads_per_block,
             num_blocks);
  }
}
BENCHMARK(BM_mm_cuda);
