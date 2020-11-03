---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: template.cpp
    title: template.cpp
  - icon: ':warning:'
    path: utils.hpp
    title: utils.hpp
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: substitute y for x if comp(y, x) is true
    links: []
  bundledCode: "#line 2 \"utils/chval.hpp\"\n#include <functional>\nnamespace workspace\
    \ {\n\n/*\n * @fn chle\n * @brief substitute y for x if comp(y, x) is true\n *\
    \ @param x reference\n * @param y const reference\n * @param comp compare function\n\
    \ * @return whether or not x is updated\n */\ntemplate <class Tp, class Comp =\
    \ std::less<Tp>>\nbool chle(Tp &x, const Tp &y, Comp comp = Comp()) {\n  return\
    \ comp(y, x) ? x = y, true : false;\n}\n\n/*\n * @fn chge\n * @brief substitute\
    \ y for x if comp(x, y) is true\n * @param x reference\n * @param y const reference\n\
    \ * @param comp compare function\n * @return whether or not x is updated\n */\n\
    template <class Tp, class Comp = std::less<Tp>>\nbool chge(Tp &x, const Tp &y,\
    \ Comp comp = Comp()) {\n  return comp(x, y) ? x = y, true : false;\n}\n\n}  //\
    \ namespace workspace\n"
  code: "#pragma once\n#include <functional>\nnamespace workspace {\n\n/*\n * @fn\
    \ chle\n * @brief substitute y for x if comp(y, x) is true\n * @param x reference\n\
    \ * @param y const reference\n * @param comp compare function\n * @return whether\
    \ or not x is updated\n */\ntemplate <class Tp, class Comp = std::less<Tp>>\n\
    bool chle(Tp &x, const Tp &y, Comp comp = Comp()) {\n  return comp(y, x) ? x =\
    \ y, true : false;\n}\n\n/*\n * @fn chge\n * @brief substitute y for x if comp(x,\
    \ y) is true\n * @param x reference\n * @param y const reference\n * @param comp\
    \ compare function\n * @return whether or not x is updated\n */\ntemplate <class\
    \ Tp, class Comp = std::less<Tp>>\nbool chge(Tp &x, const Tp &y, Comp comp = Comp())\
    \ {\n  return comp(x, y) ? x = y, true : false;\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/chval.hpp
  requiredBy:
  - template.cpp
  - utils.hpp
  timestamp: '2020-11-03 23:01:02+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils/chval.hpp
layout: document
redirect_from:
- /library/utils/chval.hpp
- /library/utils/chval.hpp.html
title: substitute y for x if comp(y, x) is true
---
