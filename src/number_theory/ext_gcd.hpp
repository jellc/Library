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
 * @return Pair of integers (x, y) s.t. ax + by = g = gcd(a, b) and (b = 0 or 0
 * <= x < |b/g|) and (a = 0 or -|a/g| < y <= 0). Return (0, 0) if (a, b) = (0,
 * 0).
 */
template <typename _T1, typename _T2>
constexpr auto ext_gcd(_T1 __a, _T2 __b) noexcept {
  static_assert(is_integral_ext<_T1>::value);
  static_assert(is_integral_ext<_T2>::value);

  using value_type = typename std::make_signed<
      typename std::common_type<_T1, _T2>::type>::type;
  using result_type = std::pair<value_type, value_type>;

  value_type a{__a}, b{__b}, p{1}, q{}, r{}, s{1};

  while (b != value_type(0)) {
    auto t = a / b;
    r ^= p ^= r ^= p -= t * r;
    s ^= q ^= s ^= q -= t * s;
    b ^= a ^= b ^= a -= t * b;
  }

  if (a < 0) p = -p, q = -q, a = -a;

  if (p < 0) {
    __a /= a, __b /= a;

    if (__b > 0)
      p += __b, q -= __a;
    else
      p -= __b, q += __a;
  }

  return result_type{p, q};
}

/**
 * @param __a Integer
 * @param __b Integer
 * @param __c Integer
 * @return Pair of integers (x, y) s.t. ax + by = c and (b = 0 or 0 <= x <
 * |b/g|). Return (0, 0) if there is no solution.
 */
template <typename _T1, typename _T2, typename _T3>
constexpr auto ext_gcd(_T1 __a, _T2 __b, _T3 __c) noexcept {
  static_assert(is_integral_ext<_T1>::value);
  static_assert(is_integral_ext<_T2>::value);
  static_assert(is_integral_ext<_T3>::value);

  using value_type = typename std::make_signed<
      typename std::common_type<_T1, _T2, _T3>::type>::type;
  using result_type = std::pair<value_type, value_type>;

  value_type a{__a}, b{__b}, p{1}, q{}, r{}, s{1};

  while (b != value_type(0)) {
    auto t = a / b;
    r ^= p ^= r ^= p -= t * r;
    s ^= q ^= s ^= q -= t * s;
    b ^= a ^= b ^= a -= t * b;
  }

  if (__c % a) return result_type{};

  __a /= a, __b /= a, __c /= a;
  p *= __c, q *= __c;

  if (__b != value_type(0)) {
    auto t = p / __b;
    p -= __b * t;
    q += __a * t;

    if (p < 0) {
      if (__b > 0)
        p += __b, q -= __a;
      else
        p -= __b, q += __a;
    }
  }

  return result_type{p, q};
}

}  // namespace workspace
