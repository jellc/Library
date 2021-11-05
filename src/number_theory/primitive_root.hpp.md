---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: src/algebra/berlekamp_massey.hpp
    title: Berlekamp-Massey Algorithm
  - icon: ':heavy_check_mark:'
    path: src/algebra/ntt.hpp
    title: Number Theoretic Transform
  - icon: ':heavy_check_mark:'
    path: src/algebra/polynomial.hpp
    title: Polynomial
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/convolution_mod.test.cpp
    title: test/library-checker/convolution_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/division_of_polynomials.test.cpp
    title: test/library-checker/division_of_polynomials.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/find_linear_recurrence.test.cpp
    title: test/library-checker/find_linear_recurrence.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/multipoint_evaluation.test.cpp
    title: test/library-checker/multipoint_evaluation.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Primitive Root
    links: []
  bundledCode: "#line 2 \"src/number_theory/primitive_root.hpp\"\n\n/**\n * @file\
    \ primitive_root.hpp\n * @brief Primitive Root\n * @date 2020-12-28\n */\n\n#line\
    \ 2 \"src/utils/sfinae.hpp\"\n\n/**\n * @file sfinae.hpp\n * @brief SFINAE\n */\n\
    \n#include <cstdint>\n#include <iterator>\n#include <type_traits>\n\n#ifndef __INT128_DEFINED__\n\
    \n#ifdef __SIZEOF_INT128__\n#define __INT128_DEFINED__ 1\n#else\n#define __INT128_DEFINED__\
    \ 0\n#endif\n\n#endif\n\nnamespace std {\n\n#if __INT128_DEFINED__\n\ntemplate\
    \ <> struct make_signed<__uint128_t> { using type = __int128_t; };\ntemplate <>\
    \ struct make_signed<__int128_t> { using type = __int128_t; };\n\ntemplate <>\
    \ struct make_unsigned<__uint128_t> { using type = __uint128_t; };\ntemplate <>\
    \ struct make_unsigned<__int128_t> { using type = __uint128_t; };\n\ntemplate\
    \ <> struct is_signed<__uint128_t> : std::false_type {};\ntemplate <> struct is_signed<__int128_t>\
    \ : std::true_type {};\n\ntemplate <> struct is_unsigned<__uint128_t> : std::true_type\
    \ {};\ntemplate <> struct is_unsigned<__int128_t> : std::false_type {};\n\n#endif\n\
    \n}  // namespace std\n\nnamespace workspace {\n\ntemplate <class Tp, class...\
    \ Args> struct variadic_front { using type = Tp; };\n\ntemplate <class... Args>\
    \ struct variadic_back;\n\ntemplate <class Tp> struct variadic_back<Tp> { using\
    \ type = Tp; };\n\ntemplate <class Tp, class... Args> struct variadic_back<Tp,\
    \ Args...> {\n  using type = typename variadic_back<Args...>::type;\n};\n\ntemplate\
    \ <class type, template <class> class trait>\nusing enable_if_trait_type = typename\
    \ std::enable_if<trait<type>::value>::type;\n\n/**\n * @brief Return type of subscripting\
    \ ( @c [] ) access.\n */\ntemplate <class _Tp>\nusing subscripted_type =\n   \
    \ typename std::decay<decltype(std::declval<_Tp&>()[0])>::type;\n\ntemplate <class\
    \ Container>\nusing element_type = typename std::decay<decltype(\n    *std::begin(std::declval<Container&>()))>::type;\n\
    \ntemplate <class _Tp, class = std::nullptr_t>\nstruct has_begin : std::false_type\
    \ {};\n\ntemplate <class _Tp>\nstruct has_begin<_Tp, decltype(std::begin(std::declval<_Tp>()),\
    \ nullptr)>\n    : std::true_type {};\n\ntemplate <class _Tp, class = void> struct\
    \ has_mod : std::false_type {};\n\ntemplate <class _Tp>\nstruct has_mod<_Tp, std::__void_t<decltype(_Tp::mod)>>\
    \ : std::true_type {};\n\ntemplate <class _Tp, class = void> struct is_integral_ext\
    \ : std::false_type {};\ntemplate <class _Tp>\nstruct is_integral_ext<\n    _Tp,\
    \ typename std::enable_if<std::is_integral<_Tp>::value>::type>\n    : std::true_type\
    \ {};\n\n#if __INT128_DEFINED__\n\ntemplate <> struct is_integral_ext<__int128_t>\
    \ : std::true_type {};\ntemplate <> struct is_integral_ext<__uint128_t> : std::true_type\
    \ {};\n\n#endif\n\n#if __cplusplus >= 201402\n\ntemplate <class _Tp>\nconstexpr\
    \ static bool is_integral_ext_v = is_integral_ext<_Tp>::value;\n\n#endif\n\ntemplate\
    \ <typename _Tp, typename = void> struct multiplicable_uint {\n  using type =\
    \ uint_least32_t;\n};\ntemplate <typename _Tp>\nstruct multiplicable_uint<\n \
    \   _Tp,\n    typename std::enable_if<(2 < sizeof(_Tp)) &&\n                 \
    \           (!__INT128_DEFINED__ || sizeof(_Tp) <= 4)>::type> {\n  using type\
    \ = uint_least64_t;\n};\n\n#if __INT128_DEFINED__\n\ntemplate <typename _Tp>\n\
    struct multiplicable_uint<_Tp,\n                          typename std::enable_if<(4\
    \ < sizeof(_Tp))>::type> {\n  using type = __uint128_t;\n};\n\n#endif\n\ntemplate\
    \ <typename _Tp> struct multiplicable_int {\n  using type =\n      typename std::make_signed<typename\
    \ multiplicable_uint<_Tp>::type>::type;\n};\n\ntemplate <typename _Tp> struct\
    \ multiplicable {\n  using type = std::conditional_t<\n      is_integral_ext<_Tp>::value,\n\
    \      std::conditional_t<std::is_signed<_Tp>::value,\n                      \
    \   typename multiplicable_int<_Tp>::type,\n                         typename\
    \ multiplicable_uint<_Tp>::type>,\n      _Tp>;\n};\n\ntemplate <class> struct\
    \ first_arg { using type = void; };\n\ntemplate <class _R, class _Tp, class...\
    \ _Args>\nstruct first_arg<_R(_Tp, _Args...)> {\n  using type = _Tp;\n};\n\ntemplate\
    \ <class _R, class _Tp, class... _Args>\nstruct first_arg<_R (*)(_Tp, _Args...)>\
    \ {\n  using type = _Tp;\n};\n\ntemplate <class _G, class _R, class _Tp, class...\
    \ _Args>\nstruct first_arg<_R (_G::*)(_Tp, _Args...)> {\n  using type = _Tp;\n\
    };\n\ntemplate <class _G, class _R, class _Tp, class... _Args>\nstruct first_arg<_R\
    \ (_G::*)(_Tp, _Args...) const> {\n  using type = _Tp;\n};\n\ntemplate <class\
    \ _Tp, class = void> struct parse_compare : first_arg<_Tp> {};\n\ntemplate <class\
    \ _Tp>\nstruct parse_compare<_Tp, std::__void_t<decltype(&_Tp::operator())>>\n\
    \    : first_arg<decltype(&_Tp::operator())> {};\n\n}  // namespace workspace\n\
    #line 10 \"src/number_theory/primitive_root.hpp\"\n\nnamespace workspace {\n\n\
    /**\n * @brief Compile time primitive root.\n *\n * @tparam __mod Positive integer\n\
    \ * @return Minimum positive one if it exists. Otherwise 0.\n */\ntemplate <class\
    \ Tp>\nconstexpr typename std::enable_if<(is_integral_ext<Tp>::value), Tp>::type\n\
    primitive_root(const Tp __mod) noexcept {\n  assert(__mod > 0);\n  using int_type\
    \ = typename multiplicable_uint<Tp>::type;\n\n  int_type __r = __mod, __p[16]\
    \ = {}, *__q = __p;\n  for (int_type __i = 2; __i <= __r / __i; ++__i) {\n   \
    \ if (__r % __i) continue;\n    *__q++ = __i;\n    while (!(__r % __i)) __r /=\
    \ __i;\n  }\n  if (__r != 1) *__q++ = __r;\n\n  int_type __tot = __mod;\n  for\
    \ (__q = __p; *__q; *__q++ = 0) (__tot /= *__q) *= *__q - 1;\n  __r = __tot, __q\
    \ = __p + 1, __p[0] = 1;\n  for (int_type __i = 2; __i <= __r / __i; ++__i) {\n\
    \    if (__r % __i) continue;\n    *__q++ = __i;\n    while (!(__r % __i)) __r\
    \ /= __i;\n  }\n  if (__r != 1) *__q++ = __r;\n\n  for (Tp __r = 1; __r != __mod;\
    \ ++__r) {\n    auto __cnt = 0;\n    for (__q = __p; *__q; ++__q) {\n      int_type\
    \ __w = 1;\n      for (int_type __e = __tot / *__q, __x = __r; __e;\n        \
    \   __e >>= 1, (__x *= __x) %= __mod)\n        if (__e & 1) (__w *= __x) %= __mod;\n\
    \      if (__w == 1 && ++__cnt > 1) break;\n    }\n    if (__cnt == 1) return\
    \ __r;\n  }\n\n  return 0;\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file primitive_root.hpp\n * @brief Primitive Root\n\
    \ * @date 2020-12-28\n */\n\n#include \"src/utils/sfinae.hpp\"\n\nnamespace workspace\
    \ {\n\n/**\n * @brief Compile time primitive root.\n *\n * @tparam __mod Positive\
    \ integer\n * @return Minimum positive one if it exists. Otherwise 0.\n */\ntemplate\
    \ <class Tp>\nconstexpr typename std::enable_if<(is_integral_ext<Tp>::value),\
    \ Tp>::type\nprimitive_root(const Tp __mod) noexcept {\n  assert(__mod > 0);\n\
    \  using int_type = typename multiplicable_uint<Tp>::type;\n\n  int_type __r =\
    \ __mod, __p[16] = {}, *__q = __p;\n  for (int_type __i = 2; __i <= __r / __i;\
    \ ++__i) {\n    if (__r % __i) continue;\n    *__q++ = __i;\n    while (!(__r\
    \ % __i)) __r /= __i;\n  }\n  if (__r != 1) *__q++ = __r;\n\n  int_type __tot\
    \ = __mod;\n  for (__q = __p; *__q; *__q++ = 0) (__tot /= *__q) *= *__q - 1;\n\
    \  __r = __tot, __q = __p + 1, __p[0] = 1;\n  for (int_type __i = 2; __i <= __r\
    \ / __i; ++__i) {\n    if (__r % __i) continue;\n    *__q++ = __i;\n    while\
    \ (!(__r % __i)) __r /= __i;\n  }\n  if (__r != 1) *__q++ = __r;\n\n  for (Tp\
    \ __r = 1; __r != __mod; ++__r) {\n    auto __cnt = 0;\n    for (__q = __p; *__q;\
    \ ++__q) {\n      int_type __w = 1;\n      for (int_type __e = __tot / *__q, __x\
    \ = __r; __e;\n           __e >>= 1, (__x *= __x) %= __mod)\n        if (__e &\
    \ 1) (__w *= __x) %= __mod;\n      if (__w == 1 && ++__cnt > 1) break;\n    }\n\
    \    if (__cnt == 1) return __r;\n  }\n\n  return 0;\n};\n\n}  // namespace workspace\n"
  dependsOn:
  - src/utils/sfinae.hpp
  isVerificationFile: false
  path: src/number_theory/primitive_root.hpp
  requiredBy:
  - src/algebra/ntt.hpp
  - src/algebra/polynomial.hpp
  - src/algebra/berlekamp_massey.hpp
  timestamp: '2021-05-25 17:32:10+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/convolution_mod.test.cpp
  - test/library-checker/division_of_polynomials.test.cpp
  - test/library-checker/multipoint_evaluation.test.cpp
  - test/library-checker/find_linear_recurrence.test.cpp
documentation_of: src/number_theory/primitive_root.hpp
layout: document
redirect_from:
- /library/src/number_theory/primitive_root.hpp
- /library/src/number_theory/primitive_root.hpp.html
title: Primitive Root
---
