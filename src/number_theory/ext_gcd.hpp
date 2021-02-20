#pragma once

/**
 * @file ext_gcd.hpp
 * @brief Extended Euclidean Algorithm
 */

#include <tuple>

#include "src/utils/sfinae.hpp"

namespace workspace {

/**
 * @param __a Integer
 * @param __b Integer
 * @return Pair of integers (x, y) s.t. ax + by = g = gcd(a, b), 0 <= x <
 * |b/g|, -|a/g| < y <= 0. Return (0, 0) if (a, b) = (0, 0).
 */
template <typename _T1, typename _T2> constexpr auto ext_gcd(_T1 __a, _T2 __b) {
  static_assert(is_integral_ext<_T1>::value);
  static_assert(is_integral_ext<_T2>::value);

  using result_type = typename std::make_signed<
      typename std::common_type<_T1, _T2>::type>::type;

  result_type a{__a}, b{__b}, p{1}, q{}, r{}, s{1};

  // Euclidean algorithm
  while (b) {
    result_type t = a / b;
    r ^= p ^= r ^= p -= t * r;
    s ^= q ^= s ^= q -= t * s;
    b ^= a ^= b ^= a -= t * b;
  }

  // Normalize
  if (a < 0) p = -p, q = -q;
  if (p < 0) p += __b / a, q -= __a / a;

  return std::make_pair(p, q);
}

}  // namespace workspace
