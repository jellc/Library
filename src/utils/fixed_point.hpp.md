---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: src/utils/cached.hpp
    title: Cached
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Fixed Point Combinator
    links: []
  bundledCode: "#line 2 \"src/utils/fixed_point.hpp\"\n\n/**\n * @file fixed_point.hpp\n\
    \ * @brief Fixed Point Combinator\n */\n\n#include <map>\n\nnamespace workspace\
    \ {\n\n/**\n * @brief Fixed Point Combinator\n */\ntemplate <class _F> class fixed_point\
    \ {\n  _F __fn;\n\n public:\n  /**\n   * @brief Construct a new fixed point object\n\
    \   *\n   * @param __fn 1st argument callable with the rest of its arguments.\n\
    \   * Return type specified.\n   */\n  fixed_point(_F __fn) noexcept : __fn(std::forward<_F>(__fn))\
    \ {}\n\n  /**\n   * @brief Apply *this to 1st argument.\n   * @param __args Rest\
    \ of arguments.\n   */\n  template <class... _Args> decltype(auto) operator()(_Args\
    \ &&...__args) const {\n    return __fn(*this, std::forward<_Args>(__args)...);\n\
    \  }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file fixed_point.hpp\n * @brief Fixed Point Combinator\n\
    \ */\n\n#include <map>\n\nnamespace workspace {\n\n/**\n * @brief Fixed Point\
    \ Combinator\n */\ntemplate <class _F> class fixed_point {\n  _F __fn;\n\n public:\n\
    \  /**\n   * @brief Construct a new fixed point object\n   *\n   * @param __fn\
    \ 1st argument callable with the rest of its arguments.\n   * Return type specified.\n\
    \   */\n  fixed_point(_F __fn) noexcept : __fn(std::forward<_F>(__fn)) {}\n\n\
    \  /**\n   * @brief Apply *this to 1st argument.\n   * @param __args Rest of arguments.\n\
    \   */\n  template <class... _Args> decltype(auto) operator()(_Args &&...__args)\
    \ const {\n    return __fn(*this, std::forward<_Args>(__args)...);\n  }\n};\n\n\
    }  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/fixed_point.hpp
  requiredBy:
  - src/utils/cached.hpp
  timestamp: '2021-05-06 07:12:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/fixed_point.hpp
layout: document
redirect_from:
- /library/src/utils/fixed_point.hpp
- /library/src/utils/fixed_point.hpp.html
title: Fixed Point Combinator
---
