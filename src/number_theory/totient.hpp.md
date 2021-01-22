---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/NTL_1_D.test.cpp
    title: test/aizu-online-judge/NTL_1_D.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Euler's Totient Function
    links: []
  bundledCode: "#line 1 \"src/number_theory/totient.hpp\"\n/**\n * @file totient.hpp\n\
    \ * @brief Euler's Totient Function\n * @date 2021-01-13\n */\n\n#include <cassert>\n\
    \n#line 2 \"src/utils/sfinae.hpp\"\n\n/**\n * @file sfinae.hpp\n * @brief SFINAE\n\
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
    \ 10 \"src/number_theory/totient.hpp\"\n\nnamespace workspace {\n\n/**\n * @brief\
    \ Euler's totient function.\n *\n * @tparam __mod Positive integer\n */\ntemplate\
    \ <class Tp>\nconstexpr typename std::enable_if<(is_integral_ext<Tp>::value),\
    \ Tp>::type\ntotient(const Tp __mod) noexcept {\n  assert(__mod > 0);\n  using\
    \ int_type = typename multiplicable_uint<Tp>::type;\n\n  int_type __r = __mod,\
    \ __p[16] = {}, *__q = __p;\n  for (int_type __i = 2; __i <= __r / __i; ++__i)\
    \ {\n    if (__r % __i) continue;\n    *__q++ = __i;\n    while (!(__r % __i))\
    \ __r /= __i;\n  }\n  if (__r != 1) *__q++ = __r;\n\n  int_type __tot = __mod;\n\
    \  for (__q = __p; *__q; *__q++ = 0) (__tot /= *__q) *= *__q - 1;\n\n  return\
    \ __tot;\n};\n\n}  // namespace workspace\n"
  code: "/**\n * @file totient.hpp\n * @brief Euler's Totient Function\n * @date 2021-01-13\n\
    \ */\n\n#include <cassert>\n\n#include \"src/utils/sfinae.hpp\"\n\nnamespace workspace\
    \ {\n\n/**\n * @brief Euler's totient function.\n *\n * @tparam __mod Positive\
    \ integer\n */\ntemplate <class Tp>\nconstexpr typename std::enable_if<(is_integral_ext<Tp>::value),\
    \ Tp>::type\ntotient(const Tp __mod) noexcept {\n  assert(__mod > 0);\n  using\
    \ int_type = typename multiplicable_uint<Tp>::type;\n\n  int_type __r = __mod,\
    \ __p[16] = {}, *__q = __p;\n  for (int_type __i = 2; __i <= __r / __i; ++__i)\
    \ {\n    if (__r % __i) continue;\n    *__q++ = __i;\n    while (!(__r % __i))\
    \ __r /= __i;\n  }\n  if (__r != 1) *__q++ = __r;\n\n  int_type __tot = __mod;\n\
    \  for (__q = __p; *__q; *__q++ = 0) (__tot /= *__q) *= *__q - 1;\n\n  return\
    \ __tot;\n};\n\n}  // namespace workspace\n"
  dependsOn:
  - src/utils/sfinae.hpp
  isVerificationFile: false
  path: src/number_theory/totient.hpp
  requiredBy: []
  timestamp: '2021-01-22 09:52:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aizu-online-judge/NTL_1_D.test.cpp
documentation_of: src/number_theory/totient.hpp
layout: document
redirect_from:
- /library/src/number_theory/totient.hpp
- /library/src/number_theory/totient.hpp.html
title: Euler's Totient Function
---
