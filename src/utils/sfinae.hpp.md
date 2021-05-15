---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: src/algebra/ntt.hpp
    title: Number Theoretic Transform
  - icon: ':heavy_check_mark:'
    path: src/algebra/polynomial.hpp
    title: Polynomial
  - icon: ':heavy_check_mark:'
    path: src/combinatorics/binomial.hpp
    title: Binomial Coefficient
  - icon: ':heavy_check_mark:'
    path: src/data_structure/segment_tree/lazy.hpp
    title: Lazy Segment Tree
  - icon: ':warning:'
    path: src/modular/inverse.hpp
    title: Inverse Table
  - icon: ':heavy_check_mark:'
    path: src/modular/modint.hpp
    title: Modular Arithmetic
  - icon: ':heavy_check_mark:'
    path: src/number_theory/ext_gcd.hpp
    title: Extended Euclidean Algorithm
  - icon: ':warning:'
    path: src/number_theory/least_factor.hpp
    title: Least Prime Factor
  - icon: ':warning:'
    path: src/number_theory/order.hpp
    title: Order
  - icon: ':heavy_check_mark:'
    path: src/number_theory/pow_mod.hpp
    title: Modular Exponentiation
  - icon: ':heavy_check_mark:'
    path: src/number_theory/primitive_root.hpp
    title: Primitive Root
  - icon: ':heavy_check_mark:'
    path: src/number_theory/sqrt_mod.hpp
    title: Tonelli-Shanks Algorithm
  - icon: ':heavy_check_mark:'
    path: src/number_theory/totient.hpp
    title: Euler's Totient Function
  - icon: ':heavy_check_mark:'
    path: src/string/rolling_hash.hpp
    title: Rolling Hash
  - icon: ':heavy_check_mark:'
    path: src/string/suffix_array.hpp
    title: Suffix Array
  - icon: ':heavy_check_mark:'
    path: src/utils/compare.hpp
    title: Compare
  - icon: ':heavy_check_mark:'
    path: src/utils/hash.hpp
    title: src/utils/hash.hpp
  - icon: ':heavy_check_mark:'
    path: src/utils/io/istream.hpp
    title: Input Stream
  - icon: ':warning:'
    path: src/utils/round_div.hpp
    title: Round Integer Division
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/2450.test.cpp
    title: test/aizu-online-judge/2450.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/ALDS1_14_C.test.cpp
    title: test/aizu-online-judge/ALDS1_14_C.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/DPL_5_D.test.cpp
    title: test/aizu-online-judge/DPL_5_D.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/ITP1_6_D.test.cpp
    title: test/aizu-online-judge/ITP1_6_D.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/ITP1_7_D.test.cpp
    title: test/aizu-online-judge/ITP1_7_D.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/NTL_1_D.test.cpp
    title: test/aizu-online-judge/NTL_1_D.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/NTL_1_E.test.cpp
    title: test/aizu-online-judge/NTL_1_E.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/associative_array.test.cpp
    title: test/library-checker/associative_array.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/bitwise_and_convolution.test.cpp
    title: test/library-checker/bitwise_and_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/bitwise_xor_convolution.test.cpp
    title: test/library-checker/bitwise_xor_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/convolution_mod.test.cpp
    title: test/library-checker/convolution_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/matrix_det.test.cpp
    title: test/library-checker/matrix_det.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/number_of_substrings.test.cpp
    title: test/library-checker/number_of_substrings.test.cpp
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
    path: test/library-checker/sort_points_by_argument.test.cpp
    title: test/library-checker/sort_points_by_argument.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/sqrt_mod.test.cpp
    title: test/library-checker/sqrt_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/subset_convolution.test.cpp
    title: test/library-checker/subset_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/suffix_array.test.cpp
    title: test/library-checker/suffix_array.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/system_of_linear_equations.test.cpp
    title: test/library-checker/system_of_linear_equations.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/zalgorithm_2.test.cpp
    title: test/library-checker/zalgorithm_2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: SFINAE
    links: []
  bundledCode: "#line 2 \"src/utils/sfinae.hpp\"\n\n/**\n * @file sfinae.hpp\n * @brief\
    \ SFINAE\n */\n\n#include <cstdint>\n#include <iterator>\n#include <type_traits>\n\
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
    \ multiplicable_uint<_Tp>::type>,\n      _Tp>;\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file sfinae.hpp\n * @brief SFINAE\n */\n\n#include\
    \ <cstdint>\n#include <iterator>\n#include <type_traits>\n\n#ifndef __INT128_DEFINED__\n\
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
    \ multiplicable_uint<_Tp>::type>,\n      _Tp>;\n};\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/sfinae.hpp
  requiredBy:
  - src/combinatorics/binomial.hpp
  - src/modular/modint.hpp
  - src/modular/inverse.hpp
  - src/string/suffix_array.hpp
  - src/string/rolling_hash.hpp
  - src/utils/compare.hpp
  - src/utils/round_div.hpp
  - src/utils/io/istream.hpp
  - src/utils/hash.hpp
  - src/algebra/ntt.hpp
  - src/algebra/polynomial.hpp
  - src/data_structure/segment_tree/lazy.hpp
  - src/number_theory/totient.hpp
  - src/number_theory/least_factor.hpp
  - src/number_theory/ext_gcd.hpp
  - src/number_theory/pow_mod.hpp
  - src/number_theory/primitive_root.hpp
  - src/number_theory/sqrt_mod.hpp
  - src/number_theory/order.hpp
  timestamp: '2021-05-10 01:25:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/number_of_substrings.test.cpp
  - test/library-checker/system_of_linear_equations.test.cpp
  - test/library-checker/associative_array.test.cpp
  - test/library-checker/matrix_det.test.cpp
  - test/library-checker/sort_points_by_argument.test.cpp
  - test/library-checker/convolution_mod.test.cpp
  - test/library-checker/range_affine_range_sum.test.cpp
  - test/library-checker/bitwise_and_convolution.test.cpp
  - test/library-checker/sqrt_mod.test.cpp
  - test/library-checker/subset_convolution.test.cpp
  - test/library-checker/bitwise_xor_convolution.test.cpp
  - test/library-checker/zalgorithm_2.test.cpp
  - test/library-checker/suffix_array.test.cpp
  - test/library-checker/point_set_range_composite.test.cpp
  - test/library-checker/queue_operate_all_composite.test.cpp
  - test/aizu-online-judge/ITP1_7_D.test.cpp
  - test/aizu-online-judge/DPL_5_D.test.cpp
  - test/aizu-online-judge/NTL_1_E.test.cpp
  - test/aizu-online-judge/ALDS1_14_C.test.cpp
  - test/aizu-online-judge/2450.test.cpp
  - test/aizu-online-judge/ITP1_6_D.test.cpp
  - test/aizu-online-judge/NTL_1_D.test.cpp
documentation_of: src/utils/sfinae.hpp
layout: document
redirect_from:
- /library/src/utils/sfinae.hpp
- /library/src/utils/sfinae.hpp.html
title: SFINAE
---
