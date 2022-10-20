#ifndef MM_CU_H
#define MM_CU_H

#include <cstddef>

namespace cuda {

__host__ __device__
inline size_t index(size_t i, size_t j, size_t n_cols) {
  return i * n_cols + j;
}

__global__
void mm_kernel(const double *a, const double *b, double *c,
               std::size_t n_rows, std::size_t n, std::size_t n_cols);

auto mm(const double *a, const double *b, double *c, std::size_t n_rows, std::size_t n,
        std::size_t n_cols, std::size_t n_threads_per_block, std::size_t n_blocks) -> void;

} // namespace cuda

#endif
