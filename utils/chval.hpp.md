---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: utils.hpp
    title: utils.hpp
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: '#line 2 "utils/chval.hpp"

    #include <functional>

    namespace workspace {

    template <class T, class Comp = std::less<T>> bool chle(T &x, const T &y, Comp
    comp = Comp()) { return comp(y, x) ? x = y, true : false; }

    template <class T, class Comp = std::less<T>> bool chge(T &x, const T &y, Comp
    comp = Comp()) { return comp(x, y) ? x = y, true : false; }

    } // namespace workspace

    '
  code: '#pragma once

    #include <functional>

    namespace workspace {

    template <class T, class Comp = std::less<T>> bool chle(T &x, const T &y, Comp
    comp = Comp()) { return comp(y, x) ? x = y, true : false; }

    template <class T, class Comp = std::less<T>> bool chge(T &x, const T &y, Comp
    comp = Comp()) { return comp(x, y) ? x = y, true : false; }

    } // namespace workspace

    '
  dependsOn: []
  isVerificationFile: false
  path: utils/chval.hpp
  requiredBy:
  - utils.hpp
  timestamp: '2020-08-14 18:02:25+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils/chval.hpp
layout: document
redirect_from:
- /library/utils/chval.hpp
- /library/utils/chval.hpp.html
title: utils/chval.hpp
---
