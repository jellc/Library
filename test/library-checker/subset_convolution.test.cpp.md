---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algebra/convolution/subset.hpp
    title: algebra/convolution/subset.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/subset_convolution
    links:
    - https://judge.yosupo.jp/problem/subset_convolution
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 310, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ modulus/modint.hpp: line 6: #pragma once found in a non-first line\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/subset_convolution\"\n\
    #include <iostream>\n\n#include \"algebra/convolution/subset.hpp\"\n#include \"\
    modulus/modint.hpp\"\n\nint main() {\n  using mint = workspace::modint<998244353>;\n\
    \  using std::cin;\n  int n;\n  cin >> n;\n  std::vector<mint> a(1 << n), b(1\
    \ << n);\n  for (auto &x : a) cin >> x;\n  for (auto &x : b) cin >> x;\n  a =\
    \ subset_convolute(a, b);\n  for (auto x : a) printf(\"%d \", x);\n  puts(\"\"\
    );\n}\n"
  dependsOn:
  - algebra/convolution/subset.hpp
  - modulus/modint.hpp
  - utils/sfinae.hpp
  isVerificationFile: true
  path: test/library-checker/subset_convolution.test.cpp
  requiredBy: []
  timestamp: '2020-11-04 18:12:33+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/subset_convolution.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/subset_convolution.test.cpp
- /verify/test/library-checker/subset_convolution.test.cpp.html
title: test/library-checker/subset_convolution.test.cpp
---
