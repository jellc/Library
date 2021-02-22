#pragma once

/**
 * @file factorial.hpp
 * @brief Factorial
 * @date 2021-01-15
 *
 *
 */

#include <vector>

namespace workspace {

template <class _Tp> _Tp factorial(int32_t __x) noexcept {
  if (__x < 0) return 0;

  static std::vector<_Tp> __t{1};
  static int32_t __i = (__t.reserve(0x1000000), 0);

  while (__i < __x) {
    ++__i;
    __t.emplace_back(__t.back() * _Tp(__i));
  }

  return __t[__x];
}

template <class _Tp> _Tp factorial_inverse(int32_t __x) noexcept {
  if (__x < 0) return 0;

  static std::vector<_Tp> __t{1};
  static int32_t __i = (__t.reserve(0x1000000), 0);

  while (__i < __x) {
    ++__i;
    __t.emplace_back(__t.back() / _Tp(__i));
  }

  return __t[__x];
}

}  // namespace workspace
