---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes: {}
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 193, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: algebra/system/monoid.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\
    \n\n#include <cstdio>\n#include <vector>\n\n#include \"src/data_structure/segment_tree/lazy.hpp\"\
    \n#include \"src/modular/modint.hpp\"\n\nint main() {\n  using namespace workspace;\n\
    \  using mint = modint<998244353>;\n  struct endo {\n    mint a = 1, b;\n    endo\
    \ operator*(endo rhs) { return {a * rhs.a, b * rhs.a + rhs.b}; }\n  };\n  struct\
    \ mono {\n    mint v, c;\n    mono operator+(mono rhs) { return {v + rhs.v, c\
    \ + rhs.c}; }\n    mono operator*(endo rhs) { return {v * rhs.a + c * rhs.b, c};\
    \ }\n  };\n\n  int n, q;\n  scanf(\"%d%d\", &n, &q);\n  lazy_segment_tree<mono,\
    \ endo> seg(n);\n  for (int i = 0, v; i < n; i++) {\n    scanf(\"%d\", &v);\n\
    \    seg[i] = {v, 1};\n  }\n  for (int t, l, r, a, b; q--;) {\n    scanf(\"%d%d%d\"\
    , &t, &l, &r);\n    if (t) {\n      printf(\"%d\\n\", seg.fold(l, r).v);\n   \
    \ } else {\n      scanf(\"%d%d\", &a, &b);\n      seg.update(l, r, {a, b});\n\
    \    }\n  }\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: test/library-checker/range_affine_range_sum.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/library-checker/range_affine_range_sum.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/range_affine_range_sum.test.cpp
- /verify/test/library-checker/range_affine_range_sum.test.cpp.html
title: test/library-checker/range_affine_range_sum.test.cpp
---
