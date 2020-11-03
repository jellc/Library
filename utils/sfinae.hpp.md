---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: combinatorics/binomial.hpp
    title: combinatorics/binomial.hpp
  - icon: ':heavy_check_mark:'
    path: data_structure/segment_tree/basic.hpp
    title: data_structure/segment_tree/basic.hpp
  - icon: ':heavy_check_mark:'
    path: data_structure/segment_tree/lazy.hpp
    title: data_structure/segment_tree/lazy.hpp
  - icon: ':warning:'
    path: dev/fraction.hpp
    title: dev/fraction.hpp
  - icon: ':heavy_check_mark:'
    path: modulus/inverse.hpp
    title: modulus/inverse.hpp
  - icon: ':heavy_check_mark:'
    path: modulus/modint.hpp
    title: base of modular arithmetic.
  - icon: ':heavy_check_mark:'
    path: number_theory/ext_gcd.hpp
    title: extended Euclidean algorithm.
  - icon: ':warning:'
    path: number_theory/least_factor.hpp
    title: calculate the least prime factor for positive integers.
  - icon: ':heavy_check_mark:'
    path: string/suffix_array.hpp
    title: string/suffix_array.hpp
  - icon: ':warning:'
    path: template.cpp
    title: template.cpp
  - icon: ':warning:'
    path: utils.hpp
    title: utils.hpp
  - icon: ':heavy_check_mark:'
    path: utils/hash.hpp
    title: utils/hash.hpp
  - icon: ':warning:'
    path: utils/round_div.hpp
    title: floor of fraction.
  - icon: ':heavy_check_mark:'
    path: utils/stream.hpp
    title: utils/stream.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/balls_and_boxes_4.test.cpp
    title: test/aizu-online-judge/balls_and_boxes_4.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/do_use_segment_tree.test.cpp
    title: test/aizu-online-judge/do_use_segment_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/extended_euclid_algorithm.test.cpp
    title: test/aizu-online-judge/extended_euclid_algorithm.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/pattern_search.test.cpp
    title: test/aizu-online-judge/pattern_search.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/range_minimum_query.test.cpp
    title: test/aizu-online-judge/range_minimum_query.test.cpp
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
    path: test/library-checker/zalgorithm.test.cpp
    title: test/library-checker/zalgorithm.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utils/sfinae.hpp\"\n#include <cstdint>\n#include <iterator>\n\
    #include <type_traits>\n\ntemplate <class type, template <class> class trait>\n\
    using enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
    \ntemplate <class Container>\nusing element_type = typename std::decay<decltype(\n\
    \    *std::begin(std::declval<Container&>()))>::type;\n\ntemplate <class T, class\
    \ = int> struct mapped_of {\n  using type = element_type<T>;\n};\ntemplate <class\
    \ T>\nstruct mapped_of<T,\n                 typename std::pair<int, typename T::mapped_type>::first_type>\
    \ {\n  using type = typename T::mapped_type;\n};\ntemplate <class T> using mapped_type\
    \ = typename mapped_of<T>::type;\n\ntemplate <class T, class = void> struct is_integral_ext\
    \ : std::false_type {};\ntemplate <class T>\nstruct is_integral_ext<\n    T, typename\
    \ std::enable_if<std::is_integral<T>::value>::type>\n    : std::true_type {};\n\
    template <> struct is_integral_ext<__int128_t> : std::true_type {};\ntemplate\
    \ <> struct is_integral_ext<__uint128_t> : std::true_type {};\n#if __cplusplus\
    \ >= 201402\ntemplate <class T>\nconstexpr static bool is_integral_ext_v = is_integral_ext<T>::value;\n\
    #endif\n\ntemplate <typename T, typename = void> struct multiplicable_uint {\n\
    \  using type = uint_least32_t;\n};\ntemplate <typename T>\nstruct multiplicable_uint<T,\
    \ typename std::enable_if<(2 < sizeof(T))>::type> {\n  using type = uint_least64_t;\n\
    };\ntemplate <typename T>\nstruct multiplicable_uint<T, typename std::enable_if<(4\
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n"
  code: "#pragma once\n#include <cstdint>\n#include <iterator>\n#include <type_traits>\n\
    \ntemplate <class type, template <class> class trait>\nusing enable_if_trait_type\
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
    };\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/sfinae.hpp
  requiredBy:
  - template.cpp
  - string/suffix_array.hpp
  - data_structure/segment_tree/lazy.hpp
  - data_structure/segment_tree/basic.hpp
  - modulus/inverse.hpp
  - modulus/modint.hpp
  - dev/fraction.hpp
  - combinatorics/binomial.hpp
  - number_theory/ext_gcd.hpp
  - number_theory/least_factor.hpp
  - utils.hpp
  - utils/hash.hpp
  - utils/round_div.hpp
  - utils/stream.hpp
  timestamp: '2020-10-10 01:30:31+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/point_set_range_composite.test.cpp
  - test/library-checker/number_of_substrings.test.cpp
  - test/library-checker/zalgorithm.test.cpp
  - test/library-checker/suffix_array.test.cpp
  - test/library-checker/associative_array.test.cpp
  - test/library-checker/static_range_inversions_query.test.cpp
  - test/library-checker/subset_convolution.test.cpp
  - test/library-checker/queue_operate_all_composite.test.cpp
  - test/library-checker/range_affine_range_sum.test.cpp
  - test/aizu-online-judge/range_minimum_query.test.cpp
  - test/aizu-online-judge/pattern_search.test.cpp
  - test/aizu-online-judge/extended_euclid_algorithm.test.cpp
  - test/aizu-online-judge/balls_and_boxes_4.test.cpp
  - test/aizu-online-judge/do_use_segment_tree.test.cpp
documentation_of: utils/sfinae.hpp
layout: document
redirect_from:
- /library/utils/sfinae.hpp
- /library/utils/sfinae.hpp.html
title: utils/sfinae.hpp
---
