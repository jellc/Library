---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: src/combinatorics/binomial.hpp
    title: Binomial Coefficient
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/DPL_5_D.test.cpp
    title: test/aizu-online-judge/DPL_5_D.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Factorial
    links: []
  bundledCode: "#line 2 \"src/combinatorics/factorial.hpp\"\n\n/**\n * @file factorial.hpp\n\
    \ * @brief Factorial\n * @date 2021-01-15\n *\n *\n */\n\n#include <cstdint>\n\
    #include <functional>\n#include <vector>\n\nnamespace workspace {\n\ntemplate\
    \ <class Tp> Tp factorial(int_fast32_t __x) noexcept {\n  if (__x < 0) return\
    \ 0;\n  static std::vector<Tp> __t{1};\n  static int_fast32_t __i = (__t.reserve(0x1000000),\
    \ 0);\n  while (__i < __x) {\n    ++__i;\n    __t.emplace_back(__t.back() * __i);\n\
    \  }\n  return __t[__x];\n}\n\ntemplate <class Tp> Tp factorial_inverse(int_fast32_t\
    \ __x) noexcept {\n  if (__x < 0) return 0;\n  static std::vector<Tp> __t{1};\n\
    \  static int_fast32_t __i = (__t.reserve(0x1000000), 0);\n  while (__i < __x)\
    \ {\n    ++__i;\n    __t.emplace_back(__t.back() / __i);\n  }\n  return __t[__x];\n\
    }\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file factorial.hpp\n * @brief Factorial\n * @date\
    \ 2021-01-15\n *\n *\n */\n\n#include <cstdint>\n#include <functional>\n#include\
    \ <vector>\n\nnamespace workspace {\n\ntemplate <class Tp> Tp factorial(int_fast32_t\
    \ __x) noexcept {\n  if (__x < 0) return 0;\n  static std::vector<Tp> __t{1};\n\
    \  static int_fast32_t __i = (__t.reserve(0x1000000), 0);\n  while (__i < __x)\
    \ {\n    ++__i;\n    __t.emplace_back(__t.back() * __i);\n  }\n  return __t[__x];\n\
    }\n\ntemplate <class Tp> Tp factorial_inverse(int_fast32_t __x) noexcept {\n \
    \ if (__x < 0) return 0;\n  static std::vector<Tp> __t{1};\n  static int_fast32_t\
    \ __i = (__t.reserve(0x1000000), 0);\n  while (__i < __x) {\n    ++__i;\n    __t.emplace_back(__t.back()\
    \ / __i);\n  }\n  return __t[__x];\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/combinatorics/factorial.hpp
  requiredBy:
  - src/combinatorics/binomial.hpp
  timestamp: '2021-01-15 02:03:49+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aizu-online-judge/DPL_5_D.test.cpp
documentation_of: src/combinatorics/factorial.hpp
layout: document
redirect_from:
- /library/src/combinatorics/factorial.hpp
- /library/src/combinatorics/factorial.hpp.html
title: Factorial
---
