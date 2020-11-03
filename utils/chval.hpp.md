---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utils/chval.hpp\"\n#include <functional>\nnamespace workspace\
    \ {\ntemplate <class T, class Comp = std::less<T>>\nbool chle(T &x, const T &y,\
    \ Comp comp = Comp()) {\n  return comp(y, x) ? x = y, true : false;\n}\ntemplate\
    \ <class T, class Comp = std::less<T>>\nbool chge(T &x, const T &y, Comp comp\
    \ = Comp()) {\n  return comp(x, y) ? x = y, true : false;\n}\n}  // namespace\
    \ workspace\n"
  code: "#pragma once\n#include <functional>\nnamespace workspace {\ntemplate <class\
    \ T, class Comp = std::less<T>>\nbool chle(T &x, const T &y, Comp comp = Comp())\
    \ {\n  return comp(y, x) ? x = y, true : false;\n}\ntemplate <class T, class Comp\
    \ = std::less<T>>\nbool chge(T &x, const T &y, Comp comp = Comp()) {\n  return\
    \ comp(x, y) ? x = y, true : false;\n}\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/chval.hpp
  requiredBy: []
  timestamp: '2020-09-27 13:39:20+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils/chval.hpp
layout: document
redirect_from:
- /library/utils/chval.hpp
- /library/utils/chval.hpp.html
title: utils/chval.hpp
---
