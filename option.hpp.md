---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: template.cpp
    title: Code template
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Optimize options
    links: []
  bundledCode: "#line 2 \"option.hpp\"\n\n/*\n * @file option.hpp\n * @brief Optimize\
    \ options\n */\n\n#ifdef ONLINE_JUDGE\n\n#pragma GCC optimize(\"O3\")\n#pragma\
    \ GCC target(\"avx,avx2\")\n#pragma GCC optimize(\"unroll-loops\")\n\n#endif\n"
  code: "#pragma once\n\n/*\n * @file option.hpp\n * @brief Optimize options\n */\n\
    \n#ifdef ONLINE_JUDGE\n\n#pragma GCC optimize(\"O3\")\n#pragma GCC target(\"avx,avx2\"\
    )\n#pragma GCC optimize(\"unroll-loops\")\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: option.hpp
  requiredBy:
  - template.cpp
  timestamp: '2020-11-07 14:25:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: option.hpp
layout: document
redirect_from:
- /library/option.hpp
- /library/option.hpp.html
title: Optimize options
---
