---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: template.cpp
    title: Code template
  - icon: ':warning:'
    path: utils.hpp
    title: all headers in utlis
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Fixed point combinator
    links: []
  bundledCode: "#line 2 \"utils/fixed_point.hpp\"\n\n/*\n * @file fixed_point.hpp\n\
    \ * @brief Fixed point combinator\n */\n\n#include <utility>\n\nnamespace workspace\
    \ {\n\n/*\n * @class fixed_point\n * @brief recursive calling of lambda expression\n\
    \ */\ntemplate <class lambda_type> class fixed_point {\n  lambda_type func;\n\n\
    \ public:\n  /*\n   * @param func 1st arg callable with the rest of args, and\
    \ the return type\n   * specified\n   */\n  fixed_point(lambda_type &&func) :\
    \ func(std::move(func)) {}\n\n  /*\n   * @brief recursively apply *this to 1st\
    \ arg of func\n   * @param args arguments of the recursive method\n   */\n  template\
    \ <class... Args> auto operator()(Args &&... args) const {\n    return func(*this,\
    \ std::forward<Args>(args)...);\n  }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file fixed_point.hpp\n * @brief Fixed point combinator\n\
    \ */\n\n#include <utility>\n\nnamespace workspace {\n\n/*\n * @class fixed_point\n\
    \ * @brief recursive calling of lambda expression\n */\ntemplate <class lambda_type>\
    \ class fixed_point {\n  lambda_type func;\n\n public:\n  /*\n   * @param func\
    \ 1st arg callable with the rest of args, and the return type\n   * specified\n\
    \   */\n  fixed_point(lambda_type &&func) : func(std::move(func)) {}\n\n  /*\n\
    \   * @brief recursively apply *this to 1st arg of func\n   * @param args arguments\
    \ of the recursive method\n   */\n  template <class... Args> auto operator()(Args\
    \ &&... args) const {\n    return func(*this, std::forward<Args>(args)...);\n\
    \  }\n};\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/fixed_point.hpp
  requiredBy:
  - template.cpp
  - utils.hpp
  timestamp: '2020-11-07 14:25:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils/fixed_point.hpp
layout: document
redirect_from:
- /library/utils/fixed_point.hpp
- /library/utils/fixed_point.hpp.html
title: Fixed point combinator
---
