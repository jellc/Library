#pragma once

/**
 * @file sqrt_mod.hpp
 * @brief Tonelli-Shanks Algorithm
 */

#include "pow_mod.hpp"
#include "src/utils/sfinae.hpp"

namespace workspace {

/**
 * @brief Compile time modular square root.
 *
 * @param __x
 * @param __mod Modulus
 * @return One if it exists. Otherwise -1.
 */
template <class _Tp>
constexpr std::enable_if_t<(is_integral_ext<_Tp>::value), _Tp> sqrt_mod(
    _Tp __x, _Tp __mod) noexcept {
  assert(__mod > 0);

  using mul_type = typename multiplicable_uint<_Tp>::type;

  if ((__x %= __mod) < 0) __x += __mod;

  if (!__x) return 0;

  if (__mod == 2) return __x;

  if (pow_mod(__x, __mod >> 1, __mod) != 1) return -1;

  _Tp __z = __builtin_ctz(__mod - 1), __q = __mod >> __z;

  mul_type __a = pow_mod(__x, (__q + 1) >> 1, __mod), __b = 2;
  while (pow_mod<_Tp>(__b, __mod >> 1, __mod) == 1) ++__b;
  __b = pow_mod<_Tp>(__b, __q, __mod);

  _Tp __shift = 0;

  for (auto __r = __a * __a % __mod * pow_mod(__x, __mod - 2, __mod) % __mod;
       __r != 1; (__r *= (__b *= __b) %= __mod) %= __mod) {
    auto __bsf = __z;

    for (auto __e = __r; __e != 1; --__bsf) (__e *= __e) %= __mod;

    while (++__shift != __bsf) (__b *= __b) %= __mod;

    (__a *= __b) %= __mod;
  }

  return __a;
};

}  // namespace workspace
