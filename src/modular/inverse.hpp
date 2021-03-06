#pragma once

/*
 * @file inverse.hpp
 * @brief Inverse Table
 */

#include <vector>

#include "modint.hpp"

namespace workspace {

// Modulus must be prime.
template <class Modint> struct inverse_table {
  static_assert(std::is_same<std::nullptr_t,
                             decltype((void *)Modint::mod, nullptr)>::value);

  using value_type = Modint;

  constexpr value_type operator()(int n) const {
    constexpr int_fast64_t mod = value_type::mod;
    assert(n %= mod);
    if (n < 0) n += mod;
    if (inv.empty()) inv = {1, mod != 1};
    for (int m(inv.size()); m <= n; ++m)
      inv.emplace_back(mod / m * -inv[mod % m]);
    return inv[n];
  }

 private:
  static std::vector<value_type> inv;
};

template <class Modint> std::vector<Modint> inverse_table<Modint>::inv;

}  // namespace workspace
