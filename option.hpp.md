---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: template.cpp
    title: template.cpp
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"option.hpp\"\n#ifdef ONLINE_JUDGE\n    #pragma GCC optimize(\"\
    O3\")\n    #pragma GCC target(\"avx,avx2\")\n    #pragma GCC optimize(\"unroll-loops\"\
    )\n#endif\n"
  code: "#pragma once\n#ifdef ONLINE_JUDGE\n    #pragma GCC optimize(\"O3\")\n   \
    \ #pragma GCC target(\"avx,avx2\")\n    #pragma GCC optimize(\"unroll-loops\"\
    )\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: option.hpp
  requiredBy:
  - template.cpp
  timestamp: '2020-09-17 20:09:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: option.hpp
layout: document
redirect_from:
- /library/option.hpp
- /library/option.hpp.html
title: option.hpp
---
