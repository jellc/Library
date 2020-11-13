---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Fixed Point Combinator
    links: []
  bundledCode: "#line 2 \"utils/fixed_point.hpp\"\n\n/*\n * @file fixed_point.hpp\n\
    \ * @brief Fixed Point Combinator\n */\n\n#include <utility>\n\nnamespace workspace\
    \ {\n\n/*\n * @class fixed_point\n * @brief Recursive calling of lambda expression.\n\
    \ */\ntemplate <class lambda_type> class fixed_point {\n  lambda_type func;\n\n\
    \ public:\n  /*\n   * @param func 1st arg callable with the rest of args, and\
    \ the return type\n   * specified.\n   */\n  fixed_point(lambda_type &&func) :\
    \ func(std::move(func)) {}\n\n  /*\n   * @brief Recursively apply *this to 1st\
    \ arg of func.\n   * @param args Arguments of the recursive method.\n   */\n \
    \ template <class... Args> auto operator()(Args &&... args) const {\n    return\
    \ func(*this, std::forward<Args>(args)...);\n  }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file fixed_point.hpp\n * @brief Fixed Point Combinator\n\
    \ */\n\n#include <utility>\n\nnamespace workspace {\n\n/*\n * @class fixed_point\n\
    \ * @brief Recursive calling of lambda expression.\n */\ntemplate <class lambda_type>\
    \ class fixed_point {\n  lambda_type func;\n\n public:\n  /*\n   * @param func\
    \ 1st arg callable with the rest of args, and the return type\n   * specified.\n\
    \   */\n  fixed_point(lambda_type &&func) : func(std::move(func)) {}\n\n  /*\n\
    \   * @brief Recursively apply *this to 1st arg of func.\n   * @param args Arguments\
    \ of the recursive method.\n   */\n  template <class... Args> auto operator()(Args\
    \ &&... args) const {\n    return func(*this, std::forward<Args>(args)...);\n\
    \  }\n};\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/fixed_point.hpp
  requiredBy: []
  timestamp: '2020-11-14 01:17:16+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils/fixed_point.hpp
layout: document
redirect_from:
- /library/utils/fixed_point.hpp
- /library/utils/fixed_point.hpp.html
title: Fixed Point Combinator
---
