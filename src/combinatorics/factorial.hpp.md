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
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Factorial
    links: []
  bundledCode: "#line 2 \"src/combinatorics/factorial.hpp\"\n\n/*\n * @brief Factorial\n\
    \ */\n\n#include <functional>\n#include <vector>\n\nnamespace workspace {\n\n\
    template <class Tp, class Op = std::multiplies<Tp>> class factorial {\n  std::vector<Tp>\
    \ fact;\n  Op op;\n\n public:\n  factorial(Tp init = 1, Op op = Op()) : fact{init},\
    \ op{op} {}\n\n  Tp operator()(int_least32_t n) {\n    if (n < 0) return 0;\n\
    \    for (int_least32_t m(fact.size()); m <= n; ++m)\n      fact.emplace_back(op(fact.back(),\
    \ m));\n    return fact[n];\n  }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @brief Factorial\n */\n\n#include <functional>\n#include\
    \ <vector>\n\nnamespace workspace {\n\ntemplate <class Tp, class Op = std::multiplies<Tp>>\
    \ class factorial {\n  std::vector<Tp> fact;\n  Op op;\n\n public:\n  factorial(Tp\
    \ init = 1, Op op = Op()) : fact{init}, op{op} {}\n\n  Tp operator()(int_least32_t\
    \ n) {\n    if (n < 0) return 0;\n    for (int_least32_t m(fact.size()); m <=\
    \ n; ++m)\n      fact.emplace_back(op(fact.back(), m));\n    return fact[n];\n\
    \  }\n};\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/combinatorics/factorial.hpp
  requiredBy:
  - src/combinatorics/binomial.hpp
  timestamp: '2020-12-08 19:06:53+09:00'
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
