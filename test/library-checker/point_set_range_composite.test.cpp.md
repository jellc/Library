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
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: data_structure/segment_tree/basic.hpp:\
    \ line -1: no such header\n"
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
  dependsOn: []
  isVerificationFile: true
  path: test/library-checker/point_set_range_composite.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/library-checker/point_set_range_composite.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/point_set_range_composite.test.cpp
- /verify/test/library-checker/point_set_range_composite.test.cpp.html
title: test/library-checker/point_set_range_composite.test.cpp
---
