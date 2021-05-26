---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/ALDS1_14_B.test.cpp
    title: test/aizu-online-judge/ALDS1_14_B.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Knuth-Morris-Pratt Algorithm
    links: []
  bundledCode: "#line 2 \"src/string/kmp.hpp\"\n\n/**\n * @file kmp.hpp\n * @brief\
    \ Knuth-Morris-Pratt Algorithm\n */\n\n#include <vector>\n\nnamespace workspace\
    \ {\n\n/**\n * @brief Morris-Pratt algorithm.\n *\n * @param __s String\n * @return\
    \ Border array of given string.\n */\ntemplate <class _String> auto mp_algorithm(const\
    \ _String& __s) {\n  std::vector<size_t> __b(__s.size() + 1);\n  for (size_t __p{__b[0]\
    \ = -1}, __q{}; __q != __s.size(); __b[++__q] = ++__p)\n    while (~__p && __s[__p]\
    \ != __s[__q]) __p = __b[__p];\n  return __b;\n}\n\n/**\n * @brief Knuth-Morris-Pratt\
    \ algorithm.\n *\n * @param __s String\n * @return Strong-border array of given\
    \ string.\n */\ntemplate <class _String> auto kmp_algorithm(const _String& __s)\
    \ {\n  auto __b = mp_algorithm(__s);\n  for (size_t __i{1}; __i != __s.size();\
    \ ++__i)\n    if (__s[__i] == __s[__b[__i]]) __b[__i] = __b[__b[__i]];\n  return\
    \ __b;\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file kmp.hpp\n * @brief Knuth-Morris-Pratt Algorithm\n\
    \ */\n\n#include <vector>\n\nnamespace workspace {\n\n/**\n * @brief Morris-Pratt\
    \ algorithm.\n *\n * @param __s String\n * @return Border array of given string.\n\
    \ */\ntemplate <class _String> auto mp_algorithm(const _String& __s) {\n  std::vector<size_t>\
    \ __b(__s.size() + 1);\n  for (size_t __p{__b[0] = -1}, __q{}; __q != __s.size();\
    \ __b[++__q] = ++__p)\n    while (~__p && __s[__p] != __s[__q]) __p = __b[__p];\n\
    \  return __b;\n}\n\n/**\n * @brief Knuth-Morris-Pratt algorithm.\n *\n * @param\
    \ __s String\n * @return Strong-border array of given string.\n */\ntemplate <class\
    \ _String> auto kmp_algorithm(const _String& __s) {\n  auto __b = mp_algorithm(__s);\n\
    \  for (size_t __i{1}; __i != __s.size(); ++__i)\n    if (__s[__i] == __s[__b[__i]])\
    \ __b[__i] = __b[__b[__i]];\n  return __b;\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/string/kmp.hpp
  requiredBy: []
  timestamp: '2021-05-27 01:59:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aizu-online-judge/ALDS1_14_B.test.cpp
documentation_of: src/string/kmp.hpp
layout: document
redirect_from:
- /library/src/string/kmp.hpp
- /library/src/string/kmp.hpp.html
title: Knuth-Morris-Pratt Algorithm
---
