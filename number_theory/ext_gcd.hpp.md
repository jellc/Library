---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utils/sfinae.hpp
    title: utils/sfinae.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/extended_euclid_algorithm.test.cpp
    title: test/aizu-online-judge/extended_euclid_algorithm.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 2 \"number_theory/ext_gcd.hpp\"\n#include <tuple>\n\n#line 2\
    \ \"utils/sfinae.hpp\"\n#include <cstdint>\n#include <type_traits>\n\ntemplate\
    \ <class type, template <class> class trait>\nusing enable_if_trait_type = typename\
    \ std::enable_if<trait<type>::value>::type;\n\ntemplate <class Container>\nusing\
    \ element_type = typename std::decay<decltype(\n    *std::begin(std::declval<Container&>()))>::type;\n\
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
    };\n#line 5 \"number_theory/ext_gcd.hpp\"\ntemplate <class int_type>\nconstexpr\
    \ typename std::enable_if<is_integral_ext<int_type>::value,\n                \
    \                  std::pair<int_type, int_type>>::type\next_gcd(int_type a, int_type\
    \ b) {\n  bool neg_a = a < 0, neg_b = b < 0;\n  int_type p{1}, q{}, r{}, s{1},\
    \ t{};\n  while (b) {\n    r ^= p ^= r ^= p -= (t = a / b) * r;\n    s ^= q ^=\
    \ s ^= q -= t * s;\n    b ^= a ^= b ^= a %= b;\n  }\n  return {neg_a ? -p : p,\
    \ neg_b ? -q : q};\n}\n"
  code: "#pragma once\n#include <tuple>\n\n#include \"utils/sfinae.hpp\"\ntemplate\
    \ <class int_type>\nconstexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                  std::pair<int_type, int_type>>::type\next_gcd(int_type\
    \ a, int_type b) {\n  bool neg_a = a < 0, neg_b = b < 0;\n  int_type p{1}, q{},\
    \ r{}, s{1}, t{};\n  while (b) {\n    r ^= p ^= r ^= p -= (t = a / b) * r;\n \
    \   s ^= q ^= s ^= q -= t * s;\n    b ^= a ^= b ^= a %= b;\n  }\n  return {neg_a\
    \ ? -p : p, neg_b ? -q : q};\n}\n"
  dependsOn:
  - utils/sfinae.hpp
  isVerificationFile: false
  path: number_theory/ext_gcd.hpp
  requiredBy: []
  timestamp: '2020-09-17 16:18:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aizu-online-judge/extended_euclid_algorithm.test.cpp
documentation_of: number_theory/ext_gcd.hpp
layout: document
redirect_from:
- /library/number_theory/ext_gcd.hpp
- /library/number_theory/ext_gcd.hpp.html
title: number_theory/ext_gcd.hpp
---
