#pragma once

/**
 * @file primitive_root.hpp
 * @brief Primitive Root
 * @date 2020-12-28
 */

#include "src/utils/sfinae.hpp"

namespace workspace {

/**
 * @brief Compile time primitive root.
 *
 * @tparam __mod Positive integer
 * @return Minimum positive one if it exists. Otherwise 0.
 */
template <class Tp>
constexpr typename std::enable_if<(is_integral_ext<Tp>::value), Tp>::type
primitive_root(const Tp __mod) noexcept {
  assert(__mod > 0);
  using int_type = typename multiplicable_uint<Tp>::type;

  int_type __r = __mod, __p[16] = {}, *__q = __p;
  for (int_type __i = 2; __i <= __r / __i; ++__i) {
    if (__r % __i) continue;
    *__q++ = __i;
    while (!(__r % __i)) __r /= __i;
  }
  if (__r != 1) *__q++ = __r;

  int_type __tot = __mod;
  for (__q = __p; *__q; *__q++ = 0) (__tot /= *__q) *= *__q - 1;
  __r = __tot, __q = __p + 1, __p[0] = 1;
  for (int_type __i = 2; __i <= __r / __i; ++__i) {
    if (__r % __i) continue;
    *__q++ = __i;
    while (!(__r % __i)) __r /= __i;
  }
  if (__r != 1) *__q++ = __r;

  for (Tp __r = 1; __r != __mod; ++__r) {
    auto __cnt = 0;
    for (__q = __p; *__q; ++__q) {
      int_type __w = 1;
      for (int_type __e = __tot / *__q, __x = __r; __e;
           __e >>= 1, (__x *= __x) %= __mod)
        if (__e & 1) (__w *= __x) %= __mod;
      if (__w == 1 && ++__cnt > 1) break;
    }
    if (__cnt == 1) return __r;
  }

  return 0;
};

}  // namespace workspace
