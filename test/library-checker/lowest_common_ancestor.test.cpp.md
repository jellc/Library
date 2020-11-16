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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/undirected/tree/heavy_light_decomposition.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\n#include <cstdio>\n\
    #include <ext/rope>\n\n#include \"graph/undirected/tree/heavy_light_decomposition.hpp\"\
    \n#include \"graph/undirected/tree/lowest_common_ancestor.hpp\"\n\nint main()\
    \ {\n  size_t n, q;\n  scanf(\"%lu%lu\", &n, &q);\n  lowest_common_ancestor lca(n);\n\
    \  heavy_light_decomposition hld(n);\n  for (size_t i = 1, p; i < n; i++) {\n\
    \    scanf(\"%lu\", &p);\n    lca.add_edge(i, p);\n    hld.add_edge(i, p);\n \
    \ }\n  lca.make(0);\n  hld.make(0);\n  for (size_t u, v; q--;) {\n    scanf(\"\
    %lu%lu\", &u, &v);\n    auto [left, right] = hld.path_decomposition(u, v);\n \
    \   std::tie(u, v) = std::make_pair(lca.query(u, v), hld.lca(u, v));\n    assert(u\
    \ == v);\n    assert(u == hld.node(left.back().first));\n    printf(\"%lu\\n\"\
    , u);\n  }\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: test/library-checker/lowest_common_ancestor.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/library-checker/lowest_common_ancestor.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/lowest_common_ancestor.test.cpp
- /verify/test/library-checker/lowest_common_ancestor.test.cpp.html
title: test/library-checker/lowest_common_ancestor.test.cpp
---
