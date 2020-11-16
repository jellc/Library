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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/undirected/two_edge_connected_components.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/two_edge_connected_components\"\
    \n#include <algorithm>\n#include <cstdio>\n\n#include \"graph/undirected/two_edge_connected_components.hpp\"\
    \n\nsigned main() {\n  int v, e;\n  scanf(\"%d%d\", &v, &e);\n  two_edge_connected_component\
    \ becc(v);\n  for (int a, b; e--;) {\n    scanf(\"%d%d\", &a, &b);\n    becc.add_edge(a,\
    \ b);\n  }\n  becc.make();\n  printf(\"%d\\n\", becc.count());\n  for (size_t\
    \ i = 0; i < becc.count(); i++) {\n    const auto &lst = becc.component(i);\n\
    \    printf(\"%d\", lst.size());\n    for (int v : lst) {\n      printf(\" %d\"\
    , v);\n    }\n    puts(\"\");\n  }\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: test/library-checker/two_edge_connected_components.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/library-checker/two_edge_connected_components.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/two_edge_connected_components.test.cpp
- /verify/test/library-checker/two_edge_connected_components.test.cpp.html
title: test/library-checker/two_edge_connected_components.test.cpp
---
