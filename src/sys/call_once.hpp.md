---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Call Once
    links: []
  bundledCode: "#line 2 \"src/sys/call_once.hpp\"\n\n/**\n * @file call_once.hpp\n\
    \ * @brief Call Once\n */\n\n#include <unordered_set>\n\nnamespace workspace {\n\
    \n/**\n * @brief Call once.\n */\ntemplate <class _F> void call_once(_F &&__f)\
    \ {\n  static std::unordered_set<void *> __called;\n  if (__called.count(std::addressof(__f)))\
    \ return;\n  __called.emplace(std::addressof(__f));\n  __f();\n}\n\n}  // namespace\
    \ workspace\n"
  code: "#pragma once\n\n/**\n * @file call_once.hpp\n * @brief Call Once\n */\n\n\
    #include <unordered_set>\n\nnamespace workspace {\n\n/**\n * @brief Call once.\n\
    \ */\ntemplate <class _F> void call_once(_F &&__f) {\n  static std::unordered_set<void\
    \ *> __called;\n  if (__called.count(std::addressof(__f))) return;\n  __called.emplace(std::addressof(__f));\n\
    \  __f();\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/sys/call_once.hpp
  requiredBy: []
  timestamp: '2021-05-16 13:37:12+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/sys/call_once.hpp
layout: document
redirect_from:
- /library/src/sys/call_once.hpp
- /library/src/sys/call_once.hpp.html
title: Call Once
---
