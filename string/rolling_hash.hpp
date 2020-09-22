#pragma once
#include <algorithm>
#include <cassert>
#include <vector>

#include "utils/random_number_generator.hpp"

struct rolling_hashed {
  using u64 = uint_least64_t;
  using u128 = __uint128_t;

  constexpr static u64 mod = (1ull << 61) - 1;
  static u64 base;

  u64 value = 0;
  size_t length = 0;

  rolling_hashed() = default;

  template <class char_type, typename std::enable_if<std::is_convertible<
                                 char_type, u64>::value>::type * = nullptr>
  rolling_hashed(char_type c) : value(u64(c) + 1), length(1) {}

  rolling_hashed(u64 value, size_t length) : value(value), length(length) {}

  operator std::pair<u64, size_t>() const { return {value, length}; }

  bool operator==(const rolling_hashed &rhs) const {
    return value == rhs.value && length == rhs.length;
  }

  bool operator!=(const rolling_hashed &rhs) const { return !operator==(rhs); }

  rolling_hashed operator+(const rolling_hashed &rhs) const {
    return {plus(value, mult(rhs.value, base_pow(length))),
            length + rhs.length};
  }

  rolling_hashed operator+=(const rolling_hashed &rhs) {
    return *this = operator+(rhs);
  }

  rolling_hashed operator-(const rolling_hashed &rhs) const {
    assert(!(length < rhs.length));
    return {minus(value, mult(rhs.value, base_pow(length - rhs.length))),
            length - rhs.length};
  }

  rolling_hashed operator-=(const rolling_hashed &rhs) {
    return *this = operator-(rhs);
  }

  static u64 base_pow(size_t exp) {
    static std::vector<u64> pow{1};
    while (pow.size() <= exp) {
      pow.emplace_back(mult(pow.back(), base));
    }
    return pow[exp];
  }

 private:
  static u64 plus(u64 lhs, u64 rhs) {
    return (lhs += rhs) < mod ? lhs : lhs - mod;
  }

  static u64 minus(u64 lhs, u64 rhs) {
    return (lhs -= rhs) < mod ? lhs : lhs + mod;
  }

  static u64 mult(u128 lhs, u64 rhs) {
    lhs *= rhs;
    lhs = (lhs >> 61) + (lhs & mod);
    return lhs < mod ? lhs : lhs - mod;
  }
};

rolling_hashed::u64 rolling_hashed::base =
    random_number_generator<u64>(1 << 30, mod - 1)();

template <class str_type> struct rolling_hash_table {
  constexpr static size_t npos = -1;

  rolling_hash_table() = default;

  rolling_hash_table(str_type str) {
    std::reverse(std::begin(str), std::end(str));
    for (auto &&c : str) suffix.emplace_back(rolling_hashed{c} + suffix.back());
    std::reverse(suffix.begin(), suffix.end());
  }

  size_t size() const { return suffix.size() - 1; }

  rolling_hashed substr(size_t pos = 0, size_t n = npos) const {
    assert(!(size() < pos));
    return suffix[pos] - suffix[pos + std::min(n, size() - pos)];
  }

 private:
  std::vector<rolling_hashed> suffix{{}};
};
