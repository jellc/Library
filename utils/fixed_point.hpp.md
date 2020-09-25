---
data:
  _extendedDependsOn: []
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
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 2 \"utils/fixed_point.hpp\"\n#include <utility>\nnamespace workspace\
    \ {\n// specify the return type of lambda.\ntemplate <class lambda_type> class\
    \ fixed_point {\n  lambda_type func;\n\n public:\n  fixed_point(lambda_type &&f)\
    \ : func(std::move(f)) {}\n  template <class... Args> auto operator()(Args &&...\
    \ args) const {\n    return func(*this, std::forward<Args>(args)...);\n  }\n};\n\
    }  // namespace workspace\n"
  code: "#pragma once\n#include <utility>\nnamespace workspace {\n// specify the return\
    \ type of lambda.\ntemplate <class lambda_type> class fixed_point {\n  lambda_type\
    \ func;\n\n public:\n  fixed_point(lambda_type &&f) : func(std::move(f)) {}\n\
    \  template <class... Args> auto operator()(Args &&... args) const {\n    return\
    \ func(*this, std::forward<Args>(args)...);\n  }\n};\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/fixed_point.hpp
  requiredBy:
  - template.cpp
  - utils.hpp
  timestamp: '2020-09-21 04:06:55+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils/fixed_point.hpp
layout: document
redirect_from:
- /library/utils/fixed_point.hpp
- /library/utils/fixed_point.hpp.html
title: utils/fixed_point.hpp
---
