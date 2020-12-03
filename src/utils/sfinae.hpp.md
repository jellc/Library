---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: src/combinatorics/binomial.hpp
    title: Binomial Coefficient
  - icon: ':heavy_check_mark:'
    path: src/data_structure/segment_tree/basic.hpp
    title: Segment Tree
  - icon: ':heavy_check_mark:'
    path: src/data_structure/segment_tree/lazy.hpp
    title: Lazy Segment Tree
  - icon: ':heavy_check_mark:'
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
  - icon: ':heavy_check_mark:'
    path: src/string/rolling_hash.hpp
    title: Rolling Hash
  - icon: ':heavy_check_mark:'
    path: src/string/suffix_array.hpp
    title: Suffix Array
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
    path: test/aizu-online-judge/DSL_2_A.test.cpp
    title: test/aizu-online-judge/DSL_2_A.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/NTL_1_E.test.cpp
    title: test/aizu-online-judge/NTL_1_E.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/associative_array.test.cpp
    title: test/library-checker/associative_array.test.cpp
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
    path: test/library-checker/static_range_inversions_query.test.cpp
    title: test/library-checker/static_range_inversions_query.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/subset_convolution.test.cpp
    title: test/library-checker/subset_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/suffix_array.test.cpp
    title: test/library-checker/suffix_array.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/zalgorithm_2.test.cpp
    title: test/library-checker/zalgorithm_2.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: SFINAE
    links: []
  bundledCode: "#line 2 \"src/utils/sfinae.hpp\"\n\n/*\n * @file sfinae.hpp\n * @brief\
    \ SFINAE\n */\n\n#include <cstdint>\n#include <iterator>\n#include <type_traits>\n\
    \nnamespace workspace {\n\ntemplate <class type, template <class> class trait>\n\
    using enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
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
    \n#ifdef __SIZEOF_INT128__\ntemplate <> struct is_integral_ext<__int128_t> : std::true_type\
    \ {};\ntemplate <> struct is_integral_ext<__uint128_t> : std::true_type {};\n\
    #endif\n\n#if __cplusplus >= 201402\ntemplate <class T>\nconstexpr static bool\
    \ is_integral_ext_v = is_integral_ext<T>::value;\n#endif\n\ntemplate <typename\
    \ T, typename = void> struct multiplicable_uint {\n  using type = uint_least32_t;\n\
    };\ntemplate <typename T>\nstruct multiplicable_uint<T, typename std::enable_if<(2\
    \ < sizeof(T))>::type> {\n  using type = uint_least64_t;\n};\n\n#ifdef __SIZEOF_INT128__\n\
    template <typename T>\nstruct multiplicable_uint<T, typename std::enable_if<(4\
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n#endif\n\n}  // namespace\
    \ workspace\n"
  code: "#pragma once\n\n/*\n * @file sfinae.hpp\n * @brief SFINAE\n */\n\n#include\
    \ <cstdint>\n#include <iterator>\n#include <type_traits>\n\nnamespace workspace\
    \ {\n\ntemplate <class type, template <class> class trait>\nusing enable_if_trait_type\
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
    \n#ifdef __SIZEOF_INT128__\ntemplate <> struct is_integral_ext<__int128_t> : std::true_type\
    \ {};\ntemplate <> struct is_integral_ext<__uint128_t> : std::true_type {};\n\
    #endif\n\n#if __cplusplus >= 201402\ntemplate <class T>\nconstexpr static bool\
    \ is_integral_ext_v = is_integral_ext<T>::value;\n#endif\n\ntemplate <typename\
    \ T, typename = void> struct multiplicable_uint {\n  using type = uint_least32_t;\n\
    };\ntemplate <typename T>\nstruct multiplicable_uint<T, typename std::enable_if<(2\
    \ < sizeof(T))>::type> {\n  using type = uint_least64_t;\n};\n\n#ifdef __SIZEOF_INT128__\n\
    template <typename T>\nstruct multiplicable_uint<T, typename std::enable_if<(4\
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n#endif\n\n}  // namespace\
    \ workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/sfinae.hpp
  requiredBy:
  - src/combinatorics/binomial.hpp
  - src/number_theory/ext_gcd.hpp
  - src/number_theory/least_factor.hpp
  - src/string/suffix_array.hpp
  - src/string/rolling_hash.hpp
  - src/data_structure/segment_tree/lazy.hpp
  - src/data_structure/segment_tree/basic.hpp
  - src/modular/modint.hpp
  - src/modular/inverse.hpp
  - src/utils/hash.hpp
  - src/utils/round_div.hpp
  - src/utils/io/istream.hpp
  timestamp: '2020-12-01 16:34:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/static_range_inversions_query.test.cpp
  - test/library-checker/queue_operate_all_composite.test.cpp
  - test/library-checker/range_affine_range_sum.test.cpp
  - test/library-checker/suffix_array.test.cpp
  - test/library-checker/point_set_range_composite.test.cpp
  - test/library-checker/zalgorithm_2.test.cpp
  - test/library-checker/subset_convolution.test.cpp
  - test/library-checker/associative_array.test.cpp
  - test/library-checker/number_of_substrings.test.cpp
  - test/aizu-online-judge/ALDS1_14_C.test.cpp
  - test/aizu-online-judge/DSL_2_A.test.cpp
  - test/aizu-online-judge/DPL_5_D.test.cpp
  - test/aizu-online-judge/NTL_1_E.test.cpp
  - test/aizu-online-judge/2450.test.cpp
documentation_of: src/utils/sfinae.hpp
layout: document
redirect_from:
- /library/src/utils/sfinae.hpp
- /library/src/utils/sfinae.hpp.html
title: SFINAE
---
