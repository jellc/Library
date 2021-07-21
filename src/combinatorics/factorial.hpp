#pragma once

/**
 * @file factorial.hpp
 * @brief Factorial
 */

#include <vector>

namespace workspace {

// Factorial
template <class _Tp, class _X> _Tp factorial(_X __x) noexcept {
  if (__x < 0) return 0;
  static std::vector<_Tp> __t{1};
  static size_t __i = (__t.reserve(0x1000000), 0);
  while (__i < size_t(__x)) __t.emplace_back(__t.back() * _Tp(++__i));
  return __t[__x];
}

// Inverse of factorial
template <class _Tp, class _X> _Tp inverse_factorial(_X __x) noexcept {
  if (__x < 0) return 0;
  static std::vector<_Tp> __t{1};
  static size_t __i = (__t.reserve(0x1000000), 0);
  while (__i < size_t(__x)) __t.emplace_back(__t.back() / _Tp(++__i));
  return __t[__x];
}

}  // namespace workspace
