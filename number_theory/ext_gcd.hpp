#pragma once
#include <tuple>

#include "utils/sfinae.hpp"
template <class int_type>
constexpr typename std::enable_if<is_integral_ext<int_type>::value,
                                  std::pair<int_type, int_type>>::type
ext_gcd(int_type a, int_type b) {
  int_type p{1}, q{}, r{}, s{1}, t{};
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
