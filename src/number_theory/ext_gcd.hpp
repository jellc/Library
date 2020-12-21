#pragma once

/*
 * @file ext_gcd
 * @brief Extended Euclidean Algorithm
 */

#include <tuple>

#include "src/utils/sfinae.hpp"

namespace workspace {

/**
 * @param a Integer
 * @param b Integer
 * @return Pair of integers (x, y) s.t. ax + by = g = gcd(a, b), |x| < |b/g|,
 * |y| < |a/g|.
 * @note return (0, 0) if (a, b) = (0, 0)
 */
template <typename T1, typename T2> constexpr auto ext_gcd(T1 a, T2 b) {
  static_assert(is_integral_ext<T1>::value);
  static_assert(is_integral_ext<T2>::value);
  using result_type =
      typename std::make_signed<typename std::common_type<T1, T2>::type>::type;
  result_type p{1}, q{}, r{}, s{1}, t;
  while (b) {
    r ^= p ^= r ^= p -= (t = a / b) * r;
    s ^= q ^= s ^= q -= t * s;
    b ^= a ^= b ^= a %= b;
  }
  if (a < 0) p = -p, q = -q;
  return std::make_pair(p, q);
}

}  // namespace workspace
