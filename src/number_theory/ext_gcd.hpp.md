---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy:
  - icon: ':warning:'
    path: src/number_theory/order.hpp
    title: Order
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/aizu-online-judge/NTL_1_E.test.cpp
    title: test/aizu-online-judge/NTL_1_E.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: Extended Euclidean Algorithm
    links: []
  bundledCode: "#line 2 \"src/number_theory/ext_gcd.hpp\"\n\n/**\n * @file ext_gcd.hpp\n\
    \ * @brief Extended Euclidean Algorithm\n */\n\n#include <tuple>\n\n#line 2 \"\
    src/utils/sfinae.hpp\"\n\n/**\n * @file sfinae.hpp\n * @brief SFINAE\n */\n\n\
    #include <cstdint>\n#include <iterator>\n#include <type_traits>\n\n#ifndef __INT128_DEFINED__\n\
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
    \ 11 \"src/number_theory/ext_gcd.hpp\"\n\nnamespace workspace {\n\n/**\n * @param\
    \ __a Integer\n * @param __b Integer\n * @return Pair of integers (x, y) s.t.\
    \ ax + by = g = gcd(a, b), 0 <= x <\n * |b/g|, -|a/g| < y <= 0. Return (0, 0)\
    \ if (a, b) = (0, 0).\n */\ntemplate <typename _T1, typename _T2> constexpr auto\
    \ ext_gcd(_T1 __a, _T2 __b) {\n  static_assert(is_integral_ext<_T1>::value);\n\
    \  static_assert(is_integral_ext<_T2>::value);\n\n  using result_type = typename\
    \ std::make_signed<\n      typename std::common_type<_T1, _T2>::type>::type;\n\
    \n  result_type a{__a}, b{__b}, p{1}, q{}, r{}, s{1};\n\n  // Euclidean algorithm\n\
    \  while (b) {\n    result_type t = a / b;\n    r ^= p ^= r ^= p -= t * r;\n \
    \   s ^= q ^= s ^= q -= t * s;\n    b ^= a ^= b ^= a -= t * b;\n  }\n\n  // Normalize\n\
    \  if (a < 0) p = -p, q = -q;\n  if (p < 0) p += __b / a, q -= __a / a;\n\n  return\
    \ std::make_pair(p, q);\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file ext_gcd.hpp\n * @brief Extended Euclidean Algorithm\n\
    \ */\n\n#include <tuple>\n\n#include \"src/utils/sfinae.hpp\"\n\nnamespace workspace\
    \ {\n\n/**\n * @param __a Integer\n * @param __b Integer\n * @return Pair of integers\
    \ (x, y) s.t. ax + by = g = gcd(a, b), 0 <= x <\n * |b/g|, -|a/g| < y <= 0. Return\
    \ (0, 0) if (a, b) = (0, 0).\n */\ntemplate <typename _T1, typename _T2> constexpr\
    \ auto ext_gcd(_T1 __a, _T2 __b) {\n  static_assert(is_integral_ext<_T1>::value);\n\
    \  static_assert(is_integral_ext<_T2>::value);\n\n  using result_type = typename\
    \ std::make_signed<\n      typename std::common_type<_T1, _T2>::type>::type;\n\
    \n  result_type a{__a}, b{__b}, p{1}, q{}, r{}, s{1};\n\n  // Euclidean algorithm\n\
    \  while (b) {\n    result_type t = a / b;\n    r ^= p ^= r ^= p -= t * r;\n \
    \   s ^= q ^= s ^= q -= t * s;\n    b ^= a ^= b ^= a -= t * b;\n  }\n\n  // Normalize\n\
    \  if (a < 0) p = -p, q = -q;\n  if (p < 0) p += __b / a, q -= __a / a;\n\n  return\
    \ std::make_pair(p, q);\n}\n\n}  // namespace workspace\n"
  dependsOn:
  - src/utils/sfinae.hpp
  isVerificationFile: false
  path: src/number_theory/ext_gcd.hpp
  requiredBy:
  - src/number_theory/order.hpp
  timestamp: '2021-02-20 12:57:04+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/aizu-online-judge/NTL_1_E.test.cpp
documentation_of: src/number_theory/ext_gcd.hpp
layout: document
redirect_from:
- /library/src/number_theory/ext_gcd.hpp
- /library/src/number_theory/ext_gcd.hpp.html
title: Extended Euclidean Algorithm
---
