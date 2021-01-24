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
  bundledCode: "#line 1 \"src/string/kmp.hpp\"\n/**\n * @file kmp.hpp\n * @brief Knuth-Morris-Pratt\
    \ Algorithm\n * @date 2021-01-08\n */\n\n#include <vector>\n\nnamespace workspace\
    \ {\n\n/**\n * @brief Morris-Pratt algorithm.\n *\n * @param __s String\n * @return\
    \ The border array of given string.\n */\ntemplate <class _Str> std::vector<size_t>\
    \ mp_algorithm(_Str const& __s) {\n  std::vector<size_t> __b(std::size(__s) +\
    \ 1);\n  for (size_t __p{__b[0] = -1}, __q{}; __q != __s.size(); __b[++__q] =\
    \ ++__p)\n    while (~__p && __s[__p] != __s[__q]) __p = __b[__p];\n  return __b;\n\
    }\n\n/**\n * @brief Knuth-Morris-Pratt algorithm.\n *\n * @param __s String\n\
    \ * @return The strong-border array of given string.\n */\ntemplate <class _Str>\
    \ std::vector<size_t> kmp_algorithm(_Str const& __s) {\n  auto __b = mp_algorithm(__s);\n\
    \  for (size_t __i{1}; __i != __s.size(); ++__i)\n    if (__s[__i] == __s[__b[__i]])\
    \ __b[__i] = __b[__b[__i]];\n  return __b;\n}\n\n}  // namespace workspace\n"
  code: "/**\n * @file kmp.hpp\n * @brief Knuth-Morris-Pratt Algorithm\n * @date 2021-01-08\n\
    \ */\n\n#include <vector>\n\nnamespace workspace {\n\n/**\n * @brief Morris-Pratt\
    \ algorithm.\n *\n * @param __s String\n * @return The border array of given string.\n\
    \ */\ntemplate <class _Str> std::vector<size_t> mp_algorithm(_Str const& __s)\
    \ {\n  std::vector<size_t> __b(std::size(__s) + 1);\n  for (size_t __p{__b[0]\
    \ = -1}, __q{}; __q != __s.size(); __b[++__q] = ++__p)\n    while (~__p && __s[__p]\
    \ != __s[__q]) __p = __b[__p];\n  return __b;\n}\n\n/**\n * @brief Knuth-Morris-Pratt\
    \ algorithm.\n *\n * @param __s String\n * @return The strong-border array of\
    \ given string.\n */\ntemplate <class _Str> std::vector<size_t> kmp_algorithm(_Str\
    \ const& __s) {\n  auto __b = mp_algorithm(__s);\n  for (size_t __i{1}; __i !=\
    \ __s.size(); ++__i)\n    if (__s[__i] == __s[__b[__i]]) __b[__i] = __b[__b[__i]];\n\
    \  return __b;\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/string/kmp.hpp
  requiredBy: []
  timestamp: '2021-01-11 15:54:41+09:00'
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
