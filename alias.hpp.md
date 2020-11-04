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
    document_title: Alias
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 310, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ alias.hpp: line 6: #pragma once found in a non-first line\n"
  code: "/*\n * @file alias.hpp\n * @brief Alias\n */\n\n#pragma once\n#include <cstdint>\n\
    #include <functional>\n#include <queue>\n#include <stack>\n#include <vector>\n\
    \nnamespace workspace {\n\nconstexpr char eol = '\\n';\n\nusing namespace std;\n\
    \nusing i32 = int_least32_t;\nusing i64 = int_least64_t;\nusing i128 = __int128_t;\n\
    using u32 = uint_least32_t;\nusing u64 = uint_least64_t;\nusing u128 = __uint128_t;\n\
    \ntemplate <class T, class Comp = less<T>>\nusing priority_queue = std::priority_queue<T,\
    \ vector<T>, Comp>;\n\ntemplate <class T> using stack = std::stack<T, vector<T>>;\n\
    \n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: alias.hpp
  requiredBy:
  - template.cpp
  timestamp: '2020-11-04 17:56:57+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: alias.hpp
layout: document
redirect_from:
- /library/alias.hpp
- /library/alias.hpp.html
title: Alias
---
