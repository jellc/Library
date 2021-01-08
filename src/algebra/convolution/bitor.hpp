#pragma once

/**
 * @file bitor.hpp
 * @brief Bitwise Or Convolution
 * @date 2021-01-08
 */

#include "zeta.hpp"

namespace workspace {

template <class A> A bitor_conv(A f, A g) {
  f = fast_zeta(f);
  g = fast_zeta(g);
  for (size_t i = 0; i != std::__bit_floor(std::size(f)); ++i) f[i] *= g[i];
  f = fast_mobius(f);
  return f;
}

}  // namespace workspace
