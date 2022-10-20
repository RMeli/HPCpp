#include <benchmark/benchmark.h>

#include "random.h"

#include "mm_serial.h"
#include "mm_cu.h"

constexpr size_t n_rows = 100;
constexpr size_t n = 200;
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

  for (auto _ : state) {
    cuda::mm(a.get(), b.get(), c.get(), n_rows, n, n_cols, 16,
             n_rows * n_cols / 16 + 1);
  }
}
BENCHMARK(BM_mm_cuda);
