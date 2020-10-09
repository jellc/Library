#pragma once
#include <cassert>
#include <vector>

#include "utils/sfinae.hpp"

// calculate the least prime factor for positive integers less than N.
template <unsigned N> class least_factor {
  unsigned least[N], prime[N >> 3], n;

 public:
  constexpr least_factor() : least{1}, prime{}, n{} {
    for (auto i = 2u; i < N; ++i) {
      if (!least[i]) prime[n++] = least[i] = i;
      for (auto *p = prime; *p && *p <= least[i] && *p * i < N; ++p) {
        least[*p * i] = *p;
      }
    }
  }

  template <typename int_type>
  constexpr
      typename std::enable_if<is_integral_ext<int_type>::value, int_type>::type
      operator()(int_type x) const {
    assert(x);
    if (x < 0) x = -x;
    assert(x < N);
    return least[x];
  }

  const std::vector<unsigned> &primes() const {
    static const std::vector<unsigned> prime_vector(prime, prime + n);
    return prime_vector;
  }
};
