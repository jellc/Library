#pragma once

/**
 * @file shuffle.hpp
 * @brief Shuffle
 */

#include <algorithm>
#include <random>

namespace workspace {

template <class _RAIter, class _Engine = std::mt19937>
void shuffle(_RAIter __first, _RAIter __last) {
  static _Engine __engine(std::random_device{}());
  std::shuffle(__first, __last, __engine);
}

}  // namespace workspace
