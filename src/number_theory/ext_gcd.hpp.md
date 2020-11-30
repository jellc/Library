---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/NTL_1_E.test.cpp
    title: test/aizu-online-judge/NTL_1_E.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Extended Euclidean Algorithm
    links: []
  bundledCode: "#line 2 \"src/number_theory/ext_gcd.hpp\"\n\n/*\n * @file ext_gcd\n\
    \ * @brief Extended Euclidean Algorithm\n */\n\n#include <tuple>\n\n#line 2 \"\
    src/utils/sfinae.hpp\"\n\n/*\n * @file sfinae.hpp\n * @brief SFINAE\n */\n\n#include\
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
    template <> struct is_integral_ext<__int128_t> : std::true_type {};\ntemplate\
    \ <> struct is_integral_ext<__uint128_t> : std::true_type {};\n#if __cplusplus\
    \ >= 201402\ntemplate <class T>\nconstexpr static bool is_integral_ext_v = is_integral_ext<T>::value;\n\
    #endif\n\ntemplate <typename T, typename = void> struct multiplicable_uint {\n\
    \  using type = uint_least32_t;\n};\ntemplate <typename T>\nstruct multiplicable_uint<T,\
    \ typename std::enable_if<(2 < sizeof(T))>::type> {\n  using type = uint_least64_t;\n\
    };\ntemplate <typename T>\nstruct multiplicable_uint<T, typename std::enable_if<(4\
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n\n}  // namespace workspace\n\
    #line 11 \"src/number_theory/ext_gcd.hpp\"\n\nnamespace workspace {\n\n/*\n *\
    \ @fn ext_gcd\n * @param a an integer\n * @param b an integer\n * @return a pair\
    \ of integers (x, y) s.t. ax + by = gcd(a, b)\n * @note return (0, 0) if (a, b)\
    \ = (0, 0)\n */\ntemplate <typename T1, typename T2>\nconstexpr typename std::enable_if<\n\
    \    (is_integral_ext<T1>::value && is_integral_ext<T2>::value),\n    std::pair<typename\
    \ std::common_type<T1, T2>::type,\n              typename std::common_type<T1,\
    \ T2>::type>>::type\next_gcd(T1 a, T2 b) {\n  typename std::common_type<T1, T2>::type\
    \ p{1}, q{}, r{}, s{1}, t{};\n  if (a < 0) {\n    std::tie(p, q) = ext_gcd(-a,\
    \ b);\n    p = -p;\n  } else if (b < 0) {\n    std::tie(p, q) = ext_gcd(a, -b);\n\
    \    q = -q;\n  } else {\n    while (b) {\n      r ^= p ^= r ^= p -= (t = a /\
    \ b) * r;\n      s ^= q ^= s ^= q -= t * s;\n      b ^= a ^= b ^= a %= b;\n  \
    \  }\n  }\n  return {p, q};\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file ext_gcd\n * @brief Extended Euclidean Algorithm\n\
    \ */\n\n#include <tuple>\n\n#include \"src/utils/sfinae.hpp\"\n\nnamespace workspace\
    \ {\n\n/*\n * @fn ext_gcd\n * @param a an integer\n * @param b an integer\n *\
    \ @return a pair of integers (x, y) s.t. ax + by = gcd(a, b)\n * @note return\
    \ (0, 0) if (a, b) = (0, 0)\n */\ntemplate <typename T1, typename T2>\nconstexpr\
    \ typename std::enable_if<\n    (is_integral_ext<T1>::value && is_integral_ext<T2>::value),\n\
    \    std::pair<typename std::common_type<T1, T2>::type,\n              typename\
    \ std::common_type<T1, T2>::type>>::type\next_gcd(T1 a, T2 b) {\n  typename std::common_type<T1,\
    \ T2>::type p{1}, q{}, r{}, s{1}, t{};\n  if (a < 0) {\n    std::tie(p, q) = ext_gcd(-a,\
    \ b);\n    p = -p;\n  } else if (b < 0) {\n    std::tie(p, q) = ext_gcd(a, -b);\n\
    \    q = -q;\n  } else {\n    while (b) {\n      r ^= p ^= r ^= p -= (t = a /\
    \ b) * r;\n      s ^= q ^= s ^= q -= t * s;\n      b ^= a ^= b ^= a %= b;\n  \
    \  }\n  }\n  return {p, q};\n}\n\n}  // namespace workspace\n"
  dependsOn:
  - src/utils/sfinae.hpp
  isVerificationFile: false
  path: src/number_theory/ext_gcd.hpp
  requiredBy: []
  timestamp: '2020-11-22 05:26:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aizu-online-judge/NTL_1_E.test.cpp
documentation_of: src/number_theory/ext_gcd.hpp
layout: document
redirect_from:
- /library/src/number_theory/ext_gcd.hpp
- /library/src/number_theory/ext_gcd.hpp.html
title: Extended Euclidean Algorithm
---