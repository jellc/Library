---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Primitive Root
    links: []
  bundledCode: "#line 1 \"src/number_theory/primitive_root.hpp\"\n/**\n * @file primitive_root.hpp\n\
    \ * @brief Primitive Root\n * @date 2020-12-28\n */\n\n#include <type_traits>\n\
    \n#line 2 \"src/utils/sfinae.hpp\"\n\n/*\n * @file sfinae.hpp\n * @brief SFINAE\n\
    \ */\n\n#include <cstdint>\n#include <iterator>\n#line 11 \"src/utils/sfinae.hpp\"\
    \n\n#ifdef __SIZEOF_INT128__\n#define __INT128_DEFINED__ 1\n#else\n#define __INT128_DEFINED__\
    \ 0\n#endif\n\nnamespace std {\n\n#if __INT128_DEFINED__\n\ntemplate <> struct\
    \ make_signed<__uint128_t> { using type = __int128_t; };\ntemplate <> struct make_signed<__int128_t>\
    \ { using type = __int128_t; };\n\ntemplate <> struct make_unsigned<__uint128_t>\
    \ { using type = __uint128_t; };\ntemplate <> struct make_unsigned<__int128_t>\
    \ { using type = __uint128_t; };\n\n#endif\n\n}  // namespace std\n\nnamespace\
    \ workspace {\n\ntemplate <class type, template <class> class trait>\nusing enable_if_trait_type\
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
    \n#if __INT128_DEFINED__\n\ntemplate <> struct is_integral_ext<__int128_t> : std::true_type\
    \ {};\ntemplate <> struct is_integral_ext<__uint128_t> : std::true_type {};\n\n\
    #endif\n\n#if __cplusplus >= 201402\n\ntemplate <class T>\nconstexpr static bool\
    \ is_integral_ext_v = is_integral_ext<T>::value;\n\n#endif\n\ntemplate <typename\
    \ T, typename = void> struct multiplicable_uint {\n  using type = uint_least32_t;\n\
    };\ntemplate <typename T>\nstruct multiplicable_uint<\n    T, typename std::enable_if<(2\
    \ < sizeof(T)) &&\n                               (!__INT128_DEFINED__ || sizeof(T)\
    \ <= 4)>::type> {\n  using type = uint_least64_t;\n};\n\n#if __INT128_DEFINED__\n\
    \ntemplate <typename T>\nstruct multiplicable_uint<T, typename std::enable_if<(4\
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n\n#endif\n\n}  // namespace\
    \ workspace\n#line 10 \"src/number_theory/primitive_root.hpp\"\n\nnamespace workspace\
    \ {\n\n/**\n * @brief Compile time primitive root\n *\n * @tparam Mod\n */\ntemplate\
    \ <auto Mod>\nconstexpr static\n    typename std::enable_if<(is_integral_ext<decltype(Mod)>::value\
    \ && Mod > 0),\n                            decltype(Mod)>::type primitive_root\
    \ = [] {\n      using result_type = decltype(Mod);\n      using int_type = typename\
    \ multiplicable_uint<result_type>::type;\n\n      auto __m = Mod - 1;\n      while\
    \ (!(__m & 1)) __m >>= 1;\n\n      int_type __p[16] = {2}, *__t = __p + 1;\n\n\
    \      for (int_type __i = 3; __i <= __m / __i; __i += 2) {\n        if (__m %\
    \ __i) continue;\n        *__t++ = __i;\n        while (!(__m % __i)) __m /= __i;\n\
    \      }\n      if (__m != 1) *__t++ = __m;\n\n      int_type __r = 1;\n     \
    \ for (bool __yet = true; __yet; ++__r) {\n        __yet = false;\n        auto\
    \ __q = __t;\n        for (auto __i = __p; __i != __t; ++__i) {\n          int_type\
    \ __w = 1, __x = __r;\n          for (auto e = (Mod - 1) / *__i; e; e >>= 1, (__x\
    \ *= __x) %= Mod)\n            if (e & 1) (__w *= __x) %= Mod;\n          if (__w\
    \ == 1) {\n            __yet = true;\n            break;\n          }\n      \
    \  }\n      }\n      return static_cast<result_type>(--__r);\n    }();\n\n}  //\
    \ namespace workspace\n"
  code: "/**\n * @file primitive_root.hpp\n * @brief Primitive Root\n * @date 2020-12-28\n\
    \ */\n\n#include <type_traits>\n\n#include \"src/utils/sfinae.hpp\"\n\nnamespace\
    \ workspace {\n\n/**\n * @brief Compile time primitive root\n *\n * @tparam Mod\n\
    \ */\ntemplate <auto Mod>\nconstexpr static\n    typename std::enable_if<(is_integral_ext<decltype(Mod)>::value\
    \ && Mod > 0),\n                            decltype(Mod)>::type primitive_root\
    \ = [] {\n      using result_type = decltype(Mod);\n      using int_type = typename\
    \ multiplicable_uint<result_type>::type;\n\n      auto __m = Mod - 1;\n      while\
    \ (!(__m & 1)) __m >>= 1;\n\n      int_type __p[16] = {2}, *__t = __p + 1;\n\n\
    \      for (int_type __i = 3; __i <= __m / __i; __i += 2) {\n        if (__m %\
    \ __i) continue;\n        *__t++ = __i;\n        while (!(__m % __i)) __m /= __i;\n\
    \      }\n      if (__m != 1) *__t++ = __m;\n\n      int_type __r = 1;\n     \
    \ for (bool __yet = true; __yet; ++__r) {\n        __yet = false;\n        auto\
    \ __q = __t;\n        for (auto __i = __p; __i != __t; ++__i) {\n          int_type\
    \ __w = 1, __x = __r;\n          for (auto e = (Mod - 1) / *__i; e; e >>= 1, (__x\
    \ *= __x) %= Mod)\n            if (e & 1) (__w *= __x) %= Mod;\n          if (__w\
    \ == 1) {\n            __yet = true;\n            break;\n          }\n      \
    \  }\n      }\n      return static_cast<result_type>(--__r);\n    }();\n\n}  //\
    \ namespace workspace\n"
  dependsOn:
  - src/utils/sfinae.hpp
  isVerificationFile: false
  path: src/number_theory/primitive_root.hpp
  requiredBy: []
  timestamp: '2020-12-28 18:43:17+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/number_theory/primitive_root.hpp
layout: document
redirect_from:
- /library/src/number_theory/primitive_root.hpp
- /library/src/number_theory/primitive_root.hpp.html
title: Primitive Root
---
