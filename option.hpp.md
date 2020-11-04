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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 310, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ option.hpp: line 6: #pragma once found in a non-first line\n"
  code: "/*\n * @file option.hpp\n * @brief Optimize options\n */\n\n#pragma once\n\
    \n#ifdef ONLINE_JUDGE\n\n#pragma GCC optimize(\"O3\")\n#pragma GCC target(\"avx,avx2\"\
    )\n#pragma GCC optimize(\"unroll-loops\")\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: option.hpp
  requiredBy:
  - template.cpp
  timestamp: '2020-11-04 17:56:57+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: option.hpp
layout: document
redirect_from:
- /library/option.hpp
- /library/option.hpp.html
title: Optimize options
---
