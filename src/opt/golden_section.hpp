#pragma once

/**
 * @file golden_section.hpp
 * @brief Golden Section
 */

#include <type_traits>

#include "src/algebra/system/operation.hpp"

namespace workspace {

/**
 * @brief Golden section search.
 */
template <class _Iterator, class _Function>
std::enable_if_t<has_binary_minus<_Iterator>::value, _Iterator> golden_section(
    _Iterator __first, _Iterator __last, _Function&& __f) {
  if (__last - __first < 2) return __first;

  decltype(__last - __first) __a{1}, __b{2};
  while (__a + __b <= __last - __first) __b ^= __a ^= __b ^= __a += __b;

  auto __f1 = __f(__last - __b), __f2 = __f(__last - __a);

  while (__a != 1) {
    __a ^= __b ^= __a ^= __b -= __a;

    if (__f2 < __f1)
      __f1 = __f2, __f2 = __f(__last - __a);

    else if ((__last -= __b) - __first < __b)
      __a ^= __b ^= __a ^= __b -= __a, __f2 = __f(__last - __a);

    else
      __f2 = __f1, __f1 = __f(__last - __b);
  }

  return __f1 < __f2 ? __last - __b : __last - __a;
}

}  // namespace workspace
