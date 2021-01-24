---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Trinary Search
    links: []
  bundledCode: "#line 2 \"src/opt/trinary_search.hpp\"\n\n/*\n * @file trinary_search.hpp\n\
    \ * @brief Trinary Search\n */\n\n#include <cassert>\n#include <type_traits>\n\
    \nnamespace workspace {\n\n/*\n * @brief Trinary search on discrete range.\n *\
    \ @param first Left end, inclusive\n * @param last Right end, exclusive\n * @param\
    \ comp Compare function\n * @return Local minimal point.\n */\ntemplate <class\
    \ Iter, class Comp>\ntypename std::enable_if<\n    std::is_convertible<decltype(std::declval<Comp>()(std::declval<Iter>(),\n\
    \                                                      std::declval<Iter>())),\n\
    \                        bool>::value,\n    Iter>::type\ntrinary_search(Iter first,\
    \ Iter last, Comp comp) {\n  assert(first < last);\n  typename std::make_signed<decltype(last\
    \ - first)>::type dist(last - first);\n  while (2 < dist) {\n    Iter left(first\
    \ + dist / 3), right(first + dist * 2 / 3);\n    if (comp(left, right))\n    \
    \  last = right, dist = (dist + dist) / 3;\n    else\n      first = left, dist\
    \ -= dist / 3;\n  }\n  if (1 < dist && comp(first + 1, first)) ++first;\n  return\
    \ first;\n}\n\n/*\n * @brief Trinary search on discrete range.\n * @param first\
    \ Left end, inclusive\n * @param last Right end, exclusive\n * @param func Function\n\
    \ * @return Local minimal point.\n */\ntemplate <class Iter, class Func>\ntypename\
    \ std::enable_if<\n    std::is_same<decltype(std::declval<Func>()(std::declval<Iter>()),\
    \ nullptr),\n                 std::nullptr_t>::value,\n    Iter>::type\ntrinary_search(Iter\
    \ const &first, Iter const &last, Func func) {\n  return trinary_search(first,\
    \ last, [&](Iter const &__i, Iter const &__j) {\n    return func(__i) < func(__j);\n\
    \  });\n}\n\n/*\n * @brief Trinary search on the real number line.\n * @param\
    \ first Left end\n * @param last Right end\n * @param eps Error tolerance\n *\
    \ @param comp Compare function\n * @return Local minimal point.\n */\ntemplate\
    \ <class Real, class Comp>\ntypename std::enable_if<\n    std::is_convertible<decltype(std::declval<Comp>()(std::declval<Real>(),\n\
    \                                                      std::declval<Real>())),\n\
    \                        bool>::value,\n    Real>::type\ntrinary_search(Real first,\
    \ Real last, Real const &eps, Comp comp) {\n  assert(first < last);\n  while (eps\
    \ < last - first) {\n    Real left{(first * 2 + last) / 3}, right{(first + last\
    \ * 2) / 3};\n    if (comp(left, right))\n      last = right;\n    else\n    \
    \  first = left;\n  }\n  return first;\n}\n\n/*\n * @brief Trinary search on the\
    \ real number line.\n * @param first Left end\n * @param last Right end\n * @param\
    \ eps Error tolerance\n * @param func Function\n * @return Local minimal point.\n\
    \ */\ntemplate <class Real, class Func>\ntypename std::enable_if<\n    std::is_same<decltype(std::declval<Func>()(std::declval<Real>()),\
    \ nullptr),\n                 std::nullptr_t>::value,\n    Real>::type\ntrinary_search(Real\
    \ const &first, Real const &last, Real const &eps,\n               Func func)\
    \ {\n  return trinary_search(\n      first, last, eps,\n      [&](Real const &__i,\
    \ Real const &__j) { return func(__i) < func(__j); });\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file trinary_search.hpp\n * @brief Trinary Search\n\
    \ */\n\n#include <cassert>\n#include <type_traits>\n\nnamespace workspace {\n\n\
    /*\n * @brief Trinary search on discrete range.\n * @param first Left end, inclusive\n\
    \ * @param last Right end, exclusive\n * @param comp Compare function\n * @return\
    \ Local minimal point.\n */\ntemplate <class Iter, class Comp>\ntypename std::enable_if<\n\
    \    std::is_convertible<decltype(std::declval<Comp>()(std::declval<Iter>(),\n\
    \                                                      std::declval<Iter>())),\n\
    \                        bool>::value,\n    Iter>::type\ntrinary_search(Iter first,\
    \ Iter last, Comp comp) {\n  assert(first < last);\n  typename std::make_signed<decltype(last\
    \ - first)>::type dist(last - first);\n  while (2 < dist) {\n    Iter left(first\
    \ + dist / 3), right(first + dist * 2 / 3);\n    if (comp(left, right))\n    \
    \  last = right, dist = (dist + dist) / 3;\n    else\n      first = left, dist\
    \ -= dist / 3;\n  }\n  if (1 < dist && comp(first + 1, first)) ++first;\n  return\
    \ first;\n}\n\n/*\n * @brief Trinary search on discrete range.\n * @param first\
    \ Left end, inclusive\n * @param last Right end, exclusive\n * @param func Function\n\
    \ * @return Local minimal point.\n */\ntemplate <class Iter, class Func>\ntypename\
    \ std::enable_if<\n    std::is_same<decltype(std::declval<Func>()(std::declval<Iter>()),\
    \ nullptr),\n                 std::nullptr_t>::value,\n    Iter>::type\ntrinary_search(Iter\
    \ const &first, Iter const &last, Func func) {\n  return trinary_search(first,\
    \ last, [&](Iter const &__i, Iter const &__j) {\n    return func(__i) < func(__j);\n\
    \  });\n}\n\n/*\n * @brief Trinary search on the real number line.\n * @param\
    \ first Left end\n * @param last Right end\n * @param eps Error tolerance\n *\
    \ @param comp Compare function\n * @return Local minimal point.\n */\ntemplate\
    \ <class Real, class Comp>\ntypename std::enable_if<\n    std::is_convertible<decltype(std::declval<Comp>()(std::declval<Real>(),\n\
    \                                                      std::declval<Real>())),\n\
    \                        bool>::value,\n    Real>::type\ntrinary_search(Real first,\
    \ Real last, Real const &eps, Comp comp) {\n  assert(first < last);\n  while (eps\
    \ < last - first) {\n    Real left{(first * 2 + last) / 3}, right{(first + last\
    \ * 2) / 3};\n    if (comp(left, right))\n      last = right;\n    else\n    \
    \  first = left;\n  }\n  return first;\n}\n\n/*\n * @brief Trinary search on the\
    \ real number line.\n * @param first Left end\n * @param last Right end\n * @param\
    \ eps Error tolerance\n * @param func Function\n * @return Local minimal point.\n\
    \ */\ntemplate <class Real, class Func>\ntypename std::enable_if<\n    std::is_same<decltype(std::declval<Func>()(std::declval<Real>()),\
    \ nullptr),\n                 std::nullptr_t>::value,\n    Real>::type\ntrinary_search(Real\
    \ const &first, Real const &last, Real const &eps,\n               Func func)\
    \ {\n  return trinary_search(\n      first, last, eps,\n      [&](Real const &__i,\
    \ Real const &__j) { return func(__i) < func(__j); });\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/opt/trinary_search.hpp
  requiredBy: []
  timestamp: '2020-12-08 15:31:04+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/opt/trinary_search.hpp
layout: document
redirect_from:
- /library/src/opt/trinary_search.hpp
- /library/src/opt/trinary_search.hpp.html
title: Trinary Search
---
