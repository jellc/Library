---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 2 \"variation/modint.hpp\"\n#include <cassert>\n#include <iostream>\n\
    template <auto &mod>  // compile-time defined modulo.\nstruct modint {\n  using\
    \ value_type = int_least64_t;\n  constexpr static modint one() noexcept { return\
    \ 1; }\n  constexpr operator value_type() const noexcept { return value; }\n \
    \ constexpr modint() noexcept = default;\n  template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\n\
    \                                             std::nullptr_t> = nullptr>\n  constexpr\
    \ modint(int_type n) noexcept : value((n %= mod) < 0 ? mod + n : n) {}\n  constexpr\
    \ modint operator++(int) noexcept {\n    modint t{*this};\n    return operator+=(1),\
    \ t;\n  }\n  constexpr modint operator--(int) noexcept {\n    modint t{*this};\n\
    \    return operator-=(1), t;\n  }\n  constexpr modint &operator++() noexcept\
    \ { return operator+=(1); }\n  constexpr modint &operator--() noexcept { return\
    \ operator-=(1); }\n  constexpr modint operator-() const noexcept {\n    return\
    \ value ? mod - value : 0;\n  }\n  constexpr modint &operator+=(const modint &rhs)\
    \ noexcept {\n    return (value += rhs.value) < mod ? 0 : value -= mod, *this;\n\
    \  }\n  constexpr modint &operator-=(const modint &rhs) noexcept {\n    return\
    \ (value += mod - rhs.value) < mod ? 0 : value -= mod, *this;\n  }\n  constexpr\
    \ modint &operator*=(const modint &rhs) noexcept {\n    return value = (int_fast64_t)value\
    \ * rhs.value % mod, *this;\n  }\n  constexpr modint &operator/=(const modint\
    \ &rhs) noexcept {\n    return operator*=(rhs.inverse());\n  }\n  template <class\
    \ int_type, std::enable_if_t<std::is_integral<int_type>::value,\n            \
    \                                 std::nullptr_t> = nullptr>\n  constexpr modint\
    \ operator+(const int_type &rhs) const noexcept {\n    return modint{*this} +=\
    \ rhs;\n  }\n  constexpr modint operator+(const modint &rhs) const noexcept {\n\
    \    return modint{*this} += rhs;\n  }\n  template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\n\
    \                                             std::nullptr_t> = nullptr>\n  constexpr\
    \ modint operator-(const int_type &rhs) const noexcept {\n    return modint{*this}\
    \ -= rhs;\n  }\n  constexpr modint operator-(const modint &rhs) const noexcept\
    \ {\n    return modint{*this} -= rhs;\n  }\n  template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\n\
    \                                             std::nullptr_t> = nullptr>\n  constexpr\
    \ modint operator*(const int_type &rhs) const noexcept {\n    return modint{*this}\
    \ *= rhs;\n  }\n  constexpr modint operator*(const modint &rhs) const noexcept\
    \ {\n    return modint{*this} *= rhs;\n  }\n  template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\n\
    \                                             std::nullptr_t> = nullptr>\n  constexpr\
    \ modint operator/(const int_type &rhs) const noexcept {\n    return modint{*this}\
    \ /= rhs;\n  }\n  constexpr modint operator/(const modint &rhs) const noexcept\
    \ {\n    return modint{*this} /= rhs;\n  }\n  template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\n\
    \                                             std::nullptr_t> = nullptr>\n  constexpr\
    \ friend modint operator+(const int_type &lhs,\n                             \
    \       const modint &rhs) noexcept {\n    return modint(lhs) + rhs;\n  }\n  template\
    \ <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\n     \
    \                                        std::nullptr_t> = nullptr>\n  constexpr\
    \ friend modint operator-(const int_type &lhs,\n                             \
    \       const modint &rhs) noexcept {\n    return modint(lhs) - rhs;\n  }\n  template\
    \ <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\n     \
    \                                        std::nullptr_t> = nullptr>\n  constexpr\
    \ friend modint operator*(const int_type &lhs,\n                             \
    \       const modint &rhs) noexcept {\n    return modint(lhs) * rhs;\n  }\n  template\
    \ <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\n     \
    \                                        std::nullptr_t> = nullptr>\n  constexpr\
    \ friend modint operator/(const int_type &lhs,\n                             \
    \       const modint &rhs) noexcept {\n    return modint(lhs) / rhs;\n  }\n  constexpr\
    \ modint inverse() const noexcept {\n    assert(value);\n    value_type a{mod},\
    \ b{value}, u{}, v{1}, t{};\n    while (b)\n      t = a / b, a ^= b ^= (a -= t\
    \ * b) ^= b, u ^= v ^= (u -= t * v) ^= v;\n    return {u};\n  }\n  constexpr static\
    \ modint pow(modint rhs, int_fast64_t e) noexcept {\n    if (e < 0) e = e % (mod\
    \ - 1) + mod - 1;\n    modint res{1};\n    while (e) {\n      if (e & 1) res *=\
    \ rhs;\n      rhs *= rhs, e >>= 1;\n    }\n    return res;\n  }\n  friend std::ostream\
    \ &operator<<(std::ostream &os,\n                                  const modint\
    \ &rhs) noexcept {\n    return os << rhs.value;\n  }\n  friend std::istream &operator>>(std::istream\
    \ &is, modint &rhs) noexcept {\n    int_fast64_t value;\n    rhs = (is >> value,\
    \ value);\n    return is;\n  }\n\n protected:\n  value_type value = 0;\n};  //\
    \ class modint\n"
  code: "#pragma once\n#include <cassert>\n#include <iostream>\ntemplate <auto &mod>\
    \  // compile-time defined modulo.\nstruct modint {\n  using value_type = int_least64_t;\n\
    \  constexpr static modint one() noexcept { return 1; }\n  constexpr operator\
    \ value_type() const noexcept { return value; }\n  constexpr modint() noexcept\
    \ = default;\n  template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\n\
    \                                             std::nullptr_t> = nullptr>\n  constexpr\
    \ modint(int_type n) noexcept : value((n %= mod) < 0 ? mod + n : n) {}\n  constexpr\
    \ modint operator++(int) noexcept {\n    modint t{*this};\n    return operator+=(1),\
    \ t;\n  }\n  constexpr modint operator--(int) noexcept {\n    modint t{*this};\n\
    \    return operator-=(1), t;\n  }\n  constexpr modint &operator++() noexcept\
    \ { return operator+=(1); }\n  constexpr modint &operator--() noexcept { return\
    \ operator-=(1); }\n  constexpr modint operator-() const noexcept {\n    return\
    \ value ? mod - value : 0;\n  }\n  constexpr modint &operator+=(const modint &rhs)\
    \ noexcept {\n    return (value += rhs.value) < mod ? 0 : value -= mod, *this;\n\
    \  }\n  constexpr modint &operator-=(const modint &rhs) noexcept {\n    return\
    \ (value += mod - rhs.value) < mod ? 0 : value -= mod, *this;\n  }\n  constexpr\
    \ modint &operator*=(const modint &rhs) noexcept {\n    return value = (int_fast64_t)value\
    \ * rhs.value % mod, *this;\n  }\n  constexpr modint &operator/=(const modint\
    \ &rhs) noexcept {\n    return operator*=(rhs.inverse());\n  }\n  template <class\
    \ int_type, std::enable_if_t<std::is_integral<int_type>::value,\n            \
    \                                 std::nullptr_t> = nullptr>\n  constexpr modint\
    \ operator+(const int_type &rhs) const noexcept {\n    return modint{*this} +=\
    \ rhs;\n  }\n  constexpr modint operator+(const modint &rhs) const noexcept {\n\
    \    return modint{*this} += rhs;\n  }\n  template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\n\
    \                                             std::nullptr_t> = nullptr>\n  constexpr\
    \ modint operator-(const int_type &rhs) const noexcept {\n    return modint{*this}\
    \ -= rhs;\n  }\n  constexpr modint operator-(const modint &rhs) const noexcept\
    \ {\n    return modint{*this} -= rhs;\n  }\n  template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\n\
    \                                             std::nullptr_t> = nullptr>\n  constexpr\
    \ modint operator*(const int_type &rhs) const noexcept {\n    return modint{*this}\
    \ *= rhs;\n  }\n  constexpr modint operator*(const modint &rhs) const noexcept\
    \ {\n    return modint{*this} *= rhs;\n  }\n  template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\n\
    \                                             std::nullptr_t> = nullptr>\n  constexpr\
    \ modint operator/(const int_type &rhs) const noexcept {\n    return modint{*this}\
    \ /= rhs;\n  }\n  constexpr modint operator/(const modint &rhs) const noexcept\
    \ {\n    return modint{*this} /= rhs;\n  }\n  template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\n\
    \                                             std::nullptr_t> = nullptr>\n  constexpr\
    \ friend modint operator+(const int_type &lhs,\n                             \
    \       const modint &rhs) noexcept {\n    return modint(lhs) + rhs;\n  }\n  template\
    \ <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\n     \
    \                                        std::nullptr_t> = nullptr>\n  constexpr\
    \ friend modint operator-(const int_type &lhs,\n                             \
    \       const modint &rhs) noexcept {\n    return modint(lhs) - rhs;\n  }\n  template\
    \ <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\n     \
    \                                        std::nullptr_t> = nullptr>\n  constexpr\
    \ friend modint operator*(const int_type &lhs,\n                             \
    \       const modint &rhs) noexcept {\n    return modint(lhs) * rhs;\n  }\n  template\
    \ <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\n     \
    \                                        std::nullptr_t> = nullptr>\n  constexpr\
    \ friend modint operator/(const int_type &lhs,\n                             \
    \       const modint &rhs) noexcept {\n    return modint(lhs) / rhs;\n  }\n  constexpr\
    \ modint inverse() const noexcept {\n    assert(value);\n    value_type a{mod},\
    \ b{value}, u{}, v{1}, t{};\n    while (b)\n      t = a / b, a ^= b ^= (a -= t\
    \ * b) ^= b, u ^= v ^= (u -= t * v) ^= v;\n    return {u};\n  }\n  constexpr static\
    \ modint pow(modint rhs, int_fast64_t e) noexcept {\n    if (e < 0) e = e % (mod\
    \ - 1) + mod - 1;\n    modint res{1};\n    while (e) {\n      if (e & 1) res *=\
    \ rhs;\n      rhs *= rhs, e >>= 1;\n    }\n    return res;\n  }\n  friend std::ostream\
    \ &operator<<(std::ostream &os,\n                                  const modint\
    \ &rhs) noexcept {\n    return os << rhs.value;\n  }\n  friend std::istream &operator>>(std::istream\
    \ &is, modint &rhs) noexcept {\n    int_fast64_t value;\n    rhs = (is >> value,\
    \ value);\n    return is;\n  }\n\n protected:\n  value_type value = 0;\n};  //\
    \ class modint\n"
  dependsOn: []
  isVerificationFile: false
  path: variation/modint.hpp
  requiredBy: []
  timestamp: '2020-09-09 07:07:14+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: variation/modint.hpp
layout: document
redirect_from:
- /library/variation/modint.hpp
- /library/variation/modint.hpp.html
title: variation/modint.hpp
---
