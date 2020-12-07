#pragma once

/*
 * @brief Subset Convolution
 */

#include <cassert>
#include <vector>

#include "lib/bit"

namespace workspace {

template <class A> A subset_conv(const A &f, const A &g) {
  const size_t len = std::__bit_floor(std::size(f));
  const size_t n = std::__countr_zero(len);

  std::vector<A> ff(n + 1, A(len)), gg(ff);
  ff[0] = f, gg[0] = g;

  for (size_t k = 0; k != n; ++k)
    for (size_t i = k + 1; ~i; --i)
      for (size_t s = 0; s != len; ++s)
        if (s >> k & 1) {
          if (i)
            ff[i][s] = ff[i - 1][s], gg[i][s] = gg[i - 1][s];
          else
            ff[i][s] = gg[i][s] = {};
          ff[i][s] += ff[i][s ^ 1 << k];
          gg[i][s] += gg[i][s ^ 1 << k];
        }

  for (size_t i = n; ~i; --i)
    for (size_t s = 0; s != len; ++s) {
      ff[i][s] *= gg[0][s];
      for (size_t j = i; j; --j) ff[i][s] += ff[i - j][s] * gg[j][s];
    }

  for (size_t k = n - 1; ~k; --k)
    for (size_t s = 0; s != len; ++s)
      if (~s >> k & 1)
        for (size_t i = n; ~i; --i) {
          ff[i][s ^ 1 << k] -= ff[i][s];
          if (i) ff[i][s] = ff[i - 1][s];
        }

  return ff[n];
}

}  // namespace workspace
