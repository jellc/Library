---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algebra/system/monoid.hpp
    title: algebra/system/monoid.hpp
  - icon: ':heavy_check_mark:'
    path: data_structure/segment_tree/basic.hpp
    title: data_structure/segment_tree/basic.hpp
  - icon: ':heavy_check_mark:'
    path: data_structure/segment_tree/waitlist.hpp
    title: data_structure/segment_tree/waitlist.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/point_set_range_composite
    links:
    - https://judge.yosupo.jp/problem/point_set_range_composite
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 310, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ modulus/modint.hpp: line 6: #pragma once found in a non-first line\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite\"\
    \n#include <cstdio>\n\n#include \"data_structure/segment_tree/basic.hpp\"\n#include\
    \ \"modulus/modint.hpp\"\n\nint main() {\n  using mint = workspace::modint<998244353>;\n\
    \  int n, q;\n  scanf(\"%d%d\", &n, &q);\n  struct mono {\n    mint c = 1, d;\n\
    \    mono operator+(const mono& rhs) { return {rhs.c * c, rhs.c * d + rhs.d};\
    \ }\n    mint eval(mint x) const { return c * x + d; }\n  };\n  segment_tree<mono>\
    \ seg(n);\n  for (int i = 0; i < n; i++) {\n    int a, b;\n    scanf(\"%d%d\"\
    , &a, &b);\n    seg[i] = {a, b};\n  }\n  for (int t, a, b, c; q--;) {\n    scanf(\"\
    %d%d%d%d\", &t, &a, &b, &c);\n    if (t) {\n      printf(\"%d\\n\", seg.fold(a,\
    \ b).eval(c));\n    } else {\n      seg[a] = {b, c};\n    }\n  }\n}\n"
  dependsOn:
  - data_structure/segment_tree/basic.hpp
  - algebra/system/monoid.hpp
  - utils/sfinae.hpp
  - data_structure/segment_tree/waitlist.hpp
  - modulus/modint.hpp
  isVerificationFile: true
  path: test/library-checker/point_set_range_composite.test.cpp
  requiredBy: []
  timestamp: '2020-11-04 18:12:33+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/point_set_range_composite.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/point_set_range_composite.test.cpp
- /verify/test/library-checker/point_set_range_composite.test.cpp.html
title: test/library-checker/point_set_range_composite.test.cpp
---
