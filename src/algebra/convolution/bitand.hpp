#pragma once

/**
 * @file bitand.hpp
 * @brief Bitwise And Convolution
 * @date 2021-01-08
 */

#include <algorithm>

#include "bitor.hpp"

namespace workspace {

template <class A> A bitand_conv(A f, A g) {
  std::reverse(std::begin(f), std::end(f));
  std::reverse(std::begin(g), std::end(g));
  f = bitor_conv(f, g);
  std::reverse(std::begin(f), std::end(f));
  return f;
}

}  // namespace workspace
