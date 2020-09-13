#pragma once
#include <tuple>
template <class int_type>
constexpr typename std::enable_if<std::is_integral<int_type>::value,
                                  std::pair<int_type, int_type>>::type
ext_gcd(int_type a, int_type b) {
  bool neg_a = a < 0, neg_b = b < 0;
  int_type p{1}, q{}, r{}, s{1}, t{};
  while (b) {
    r ^= p ^= r ^= p -= (t = a / b) * r;
    s ^= q ^= s ^= q -= t * s;
    b ^= a ^= b ^= a %= b;
  }
  return {neg_a ? -p : p, neg_b ? -q : q};
}
