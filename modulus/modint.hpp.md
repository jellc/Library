---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utils/sfinae.hpp
    title: utils/sfinae.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: combinatorics/binomial.hpp
    title: combinatorics/binomial.hpp
  - icon: ':heavy_check_mark:'
    path: modulus/inverse.hpp
    title: modulus/inverse.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/subset_convolution.test.cpp
    title: test/library-checker/subset_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/queue_operate_all_composite.test.cpp
    title: test/library-checker/queue_operate_all_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/range_affine_range_sum.test.cpp
    title: test/library-checker/range_affine_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/point_set_range_composite.test.cpp
    title: test/library-checker/point_set_range_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/balls_and_boxes_4.test.cpp
    title: test/aizu-online-judge/balls_and_boxes_4.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 2 \"modulus/modint.hpp\"\n#include <cassert>\n#include <iostream>\n\
    \n#line 2 \"utils/sfinae.hpp\"\n#include <cstdint>\n#include <type_traits>\n\n\
    template <class type, template <class> class trait>\nusing enable_if_trait_type\
    \ = typename std::enable_if<trait<type>::value>::type;\n\ntemplate <class Container>\n\
    using element_type = typename std::decay<decltype(\n    *std::begin(std::declval<Container&>()))>::type;\n\
    \ntemplate <class T, class = int> struct mapped_of {\n  using type = element_type<T>;\n\
    };\ntemplate <class T>\nstruct mapped_of<T,\n                 typename std::pair<int,\
    \ typename T::mapped_type>::first_type> {\n  using type = typename T::mapped_type;\n\
    };\ntemplate <class T> using mapped_type = typename mapped_of<T>::type;\n\ntemplate\
    \ <class T, class = void> struct is_integral_ext : std::false_type {};\ntemplate\
    \ <class T>\nstruct is_integral_ext<\n    T, typename std::enable_if<std::is_integral<T>::value>::type>\n\
    \    : std::true_type {};\ntemplate <> struct is_integral_ext<__int128_t> : std::true_type\
    \ {};\ntemplate <> struct is_integral_ext<__uint128_t> : std::true_type {};\n\
    #if __cplusplus >= 201402\ntemplate <class T>\nconstexpr static bool is_integral_ext_v\
    \ = is_integral_ext<T>::value;\n#endif\n\ntemplate <typename T, typename = void>\
    \ struct multiplicable_uint {\n  using type = uint_least32_t;\n};\ntemplate <typename\
    \ T>\nstruct multiplicable_uint<T, typename std::enable_if<(2 < sizeof(T))>::type>\
    \ {\n  using type = uint_least64_t;\n};\ntemplate <typename T>\nstruct multiplicable_uint<T,\
    \ typename std::enable_if<(4 < sizeof(T))>::type> {\n  using type = __uint128_t;\n\
    };\n#line 6 \"modulus/modint.hpp\"\n\ntemplate <auto Mod = 0, typename Mod_type\
    \ = decltype(Mod)> struct modint {\n  static_assert(is_integral_ext<decltype(Mod)>::value,\n\
    \                \"Mod must be integral type.\");\n  static_assert(!(Mod < 0),\
    \ \"Mod must be non-negative.\");\n\n  using mod_type = typename std::conditional<\n\
    \      Mod != 0, typename std::add_const<Mod_type>::type, Mod_type>::type;\n \
    \ static mod_type mod;\n\n  using value_type = typename std::decay<mod_type>::type;\n\
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
    \ Mod_type>::mod = Mod;\n\nusing modint_runtime = modint<0>;\n"
  code: "#pragma once\n#include <cassert>\n#include <iostream>\n\n#include \"utils/sfinae.hpp\"\
    \n\ntemplate <auto Mod = 0, typename Mod_type = decltype(Mod)> struct modint {\n\
    \  static_assert(is_integral_ext<decltype(Mod)>::value,\n                \"Mod\
    \ must be integral type.\");\n  static_assert(!(Mod < 0), \"Mod must be non-negative.\"\
    );\n\n  using mod_type = typename std::conditional<\n      Mod != 0, typename\
    \ std::add_const<Mod_type>::type, Mod_type>::type;\n  static mod_type mod;\n\n\
    \  using value_type = typename std::decay<mod_type>::type;\n\n  constexpr operator\
    \ value_type() const noexcept { return value; }\n\n  constexpr static modint one()\
    \ noexcept { return 1; }\n\n  constexpr modint() noexcept = default;\n\n  template\
    \ <class int_type,\n            typename std::enable_if<is_integral_ext<int_type>::value>::type\
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
    \ Mod_type>::mod = Mod;\n\nusing modint_runtime = modint<0>;\n"
  dependsOn:
  - utils/sfinae.hpp
  isVerificationFile: false
  path: modulus/modint.hpp
  requiredBy:
  - combinatorics/binomial.hpp
  - modulus/inverse.hpp
  timestamp: '2020-09-21 02:49:05+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/subset_convolution.test.cpp
  - test/library-checker/queue_operate_all_composite.test.cpp
  - test/library-checker/range_affine_range_sum.test.cpp
  - test/library-checker/point_set_range_composite.test.cpp
  - test/aizu-online-judge/balls_and_boxes_4.test.cpp
documentation_of: modulus/modint.hpp
layout: document
redirect_from:
- /library/modulus/modint.hpp
- /library/modulus/modint.hpp.html
title: modulus/modint.hpp
---
