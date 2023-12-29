#pragma once

/**
 * @file majority_vote.hpp
 * @brief Boyer-Moore Majority Vote Algorithm
 */

#include <algorithm>
#include <cassert>
#include <vector>

namespace workspace {

/**
 * @brief Boyer-Moore majority vote algorithm.
 * @return Elements which appears at least k times in a given range.
 * @note Runs in O(n * floor(n / k)) time, where n is the number of elements in
 * a given range.
 */
template <class _Iterator>
auto majority_vote(_Iterator __first, _Iterator __last, size_t __k) {
  assert(__k);

  using value_type = typename std::iterator_traits<_Iterator>::value_type;

  struct pile {
    value_type value;
    size_t count;
    operator value_type() const { return value; }
  };

  std::vector<pile> __piles;
  size_t __max = std::distance(__first, __last) / __k;

  for (auto __it = __first; __it != __last; ++__it) {
    bool __exist = false;

    for (auto &__x : __piles)
      if (__x.value == *__it) {
        ++__x.count, __exist = true;
        break;
      }

    if (__exist) continue;

    if (__piles.size() < __max)
      __piles.push_back({*__it, 1});

    else {
      for (auto &__x : __piles) __x.count -= 1;
      __piles.erase(std::remove_if(__piles.begin(), __piles.end(),
                                   [](const auto &__x) { return !__x.count; }),
                    __piles.end());
    }
  }

  for (auto &&__x : __piles) __x.count = 0;

  while (__first != __last) {
    for (auto &__x : __piles)
      if (__x.value == *__first) {
        ++__x.count;
        break;
      }
    ++__first;
  }

  __piles.erase(
      std::remove_if(__piles.begin(), __piles.end(),
                     [&](const auto &__x) { return __x.count < __k; }),
      __piles.end());

  return __piles;
}

}  // namespace workspace
