---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Change Less/Greater
    links: []
  bundledCode: "#line 2 \"utils/chval.hpp\"\n\n/*\n * @file chval.hpp\n * @brief Change\
    \ Less/Greater\n */\n\n#include <functional>\n\nnamespace workspace {\n\n/*\n\
    \ * @fn chle\n * @brief Substitute y for x if comp(y, x) is true.\n * @param x\
    \ Reference\n * @param y Const reference\n * @param comp Compare function\n *\
    \ @return Whether or not x is updated\n */\ntemplate <class Tp, class Comp = std::less<Tp>>\n\
    bool chle(Tp &x, const Tp &y, Comp comp = Comp()) {\n  return comp(y, x) ? x =\
    \ y, true : false;\n}\n\n/*\n * @fn chge\n * @brief Substitute y for x if comp(x,\
    \ y) is true.\n * @param x Reference\n * @param y Const reference\n * @param comp\
    \ Compare function\n * @return Whether or not x is updated\n */\ntemplate <class\
    \ Tp, class Comp = std::less<Tp>>\nbool chge(Tp &x, const Tp &y, Comp comp = Comp())\
    \ {\n  return comp(x, y) ? x = y, true : false;\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file chval.hpp\n * @brief Change Less/Greater\n */\n\
    \n#include <functional>\n\nnamespace workspace {\n\n/*\n * @fn chle\n * @brief\
    \ Substitute y for x if comp(y, x) is true.\n * @param x Reference\n * @param\
    \ y Const reference\n * @param comp Compare function\n * @return Whether or not\
    \ x is updated\n */\ntemplate <class Tp, class Comp = std::less<Tp>>\nbool chle(Tp\
    \ &x, const Tp &y, Comp comp = Comp()) {\n  return comp(y, x) ? x = y, true :\
    \ false;\n}\n\n/*\n * @fn chge\n * @brief Substitute y for x if comp(x, y) is\
    \ true.\n * @param x Reference\n * @param y Const reference\n * @param comp Compare\
    \ function\n * @return Whether or not x is updated\n */\ntemplate <class Tp, class\
    \ Comp = std::less<Tp>>\nbool chge(Tp &x, const Tp &y, Comp comp = Comp()) {\n\
    \  return comp(x, y) ? x = y, true : false;\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/chval.hpp
  requiredBy: []
  timestamp: '2020-11-14 01:17:16+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils/chval.hpp
layout: document
redirect_from:
- /library/utils/chval.hpp
- /library/utils/chval.hpp.html
title: Change Less/Greater
---
