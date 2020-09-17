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
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 2 \"gcc_option.hpp\"\n#ifdef ONLINE_JUDGE\n    #pragma GCC optimize(\"\
    O3\")\n    #pragma GCC target(\"avx,avx2\")\n    #pragma GCC optimize(\"unroll-loops\"\
    )\n#endif\n"
  code: "#pragma once\n#ifdef ONLINE_JUDGE\n    #pragma GCC optimize(\"O3\")\n   \
    \ #pragma GCC target(\"avx,avx2\")\n    #pragma GCC optimize(\"unroll-loops\"\
    )\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: gcc_option.hpp
  requiredBy:
  - template.cpp
  timestamp: '2020-08-29 23:04:40+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: gcc_option.hpp
layout: document
redirect_from:
- /library/gcc_option.hpp
- /library/gcc_option.hpp.html
title: gcc_option.hpp
---
