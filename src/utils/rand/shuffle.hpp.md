---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Shuffle
    links: []
  bundledCode: "#line 2 \"src/utils/rand/shuffle.hpp\"\n\n/**\n * @file shuffle.hpp\n\
    \ * @brief Shuffle\n */\n\n#include <algorithm>\n#include <random>\n\nnamespace\
    \ workspace {\n\ntemplate <class RAIter>\nvoid shuffle(RAIter const& __first,\
    \ RAIter const& __last) {\n  static std::mt19937 engine(std::random_device{}());\n\
    \  std::shuffle(__first, __last, engine);\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file shuffle.hpp\n * @brief Shuffle\n */\n\n#include\
    \ <algorithm>\n#include <random>\n\nnamespace workspace {\n\ntemplate <class RAIter>\n\
    void shuffle(RAIter const& __first, RAIter const& __last) {\n  static std::mt19937\
    \ engine(std::random_device{}());\n  std::shuffle(__first, __last, engine);\n\
    }\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/rand/shuffle.hpp
  requiredBy: []
  timestamp: '2020-12-12 22:42:49+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/rand/shuffle.hpp
layout: document
redirect_from:
- /library/src/utils/rand/shuffle.hpp
- /library/src/utils/rand/shuffle.hpp.html
title: Shuffle
---
