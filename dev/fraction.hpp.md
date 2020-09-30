---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utils/sfinae.hpp
    title: utils/sfinae.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utils/sfinae.hpp\"\n#include <cstdint>\n#include <type_traits>\n\
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
    };\n#line 3 \"dev/fraction.hpp\"\ntemplate <class T> struct fraction {\n  static_assert(is_integral_ext_v<T>);\n\
    \  T num, den;\n  constexpr fraction(const T &num = 0, const T &den = 1) : num(num),\
    \ den(den) {}\n  constexpr fraction operator-() const { return {-num, den}; }\n\
    \  constexpr fraction operator-(const fraction &rhs) const {\n    return {num\
    \ * rhs.den - rhs.num * den, den * rhs.den};\n  }\n  constexpr bool operator<(const\
    \ fraction &rhs) const {\n    return operator-(rhs).num < 0;\n  }\n\n private:\n\
    \  constexpr void normalize();\n};\n"
  code: "#pragma once\n#include \"utils/sfinae.hpp\"\ntemplate <class T> struct fraction\
    \ {\n  static_assert(is_integral_ext_v<T>);\n  T num, den;\n  constexpr fraction(const\
    \ T &num = 0, const T &den = 1) : num(num), den(den) {}\n  constexpr fraction\
    \ operator-() const { return {-num, den}; }\n  constexpr fraction operator-(const\
    \ fraction &rhs) const {\n    return {num * rhs.den - rhs.num * den, den * rhs.den};\n\
    \  }\n  constexpr bool operator<(const fraction &rhs) const {\n    return operator-(rhs).num\
    \ < 0;\n  }\n\n private:\n  constexpr void normalize();\n};\n"
  dependsOn:
  - utils/sfinae.hpp
  isVerificationFile: false
  path: dev/fraction.hpp
  requiredBy: []
  timestamp: '2020-09-17 16:18:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: dev/fraction.hpp
layout: document
redirect_from:
- /library/dev/fraction.hpp
- /library/dev/fraction.hpp.html
title: dev/fraction.hpp
---
