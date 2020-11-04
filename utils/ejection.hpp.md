---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: template.cpp
    title: Code template
  - icon: ':warning:'
    path: utils.hpp
    title: utils.hpp
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Ejection from try block
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 310, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ utils/ejection.hpp: line 6: #pragma once found in a non-first line\n"
  code: "/*\n * @file ejection.hpp\n * @brief Ejection from try block\n */\n\n#pragma\
    \ once\n#include <iostream>\n\nnamespace workspace {\n\n/*\n * @brief eject from\
    \ a try block, throw nullptr\n * @param arg output\n */\ntemplate <class Tp> void\
    \ eject(Tp const &arg) {\n  std::cout << arg << \"\\n\";\n  throw nullptr;\n}\n\
    \n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/ejection.hpp
  requiredBy:
  - template.cpp
  - utils.hpp
  timestamp: '2020-11-04 17:56:57+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils/ejection.hpp
layout: document
redirect_from:
- /library/utils/ejection.hpp
- /library/utils/ejection.hpp.html
title: Ejection from try block
---
