---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/ALDS1_14_B.test.cpp
    title: test/aizu-online-judge/ALDS1_14_B.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Knuth-Morris-Pratt Algorithm
    links: []
  bundledCode: "#line 1 \"src/string/kmp.hpp\"\n/**\n * @file kmp.hpp\n * @brief Knuth-Morris-Pratt\
    \ Algorithm\n * @date 2021-01-08\n */\n\n#include <vector>\n\nnamespace workspace\
    \ {\n\n/**\n * @brief Knuth-Morris-Pratt algorithm.\n *\n * @param __s A string\n\
    \ * @return The i-th element (1-indexed) describes the prefix of length i.\n */\n\
    template <class _Str> std::vector<size_t> kmp_algorithm(_Str const& __s) {\n \
    \ std::vector<size_t> __k(std::size(__s));\n  if (!__k.empty())\n    for (size_t\
    \ __p{}, __q{1}; __q != __k.size(); __k[__q++] = ++__p)\n      while (__s[__p]\
    \ != __s[__q]) {\n        if (!__p--) break;\n        __p = __k[__p];\n      }\n\
    \  return __k;\n}\n\n}  // namespace workspace\n"
  code: "/**\n * @file kmp.hpp\n * @brief Knuth-Morris-Pratt Algorithm\n * @date 2021-01-08\n\
    \ */\n\n#include <vector>\n\nnamespace workspace {\n\n/**\n * @brief Knuth-Morris-Pratt\
    \ algorithm.\n *\n * @param __s A string\n * @return The i-th element (1-indexed)\
    \ describes the prefix of length i.\n */\ntemplate <class _Str> std::vector<size_t>\
    \ kmp_algorithm(_Str const& __s) {\n  std::vector<size_t> __k(std::size(__s));\n\
    \  if (!__k.empty())\n    for (size_t __p{}, __q{1}; __q != __k.size(); __k[__q++]\
    \ = ++__p)\n      while (__s[__p] != __s[__q]) {\n        if (!__p--) break;\n\
    \        __p = __k[__p];\n      }\n  return __k;\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/string/kmp.hpp
  requiredBy: []
  timestamp: '2021-01-08 22:21:16+09:00'
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
