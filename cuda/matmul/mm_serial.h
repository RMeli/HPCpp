#ifndef MM_SERIAL_H
#define MM_SERIAL_H

#include <cstddef>
#include <memory>

namespace serial {

inline auto index(size_t i, size_t j, size_t n_cols) -> size_t {
  return i * n_cols + j;
}

auto mm(const double *a, const double *b, double *c, std::size_t n_rows,
               std::size_t n, std::size_t n_cols) -> void;

auto mm(std::unique_ptr<double[]> &a, std::unique_ptr<double[]> &b,
               std::unique_ptr<double[]> &c, std::size_t n_rows, std::size_t n,
               std::size_t n_cols) -> void;

} // namespace serial

#endif