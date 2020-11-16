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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/directed/strongly_connected_components.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/scc\"\n#include <cstdio>\n\
    \n#include \"graph/directed/strongly_connected_components.hpp\"\n\nint main()\
    \ {\n  int n, m;\n  scanf(\"%d%d\", &n, &m);\n  strongly_connected_components\
    \ scc(n);\n  for (int a, b; m--;) {\n    scanf(\"%d%d\", &a, &b);\n    scc.add_edge(a,\
    \ b);\n  }\n  printf(\"%d\\n\", scc.count());\n  std::vector<std::vector<size_t>>\
    \ comps(scc.count());\n  for (int i = 0; i < n; i++) {\n    comps[scc[i]].emplace_back(i);\n\
    \  }\n  for (auto &comp : comps) {\n    printf(\"%d\", size(comp));\n    for (int\
    \ v : comp) printf(\" %d\", v);\n    puts(\"\");\n  }\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: test/library-checker/scc.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/library-checker/scc.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/scc.test.cpp
- /verify/test/library-checker/scc.test.cpp.html
title: test/library-checker/scc.test.cpp
---
