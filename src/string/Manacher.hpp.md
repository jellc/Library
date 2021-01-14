---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/2934.test.cpp
    title: test/aizu-online-judge/2934.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Manacher's Algorithm
    links: []
  bundledCode: "#line 2 \"src/string/Manacher.hpp\"\n\n/**\n * @file Manacher.hpp\n\
    \ * @brief Manacher's Algorithm\n */\n\n#include <vector>\n\nnamespace workspace\
    \ {\n\n/**\n * @brief Manacher's Algorithm.\n *\n * @param __s String\n * @return\
    \ Radiuses of the longest palindromic substring with each fixed center.\n */\n\
    template <class _Str> std::vector<size_t> Manacher(_Str const &__s) {\n  const\
    \ auto __n = std::size(__s);\n  std::vector<size_t> __r(__n);\n  for (size_t __i\
    \ = 0, __c = 0; __i != __n; ++__i)\n    if (auto __j = __c * 2 - __i; __j < __n\
    \ && __c + __r[__c] > __i + __r[__j])\n      __r[__i] = __r[__j];\n    else {\n\
    \      __j = __c + __r[__c] - __i;\n      while (__i >= __j && __i + __j != __n\
    \ && __s[__i - __j] == __s[__i + __j])\n        ++__j;\n      __r[__c = __i] =\
    \ __j;\n    }\n  return __r;\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file Manacher.hpp\n * @brief Manacher's Algorithm\n\
    \ */\n\n#include <vector>\n\nnamespace workspace {\n\n/**\n * @brief Manacher's\
    \ Algorithm.\n *\n * @param __s String\n * @return Radiuses of the longest palindromic\
    \ substring with each fixed center.\n */\ntemplate <class _Str> std::vector<size_t>\
    \ Manacher(_Str const &__s) {\n  const auto __n = std::size(__s);\n  std::vector<size_t>\
    \ __r(__n);\n  for (size_t __i = 0, __c = 0; __i != __n; ++__i)\n    if (auto\
    \ __j = __c * 2 - __i; __j < __n && __c + __r[__c] > __i + __r[__j])\n      __r[__i]\
    \ = __r[__j];\n    else {\n      __j = __c + __r[__c] - __i;\n      while (__i\
    \ >= __j && __i + __j != __n && __s[__i - __j] == __s[__i + __j])\n        ++__j;\n\
    \      __r[__c = __i] = __j;\n    }\n  return __r;\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/string/Manacher.hpp
  requiredBy: []
  timestamp: '2021-01-15 02:34:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aizu-online-judge/2934.test.cpp
documentation_of: src/string/Manacher.hpp
layout: document
redirect_from:
- /library/src/string/Manacher.hpp
- /library/src/string/Manacher.hpp.html
title: Manacher's Algorithm
---
