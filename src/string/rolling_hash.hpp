#pragma once

/**
 * @file rolling_hash.hpp
 * @brief Rolling Hash
 */

#include <algorithm>
#include <cassert>
#include <vector>

#include "src/opt/binary_search.hpp"
#include "src/utils/rand/rng.hpp"
#include "src/utils/sfinae.hpp"

namespace workspace {

/**
 * @struct rolling_hashed
 * @brief hash data of a string.
 */
struct rolling_hashed {
  using u64 = uint_least64_t;
  using u128 = __uint128_t;

  /**
   * @brief modulus used for hashing.
   */
  constexpr static u64 mod = (1ull << 61) - 1;

  const static u64 base;

  /**
   * @brief hash value.
   */
  u64 value = 0;

  /**
   * @brief length of the string.
   */
  size_t length = 0;

  rolling_hashed() = default;

  /**
   * @brief construct hash data from one character.
   * @param c a character
   */
  template <class char_type, typename std::enable_if<std::is_convertible<
                                 char_type, u64>::value>::type * = nullptr>
  rolling_hashed(char_type c) : value(u64(c) + 1), length(1) {}

  rolling_hashed(u64 value, size_t length) : value(value), length(length) {}

  operator std::pair<u64, size_t>() const { return {value, length}; }

  operator u64() const { return value; }

  /**
   * @return whether or not (*this) and (rhs) are equal
   * @param rhs
   */
  bool operator==(const rolling_hashed &rhs) const {
    return value == rhs.value && length == rhs.length;
  }

  /**
   * @return whether or not (*this) and (rhs) are distinct
   * @param rhs
   */
  bool operator!=(const rolling_hashed &rhs) const { return !operator==(rhs); }

  /**
   * @param rhs the right operand
   * @return hash data of concatenated string
   */
  rolling_hashed operator+(const rolling_hashed &rhs) const {
    return {plus(value, mult(rhs.value, base_pow(length))),
            length + rhs.length};
  }

  /**
   * @param rhs appended to right end
   * @return reference to updated hash data
   */
  rolling_hashed operator+=(const rolling_hashed &rhs) {
    return *this = operator+(rhs);
  }

  /**
   * @param rhs the erased suffix
   * @return hash data of erased string
   */
  rolling_hashed operator-(const rolling_hashed &rhs) const {
    assert(!(length < rhs.length));
    return {minus(value, mult(rhs.value, base_pow(length - rhs.length))),
            length - rhs.length};
  }

  /**
   * @param rhs erased from right end
   * @return reference to updated hash data
   */
  rolling_hashed operator-=(const rolling_hashed &rhs) {
    return *this = operator-(rhs);
  }

  /**
   * @fn base_pow
   * @param exp the exponent
   * @return base ** pow
   */
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

/**
 * @brief base used for hashing
 */
const rolling_hashed::u64 rolling_hashed::base =
    random_number_generator<u64>(1 << 30, mod - 1)();

/**
 * @struct rolling_hash_table
 * @brief make hash data table of suffix.
 */
template <class str_type> struct rolling_hash_table {
  constexpr static size_t npos = -1;

  rolling_hash_table() = default;

  rolling_hash_table(str_type str) {
    std::reverse(std::begin(str), std::end(str));
    for (auto &&c : str) suffix.emplace_back(rolling_hashed{c} + suffix.back());
    std::reverse(suffix.begin(), suffix.end());
  }

  template <class Tp, typename = typename std::enable_if<
                          std::is_convertible<rolling_hashed, Tp>::value>::type>
  operator Tp() const {
    return substr();
  }

  operator rolling_hashed() const { return substr(); }

  /**
   * @return length of the string
   */
  size_t size() const { return suffix.size() - 1; }

  /**
   * @param pos start position
   * @param n length of the substring
   * @return hash data of the substring
   */
  rolling_hashed substr(size_t pos = 0, size_t n = npos) const {
    assert(!(size() < pos));
    return suffix[pos] - suffix[pos + std::min(n, size() - pos)];
  }

  /**
   * @param rhs
   * @return length of the longest common prefix
   */
  size_t lcp(rolling_hash_table const &rhs) const {
    auto n = std::min(size(), rhs.size());
    return binary_search<size_t>(
        0, n + 1, [&](size_t l) { return substr(0, l) == rhs.substr(0, l); });
  }

 private:
  std::vector<rolling_hashed> suffix{{}};
};

}  // namespace workspace
