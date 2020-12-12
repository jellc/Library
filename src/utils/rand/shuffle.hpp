#pragma once

/**
 * @file shuffle.hpp
 * @brief Shuffle
 */

#include <algorithm>
#include <random>

namespace workspace {

template <class RAIter>
void shuffle(RAIter const& __first, RAIter const& __last) {
  static std::mt19937 engine(std::random_device(){});
  std::shuffle(__first, __last, engine);
}

}  // namespace workspace
