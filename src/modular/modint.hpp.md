---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: src/combinatorics/binomial.hpp
    title: Binomial Coefficient
  - icon: ':warning:'
    path: src/modular/inverse.hpp
    title: Inverse Table
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/DPL_5_D.test.cpp
    title: test/aizu-online-judge/DPL_5_D.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/bitwise_and_convolution.test.cpp
    title: test/library-checker/bitwise_and_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/bitwise_xor_convolution.test.cpp
    title: test/library-checker/bitwise_xor_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/point_set_range_composite.test.cpp
    title: test/library-checker/point_set_range_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/queue_operate_all_composite.test.cpp
    title: test/library-checker/queue_operate_all_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/range_affine_range_sum.test.cpp
    title: test/library-checker/range_affine_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/subset_convolution.test.cpp
    title: test/library-checker/subset_convolution.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Modular Arithmetic
    links: []
  bundledCode: "#line 2 \"src/modular/modint.hpp\"\n\n/*\n * @file modint.hpp\n *\
    \ @brief Modular Arithmetic\n */\n\n#include <cassert>\n#include <iostream>\n\n\
    #line 2 \"src/utils/sfinae.hpp\"\n\n/**\n * @file sfinae.hpp\n * @brief SFINAE\n\
    \ */\n\n#include <cstdint>\n#include <iterator>\n#include <type_traits>\n\n#ifndef\
    \ __INT128_DEFINED__\n\n#ifdef __SIZEOF_INT128__\n#define __INT128_DEFINED__ 1\n\
    #else\n#define __INT128_DEFINED__ 0\n#endif\n\n#endif\n\nnamespace std {\n\n#if\
    \ __INT128_DEFINED__\n\ntemplate <> struct make_signed<__uint128_t> { using type\
    \ = __int128_t; };\ntemplate <> struct make_signed<__int128_t> { using type =\
    \ __int128_t; };\n\ntemplate <> struct make_unsigned<__uint128_t> { using type\
    \ = __uint128_t; };\ntemplate <> struct make_unsigned<__int128_t> { using type\
    \ = __uint128_t; };\n\n#endif\n\n}  // namespace std\n\nnamespace workspace {\n\
    \ntemplate <class Tp, class... Args> struct variadic_front { using type = Tp;\
    \ };\n\ntemplate <class... Args> struct variadic_back;\n\ntemplate <class Tp>\
    \ struct variadic_back<Tp> { using type = Tp; };\n\ntemplate <class Tp, class...\
    \ Args> struct variadic_back<Tp, Args...> {\n  using type = typename variadic_back<Args...>::type;\n\
    };\n\ntemplate <class type, template <class> class trait>\nusing enable_if_trait_type\
    \ = typename std::enable_if<trait<type>::value>::type;\n\ntemplate <class Container>\n\
    using element_type = typename std::decay<decltype(\n    *std::begin(std::declval<Container&>()))>::type;\n\
    \ntemplate <class T, class = std::nullptr_t>\nstruct has_begin : std::false_type\
    \ {};\n\ntemplate <class T>\nstruct has_begin<T, decltype(std::begin(std::declval<T>()),\
    \ nullptr)>\n    : std::true_type {};\n\ntemplate <class T, class = int> struct\
    \ mapped_of {\n  using type = element_type<T>;\n};\ntemplate <class T>\nstruct\
    \ mapped_of<T,\n                 typename std::pair<int, typename T::mapped_type>::first_type>\
    \ {\n  using type = typename T::mapped_type;\n};\ntemplate <class T> using mapped_type\
    \ = typename mapped_of<T>::type;\n\ntemplate <class T, class = void> struct is_integral_ext\
    \ : std::false_type {};\ntemplate <class T>\nstruct is_integral_ext<\n    T, typename\
    \ std::enable_if<std::is_integral<T>::value>::type>\n    : std::true_type {};\n\
    \n#if __INT128_DEFINED__\n\ntemplate <> struct is_integral_ext<__int128_t> : std::true_type\
    \ {};\ntemplate <> struct is_integral_ext<__uint128_t> : std::true_type {};\n\n\
    #endif\n\n#if __cplusplus >= 201402\n\ntemplate <class T>\nconstexpr static bool\
    \ is_integral_ext_v = is_integral_ext<T>::value;\n\n#endif\n\ntemplate <typename\
    \ T, typename = void> struct multiplicable_uint {\n  using type = uint_least32_t;\n\
    };\ntemplate <typename T>\nstruct multiplicable_uint<\n    T, typename std::enable_if<(2\
    \ < sizeof(T)) &&\n                               (!__INT128_DEFINED__ || sizeof(T)\
    \ <= 4)>::type> {\n  using type = uint_least64_t;\n};\n\n#if __INT128_DEFINED__\n\
    \ntemplate <typename T>\nstruct multiplicable_uint<T, typename std::enable_if<(4\
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n\n#endif\n\ntemplate\
    \ <typename T> struct multiplicable_int {\n  using type =\n      typename std::make_signed<typename\
    \ multiplicable_uint<T>::type>::type;\n};\n\n}  // namespace workspace\n#line\
    \ 12 \"src/modular/modint.hpp\"\n\nnamespace workspace {\n\nnamespace internal\
    \ {\n\n/*\n * @struct modint_base\n * @brief base of modular arithmetic.\n * @tparam\
    \ Mod identifier, which represents modulus if positive\n */\ntemplate <auto Mod>\
    \ struct modint_base {\n  static_assert(is_integral_ext<decltype(Mod)>::value,\n\
    \                \"Mod must be integral type.\");\n\n  using mod_type =\n    \
    \  typename std::conditional<0 < Mod,\n                                typename\
    \ std::add_const<decltype(Mod)>::type,\n                                decltype(Mod)>::type;\n\
    \  static mod_type mod;\n\n  using value_type = typename std::decay<mod_type>::type;\n\
    \n  constexpr operator value_type() const noexcept { return value; }\n\n  constexpr\
    \ static modint_base one() noexcept { return 1; }\n\n  constexpr modint_base()\
    \ noexcept = default;\n\n  template <class int_type,\n            typename std::enable_if<is_integral_ext<int_type>::value>::type\
    \ * =\n                nullptr>\n  constexpr modint_base(int_type n) noexcept\n\
    \      : value((n %= mod) < 0 ? mod + n : n) {}\n\n  constexpr modint_base(bool\
    \ n) noexcept : modint_base(int(n)) {}\n\n  constexpr modint_base operator++(int)\
    \ noexcept {\n    modint_base t{*this};\n    return operator+=(1), t;\n  }\n\n\
    \  constexpr modint_base operator--(int) noexcept {\n    modint_base t{*this};\n\
    \    return operator-=(1), t;\n  }\n\n  constexpr modint_base &operator++() noexcept\
    \ { return operator+=(1); }\n\n  constexpr modint_base &operator--() noexcept\
    \ { return operator-=(1); }\n\n  constexpr modint_base operator-() const noexcept\
    \ {\n    return value ? mod - value : 0;\n  }\n\n  constexpr modint_base &operator+=(const\
    \ modint_base &rhs) noexcept {\n    return (value += rhs.value) < mod ? 0 : value\
    \ -= mod, *this;\n  }\n\n  constexpr modint_base &operator-=(const modint_base\
    \ &rhs) noexcept {\n    return (value += mod - rhs.value) < mod ? 0 : value -=\
    \ mod, *this;\n  }\n\n  constexpr modint_base &operator*=(const modint_base &rhs)\
    \ noexcept {\n    return value = (typename multiplicable_uint<value_type>::type)value\
    \ *\n                   rhs.value % mod,\n           *this;\n  }\n\n  constexpr\
    \ modint_base &operator/=(const modint_base &rhs) noexcept {\n    return operator*=(rhs.inverse());\n\
    \  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  operator+(const int_type\
    \ &rhs) const noexcept {\n    return modint_base{*this} += rhs;\n  }\n\n  constexpr\
    \ modint_base operator+(const modint_base &rhs) const noexcept {\n    return modint_base{*this}\
    \ += rhs;\n  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  operator-(const int_type\
    \ &rhs) const noexcept {\n    return modint_base{*this} -= rhs;\n  }\n\n  constexpr\
    \ modint_base operator-(const modint_base &rhs) const noexcept {\n    return modint_base{*this}\
    \ -= rhs;\n  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  operator*(const int_type\
    \ &rhs) const noexcept {\n    return modint_base{*this} *= rhs;\n  }\n\n  constexpr\
    \ modint_base operator*(const modint_base &rhs) const noexcept {\n    return modint_base{*this}\
    \ *= rhs;\n  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  operator/(const int_type\
    \ &rhs) const noexcept {\n    return modint_base{*this} /= rhs;\n  }\n\n  constexpr\
    \ modint_base operator/(const modint_base &rhs) const noexcept {\n    return modint_base{*this}\
    \ /= rhs;\n  }\n\n  template <class int_type>\n  constexpr friend typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                           modint_base>::type\n  operator+(const\
    \ int_type &lhs, const modint_base &rhs) noexcept {\n    return modint_base(lhs)\
    \ + rhs;\n  }\n\n  template <class int_type>\n  constexpr friend typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                           modint_base>::type\n  operator-(const\
    \ int_type &lhs, const modint_base &rhs) noexcept {\n    return modint_base(lhs)\
    \ - rhs;\n  }\n\n  template <class int_type>\n  constexpr friend typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                           modint_base>::type\n  operator*(const\
    \ int_type &lhs, const modint_base &rhs) noexcept {\n    return modint_base(lhs)\
    \ * rhs;\n  }\n\n  template <class int_type>\n  constexpr friend typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                           modint_base>::type\n  operator/(const\
    \ int_type &lhs, const modint_base &rhs) noexcept {\n    return modint_base(lhs)\
    \ / rhs;\n  }\n\n  constexpr modint_base inverse() const noexcept {\n    assert(value);\n\
    \    value_type a{mod}, b{value}, u{}, v{1}, t{};\n    while (b)\n      t = a\
    \ / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;\n    return {u};\n\
    \  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  power(int_type e) noexcept\
    \ {\n    return pow(*this, e);\n  }\n\n  template <class int_type>\n  friend constexpr\
    \ typename std::enable_if<is_integral_ext<int_type>::value,\n                \
    \                           modint_base>::type\n  pow(modint_base b, int_type\
    \ e) noexcept {\n    modint_base res{1};\n    for (e < 0 ? b = b.inverse(), e\
    \ = -e : 0; e; e >>= 1, b *= b)\n      if (e & 1) res *= b;\n    return res;\n\
    \  }\n\n  friend std::ostream &operator<<(std::ostream &os,\n                \
    \                  const modint_base &rhs) noexcept {\n    return os << rhs.value;\n\
    \  }\n\n  friend std::istream &operator>>(std::istream &is, modint_base &rhs)\
    \ noexcept {\n    intmax_t value;\n    rhs = (is >> value, value);\n    return\
    \ is;\n  }\n\n protected:\n  value_type value = 0;\n};\n\ntemplate <auto Mod>\n\
    typename modint_base<Mod>::mod_type modint_base<Mod>::mod = Mod;\n\n}  // namespace\
    \ internal\n\n/*\n * @typedef modint\n * @brief modular arithmetic.\n * @tparam\
    \ Mod modulus\n */\ntemplate <auto Mod, typename std::enable_if<(Mod > 0)>::type\
    \ * = nullptr>\nusing modint = internal::modint_base<Mod>;\n\n/*\n * @typedef\
    \ modint_runtime\n * @brief runtime modular arithmetic.\n * @tparam type_id uniquely\
    \ assigned\n */\ntemplate <unsigned type_id = 0>\nusing modint_runtime = internal::modint_base<-(signed)type_id>;\n\
    \n// #define modint_newtype modint_runtime<__COUNTER__>\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file modint.hpp\n * @brief Modular Arithmetic\n */\n\
    \n#include <cassert>\n#include <iostream>\n\n#include \"../utils/sfinae.hpp\"\n\
    \nnamespace workspace {\n\nnamespace internal {\n\n/*\n * @struct modint_base\n\
    \ * @brief base of modular arithmetic.\n * @tparam Mod identifier, which represents\
    \ modulus if positive\n */\ntemplate <auto Mod> struct modint_base {\n  static_assert(is_integral_ext<decltype(Mod)>::value,\n\
    \                \"Mod must be integral type.\");\n\n  using mod_type =\n    \
    \  typename std::conditional<0 < Mod,\n                                typename\
    \ std::add_const<decltype(Mod)>::type,\n                                decltype(Mod)>::type;\n\
    \  static mod_type mod;\n\n  using value_type = typename std::decay<mod_type>::type;\n\
    \n  constexpr operator value_type() const noexcept { return value; }\n\n  constexpr\
    \ static modint_base one() noexcept { return 1; }\n\n  constexpr modint_base()\
    \ noexcept = default;\n\n  template <class int_type,\n            typename std::enable_if<is_integral_ext<int_type>::value>::type\
    \ * =\n                nullptr>\n  constexpr modint_base(int_type n) noexcept\n\
    \      : value((n %= mod) < 0 ? mod + n : n) {}\n\n  constexpr modint_base(bool\
    \ n) noexcept : modint_base(int(n)) {}\n\n  constexpr modint_base operator++(int)\
    \ noexcept {\n    modint_base t{*this};\n    return operator+=(1), t;\n  }\n\n\
    \  constexpr modint_base operator--(int) noexcept {\n    modint_base t{*this};\n\
    \    return operator-=(1), t;\n  }\n\n  constexpr modint_base &operator++() noexcept\
    \ { return operator+=(1); }\n\n  constexpr modint_base &operator--() noexcept\
    \ { return operator-=(1); }\n\n  constexpr modint_base operator-() const noexcept\
    \ {\n    return value ? mod - value : 0;\n  }\n\n  constexpr modint_base &operator+=(const\
    \ modint_base &rhs) noexcept {\n    return (value += rhs.value) < mod ? 0 : value\
    \ -= mod, *this;\n  }\n\n  constexpr modint_base &operator-=(const modint_base\
    \ &rhs) noexcept {\n    return (value += mod - rhs.value) < mod ? 0 : value -=\
    \ mod, *this;\n  }\n\n  constexpr modint_base &operator*=(const modint_base &rhs)\
    \ noexcept {\n    return value = (typename multiplicable_uint<value_type>::type)value\
    \ *\n                   rhs.value % mod,\n           *this;\n  }\n\n  constexpr\
    \ modint_base &operator/=(const modint_base &rhs) noexcept {\n    return operator*=(rhs.inverse());\n\
    \  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  operator+(const int_type\
    \ &rhs) const noexcept {\n    return modint_base{*this} += rhs;\n  }\n\n  constexpr\
    \ modint_base operator+(const modint_base &rhs) const noexcept {\n    return modint_base{*this}\
    \ += rhs;\n  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  operator-(const int_type\
    \ &rhs) const noexcept {\n    return modint_base{*this} -= rhs;\n  }\n\n  constexpr\
    \ modint_base operator-(const modint_base &rhs) const noexcept {\n    return modint_base{*this}\
    \ -= rhs;\n  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  operator*(const int_type\
    \ &rhs) const noexcept {\n    return modint_base{*this} *= rhs;\n  }\n\n  constexpr\
    \ modint_base operator*(const modint_base &rhs) const noexcept {\n    return modint_base{*this}\
    \ *= rhs;\n  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  operator/(const int_type\
    \ &rhs) const noexcept {\n    return modint_base{*this} /= rhs;\n  }\n\n  constexpr\
    \ modint_base operator/(const modint_base &rhs) const noexcept {\n    return modint_base{*this}\
    \ /= rhs;\n  }\n\n  template <class int_type>\n  constexpr friend typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                           modint_base>::type\n  operator+(const\
    \ int_type &lhs, const modint_base &rhs) noexcept {\n    return modint_base(lhs)\
    \ + rhs;\n  }\n\n  template <class int_type>\n  constexpr friend typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                           modint_base>::type\n  operator-(const\
    \ int_type &lhs, const modint_base &rhs) noexcept {\n    return modint_base(lhs)\
    \ - rhs;\n  }\n\n  template <class int_type>\n  constexpr friend typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                           modint_base>::type\n  operator*(const\
    \ int_type &lhs, const modint_base &rhs) noexcept {\n    return modint_base(lhs)\
    \ * rhs;\n  }\n\n  template <class int_type>\n  constexpr friend typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                           modint_base>::type\n  operator/(const\
    \ int_type &lhs, const modint_base &rhs) noexcept {\n    return modint_base(lhs)\
    \ / rhs;\n  }\n\n  constexpr modint_base inverse() const noexcept {\n    assert(value);\n\
    \    value_type a{mod}, b{value}, u{}, v{1}, t{};\n    while (b)\n      t = a\
    \ / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;\n    return {u};\n\
    \  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  power(int_type e) noexcept\
    \ {\n    return pow(*this, e);\n  }\n\n  template <class int_type>\n  friend constexpr\
    \ typename std::enable_if<is_integral_ext<int_type>::value,\n                \
    \                           modint_base>::type\n  pow(modint_base b, int_type\
    \ e) noexcept {\n    modint_base res{1};\n    for (e < 0 ? b = b.inverse(), e\
    \ = -e : 0; e; e >>= 1, b *= b)\n      if (e & 1) res *= b;\n    return res;\n\
    \  }\n\n  friend std::ostream &operator<<(std::ostream &os,\n                \
    \                  const modint_base &rhs) noexcept {\n    return os << rhs.value;\n\
    \  }\n\n  friend std::istream &operator>>(std::istream &is, modint_base &rhs)\
    \ noexcept {\n    intmax_t value;\n    rhs = (is >> value, value);\n    return\
    \ is;\n  }\n\n protected:\n  value_type value = 0;\n};\n\ntemplate <auto Mod>\n\
    typename modint_base<Mod>::mod_type modint_base<Mod>::mod = Mod;\n\n}  // namespace\
    \ internal\n\n/*\n * @typedef modint\n * @brief modular arithmetic.\n * @tparam\
    \ Mod modulus\n */\ntemplate <auto Mod, typename std::enable_if<(Mod > 0)>::type\
    \ * = nullptr>\nusing modint = internal::modint_base<Mod>;\n\n/*\n * @typedef\
    \ modint_runtime\n * @brief runtime modular arithmetic.\n * @tparam type_id uniquely\
    \ assigned\n */\ntemplate <unsigned type_id = 0>\nusing modint_runtime = internal::modint_base<-(signed)type_id>;\n\
    \n// #define modint_newtype modint_runtime<__COUNTER__>\n\n}  // namespace workspace\n"
  dependsOn:
  - src/utils/sfinae.hpp
  isVerificationFile: false
  path: src/modular/modint.hpp
  requiredBy:
  - src/combinatorics/binomial.hpp
  - src/modular/inverse.hpp
  timestamp: '2021-01-22 09:52:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/bitwise_xor_convolution.test.cpp
  - test/library-checker/queue_operate_all_composite.test.cpp
  - test/library-checker/bitwise_and_convolution.test.cpp
  - test/library-checker/range_affine_range_sum.test.cpp
  - test/library-checker/subset_convolution.test.cpp
  - test/library-checker/point_set_range_composite.test.cpp
  - test/aizu-online-judge/DPL_5_D.test.cpp
documentation_of: src/modular/modint.hpp
layout: document
redirect_from:
- /library/src/modular/modint.hpp
- /library/src/modular/modint.hpp.html
title: Modular Arithmetic
---
