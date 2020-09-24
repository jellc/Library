---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: modulus/modint.hpp
    title: modulus/modint.hpp
  - icon: ':question:'
    path: utils/sfinae.hpp
    title: utils/sfinae.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: combinatorics/binomial.hpp
    title: combinatorics/binomial.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/balls_and_boxes_4.test.cpp
    title: test/aizu-online-judge/balls_and_boxes_4.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 2 \"modulus/inverse.hpp\"\n#include <vector>\n\n#line 2 \"modulus/modint.hpp\"\
    \n#include <cassert>\n#include <iostream>\n\n#line 2 \"utils/sfinae.hpp\"\n#include\
    \ <cstdint>\n#include <type_traits>\n\ntemplate <class type, template <class>\
    \ class trait>\nusing enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
    \ntemplate <class Container>\nusing element_type = typename std::decay<decltype(\n\
    \    *std::begin(std::declval<Container&>()))>::type;\n\ntemplate <class T, class\
    \ = int> struct mapped_of {\n  using type = element_type<T>;\n};\ntemplate <class\
    \ T>\nstruct mapped_of<T,\n                 typename std::pair<int, typename T::mapped_type>::first_type>\
    \ {\n  using type = typename T::mapped_type;\n};\ntemplate <class T> using mapped_type\
    \ = typename mapped_of<T>::type;\n\ntemplate <class T, class = void> struct is_integral_ext\
    \ : std::false_type {};\ntemplate <class T>\nstruct is_integral_ext<\n    T, typename\
    \ std::enable_if<std::is_integral<T>::value>::type>\n    : std::true_type {};\n\
    template <> struct is_integral_ext<__int128_t> : std::true_type {};\ntemplate\
    \ <> struct is_integral_ext<__uint128_t> : std::true_type {};\n#if __cplusplus\
    \ >= 201402\ntemplate <class T>\nconstexpr static bool is_integral_ext_v = is_integral_ext<T>::value;\n\
    #endif\n\ntemplate <typename T, typename = void> struct multiplicable_uint {\n\
    \  using type = uint_least32_t;\n};\ntemplate <typename T>\nstruct multiplicable_uint<T,\
    \ typename std::enable_if<(2 < sizeof(T))>::type> {\n  using type = uint_least64_t;\n\
    };\ntemplate <typename T>\nstruct multiplicable_uint<T, typename std::enable_if<(4\
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n#line 6 \"modulus/modint.hpp\"\
    \n\n// A non-positive Mod corresponds a runtime type of modint.\ntemplate <auto\
    \ Mod = 0, typename Mod_type = decltype(Mod)> struct modint {\n  static_assert(is_integral_ext<decltype(Mod)>::value,\n\
    \                \"Mod must be integral type.\");\n\n  using mod_type = typename\
    \ std::conditional<\n      0 < Mod, typename std::add_const<Mod_type>::type, Mod_type>::type;\n\
    \  static mod_type mod;\n\n  using value_type = typename std::decay<mod_type>::type;\n\
    \n  constexpr operator value_type() const noexcept { return value; }\n\n  constexpr\
    \ static modint one() noexcept { return 1; }\n\n  constexpr modint() noexcept\
    \ = default;\n\n  template <class int_type,\n            typename std::enable_if<is_integral_ext<int_type>::value>::type\
    \ * =\n                nullptr>\n  constexpr modint(int_type n) noexcept : value((n\
    \ %= mod) < 0 ? mod + n : n) {}\n\n  constexpr modint(bool n) noexcept : modint(int(n))\
    \ {}\n\n  constexpr modint operator++(int) noexcept {\n    modint t{*this};\n\
    \    return operator+=(1), t;\n  }\n\n  constexpr modint operator--(int) noexcept\
    \ {\n    modint t{*this};\n    return operator-=(1), t;\n  }\n\n  constexpr modint\
    \ &operator++() noexcept { return operator+=(1); }\n\n  constexpr modint &operator--()\
    \ noexcept { return operator-=(1); }\n\n  constexpr modint operator-() const noexcept\
    \ {\n    return value ? mod - value : 0;\n  }\n\n  constexpr modint &operator+=(const\
    \ modint &rhs) noexcept {\n    return (value += rhs.value) < mod ? 0 : value -=\
    \ mod, *this;\n  }\n\n  constexpr modint &operator-=(const modint &rhs) noexcept\
    \ {\n    return (value += mod - rhs.value) < mod ? 0 : value -= mod, *this;\n\
    \  }\n\n  constexpr modint &operator*=(const modint &rhs) noexcept {\n    return\
    \ value = (typename multiplicable_uint<value_type>::type)value *\n           \
    \        rhs.value % mod,\n           *this;\n  }\n\n  constexpr modint &operator/=(const\
    \ modint &rhs) noexcept {\n    return operator*=(rhs.inverse());\n  }\n\n  template\
    \ <class int_type>\n  constexpr\n      typename std::enable_if<is_integral_ext<int_type>::value,\
    \ modint>::type\n      operator+(const int_type &rhs) const noexcept {\n    return\
    \ modint{*this} += rhs;\n  }\n\n  constexpr modint operator+(const modint &rhs)\
    \ const noexcept {\n    return modint{*this} += rhs;\n  }\n\n  template <class\
    \ int_type>\n  constexpr\n      typename std::enable_if<is_integral_ext<int_type>::value,\
    \ modint>::type\n      operator-(const int_type &rhs) const noexcept {\n    return\
    \ modint{*this} -= rhs;\n  }\n\n  constexpr modint operator-(const modint &rhs)\
    \ const noexcept {\n    return modint{*this} -= rhs;\n  }\n\n  template <class\
    \ int_type>\n  constexpr\n      typename std::enable_if<is_integral_ext<int_type>::value,\
    \ modint>::type\n      operator*(const int_type &rhs) const noexcept {\n    return\
    \ modint{*this} *= rhs;\n  }\n\n  constexpr modint operator*(const modint &rhs)\
    \ const noexcept {\n    return modint{*this} *= rhs;\n  }\n\n  template <class\
    \ int_type>\n  constexpr\n      typename std::enable_if<is_integral_ext<int_type>::value,\
    \ modint>::type\n      operator/(const int_type &rhs) const noexcept {\n    return\
    \ modint{*this} /= rhs;\n  }\n\n  constexpr modint operator/(const modint &rhs)\
    \ const noexcept {\n    return modint{*this} /= rhs;\n  }\n\n  template <class\
    \ int_type>\n  constexpr friend\n      typename std::enable_if<is_integral_ext<int_type>::value,\
    \ modint>::type\n      operator+(const int_type &lhs, const modint &rhs) noexcept\
    \ {\n    return modint(lhs) + rhs;\n  }\n\n  template <class int_type>\n  constexpr\
    \ friend\n      typename std::enable_if<is_integral_ext<int_type>::value, modint>::type\n\
    \      operator-(const int_type &lhs, const modint &rhs) noexcept {\n    return\
    \ modint(lhs) - rhs;\n  }\n\n  template <class int_type>\n  constexpr friend\n\
    \      typename std::enable_if<is_integral_ext<int_type>::value, modint>::type\n\
    \      operator*(const int_type &lhs, const modint &rhs) noexcept {\n    return\
    \ modint(lhs) * rhs;\n  }\n\n  template <class int_type>\n  constexpr friend\n\
    \      typename std::enable_if<is_integral_ext<int_type>::value, modint>::type\n\
    \      operator/(const int_type &lhs, const modint &rhs) noexcept {\n    return\
    \ modint(lhs) / rhs;\n  }\n\n  constexpr modint inverse() const noexcept {\n \
    \   assert(value);\n    value_type a{mod}, b{value}, u{}, v{1}, t{};\n    while\
    \ (b)\n      t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^=\
    \ v;\n    return {u};\n  }\n\n  template <class int_type>\n  constexpr\n     \
    \ typename std::enable_if<is_integral_ext<int_type>::value, modint>::type\n  \
    \    power(int_type e) noexcept {\n    if (e < 0) e = e % (mod - 1) + mod - 1;\n\
    \    modint res{1};\n    for (modint p{value}; e; e >>= 1, p *= p) {\n      if\
    \ (e & 1) res *= p;\n    }\n    return res;\n  }\n\n  template <class int_type>\n\
    \  friend constexpr\n      typename std::enable_if<is_integral_ext<int_type>::value,\
    \ modint>::type\n      pow(modint b, int_type e) noexcept {\n    modint res{1};\n\
    \    for ((e %= mod - 1) < 0 ? e += mod - 1 : 0; e; e >>= 1, b *= b)\n      if\
    \ (e & 1) res *= b;\n    return res;\n  }\n\n  friend std::ostream &operator<<(std::ostream\
    \ &os,\n                                  const modint &rhs) noexcept {\n    return\
    \ os << rhs.value;\n  }\n\n  friend std::istream &operator>>(std::istream &is,\
    \ modint &rhs) noexcept {\n    intmax_t value;\n    rhs = (is >> value, value);\n\
    \    return is;\n  }\n\n protected:\n  value_type value = 0;\n};\n\ntemplate <auto\
    \ Mod, typename Mod_type>\ntypename modint<Mod, Mod_type>::mod_type modint<Mod,\
    \ Mod_type>::mod = Mod;\n\ntemplate <unsigned type_id = 0> using modint_runtime\
    \ = modint<-(signed)type_id>;\n// #define modint_newtype modint<-__COUNTER__>\n\
    #line 5 \"modulus/inverse.hpp\"\ntemplate <class, class = int> struct inverse;\n\
    // mod must be prime.\ntemplate <class Modint>\nstruct inverse<Modint, decltype((void\
    \ *)Modint::mod, 0)> {\n  using value_type = Modint;\n  constexpr value_type operator()(int\
    \ n) const {\n    constexpr int_fast64_t mod = value_type::mod;\n    assert(n\
    \ %= mod);\n    if (n < 0) n += mod;\n    if (inv.empty()) inv = {1, mod != 1};\n\
    \    for (int m(inv.size()); m <= n; ++m)\n      inv.emplace_back(mod / m * -inv[mod\
    \ % m]);\n    return inv[n];\n  }\n\n private:\n  static std::vector<value_type>\
    \ inv;\n};\ntemplate <class Modint>\nstd::vector<Modint> inverse<Modint, decltype((void\
    \ *)Modint::mod, 0)>::inv;\n"
  code: "#pragma once\n#include <vector>\n\n#include \"modint.hpp\"\ntemplate <class,\
    \ class = int> struct inverse;\n// mod must be prime.\ntemplate <class Modint>\n\
    struct inverse<Modint, decltype((void *)Modint::mod, 0)> {\n  using value_type\
    \ = Modint;\n  constexpr value_type operator()(int n) const {\n    constexpr int_fast64_t\
    \ mod = value_type::mod;\n    assert(n %= mod);\n    if (n < 0) n += mod;\n  \
    \  if (inv.empty()) inv = {1, mod != 1};\n    for (int m(inv.size()); m <= n;\
    \ ++m)\n      inv.emplace_back(mod / m * -inv[mod % m]);\n    return inv[n];\n\
    \  }\n\n private:\n  static std::vector<value_type> inv;\n};\ntemplate <class\
    \ Modint>\nstd::vector<Modint> inverse<Modint, decltype((void *)Modint::mod, 0)>::inv;\n"
  dependsOn:
  - modulus/modint.hpp
  - utils/sfinae.hpp
  isVerificationFile: false
  path: modulus/inverse.hpp
  requiredBy:
  - combinatorics/binomial.hpp
  timestamp: '2020-09-23 23:35:05+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aizu-online-judge/balls_and_boxes_4.test.cpp
documentation_of: modulus/inverse.hpp
layout: document
redirect_from:
- /library/modulus/inverse.hpp
- /library/modulus/inverse.hpp.html
title: modulus/inverse.hpp
---
