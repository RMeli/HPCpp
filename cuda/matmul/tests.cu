#include <gtest/gtest.h>

#include "mm_cu.h"
#include "mm_serial.h"

#include <array>
#include <memory>

TEST(serial, identity)
{
    constexpr size_t n_rows = 2;
    constexpr size_t n_cols = 2;
    constexpr size_t n = n_rows * n_cols;

    std::array<double, n> a = {1., 2., 3., 4.};
    std::array<double, n> b = {1., 0., 0., 1.};
    auto c = std::make_unique<double[]>(n);

    std::array<double, n> expected = {1., 2., 3., 4.};

    serial::mm(a.data(), b.data(), c.get(), n_rows, n_cols, n_cols);

    for (size_t i = 0; i < n; ++i) {
      EXPECT_FLOAT_EQ(c[i], expected[i])
          << "Vectors 'c' and 'expected' differ at index " << i;
    }
}

TEST(cuda, identity) {
  constexpr size_t n_rows = 2;
  constexpr size_t n_cols = 2;
  constexpr size_t n = n_rows * n_cols;

  std::array<double, n> a = {1., 2., 3., 4.};
  std::array<double, n> b = {1., 0., 0., 1.};
  auto c = std::make_unique<double[]>(n);

  std::array<double, n> expected = {1., 2., 3., 4.};

  cuda::mm(a.data(), b.data(), c.get(), n_rows, n_cols, n_cols, 2, 1);

  for (size_t i = 0; i < n; ++i) {
    EXPECT_FLOAT_EQ(c[i], expected[i])
        << "Vectors 'c' and 'expected' differ at index " << i;
  }
}
