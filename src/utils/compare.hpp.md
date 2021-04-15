---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/sort_points_by_argument.test.cpp
    title: test/library-checker/sort_points_by_argument.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Compare
    links: []
  bundledCode: "#line 1 \"src/utils/compare.hpp\"\n/**\n * @file compare.hpp\n * @brief\
    \ Compare\n */\n\n#line 2 \"src/utils/sfinae.hpp\"\n\n/**\n * @file sfinae.hpp\n\
    \ * @brief SFINAE\n */\n\n#include <cstdint>\n#include <iterator>\n#include <type_traits>\n\
    \n#ifndef __INT128_DEFINED__\n\n#ifdef __SIZEOF_INT128__\n#define __INT128_DEFINED__\
    \ 1\n#else\n#define __INT128_DEFINED__ 0\n#endif\n\n#endif\n\nnamespace std {\n\
    \n#if __INT128_DEFINED__\n\ntemplate <> struct make_signed<__uint128_t> { using\
    \ type = __int128_t; };\ntemplate <> struct make_signed<__int128_t> { using type\
    \ = __int128_t; };\n\ntemplate <> struct make_unsigned<__uint128_t> { using type\
    \ = __uint128_t; };\ntemplate <> struct make_unsigned<__int128_t> { using type\
    \ = __uint128_t; };\n\ntemplate <> struct is_signed<__uint128_t> : std::false_type\
    \ {};\ntemplate <> struct is_signed<__int128_t> : std::true_type {};\n\ntemplate\
    \ <> struct is_unsigned<__uint128_t> : std::true_type {};\ntemplate <> struct\
    \ is_unsigned<__int128_t> : std::false_type {};\n\n#endif\n\n}  // namespace std\n\
    \nnamespace workspace {\n\ntemplate <class Tp, class... Args> struct variadic_front\
    \ { using type = Tp; };\n\ntemplate <class... Args> struct variadic_back;\n\n\
    template <class Tp> struct variadic_back<Tp> { using type = Tp; };\n\ntemplate\
    \ <class Tp, class... Args> struct variadic_back<Tp, Args...> {\n  using type\
    \ = typename variadic_back<Args...>::type;\n};\n\ntemplate <class type, template\
    \ <class> class trait>\nusing enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
    \n/**\n * @brief Return type of subscripting ( @c [] ) access.\n */\ntemplate\
    \ <class _Tp>\nusing subscripted_type =\n    typename std::decay<decltype(std::declval<_Tp&>()[0])>::type;\n\
    \ntemplate <class Container>\nusing element_type = typename std::decay<decltype(\n\
    \    *std::begin(std::declval<Container&>()))>::type;\n\ntemplate <class _Tp,\
    \ class = std::nullptr_t>\nstruct has_begin : std::false_type {};\n\ntemplate\
    \ <class _Tp>\nstruct has_begin<_Tp, decltype(std::begin(std::declval<_Tp>()),\
    \ nullptr)>\n    : std::true_type {};\n\ntemplate <class _Tp, class = std::nullptr_t>\n\
    struct has_mod : std::false_type {};\n\ntemplate <class _Tp>\nstruct has_mod<_Tp,\
    \ decltype(_Tp::mod, nullptr)> : std::true_type {};\n\ntemplate <class _Tp, class\
    \ = void> struct is_integral_ext : std::false_type {};\ntemplate <class _Tp>\n\
    struct is_integral_ext<\n    _Tp, typename std::enable_if<std::is_integral<_Tp>::value>::type>\n\
    \    : std::true_type {};\n\n#if __INT128_DEFINED__\n\ntemplate <> struct is_integral_ext<__int128_t>\
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
    \ multiplicable_uint<_Tp>::type>,\n      _Tp>;\n};\n\n}  // namespace workspace\n\
    #line 7 \"src/utils/compare.hpp\"\n\nnamespace workspace {\n\n/**\n * @brief Compare\
    \ 2 points by their value of `atan2`.\n *\n * @return\n */\ntemplate <class _Tp>\n\
    bool compare_arg(const _Tp& __p1, const _Tp& __p2) noexcept {\n  const auto& [__x1,\
    \ __y1] = __p1;\n  const auto& [__x2, __y2] = __p2;\n\n  using value_type = std::decay_t<decltype(__x1)>;\n\
    \  using mul_type = typename multiplicable<value_type>::type;\n\n  if (__y1 ==\
    \ value_type(0))\n    return value_type(0) <= __x1 &&\n           (value_type(0)\
    \ < __y2 ||\n            (__y2 == value_type(0) && __x2 < value_type(0)));\n\n\
    \  return value_type(0) < __y1\n             ? value_type(0) <= __y2 &&\n    \
    \               mul_type(__y1) * __x2 < mul_type(__x1) * __y2\n             :\
    \ value_type(0) <= __y2 ||\n                   mul_type(__y1) * __x2 < mul_type(__x1)\
    \ * __y2;\n}\n\n}  // namespace workspace\n"
  code: "/**\n * @file compare.hpp\n * @brief Compare\n */\n\n#include \"sfinae.hpp\"\
    \n\nnamespace workspace {\n\n/**\n * @brief Compare 2 points by their value of\
    \ `atan2`.\n *\n * @return\n */\ntemplate <class _Tp>\nbool compare_arg(const\
    \ _Tp& __p1, const _Tp& __p2) noexcept {\n  const auto& [__x1, __y1] = __p1;\n\
    \  const auto& [__x2, __y2] = __p2;\n\n  using value_type = std::decay_t<decltype(__x1)>;\n\
    \  using mul_type = typename multiplicable<value_type>::type;\n\n  if (__y1 ==\
    \ value_type(0))\n    return value_type(0) <= __x1 &&\n           (value_type(0)\
    \ < __y2 ||\n            (__y2 == value_type(0) && __x2 < value_type(0)));\n\n\
    \  return value_type(0) < __y1\n             ? value_type(0) <= __y2 &&\n    \
    \               mul_type(__y1) * __x2 < mul_type(__x1) * __y2\n             :\
    \ value_type(0) <= __y2 ||\n                   mul_type(__y1) * __x2 < mul_type(__x1)\
    \ * __y2;\n}\n\n}  // namespace workspace\n"
  dependsOn:
  - src/utils/sfinae.hpp
  isVerificationFile: false
  path: src/utils/compare.hpp
  requiredBy: []
  timestamp: '2021-04-11 21:05:14+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/sort_points_by_argument.test.cpp
documentation_of: src/utils/compare.hpp
layout: document
redirect_from:
- /library/src/utils/compare.hpp
- /library/src/utils/compare.hpp.html
title: Compare
---
