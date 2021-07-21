#pragma once

/**
 * @file binomial.hpp
 * @brief Binomial Coefficient
 */

#include <cassert>

#include "factorial.hpp"

namespace workspace {

namespace _binom_impl {

struct _binom_table {
  constexpr static int size = 132;
  __uint128_t __b[size][size]{1};

  constexpr _binom_table() noexcept {
    for (int __i = 1; __i != size; ++__i)
      for (int __j = 0; __j != __i; ++__j)
        __b[__i][__j] += __b[__i - 1][__j],
            __b[__i][__j + 1] += __b[__i - 1][__j];
  }

  constexpr auto operator()(int __x, int __y) const noexcept {
    return __x < 0 || __x < __y ? 0 : (assert(__x < size), __b[__x][__y]);
  }
};

constexpr _binom_table table;

}  // namespace _binom_impl

/**
 * @brief Binomial coefficient for integer args. Be careful with overflow.
 */
template <class _Tp, class _X, class _Y>
constexpr _Tp binomial(_X __x, _Y __y) {
  if constexpr (is_integral_ext<_Tp>::value)
    return _binom_impl::table(__x, __y);

  if (__y < 0 || __x < __y) return 0;

  return factorial<_Tp>(__x) * inverse_factorial<_Tp>(__y) *
         inverse_factorial<_Tp>(__x - __y);
}

/**
 * @brief Catalan number.
 */
template <class _Tp, class _X> constexpr _Tp catalan(_X __x) {
  return __x < 0
             ? _Tp(0)
             : binomial<_Tp>(__x << 1, __x) - binomial<_Tp>(__x << 1, __x + 1);
}

}  // namespace workspace
