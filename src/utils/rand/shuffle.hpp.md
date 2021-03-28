---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Shuffle
    links: []
  bundledCode: "#line 2 \"src/utils/rand/shuffle.hpp\"\n\n/**\n * @file shuffle.hpp\n\
    \ * @brief Shuffle\n */\n\n#include <algorithm>\n#include <random>\n\nnamespace\
    \ workspace {\n\ntemplate <class _RAIter, class _Engine = std::mt19937>\nvoid\
    \ shuffle(_RAIter __first, _RAIter __last) {\n  static _Engine __engine(std::random_device{}());\n\
    \  std::shuffle(__first, __last, __engine);\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file shuffle.hpp\n * @brief Shuffle\n */\n\n#include\
    \ <algorithm>\n#include <random>\n\nnamespace workspace {\n\ntemplate <class _RAIter,\
    \ class _Engine = std::mt19937>\nvoid shuffle(_RAIter __first, _RAIter __last)\
    \ {\n  static _Engine __engine(std::random_device{}());\n  std::shuffle(__first,\
    \ __last, __engine);\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/rand/shuffle.hpp
  requiredBy: []
  timestamp: '2021-03-28 15:08:08+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/rand/shuffle.hpp
layout: document
redirect_from:
- /library/src/utils/rand/shuffle.hpp
- /library/src/utils/rand/shuffle.hpp.html
title: Shuffle
---
