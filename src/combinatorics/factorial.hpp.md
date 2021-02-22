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
    \ * @brief Factorial\n * @date 2021-01-15\n *\n *\n */\n\n#include <vector>\n\n\
    namespace workspace {\n\ntemplate <class _Tp> _Tp factorial(int32_t __x) noexcept\
    \ {\n  if (__x < 0) return 0;\n\n  static std::vector<_Tp> __t{1};\n  static int32_t\
    \ __i = (__t.reserve(0x1000000), 0);\n\n  while (__i < __x) {\n    ++__i;\n  \
    \  __t.emplace_back(__t.back() * _Tp(__i));\n  }\n\n  return __t[__x];\n}\n\n\
    template <class _Tp> _Tp factorial_inverse(int32_t __x) noexcept {\n  if (__x\
    \ < 0) return 0;\n\n  static std::vector<_Tp> __t{1};\n  static int32_t __i =\
    \ (__t.reserve(0x1000000), 0);\n\n  while (__i < __x) {\n    ++__i;\n    __t.emplace_back(__t.back()\
    \ / _Tp(__i));\n  }\n\n  return __t[__x];\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file factorial.hpp\n * @brief Factorial\n * @date\
    \ 2021-01-15\n *\n *\n */\n\n#include <vector>\n\nnamespace workspace {\n\ntemplate\
    \ <class _Tp> _Tp factorial(int32_t __x) noexcept {\n  if (__x < 0) return 0;\n\
    \n  static std::vector<_Tp> __t{1};\n  static int32_t __i = (__t.reserve(0x1000000),\
    \ 0);\n\n  while (__i < __x) {\n    ++__i;\n    __t.emplace_back(__t.back() *\
    \ _Tp(__i));\n  }\n\n  return __t[__x];\n}\n\ntemplate <class _Tp> _Tp factorial_inverse(int32_t\
    \ __x) noexcept {\n  if (__x < 0) return 0;\n\n  static std::vector<_Tp> __t{1};\n\
    \  static int32_t __i = (__t.reserve(0x1000000), 0);\n\n  while (__i < __x) {\n\
    \    ++__i;\n    __t.emplace_back(__t.back() / _Tp(__i));\n  }\n\n  return __t[__x];\n\
    }\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/combinatorics/factorial.hpp
  requiredBy:
  - src/combinatorics/binomial.hpp
  timestamp: '2021-02-22 17:01:40+09:00'
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
