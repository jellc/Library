---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"combinatorics/factorial.hpp\"\n#include <functional>\n#include\
    \ <vector>\ntemplate <class T, class Op = std::multiplies<T>>\nclass factorial\n\
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
  path: combinatorics/factorial.hpp
  requiredBy: []
  timestamp: '2020-08-16 13:02:00+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: combinatorics/factorial.hpp
layout: document
redirect_from:
- /library/combinatorics/factorial.hpp
- /library/combinatorics/factorial.hpp.html
title: combinatorics/factorial.hpp
---
