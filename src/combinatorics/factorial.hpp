#pragma once

/**
 * @file factorial.hpp
 * @brief Factorial
 * @date 2021-01-15
 *
 *
 */

#include <cstdint>
#include <functional>
#include <vector>

namespace workspace {

template <class Tp> Tp factorial(int_fast32_t __x) noexcept {
  if (__x < 0) return 0;
  static std::vector<Tp> __t{1};
  static int_fast32_t __i = (__t.reserve(0x1000000), 0);
  while (__i < __x) {
    ++__i;
    __t.emplace_back(__t.back() * __i);
  }
  return __t[__x];
}

template <class Tp> Tp factorial_inverse(int_fast32_t __x) noexcept {
  if (__x < 0) return 0;
  static std::vector<Tp> __t{1};
  static int_fast32_t __i = (__t.reserve(0x1000000), 0);
  while (__i < __x) {
    ++__i;
    __t.emplace_back(__t.back() / __i);
  }
  return __t[__x];
}

}  // namespace workspace
