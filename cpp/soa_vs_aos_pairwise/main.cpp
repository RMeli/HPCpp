#include <array>
#include <numeric>
#include <vector>
#include <iostream>

#include "timer.h"
#include <benchmark/benchmark.h>

constexpr size_t dims = 3;
using Position = std::array<double, dims>;
using Force = std::array<double, dims>;

std::vector<Force> forces_aos(const std::vector<Position>& positions);
std::vector<double> forces_soa(const std::vector<double>& positions);
std::vector<Force> forces_aos_noalloc(const std::vector<Position> &positions, std::vector<Force>& f);
std::vector<double> forces_soa_noalloc(const std::vector<double> &positions, std::vector<double>& f);

constexpr size_t N = 1000;

static void BM_forces_soa(benchmark::State& state){
  std::vector<double> positions_soa(dims * N, 1.0);

  for (auto _: state){
    auto f_aos = forces_soa(positions_soa);
  }
}
BENCHMARK(BM_forces_soa);

static void BM_forces_soa_noalloc(benchmark::State& state){
  std::vector<double> positions_soa(dims * N, 1.0);
  std::vector<double> fn_soa(dims * N, 0.0);

  for (auto _: state){
    forces_soa_noalloc(positions_soa, fn_soa);
  }
}
BENCHMARK(BM_forces_soa_noalloc);

static void BM_forces_aos(benchmark::State& state){
  std::vector<Position> positions_aos(N, {1.0, 1.0, 1.0});

  for (auto _: state){
    auto f_aos = forces_aos(positions_aos);
  }
}
BENCHMARK(BM_forces_aos);

static void BM_forces_aos_noalloc(benchmark::State& state){
  std::vector<Position> positions_aos(N, {1.0, 1.0, 1.0});
  std::vector<Force> fn_aos(N, {0.0, 0.0, 0.0});

  for (auto _: state){
    forces_aos_noalloc(positions_aos, fn_aos);
  }
}
BENCHMARK(BM_forces_aos_noalloc);

BENCHMARK_MAIN();

/*
int main(){
    constexpr size_t N = 1000;
    constexpr size_t repeats = 100;

    std::vector<Force> fn_aos(N, {0.0, 0.0, 0.0});
    std::vector<double> fn_soa(dims * N, 0.0);

    Timer t;

    t.start();
    for (size_t i = 0; i < repeats; ++i) {
      auto f_aos = forces_soa(positions_soa);
    }
    auto elapsed = t.stop();
    std::cout << "AOS: " << elapsed.count() << " ms" << '\n';

    t.start();
    for (size_t i = 0; i < repeats; ++i) {
      forces_aos_noalloc(positions_aos, fn_aos);
    }
    elapsed = t.stop();
    std::cout << "AOS (noalloc): " << elapsed.count() << " ms" << '\n';

    t.start();
    for (size_t i = 0; i < repeats; ++i) {
      auto f_soa = forces_soa(positions_soa);
    }
    elapsed = t.stop();
    std::cout << "SOA: " << elapsed.count() << " ms" << '\n';

    t.start();
    for (size_t i = 0; i < repeats; ++i) {
      forces_soa_noalloc(positions_soa, fn_soa);
    }
    elapsed = t.stop();
    std::cout << "SOA (noalloc): " << elapsed.count() << " ms" << '\n';
}
*/
std::vector<Force> forces_aos(const std::vector<Position>& positions){
    const size_t n = positions.size();

    std::vector<Force> f(n);

    for(size_t i = 0; i < n; i++){
        for(size_t j = 0; j < i; j++){
            std::array<double, dims> d;
            for(size_t k = 0; k < dims; k++){
              d[k] = positions[i][k] - positions[j][k];
            }

            double r = std::inner_product(d.cbegin(), d.cend(), d.cbegin(), 0.0);

            for(size_t k = 0; k < dims; k++){
               f[i][k] += r * d[k];
               f[j][k] -= r * d[k];
            }
        }
    }

    return f;
}

std::vector<double> forces_soa(const std::vector<double>& positions) {
  const size_t n = positions.size();

  std::vector<double> f(n);

  for (size_t i = 0; i < n; i+=dims) {
    for (size_t j = 0; j < i; j+=dims) {
      std::array<double, dims> d;
      for (size_t k = 0; k < dims; k++) {
        d[k] = positions[i + k] - positions[j + k];
      }

      double r = std::inner_product(d.cbegin(), d.cend(), d.cbegin(), 0.0);

      for (size_t k = 0; k < dims; k++) {
        f[i + k] += r * d[k];
        f[j + k] -= r * d[k];
      }
    }
  }

  return f;
}

std::vector<Force> forces_aos_noalloc(const std::vector<Position> &positions, std::vector<Force>& f) {
  const size_t n = positions.size();

  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < i; j++) {
      std::array<double, dims> d;
      for (size_t k = 0; k < dims; k++) {
        d[k] = positions[i][k] - positions[j][k];
      }

      double r = std::inner_product(d.cbegin(), d.cend(), d.cbegin(), 0.0);

      for (size_t k = 0; k < dims; k++) {
        f[i][k] += r * d[k];
        f[j][k] -= r * d[k];
      }
    }
  }

  return f;
}

std::vector<double> forces_soa_noalloc(const std::vector<double> &positions, std::vector<double>& f) {
  const size_t n = positions.size();

  for (size_t i = 0; i < n; i += dims) {
    for (size_t j = 0; j < i; j += dims) {
      std::array<double, dims> d;
      for (size_t k = 0; k < dims; k++) {
        d[k] = positions[i + k] - positions[j + k];
      }

      double r = std::inner_product(d.cbegin(), d.cend(), d.cbegin(), 0.0);

      for (size_t k = 0; k < dims; k++) {
        f[i + k] += r * d[k];
        f[j + k] -= r * d[k];
      }
    }
  }

  return f;
}