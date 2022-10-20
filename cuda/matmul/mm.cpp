#include "mm_serial.h"

#include <cstddef>

namespace serial {

auto mm(const double *a, const double *b, double *c, std::size_t n_rows,
               std::size_t n, std::size_t n_cols) -> void {
  for (std::size_t i = 0; i < n_rows; i++) {
    for (std::size_t j = 0; j < n_cols; j++) {
      auto r = 0.0;
      for (std::size_t k = 0; k < n; k++) {
        r += a[index(i, k, n)] * b[index(k, j, n_cols)];
      }
      c[index(i, j, n_cols)] = r;
    }
  }
}

auto mm(std::unique_ptr<double[]> &a, std::unique_ptr<double[]> &b,
               std::unique_ptr<double[]> &c, std::size_t n_rows, std::size_t n,
               std::size_t n_cols) -> void {
  mm(a.get(), b.get(), c.get(), n_rows, n, n_cols);
}
} // namespace serial