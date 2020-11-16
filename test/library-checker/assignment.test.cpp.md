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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/directed/flow/min_cost_flow.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/assignment\"\n#include\
    \ <cstdint>\n#include <cstdio>\n\n#include \"graph/directed/flow/min_cost_flow.hpp\"\
    \n\nint main() {\n  int n;\n  scanf(\"%d\", &n);\n  min_cost_flow<int, int64_t>\
    \ mcf(n * 2);\n  for (int i = 0; i < n; i++) {\n    mcf.supply(i, 1);\n    mcf.supply(i\
    \ + n, -1);\n    for (int j = 0; j < n; j++) {\n      int a;\n      scanf(\"%d\"\
    , &a);\n      mcf.add_edge(i, j + n, 1, a);\n    }\n  }\n  printf(\"%lld\\n\"\
    , mcf.optimal());\n  for (int i = 0; i < n; i++) {\n    for (auto &e : mcf[i])\
    \ {\n      if (!e.cap) printf(\"%d \", e.dst - n);\n    }\n  }\n  puts(\"\");\n\
    }\n"
  dependsOn: []
  isVerificationFile: true
  path: test/library-checker/assignment.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/library-checker/assignment.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/assignment.test.cpp
- /verify/test/library-checker/assignment.test.cpp.html
title: test/library-checker/assignment.test.cpp
---
