---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: template.cpp
    title: Code template
  - icon: ':warning:'
    path: utils.hpp
    title: all headers in utlis
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Change less/greater
    links: []
  bundledCode: "#line 2 \"utils/chval.hpp\"\n\n/*\n * @file chval.hpp\n * @brief Change\
    \ less/greater\n */\n\n#include <functional>\n\nnamespace workspace {\n\n/*\n\
    \ * @fn chle\n * @brief substitute y for x if comp(y, x) is true\n * @param x\
    \ reference\n * @param y const reference\n * @param comp compare function\n *\
    \ @return whether or not x is updated\n */\ntemplate <class Tp, class Comp = std::less<Tp>>\n\
    bool chle(Tp &x, const Tp &y, Comp comp = Comp()) {\n  return comp(y, x) ? x =\
    \ y, true : false;\n}\n\n/*\n * @fn chge\n * @brief substitute y for x if comp(x,\
    \ y) is true\n * @param x reference\n * @param y const reference\n * @param comp\
    \ compare function\n * @return whether or not x is updated\n */\ntemplate <class\
    \ Tp, class Comp = std::less<Tp>>\nbool chge(Tp &x, const Tp &y, Comp comp = Comp())\
    \ {\n  return comp(x, y) ? x = y, true : false;\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file chval.hpp\n * @brief Change less/greater\n */\n\
    \n#include <functional>\n\nnamespace workspace {\n\n/*\n * @fn chle\n * @brief\
    \ substitute y for x if comp(y, x) is true\n * @param x reference\n * @param y\
    \ const reference\n * @param comp compare function\n * @return whether or not\
    \ x is updated\n */\ntemplate <class Tp, class Comp = std::less<Tp>>\nbool chle(Tp\
    \ &x, const Tp &y, Comp comp = Comp()) {\n  return comp(y, x) ? x = y, true :\
    \ false;\n}\n\n/*\n * @fn chge\n * @brief substitute y for x if comp(x, y) is\
    \ true\n * @param x reference\n * @param y const reference\n * @param comp compare\
    \ function\n * @return whether or not x is updated\n */\ntemplate <class Tp, class\
    \ Comp = std::less<Tp>>\nbool chge(Tp &x, const Tp &y, Comp comp = Comp()) {\n\
    \  return comp(x, y) ? x = y, true : false;\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/chval.hpp
  requiredBy:
  - template.cpp
  - utils.hpp
  timestamp: '2020-11-07 14:25:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils/chval.hpp
layout: document
redirect_from:
- /library/utils/chval.hpp
- /library/utils/chval.hpp.html
title: Change less/greater
---
