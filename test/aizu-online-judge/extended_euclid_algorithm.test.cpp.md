---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: number_theory/ext_gcd.hpp
    title: Extended Euclidean algorithm
  - icon: ':heavy_check_mark:'
    path: utils/sfinae.hpp
    title: utils/sfinae.hpp
  - icon: ':heavy_check_mark:'
    path: utils/stream.hpp
    title: utils/stream.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_E
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_E
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 310, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ number_theory/ext_gcd.hpp: line 6: #pragma once found in a non-first line\n"
  code: "#define PROBLEM \\\n  \"https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_E\"\
    \n#include \"number_theory/ext_gcd.hpp\"\n#include \"utils/stream.hpp\"\n\nint\
    \ main() {\n  int a, b;\n  std::cin >> a >> b;\n  __int128_t _a = a, _b = b;\n\
    \  auto [x, y] = workspace::ext_gcd(_a, b);\n  if (x > 0) x -= b, y += a;\n  if\
    \ ((y - x) * 2 > a + b) x += b, y -= a;\n  a = x, b = y;\n  std::cout << std::tie(a,\
    \ b) << \"\\n\";\n}\n"
  dependsOn:
  - number_theory/ext_gcd.hpp
  - utils/sfinae.hpp
  - utils/stream.hpp
  isVerificationFile: true
  path: test/aizu-online-judge/extended_euclid_algorithm.test.cpp
  requiredBy: []
  timestamp: '2020-11-04 17:56:57+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aizu-online-judge/extended_euclid_algorithm.test.cpp
layout: document
redirect_from:
- /verify/test/aizu-online-judge/extended_euclid_algorithm.test.cpp
- /verify/test/aizu-online-judge/extended_euclid_algorithm.test.cpp.html
title: test/aizu-online-judge/extended_euclid_algorithm.test.cpp
---
