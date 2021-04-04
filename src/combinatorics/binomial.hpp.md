---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/combinatorics/factorial.hpp
    title: Factorial
  - icon: ':question:'
    path: src/modular/modint.hpp
    title: Modular Arithmetic
  - icon: ':question:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/DPL_5_D.test.cpp
    title: test/aizu-online-judge/DPL_5_D.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Binomial Coefficient
    links: []
  bundledCode: "#line 2 \"src/combinatorics/binomial.hpp\"\n\n/**\n * @file binomial.hpp\n\
    \ * @brief Binomial Coefficient\n * @date 2021-01-15\n *\n *\n */\n\n#line 2 \"\
    src/modular/modint.hpp\"\n\n/**\n * @file modint.hpp\n *\n * @brief Modular Arithmetic\n\
    \ */\n\n#include <cassert>\n#include <iostream>\n#include <vector>\n\n#line 2\
    \ \"src/utils/sfinae.hpp\"\n\n/**\n * @file sfinae.hpp\n * @brief SFINAE\n */\n\
    \n#include <cstdint>\n#include <iterator>\n#include <type_traits>\n\n#ifndef __INT128_DEFINED__\n\
    \n#ifdef __SIZEOF_INT128__\n#define __INT128_DEFINED__ 1\n#else\n#define __INT128_DEFINED__\
    \ 0\n#endif\n\n#endif\n\nnamespace std {\n\n#if __INT128_DEFINED__\n\ntemplate\
    \ <> struct make_signed<__uint128_t> { using type = __int128_t; };\ntemplate <>\
    \ struct make_signed<__int128_t> { using type = __int128_t; };\n\ntemplate <>\
    \ struct make_unsigned<__uint128_t> { using type = __uint128_t; };\ntemplate <>\
    \ struct make_unsigned<__int128_t> { using type = __uint128_t; };\n\n#endif\n\n\
    }  // namespace std\n\nnamespace workspace {\n\ntemplate <class Tp, class... Args>\
    \ struct variadic_front { using type = Tp; };\n\ntemplate <class... Args> struct\
    \ variadic_back;\n\ntemplate <class Tp> struct variadic_back<Tp> { using type\
    \ = Tp; };\n\ntemplate <class Tp, class... Args> struct variadic_back<Tp, Args...>\
    \ {\n  using type = typename variadic_back<Args...>::type;\n};\n\ntemplate <class\
    \ type, template <class> class trait>\nusing enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
    \ntemplate <class Container>\nusing element_type = typename std::decay<decltype(\n\
    \    *std::begin(std::declval<Container&>()))>::type;\n\ntemplate <class T, class\
    \ = std::nullptr_t>\nstruct has_begin : std::false_type {};\n\ntemplate <class\
    \ T>\nstruct has_begin<T, decltype(std::begin(std::declval<T>()), nullptr)>\n\
    \    : std::true_type {};\n\ntemplate <class T, class = int> struct mapped_of\
    \ {\n  using type = element_type<T>;\n};\ntemplate <class T>\nstruct mapped_of<T,\n\
    \                 typename std::pair<int, typename T::mapped_type>::first_type>\
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
    \ 14 \"src/modular/modint.hpp\"\n\nnamespace workspace {\n\nnamespace _modint_impl\
    \ {\n\n/**\n * @brief Modular arithmetic.\n *\n * @tparam Mod identifier, which\
    \ represents modulus if positive\n * @tparam Storage Reserved size for inverse\
    \ calculation\n */\ntemplate <auto Mod, unsigned Storage> struct modint {\n  static_assert(is_integral_ext<decltype(Mod)>::value,\n\
    \                \"Mod must be integral type.\");\n\n  using mod_type = typename\
    \ std::make_signed<typename std::conditional<\n      0 < Mod, typename std::add_const<decltype(Mod)>::type,\n\
    \      decltype(Mod)>::type>::type;\n\n  using value_type = typename std::decay<mod_type>::type;\n\
    \n  using mul_type = typename multiplicable_uint<value_type>::type;\n\n  // Modulus\n\
    \  static mod_type mod;\n\n  static unsigned storage;\n\n  constexpr static void\
    \ reserve(unsigned __n) noexcept { storage = __n; }\n\n private:\n  value_type\
    \ value = 0;\n\n  struct direct_ctor_t {};\n  constexpr static direct_ctor_t direct_ctor_tag{};\n\
    \n  // Direct constructor\n  template <class _Tp> constexpr modint(_Tp __n, direct_ctor_t)\
    \ : value(__n) {}\n\n public:\n  constexpr modint() noexcept = default;\n\n  template\
    \ <class _Tp, typename std::enable_if<\n                           is_integral_ext<_Tp>::value>::type\
    \ * = nullptr>\n  constexpr modint(_Tp __n) noexcept\n      : value((__n %= mod)\
    \ < 0 ? __n += mod : __n) {}\n\n  constexpr modint(bool __n) noexcept : value(__n)\
    \ {}\n\n  constexpr operator value_type() const noexcept { return value; }\n\n\
    \  constexpr static modint one() noexcept { return 1; }\n\n  // unary operators\
    \ {{\n  constexpr modint operator++(int) noexcept {\n    modint __t{*this};\n\
    \    operator++();\n    return __t;\n  }\n\n  constexpr modint operator--(int)\
    \ noexcept {\n    modint __t{*this};\n    operator--();\n    return __t;\n  }\n\
    \n  constexpr modint &operator++() noexcept {\n    if (++value == mod) value =\
    \ 0;\n    return *this;\n  }\n\n  constexpr modint &operator--() noexcept {\n\
    \    if (!value)\n      value = mod - 1;\n    else\n      --value;\n    return\
    \ *this;\n  }\n\n  constexpr modint operator+() const noexcept { return *this;\
    \ }\n\n  constexpr modint operator-() const noexcept {\n    return {value ? mod\
    \ - value : 0, direct_ctor_tag};\n  }\n\n  // }} unary operators\n\n  // operator+=\
    \ {{\n\n  constexpr modint &operator+=(const modint &__x) noexcept {\n    if ((value\
    \ += __x.value) >= mod) value -= mod;\n    return *this;\n  }\n\n  template <class\
    \ _Tp>\n  constexpr typename std::enable_if<is_integral_ext<_Tp>::value, modint>::type\
    \ &\n  operator+=(_Tp const &__x) noexcept {\n    if (((value += __x) %= mod)\
    \ < 0) value += mod;\n    return *this;\n  }\n\n  // }} operator+=\n\n  // operator+\
    \ {{\n\n  template <class _Tp>\n  constexpr typename std::enable_if<is_integral_ext<_Tp>::value,\
    \ modint>::type\n  operator+(_Tp const &__x) const noexcept {\n    return modint{*this}\
    \ += __x;\n  }\n\n  constexpr modint operator+(modint __x) const noexcept { return\
    \ __x += *this; }\n\n  template <class _Tp>\n  constexpr friend\n      typename\
    \ std::enable_if<is_integral_ext<_Tp>::value, modint>::type\n      operator+(_Tp\
    \ const &__x, modint __y) noexcept {\n    return __y += __x;\n  }\n\n  // }} operator+\n\
    \n  // operator-= {{\n\n  constexpr modint &operator-=(const modint &__x) noexcept\
    \ {\n    if ((value -= __x.value) < 0) value += mod;\n    return *this;\n  }\n\
    \n  template <class _Tp>\n  constexpr typename std::enable_if<is_integral_ext<_Tp>::value,\
    \ modint>::type &\n  operator-=(_Tp __x) noexcept {\n    if (((value -= __x) %=\
    \ mod) < 0) value += mod;\n    return *this;\n  }\n\n  // }} operator-=\n\n  //\
    \ operator- {{\n\n  template <class _Tp>\n  constexpr typename std::enable_if<is_integral_ext<_Tp>::value,\
    \ modint>::type\n  operator-(_Tp const &__x) const noexcept {\n    return modint{*this}\
    \ -= __x;\n  }\n\n  constexpr modint operator-(const modint &__x) const noexcept\
    \ {\n    return modint{*this} -= __x;\n  }\n\n  template <class _Tp>\n  constexpr\
    \ friend\n      typename std::enable_if<is_integral_ext<_Tp>::value, modint>::type\n\
    \      operator-(_Tp __x, const modint &__y) noexcept {\n    if (((__x -= __y.value)\
    \ %= mod) < 0) __x += mod;\n    return {__x, direct_ctor_tag};\n  }\n\n  // }}\
    \ operator-\n\n  // operator*= {{\n\n  constexpr modint &operator*=(const modint\
    \ &__x) noexcept {\n    value =\n        static_cast<value_type>(value * static_cast<mul_type>(__x.value)\
    \ % mod);\n    return *this;\n  }\n\n  template <class _Tp>\n  constexpr typename\
    \ std::enable_if<is_integral_ext<_Tp>::value, modint>::type &\n  operator*=(_Tp\
    \ __x) noexcept {\n    value = static_cast<value_type>(\n        value * mul_type((__x\
    \ %= mod) < 0 ? __x + mod : __x) % mod);\n    return *this;\n  }\n\n  // }} operator*=\n\
    \n  // operator* {{\n\n  constexpr modint operator*(const modint &__x) const noexcept\
    \ {\n    return {static_cast<mul_type>(value) * __x.value % mod, direct_ctor_tag};\n\
    \  }\n\n  template <class _Tp>\n  constexpr typename std::enable_if<is_integral_ext<_Tp>::value,\
    \ modint>::type\n  operator*(_Tp __x) const noexcept {\n    __x %= mod;\n    if\
    \ (__x < 0) __x += mod;\n    return {static_cast<mul_type>(value) * __x % mod,\
    \ direct_ctor_tag};\n  }\n\n  template <class _Tp>\n  constexpr friend\n     \
    \ typename std::enable_if<is_integral_ext<_Tp>::value, modint>::type\n      operator*(_Tp\
    \ __x, const modint &__y) noexcept {\n    __x %= mod;\n    if (__x < 0) __x +=\
    \ mod;\n    return {static_cast<mul_type>(__x) * __y.value % mod, direct_ctor_tag};\n\
    \  }\n\n  // }} operator*\n\n protected:\n  static value_type _mem(value_type\
    \ __x) {\n    static std::vector<value_type> __m{0, 1};\n    static value_type\
    \ __i = (__m.reserve(Storage), 1);\n    while (__i < __x) {\n      ++__i;\n  \
    \    __m.emplace_back(mod - mul_type(mod / __i) * __m[mod % __i] % mod);\n   \
    \ }\n    return __m[__x];\n  }\n\n  template <class _Tp>\n  constexpr static\n\
    \      typename std::enable_if<is_integral_ext<_Tp>::value, value_type>::type\n\
    \      _div(mul_type __r, _Tp __x) noexcept {\n    assert(__x != _Tp(0));\n  \
    \  if (!__r) return 0;\n\n    std::make_signed_t<_Tp> __v{};\n    bool __neg =\
    \ __x < 0 ? __x = -__x, true : false;\n\n    if (static_cast<decltype(storage)>(__x)\
    \ < storage)\n      __v = _mem(__x);\n    else {\n      decltype(__v) __y{mod},\
    \ __u{1}, __t;\n\n      while (__x)\n        __t = __y / __x, __y ^= __x ^= (__y\
    \ -= __t * __x) ^= __x,\n        __v ^= __u ^= (__v -= __t * __u) ^= __u;\n\n\
    \      if (__y < 0) __neg ^= 1;\n    }\n\n    if (__neg)\n      __v = 0 < __v\
    \ ? mod - __v : -__v;\n    else if (__v < 0)\n      __v += mod;\n\n    return\
    \ __r == mul_type(1) ? static_cast<value_type>(__v)\n                        \
    \      : static_cast<value_type>(__r * __v % mod);\n  }\n\n public:\n  // operator/=\
    \ {{\n\n  constexpr modint &operator/=(const modint &__x) noexcept {\n    if (value)\
    \ value = _div(value, __x.value);\n    return *this;\n  }\n\n  template <class\
    \ _Tp>\n  constexpr typename std::enable_if<is_integral_ext<_Tp>::value, modint>::type\
    \ &\n  operator/=(_Tp __x) noexcept {\n    if (value) value = _div(value, __x\
    \ %= mod);\n    return *this;\n  }\n\n  // }} operator/=\n\n  // operator/ {{\n\
    \n  constexpr modint operator/(const modint &__x) const noexcept {\n    if (!value)\
    \ return {};\n    return {_div(value, __x.value), direct_ctor_tag};\n  }\n\n \
    \ template <class _Tp>\n  constexpr typename std::enable_if<is_integral_ext<_Tp>::value,\
    \ modint>::type\n  operator/(_Tp __x) const noexcept {\n    if (!value) return\
    \ {};\n    return {_div(value, __x %= mod), direct_ctor_tag};\n  }\n\n  template\
    \ <class _Tp>\n  constexpr friend\n      typename std::enable_if<is_integral_ext<_Tp>::value,\
    \ modint>::type\n      operator/(_Tp __x, const modint &__y) noexcept {\n    if\
    \ (!__x) return {};\n    if ((__x %= mod) < 0) __x += mod;\n    return {_div(__x,\
    \ __y.value), direct_ctor_tag};\n  }\n\n  // }} operator/\n\n  constexpr modint\
    \ inv() const noexcept { return _div(1, value); }\n\n  template <class _Tp>\n\
    \  friend constexpr\n      typename std::enable_if<is_integral_ext<_Tp>::value,\
    \ modint>::type\n      pow(modint __b, _Tp __e) noexcept {\n    if (__e < 0) {\n\
    \      __e = -__e;\n      __b.value = _div(1, __b.value);\n    }\n\n    modint\
    \ __r{1, direct_ctor_tag};\n\n    for (; __e; __e >>= 1, __b *= __b)\n      if\
    \ (__e & 1) __r *= __b;\n\n    return __r;\n  }\n\n  template <class _Tp>\n  constexpr\
    \ typename std::enable_if<is_integral_ext<_Tp>::value, modint>::type\n  pow(_Tp\
    \ __e) const noexcept {\n    modint __r{1, direct_ctor_tag};\n\n    for (modint\
    \ __b{__e < 0 ? __e = -__e, _div(1, value) : value,\n                        \
    \      direct_ctor_tag};\n         __e; __e >>= 1, __b *= __b)\n      if (__e\
    \ & 1) __r *= __b;\n\n    return __r;\n  }\n\n  template <class _Os>\n  friend\
    \ _Os &operator<<(_Os &__os, const modint &__x) noexcept {\n    return __os <<\
    \ __x.value;\n  }\n\n  friend std::istream &operator>>(std::istream &__is, modint\
    \ &__x) noexcept {\n    std::string __s;\n    __is >> __s;\n    bool __neg = false;\n\
    \    if (__s.front() == '-') {\n      __neg = true;\n      __s.erase(__s.begin());\n\
    \    }\n    __x = 0;\n    for (char __c : __s) __x = __x * 10 + (__c - '0');\n\
    \    if (__neg) __x = -__x;\n    return __is;\n  }\n};\n\ntemplate <auto Mod,\
    \ unsigned Storage>\ntypename modint<Mod, Storage>::mod_type modint<Mod, Storage>::mod\
    \ =\n    Mod > 0 ? Mod : 0;\n\ntemplate <auto Mod, unsigned Storage>\nunsigned\
    \ modint<Mod, Storage>::storage = Storage;\n\n}  // namespace _modint_impl\n\n\
    /**\n * @brief Modular arithmetic.\n *\n * @tparam Mod modulus\n * @tparam Storage\
    \ Reserved size for inverse calculation\n */\ntemplate <auto Mod, unsigned Storage\
    \ = 0,\n          typename std::enable_if<(Mod > 0)>::type * = nullptr>\nusing\
    \ modint = _modint_impl::modint<Mod, Storage>;\n\n/**\n * @brief Runtime modular\
    \ arithmetic.\n *\n * @tparam type_id uniquely assigned\n * @tparam Storage Reserved\
    \ size for inverse calculation\n */\ntemplate <unsigned type_id = 0, unsigned\
    \ Storage = 0>\nusing modint_runtime = _modint_impl::modint<-(signed)type_id,\
    \ Storage>;\n\n// #define modint_newtype modint_runtime<__COUNTER__>\n\n}  //\
    \ namespace workspace\n#line 2 \"src/combinatorics/factorial.hpp\"\n\n/**\n *\
    \ @file factorial.hpp\n * @brief Factorial\n * @date 2021-01-15\n *\n *\n */\n\
    \n#line 12 \"src/combinatorics/factorial.hpp\"\n\nnamespace workspace {\n\ntemplate\
    \ <class _Tp> _Tp factorial(int32_t __x) noexcept {\n  if (__x < 0) return 0;\n\
    \n  static std::vector<_Tp> __t{1};\n  static int32_t __i = (__t.reserve(0x1000000),\
    \ 0);\n\n  while (__i < __x) {\n    ++__i;\n    __t.emplace_back(__t.back() *\
    \ _Tp(__i));\n  }\n\n  return __t[__x];\n}\n\ntemplate <class _Tp> _Tp factorial_inverse(int32_t\
    \ __x) noexcept {\n  if (__x < 0) return 0;\n\n  static std::vector<_Tp> __t{1};\n\
    \  static int32_t __i = (__t.reserve(0x1000000), 0);\n\n  while (__i < __x) {\n\
    \    ++__i;\n    __t.emplace_back(__t.back() / _Tp(__i));\n  }\n\n  return __t[__x];\n\
    }\n\n}  // namespace workspace\n#line 13 \"src/combinatorics/binomial.hpp\"\n\n\
    namespace workspace {\n\n/**\n * @brief Binomial coefficient for integer args.\n\
    \ */\ntemplate <class Tp> Tp binomial(int_fast32_t __x, int_fast32_t __y) {\n\
    \  if (!__y) return 1;\n  if (__y < 0 || __x < __y) return 0;\n  return factorial<Tp>(__x)\
    \ * factorial_inverse<Tp>(__y) *\n         factorial_inverse<Tp>(__x - __y);\n\
    }\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file binomial.hpp\n * @brief Binomial Coefficient\n\
    \ * @date 2021-01-15\n *\n *\n */\n\n#include \"../modular/modint.hpp\"\n#include\
    \ \"factorial.hpp\"\n\nnamespace workspace {\n\n/**\n * @brief Binomial coefficient\
    \ for integer args.\n */\ntemplate <class Tp> Tp binomial(int_fast32_t __x, int_fast32_t\
    \ __y) {\n  if (!__y) return 1;\n  if (__y < 0 || __x < __y) return 0;\n  return\
    \ factorial<Tp>(__x) * factorial_inverse<Tp>(__y) *\n         factorial_inverse<Tp>(__x\
    \ - __y);\n}\n\n}  // namespace workspace\n"
  dependsOn:
  - src/modular/modint.hpp
  - src/utils/sfinae.hpp
  - src/combinatorics/factorial.hpp
  isVerificationFile: false
  path: src/combinatorics/binomial.hpp
  requiredBy: []
  timestamp: '2021-03-29 22:27:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aizu-online-judge/DPL_5_D.test.cpp
documentation_of: src/combinatorics/binomial.hpp
layout: document
redirect_from:
- /library/src/combinatorics/binomial.hpp
- /library/src/combinatorics/binomial.hpp.html
title: Binomial Coefficient
---
