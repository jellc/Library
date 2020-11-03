---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utils/sfinae.hpp
    title: utils/sfinae.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: template.cpp
    title: template.cpp
  - icon: ':warning:'
    path: utils.hpp
    title: utils.hpp
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utils/floor_div.hpp\"\n#include <cassert>\n\n#line 2 \"\
    utils/sfinae.hpp\"\n#include <cstdint>\n#include <iterator>\n#include <type_traits>\n\
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
    };\n#line 5 \"utils/floor_div.hpp\"\n\ntemplate <typename int_type>\nconstexpr\n\
    \    typename std::enable_if<is_integral_ext<int_type>::value, int_type>::type\n\
    \    floor_div(int_type x, int_type y) {\n  assert(y != 0);\n  if (y < 0) x =\
    \ -x, y = -y;\n  return x < 0 ? (x - y + 1) / y : x / y;\n}\n"
  code: "#pragma once\n#include <cassert>\n\n#include \"sfinae.hpp\"\n\ntemplate <typename\
    \ int_type>\nconstexpr\n    typename std::enable_if<is_integral_ext<int_type>::value,\
    \ int_type>::type\n    floor_div(int_type x, int_type y) {\n  assert(y != 0);\n\
    \  if (y < 0) x = -x, y = -y;\n  return x < 0 ? (x - y + 1) / y : x / y;\n}\n"
  dependsOn:
  - utils/sfinae.hpp
  isVerificationFile: false
  path: utils/floor_div.hpp
  requiredBy:
  - template.cpp
  - utils.hpp
  timestamp: '2020-10-26 11:02:22+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils/floor_div.hpp
layout: document
redirect_from:
- /library/utils/floor_div.hpp
- /library/utils/floor_div.hpp.html
title: utils/floor_div.hpp
---
