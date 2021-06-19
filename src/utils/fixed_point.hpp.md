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
    \ {\n\n/**\n * @brief Fixed Point Combinator.\n */\ntemplate <class _F> class\
    \ fixed_point {\n public:\n  // Construct a new fixed-point object.\n  fixed_point(_F\
    \ __x) noexcept : __fn(__x) {}\n\n  // Function call.\n  template <class... _Args>\
    \ decltype(auto) operator()(_Args... __args) {\n    return _wrapper{__fn}(std::forward<_Args>(__args)...);\n\
    \  }\n\n private:\n  _F __fn;\n\n  struct _wrapper {\n    _F &__ref;\n\n    template\
    \ <class... _Args> decltype(auto) operator()(_Args... __args) {\n      return\
    \ __ref(*this, std::forward<_Args>(__args)...);\n    }\n  };\n};\n\n}  // namespace\
    \ workspace\n"
  code: "#pragma once\n\n/**\n * @file fixed_point.hpp\n * @brief Fixed Point Combinator\n\
    \ */\n\n#include <map>\n\nnamespace workspace {\n\n/**\n * @brief Fixed Point\
    \ Combinator.\n */\ntemplate <class _F> class fixed_point {\n public:\n  // Construct\
    \ a new fixed-point object.\n  fixed_point(_F __x) noexcept : __fn(__x) {}\n\n\
    \  // Function call.\n  template <class... _Args> decltype(auto) operator()(_Args...\
    \ __args) {\n    return _wrapper{__fn}(std::forward<_Args>(__args)...);\n  }\n\
    \n private:\n  _F __fn;\n\n  struct _wrapper {\n    _F &__ref;\n\n    template\
    \ <class... _Args> decltype(auto) operator()(_Args... __args) {\n      return\
    \ __ref(*this, std::forward<_Args>(__args)...);\n    }\n  };\n};\n\n}  // namespace\
    \ workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/fixed_point.hpp
  requiredBy:
  - src/utils/cached.hpp
  timestamp: '2021-06-19 22:40:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/fixed_point.hpp
layout: document
redirect_from:
- /library/src/utils/fixed_point.hpp
- /library/src/utils/fixed_point.hpp.html
title: Fixed Point Combinator
---
