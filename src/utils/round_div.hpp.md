---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/utils/sfinae.hpp
    title: src/utils/sfinae.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Round Integer Division
    links: []
  bundledCode: "#line 2 \"src/utils/round_div.hpp\"\n\n/*\n * @file round_div.hpp\n\
    \ * @brief Round Integer Division\n */\n\n#include <cassert>\n\n#line 2 \"src/utils/sfinae.hpp\"\
    \n#include <cstdint>\n#include <iterator>\n#include <type_traits>\n\ntemplate\
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
    };\n#line 11 \"src/utils/round_div.hpp\"\n\nnamespace workspace {\n\n/*\n * @fn\
    \ floor_div\n * @brief floor of fraction.\n * @param x the numerator\n * @param\
    \ y the denominator\n * @return maximum integer z s.t. z <= x / y\n * @note y\
    \ must be nonzero.\n */\ntemplate <typename T1, typename T2>\nconstexpr typename\
    \ std::enable_if<(is_integral_ext<T1>::value &&\n                            \
    \       is_integral_ext<T2>::value),\n                                  typename\
    \ std::common_type<T1, T2>::type>::type\nfloor_div(T1 x, T2 y) {\n  assert(y !=\
    \ 0);\n  if (y < 0) x = -x, y = -y;\n  return x < 0 ? (x - y + 1) / y : x / y;\n\
    }\n\n/*\n * @fn ceil_div\n * @brief ceil of fraction.\n * @param x the numerator\n\
    \ * @param y the denominator\n * @return minimum integer z s.t. z >= x / y\n *\
    \ @note y must be nonzero.\n */\ntemplate <typename T1, typename T2>\nconstexpr\
    \ typename std::enable_if<(is_integral_ext<T1>::value &&\n                   \
    \                is_integral_ext<T2>::value),\n                              \
    \    typename std::common_type<T1, T2>::type>::type\nceil_div(T1 x, T2 y) {\n\
    \  assert(y != 0);\n  if (y < 0) x = -x, y = -y;\n  return x < 0 ? x / y : (x\
    \ + y - 1) / y;\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file round_div.hpp\n * @brief Round Integer Division\n\
    \ */\n\n#include <cassert>\n\n#include \"sfinae.hpp\"\n\nnamespace workspace {\n\
    \n/*\n * @fn floor_div\n * @brief floor of fraction.\n * @param x the numerator\n\
    \ * @param y the denominator\n * @return maximum integer z s.t. z <= x / y\n *\
    \ @note y must be nonzero.\n */\ntemplate <typename T1, typename T2>\nconstexpr\
    \ typename std::enable_if<(is_integral_ext<T1>::value &&\n                   \
    \                is_integral_ext<T2>::value),\n                              \
    \    typename std::common_type<T1, T2>::type>::type\nfloor_div(T1 x, T2 y) {\n\
    \  assert(y != 0);\n  if (y < 0) x = -x, y = -y;\n  return x < 0 ? (x - y + 1)\
    \ / y : x / y;\n}\n\n/*\n * @fn ceil_div\n * @brief ceil of fraction.\n * @param\
    \ x the numerator\n * @param y the denominator\n * @return minimum integer z s.t.\
    \ z >= x / y\n * @note y must be nonzero.\n */\ntemplate <typename T1, typename\
    \ T2>\nconstexpr typename std::enable_if<(is_integral_ext<T1>::value &&\n    \
    \                               is_integral_ext<T2>::value),\n               \
    \                   typename std::common_type<T1, T2>::type>::type\nceil_div(T1\
    \ x, T2 y) {\n  assert(y != 0);\n  if (y < 0) x = -x, y = -y;\n  return x < 0\
    \ ? x / y : (x + y - 1) / y;\n}\n\n}  // namespace workspace\n"
  dependsOn:
  - src/utils/sfinae.hpp
  isVerificationFile: false
  path: src/utils/round_div.hpp
  requiredBy: []
  timestamp: '2020-11-16 14:21:51+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/round_div.hpp
layout: document
redirect_from:
- /library/src/utils/round_div.hpp
- /library/src/utils/round_div.hpp.html
title: Round Integer Division
---
