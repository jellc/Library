---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/zalgorithm.test.cpp
    title: test/library-checker/zalgorithm.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Z-Algorithm
    links: []
  bundledCode: "#line 2 \"src/string/z_algorithm.hpp\"\n\n/**\n * @file z_algorithm.hpp\n\
    \ * @brief Z-Algorithm\n * @date 2021-01-08\n */\n\n#include <string>\n#include\
    \ <vector>\n\nnamespace workspace {\n\n/**\n * @brief Construct Z-array in linear\
    \ time.\n * @param __s A string\n * @return The i-th element (0-indexed) is the\
    \ length of the Longest Common\n * Prefix between __s and __s[i:].\n */\ntemplate\
    \ <class _Str> std::vector<size_t> z_algorithm(_Str const &__s) {\n  std::vector<size_t>\
    \ __z(__s.size());\n  if (!__z.empty()) {\n    for (size_t __i{1}, __j{0}; __i\
    \ != __s.size(); ++__i) {\n      if (__z[__i - __j] + __i < __z[__j] + __j) {\n\
    \        __z[__i] = __z[__i - __j];\n      } else {\n        size_t __k{__z[__j]\
    \ + __j > __i ? __z[__j] + __j - __i : 0};\n        while (__k + __i < __s.size()\
    \ && __s[__k] == __s[__k + __i]) ++__k;\n        __z[__i] = __k;\n        __j\
    \ = __i;\n      }\n    }\n    __z.front() = __s.size();\n  }\n  return __z;\n\
    }\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file z_algorithm.hpp\n * @brief Z-Algorithm\n *\
    \ @date 2021-01-08\n */\n\n#include <string>\n#include <vector>\n\nnamespace workspace\
    \ {\n\n/**\n * @brief Construct Z-array in linear time.\n * @param __s A string\n\
    \ * @return The i-th element (0-indexed) is the length of the Longest Common\n\
    \ * Prefix between __s and __s[i:].\n */\ntemplate <class _Str> std::vector<size_t>\
    \ z_algorithm(_Str const &__s) {\n  std::vector<size_t> __z(__s.size());\n  if\
    \ (!__z.empty()) {\n    for (size_t __i{1}, __j{0}; __i != __s.size(); ++__i)\
    \ {\n      if (__z[__i - __j] + __i < __z[__j] + __j) {\n        __z[__i] = __z[__i\
    \ - __j];\n      } else {\n        size_t __k{__z[__j] + __j > __i ? __z[__j]\
    \ + __j - __i : 0};\n        while (__k + __i < __s.size() && __s[__k] == __s[__k\
    \ + __i]) ++__k;\n        __z[__i] = __k;\n        __j = __i;\n      }\n    }\n\
    \    __z.front() = __s.size();\n  }\n  return __z;\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/string/z_algorithm.hpp
  requiredBy: []
  timestamp: '2021-01-08 22:31:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/zalgorithm.test.cpp
documentation_of: src/string/z_algorithm.hpp
layout: document
redirect_from:
- /library/src/string/z_algorithm.hpp
- /library/src/string/z_algorithm.hpp.html
title: Z-Algorithm
---
