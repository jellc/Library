/**
 * @file totient.hpp
 * @brief Euler's Totient Function
 * @date 2021-01-13
 */

#include <cassert>

#include "src/utils/sfinae.hpp"

namespace workspace {

/**
 * @brief Euler's totient function.
 *
 * @tparam __mod Positive integer
 */
template <class Tp>
constexpr typename std::enable_if<(is_integral_ext<Tp>::value), Tp>::type
totient(const Tp __mod) noexcept {
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

  return __tot;
};

}  // namespace workspace
