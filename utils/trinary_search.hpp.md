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
    links: []
  bundledCode: "#line 2 \"utils/trinary_search.hpp\"\n#include <cassert>\n#include\
    \ <cstdint>\n// trinary search on discrete range.\ntemplate <class iter_type,\
    \ class comp_type>\niter_type trinary(iter_type first, iter_type last, comp_type\
    \ comp)\n{\n    assert(first < last);\n    intmax_t dist(last - first);\n    while(dist\
    \ > 2)\n    {\n        iter_type left(first + dist / 3), right(first + dist *\
    \ 2 / 3);\n        if(comp(left, right)) last = right, dist = dist * 2 / 3;\n\
    \        else first = left, dist -= dist / 3;\n    }\n    if(dist > 1 && comp(first\
    \ + 1, first)) ++first;\n    return first;\n}\n// trinary search on real numbers.\n\
    template <class comp_type>\nlong double trinary(long double first, long double\
    \ last, const long double eps, comp_type comp)\n{\n    assert(first < last);\n\
    \    while(last - first > eps)\n    {\n        long double left{(first * 2 + last)\
    \ / 3}, right{(first + last * 2) / 3};\n        if(comp(left, right)) last = right;\n\
    \        else first = left;\n    }\n    return first;\n}\n"
  code: "#pragma once\n#include <cassert>\n#include <cstdint>\n// trinary search on\
    \ discrete range.\ntemplate <class iter_type, class comp_type>\niter_type trinary(iter_type\
    \ first, iter_type last, comp_type comp)\n{\n    assert(first < last);\n    intmax_t\
    \ dist(last - first);\n    while(dist > 2)\n    {\n        iter_type left(first\
    \ + dist / 3), right(first + dist * 2 / 3);\n        if(comp(left, right)) last\
    \ = right, dist = dist * 2 / 3;\n        else first = left, dist -= dist / 3;\n\
    \    }\n    if(dist > 1 && comp(first + 1, first)) ++first;\n    return first;\n\
    }\n// trinary search on real numbers.\ntemplate <class comp_type>\nlong double\
    \ trinary(long double first, long double last, const long double eps, comp_type\
    \ comp)\n{\n    assert(first < last);\n    while(last - first > eps)\n    {\n\
    \        long double left{(first * 2 + last) / 3}, right{(first + last * 2) /\
    \ 3};\n        if(comp(left, right)) last = right;\n        else first = left;\n\
    \    }\n    return first;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/trinary_search.hpp
  requiredBy:
  - utils.hpp
  timestamp: '2020-08-14 02:41:54+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils/trinary_search.hpp
layout: document
redirect_from:
- /library/utils/trinary_search.hpp
- /library/utils/trinary_search.hpp.html
title: utils/trinary_search.hpp
---
