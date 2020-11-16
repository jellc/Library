#pragma once

/*
 * @file ext_gcd
 * @brief Extended Euclidean Algorithm
 */

#include <tuple>

#include "src/utils/sfinae.hpp"

namespace workspace {

/*
 * @fn ext_gcd
 * @param a an integer
 * @param b an integer
 * @return a pair of integers (x, y) s.t. ax + by = gcd(a, b)
 * @note return (0, 0) if (a, b) = (0, 0)
 */
template <typename T1, typename T2>
constexpr typename std::enable_if<
    (is_integral_ext<T1>::value && is_integral_ext<T2>::value),
    std::pair<typename std::common_type<T1, T2>::type,
              typename std::common_type<T1, T2>::type>>::type
ext_gcd(T1 a, T2 b) {
  typename std::common_type<T1, T2>::type p{1}, q{}, r{}, s{1}, t{};
  if (a < 0) {
    std::tie(p, q) = ext_gcd(-a, b);
    p = -p;
  } else if (b < 0) {
    std::tie(p, q) = ext_gcd(a, -b);
    q = -q;
  } else {
    while (b) {
      r ^= p ^= r ^= p -= (t = a / b) * r;
      s ^= q ^= s ^= q -= t * s;
      b ^= a ^= b ^= a %= b;
    }
  }
  return {p, q};
}

}  // namespace workspace
