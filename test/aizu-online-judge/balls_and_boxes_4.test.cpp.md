---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: combinatorics/binomial.hpp
    title: combinatorics/binomial.hpp
  - icon: ':heavy_check_mark:'
    path: combinatorics/factorial.hpp
    title: combinatorics/factorial.hpp
  - icon: ':heavy_check_mark:'
    path: modulus/inverse.hpp
    title: modulus/inverse.hpp
  - icon: ':heavy_check_mark:'
    path: modulus/modint.hpp
    title: Modular arithmetic
  - icon: ':heavy_check_mark:'
    path: utils/sfinae.hpp
    title: utils/sfinae.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/5/DPL_5_D
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/5/DPL_5_D
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 310, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ modulus/modint.hpp: line 6: #pragma once found in a non-first line\n"
  code: "#define PROBLEM \\\n  \"https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/5/DPL_5_D\"\
    \n#include <cstdio>\n\n#include \"combinatorics/binomial.hpp\"\n\nint main() {\n\
    \  int n, k;\n  scanf(\"%d%d\", &n, &k);\n  printf(\"%d\\n\", binomial<workspace::modint<1000000007>>()(n\
    \ + k - 1, n));\n}\n"
  dependsOn:
  - combinatorics/binomial.hpp
  - combinatorics/factorial.hpp
  - modulus/inverse.hpp
  - modulus/modint.hpp
  - utils/sfinae.hpp
  isVerificationFile: true
  path: test/aizu-online-judge/balls_and_boxes_4.test.cpp
  requiredBy: []
  timestamp: '2020-11-04 18:12:33+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aizu-online-judge/balls_and_boxes_4.test.cpp
layout: document
redirect_from:
- /verify/test/aizu-online-judge/balls_and_boxes_4.test.cpp
- /verify/test/aizu-online-judge/balls_and_boxes_4.test.cpp.html
title: test/aizu-online-judge/balls_and_boxes_4.test.cpp
---
