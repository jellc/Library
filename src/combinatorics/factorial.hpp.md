---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: src/combinatorics/binomial.hpp
    title: Binomial Coefficient
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/balls_and_boxes_4.test.cpp
    title: test/aizu-online-judge/balls_and_boxes_4.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/combinatorics/factorial.hpp\"\n#include <functional>\n\
    #include <vector>\ntemplate <class T, class Op = std::multiplies<T>>\nclass factorial\n\
    {\n    std::vector<T> fact;\n    Op op;\npublic:\n    factorial(T init = 1, Op\
    \ op = Op()) : fact{init}, op{op} {}\n    T operator()(const int &n)\n    {\n\
    \        if(n < 0) return 0;\n        for(int m(fact.size()); m <= n; ++m) fact.emplace_back(op(fact.back(),\
    \ m));\n        return fact[n];\n    }\n}; // class factorial\n"
  code: "#pragma once\n#include <functional>\n#include <vector>\ntemplate <class T,\
    \ class Op = std::multiplies<T>>\nclass factorial\n{\n    std::vector<T> fact;\n\
    \    Op op;\npublic:\n    factorial(T init = 1, Op op = Op()) : fact{init}, op{op}\
    \ {}\n    T operator()(const int &n)\n    {\n        if(n < 0) return 0;\n   \
    \     for(int m(fact.size()); m <= n; ++m) fact.emplace_back(op(fact.back(), m));\n\
    \        return fact[n];\n    }\n}; // class factorial\n"
  dependsOn: []
  isVerificationFile: false
  path: src/combinatorics/factorial.hpp
  requiredBy:
  - src/combinatorics/binomial.hpp
  timestamp: '2020-11-16 17:54:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aizu-online-judge/balls_and_boxes_4.test.cpp
documentation_of: src/combinatorics/factorial.hpp
layout: document
redirect_from:
- /library/src/combinatorics/factorial.hpp
- /library/src/combinatorics/factorial.hpp.html
title: src/combinatorics/factorial.hpp
---
