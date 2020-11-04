---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algebra/system/monoid.hpp
    title: algebra/system/monoid.hpp
  - icon: ':heavy_check_mark:'
    path: data_structure/segment_tree/lazy.hpp
    title: data_structure/segment_tree/lazy.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/range_affine_range_sum
    links:
    - https://judge.yosupo.jp/problem/range_affine_range_sum
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 310, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ modulus/modint.hpp: line 6: #pragma once found in a non-first line\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\
    \n#include <cstdio>\n#include <vector>\n\n#include \"data_structure/segment_tree/lazy.hpp\"\
    \n#include \"modulus/modint.hpp\"\n\nint main() {\n  using mint = workspace::modint<998244353>;\n\
    \  struct endo {\n    mint a = 1, b;\n    endo operator*(endo rhs) { return {a\
    \ * rhs.a, b * rhs.a + rhs.b}; }\n  };\n  struct mono {\n    mint v, c;\n    mono\
    \ operator+(mono rhs) { return {v + rhs.v, c + rhs.c}; }\n    mono operator*(endo\
    \ rhs) { return {v * rhs.a + c * rhs.b, c}; }\n  };\n\n  int n, q;\n  scanf(\"\
    %d%d\", &n, &q);\n  lazy_segment_tree<mono, endo> seg(n);\n  for (int i = 0, v;\
    \ i < n; i++) {\n    scanf(\"%d\", &v);\n    seg[i] = {v, 1};\n  }\n  for (int\
    \ t, l, r, a, b; q--;) {\n    scanf(\"%d%d%d\", &t, &l, &r);\n    if (t) {\n \
    \     printf(\"%d\\n\", seg.fold(l, r).v);\n    } else {\n      scanf(\"%d%d\"\
    , &a, &b);\n      seg.update(l, r, {a, b});\n    }\n  }\n}\n"
  dependsOn:
  - data_structure/segment_tree/lazy.hpp
  - algebra/system/monoid.hpp
  - utils/sfinae.hpp
  - data_structure/segment_tree/waitlist.hpp
  - modulus/modint.hpp
  isVerificationFile: true
  path: test/library-checker/range_affine_range_sum.test.cpp
  requiredBy: []
  timestamp: '2020-11-04 18:12:33+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/range_affine_range_sum.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/range_affine_range_sum.test.cpp
- /verify/test/library-checker/range_affine_range_sum.test.cpp.html
title: test/library-checker/range_affine_range_sum.test.cpp
---
