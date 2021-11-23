---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: src/algebra/rational.hpp
    title: Rational
  - icon: ':heavy_check_mark:'
    path: src/data_structure/segment_tree/lazy.hpp
    title: Lazy Segment Tree
  - icon: ':warning:'
    path: src/opt/golden_section.hpp
    title: Golden Section
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/2450.test.cpp
    title: test/aizu-online-judge/2450.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/range_affine_range_sum.test.cpp
    title: test/library-checker/range_affine_range_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Operation Traits
    links: []
  bundledCode: "#line 2 \"src/algebra/system/operation.hpp\"\n\n/**\n * @file operation.hpp\n\
    \ * @brief Operation Traits\n */\n\n#include <type_traits>\n\n#line 2 \"lib/cxx17\"\
    \n\n#line 2 \"lib/cxx14\"\n\n#ifndef _CXX14_CONSTEXPR\n#if __cplusplus >= 201402L\n\
    #define _CXX14_CONSTEXPR constexpr\n#else\n#define _CXX14_CONSTEXPR\n#endif\n\
    #endif\n#line 4 \"lib/cxx17\"\n\n#ifndef _CXX17_CONSTEXPR\n#if __cplusplus >=\
    \ 201703L\n#define _CXX17_CONSTEXPR constexpr\n#else\n#define _CXX17_CONSTEXPR\n\
    #endif\n#endif\n\n#ifndef _CXX17_STATIC_ASSERT\n#if __cplusplus >= 201703L\n#define\
    \ _CXX17_STATIC_ASSERT static_assert\n#else\n#define _CXX17_STATIC_ASSERT assert\n\
    #endif\n#endif\n\n#include <iterator>\n\n#if __cplusplus < 201703L\n\nnamespace\
    \ std {\n\n/**\n *  @brief  Return the size of a container.\n *  @param  __cont\
    \  Container.\n */\ntemplate <typename _Container>\nconstexpr auto size(const\
    \ _Container& __cont) noexcept(noexcept(__cont.size()))\n    -> decltype(__cont.size())\
    \ {\n  return __cont.size();\n}\n\n/**\n *  @brief  Return the size of an array.\n\
    \ */\ntemplate <typename _Tp, size_t _Nm>\nconstexpr size_t size(const _Tp (&)[_Nm])\
    \ noexcept {\n  return _Nm;\n}\n\nstruct monostate {};\n\n}  // namespace std\n\
    \n#else\n\n#include <variant>\n\n#endif\n#line 11 \"src/algebra/system/operation.hpp\"\
    \n\nnamespace workspace {\n\n// Unary `+`\ntemplate <class _Tp>\nusing require_unary_plus\
    \ = std::enable_if_t<\n    std::is_convertible<decltype(+std::declval<const _Tp\
    \ &>()), _Tp>::value>;\n\ntemplate <class _Tp, class = void> struct has_unary_plus\
    \ : std::false_type {};\n\ntemplate <class _Tp>\nstruct has_unary_plus<_Tp, require_unary_plus<_Tp>>\
    \ : std::true_type {};\n\n// Unary `-`\ntemplate <class _Tp>\nusing require_unary_minus\
    \ = std::enable_if_t<\n    std::is_convertible<decltype(-std::declval<const _Tp\
    \ &>()), _Tp>::value>;\n\ntemplate <class _Tp, class = void> struct has_unary_minus\
    \ : std::false_type {};\n\ntemplate <class _Tp>\nstruct has_unary_minus<_Tp, require_unary_minus<_Tp>>\
    \ : std::true_type {};\n\n// Binary `+`\ntemplate <class _Tp1, class _Tp2 = _Tp1>\n\
    using require_binary_plus =\n    std::enable_if_t<std::is_convertible<decltype(std::declval<const\
    \ _Tp1 &>() +\n                                                  std::declval<const\
    \ _Tp2 &>()),\n                                         _Tp1>::value>;\n\ntemplate\
    \ <class _Tp1, class _Tp2 = _Tp1, class = void>\nstruct has_binary_plus : std::false_type\
    \ {};\n\ntemplate <class _Tp1, class _Tp2>\nstruct has_binary_plus<_Tp1, _Tp2,\
    \ require_binary_plus<_Tp1, _Tp2>>\n    : std::true_type {};\n\n// Binary `-`\n\
    template <class _Tp1, class _Tp2 = _Tp1>\nusing require_binary_minus =\n    std::__void_t<decltype(std::declval<const\
    \ _Tp1 &>() -\n                           std::declval<const _Tp2 &>())>;\n\n\
    template <class _Tp1, class _Tp2 = _Tp1, class = void>\nstruct has_binary_minus\
    \ : std::false_type {};\n\ntemplate <class _Tp1, class _Tp2>\nstruct has_binary_minus<_Tp1,\
    \ _Tp2, require_binary_minus<_Tp1, _Tp2>>\n    : std::true_type {};\n\n// Binary\
    \ `*`\ntemplate <class _Tp1, class _Tp2 = _Tp1>\nusing require_binary_multiplies\
    \ =\n    std::enable_if_t<std::is_convertible<decltype(std::declval<const _Tp1\
    \ &>() *\n                                                  std::declval<const\
    \ _Tp2 &>()),\n                                         _Tp1>::value>;\n\ntemplate\
    \ <class _Tp1, class _Tp2 = _Tp1, class = void>\nstruct has_binary_multiplies\
    \ : std::false_type {};\n\ntemplate <class _Tp1, class _Tp2>\nstruct has_binary_multiplies<_Tp1,\
    \ _Tp2, require_binary_multiplies<_Tp1, _Tp2>>\n    : std::true_type {};\n\n//\
    \ Binary `/`\ntemplate <class _Tp1, class _Tp2 = _Tp1>\nusing require_binary_divides\
    \ =\n    std::enable_if_t<std::is_convertible<decltype(std::declval<const _Tp1\
    \ &>() /\n                                                  std::declval<const\
    \ _Tp2 &>()),\n                                         _Tp1>::value>;\n\ntemplate\
    \ <class _Tp1, class _Tp2 = _Tp1, class = void>\nstruct has_binary_divides : std::false_type\
    \ {};\n\ntemplate <class _Tp1, class _Tp2>\nstruct has_binary_divides<_Tp1, _Tp2,\
    \ require_binary_divides<_Tp1, _Tp2>>\n    : std::true_type {};\n\n// Binary `%`\n\
    template <class _Tp1, class _Tp2 = _Tp1>\nusing require_binary_modulus =\n   \
    \ std::enable_if_t<std::is_convertible<decltype(std::declval<const _Tp1 &>() %\n\
    \                                                  std::declval<const _Tp2 &>()),\n\
    \                                         _Tp1>::value>;\n\ntemplate <class _Tp1,\
    \ class _Tp2 = _Tp1, class = void>\nstruct has_binary_modulus : std::false_type\
    \ {};\n\ntemplate <class _Tp1, class _Tp2>\nstruct has_binary_modulus<_Tp1, _Tp2,\
    \ require_binary_modulus<_Tp1, _Tp2>>\n    : std::true_type {};\n\ntemplate <class\
    \ _Tp1, class _Tp2 = _Tp1, class = void, class = void,\n          class = void,\
    \ class = void>\nstruct has_arithmetic : std::false_type {};\n\ntemplate <class\
    \ _Tp1, class _Tp2>\nstruct has_arithmetic<_Tp1, _Tp2, require_binary_plus<_Tp1,\
    \ _Tp2>,\n                      require_binary_minus<_Tp1, _Tp2>,\n          \
    \            require_binary_multiplies<_Tp1, _Tp2>,\n                      require_binary_divides<_Tp1,\
    \ _Tp2>> : std::true_type {};\n\ntemplate <class _Tp1, class _Tp2 = _Tp1>\nusing\
    \ require_arithmetic = std::enable_if_t<has_arithmetic<_Tp1, _Tp2>::value>;\n\n\
    // Binary `<`\ntemplate <class _Tp, class = void> struct is_comparable : std::false_type\
    \ {};\n\ntemplate <class _Tp>\nstruct is_comparable<_Tp, std::__void_t<decltype(std::declval<const\
    \ _Tp &>() <\n                                                 std::declval<const\
    \ _Tp &>())>>\n    : std::true_type {};\n\ntemplate <class _Tp, bool _Default\
    \ = false> struct try_less : std::less<_Tp> {\n  constexpr bool operator()(const\
    \ _Tp &__x, const _Tp &__y) noexcept {\n    if _CXX17_CONSTEXPR (is_comparable<_Tp>::value)\n\
    \      return std::less<_Tp>::operator()(__x, __y);\n    else\n      return _Default;\n\
    \  }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file operation.hpp\n * @brief Operation Traits\n\
    \ */\n\n#include <type_traits>\n\n#include \"lib/cxx17\"\n\nnamespace workspace\
    \ {\n\n// Unary `+`\ntemplate <class _Tp>\nusing require_unary_plus = std::enable_if_t<\n\
    \    std::is_convertible<decltype(+std::declval<const _Tp &>()), _Tp>::value>;\n\
    \ntemplate <class _Tp, class = void> struct has_unary_plus : std::false_type {};\n\
    \ntemplate <class _Tp>\nstruct has_unary_plus<_Tp, require_unary_plus<_Tp>> :\
    \ std::true_type {};\n\n// Unary `-`\ntemplate <class _Tp>\nusing require_unary_minus\
    \ = std::enable_if_t<\n    std::is_convertible<decltype(-std::declval<const _Tp\
    \ &>()), _Tp>::value>;\n\ntemplate <class _Tp, class = void> struct has_unary_minus\
    \ : std::false_type {};\n\ntemplate <class _Tp>\nstruct has_unary_minus<_Tp, require_unary_minus<_Tp>>\
    \ : std::true_type {};\n\n// Binary `+`\ntemplate <class _Tp1, class _Tp2 = _Tp1>\n\
    using require_binary_plus =\n    std::enable_if_t<std::is_convertible<decltype(std::declval<const\
    \ _Tp1 &>() +\n                                                  std::declval<const\
    \ _Tp2 &>()),\n                                         _Tp1>::value>;\n\ntemplate\
    \ <class _Tp1, class _Tp2 = _Tp1, class = void>\nstruct has_binary_plus : std::false_type\
    \ {};\n\ntemplate <class _Tp1, class _Tp2>\nstruct has_binary_plus<_Tp1, _Tp2,\
    \ require_binary_plus<_Tp1, _Tp2>>\n    : std::true_type {};\n\n// Binary `-`\n\
    template <class _Tp1, class _Tp2 = _Tp1>\nusing require_binary_minus =\n    std::__void_t<decltype(std::declval<const\
    \ _Tp1 &>() -\n                           std::declval<const _Tp2 &>())>;\n\n\
    template <class _Tp1, class _Tp2 = _Tp1, class = void>\nstruct has_binary_minus\
    \ : std::false_type {};\n\ntemplate <class _Tp1, class _Tp2>\nstruct has_binary_minus<_Tp1,\
    \ _Tp2, require_binary_minus<_Tp1, _Tp2>>\n    : std::true_type {};\n\n// Binary\
    \ `*`\ntemplate <class _Tp1, class _Tp2 = _Tp1>\nusing require_binary_multiplies\
    \ =\n    std::enable_if_t<std::is_convertible<decltype(std::declval<const _Tp1\
    \ &>() *\n                                                  std::declval<const\
    \ _Tp2 &>()),\n                                         _Tp1>::value>;\n\ntemplate\
    \ <class _Tp1, class _Tp2 = _Tp1, class = void>\nstruct has_binary_multiplies\
    \ : std::false_type {};\n\ntemplate <class _Tp1, class _Tp2>\nstruct has_binary_multiplies<_Tp1,\
    \ _Tp2, require_binary_multiplies<_Tp1, _Tp2>>\n    : std::true_type {};\n\n//\
    \ Binary `/`\ntemplate <class _Tp1, class _Tp2 = _Tp1>\nusing require_binary_divides\
    \ =\n    std::enable_if_t<std::is_convertible<decltype(std::declval<const _Tp1\
    \ &>() /\n                                                  std::declval<const\
    \ _Tp2 &>()),\n                                         _Tp1>::value>;\n\ntemplate\
    \ <class _Tp1, class _Tp2 = _Tp1, class = void>\nstruct has_binary_divides : std::false_type\
    \ {};\n\ntemplate <class _Tp1, class _Tp2>\nstruct has_binary_divides<_Tp1, _Tp2,\
    \ require_binary_divides<_Tp1, _Tp2>>\n    : std::true_type {};\n\n// Binary `%`\n\
    template <class _Tp1, class _Tp2 = _Tp1>\nusing require_binary_modulus =\n   \
    \ std::enable_if_t<std::is_convertible<decltype(std::declval<const _Tp1 &>() %\n\
    \                                                  std::declval<const _Tp2 &>()),\n\
    \                                         _Tp1>::value>;\n\ntemplate <class _Tp1,\
    \ class _Tp2 = _Tp1, class = void>\nstruct has_binary_modulus : std::false_type\
    \ {};\n\ntemplate <class _Tp1, class _Tp2>\nstruct has_binary_modulus<_Tp1, _Tp2,\
    \ require_binary_modulus<_Tp1, _Tp2>>\n    : std::true_type {};\n\ntemplate <class\
    \ _Tp1, class _Tp2 = _Tp1, class = void, class = void,\n          class = void,\
    \ class = void>\nstruct has_arithmetic : std::false_type {};\n\ntemplate <class\
    \ _Tp1, class _Tp2>\nstruct has_arithmetic<_Tp1, _Tp2, require_binary_plus<_Tp1,\
    \ _Tp2>,\n                      require_binary_minus<_Tp1, _Tp2>,\n          \
    \            require_binary_multiplies<_Tp1, _Tp2>,\n                      require_binary_divides<_Tp1,\
    \ _Tp2>> : std::true_type {};\n\ntemplate <class _Tp1, class _Tp2 = _Tp1>\nusing\
    \ require_arithmetic = std::enable_if_t<has_arithmetic<_Tp1, _Tp2>::value>;\n\n\
    // Binary `<`\ntemplate <class _Tp, class = void> struct is_comparable : std::false_type\
    \ {};\n\ntemplate <class _Tp>\nstruct is_comparable<_Tp, std::__void_t<decltype(std::declval<const\
    \ _Tp &>() <\n                                                 std::declval<const\
    \ _Tp &>())>>\n    : std::true_type {};\n\ntemplate <class _Tp, bool _Default\
    \ = false> struct try_less : std::less<_Tp> {\n  constexpr bool operator()(const\
    \ _Tp &__x, const _Tp &__y) noexcept {\n    if _CXX17_CONSTEXPR (is_comparable<_Tp>::value)\n\
    \      return std::less<_Tp>::operator()(__x, __y);\n    else\n      return _Default;\n\
    \  }\n};\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/algebra/system/operation.hpp
  requiredBy:
  - src/opt/golden_section.hpp
  - src/algebra/rational.hpp
  - src/data_structure/segment_tree/lazy.hpp
  timestamp: '2021-08-27 14:11:15+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/range_affine_range_sum.test.cpp
  - test/aizu-online-judge/2450.test.cpp
documentation_of: src/algebra/system/operation.hpp
layout: document
redirect_from:
- /library/src/algebra/system/operation.hpp
- /library/src/algebra/system/operation.hpp.html
title: Operation Traits
---
