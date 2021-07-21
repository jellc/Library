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
    \ * @brief Factorial\n */\n\n#include <vector>\n\nnamespace workspace {\n\n//\
    \ Factorial\ntemplate <class _Tp, class _X> _Tp factorial(_X __x) noexcept {\n\
    \  if (__x < 0) return 0;\n  static std::vector<_Tp> __t{1};\n  static size_t\
    \ __i = (__t.reserve(0x1000000), 0);\n  while (__i < size_t(__x)) __t.emplace_back(__t.back()\
    \ * _Tp(++__i));\n  return __t[__x];\n}\n\n// Inverse of factorial\ntemplate <class\
    \ _Tp, class _X> _Tp inverse_factorial(_X __x) noexcept {\n  if (__x < 0) return\
    \ 0;\n  static std::vector<_Tp> __t{1};\n  static size_t __i = (__t.reserve(0x1000000),\
    \ 0);\n  while (__i < size_t(__x)) __t.emplace_back(__t.back() / _Tp(++__i));\n\
    \  return __t[__x];\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file factorial.hpp\n * @brief Factorial\n */\n\n\
    #include <vector>\n\nnamespace workspace {\n\n// Factorial\ntemplate <class _Tp,\
    \ class _X> _Tp factorial(_X __x) noexcept {\n  if (__x < 0) return 0;\n  static\
    \ std::vector<_Tp> __t{1};\n  static size_t __i = (__t.reserve(0x1000000), 0);\n\
    \  while (__i < size_t(__x)) __t.emplace_back(__t.back() * _Tp(++__i));\n  return\
    \ __t[__x];\n}\n\n// Inverse of factorial\ntemplate <class _Tp, class _X> _Tp\
    \ inverse_factorial(_X __x) noexcept {\n  if (__x < 0) return 0;\n  static std::vector<_Tp>\
    \ __t{1};\n  static size_t __i = (__t.reserve(0x1000000), 0);\n  while (__i <\
    \ size_t(__x)) __t.emplace_back(__t.back() / _Tp(++__i));\n  return __t[__x];\n\
    }\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/combinatorics/factorial.hpp
  requiredBy:
  - src/combinatorics/binomial.hpp
  timestamp: '2021-07-22 00:37:02+09:00'
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
