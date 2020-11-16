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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/directed/flow/Dinic.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/bipartitematching\"\n#include\
    \ \"graph/directed/flow/Dinic.hpp\"\n#include <cstdio>\n\nint main()\n{\n    int\
    \ l,r,m; scanf(\"%d%d%d\",&l,&r,&m);\n    Dinic<int> dinic(l+r+2);\n    const\
    \ int s=l+r,t=s+1;\n\n    for(int i = 0,a,b; i < m; ++i)\n    {\n        scanf(\"\
    %d%d\",&a,&b);\n        dinic.add_edge(a,b+l,1);\n    }\n    for(int i = 0; i\
    \ < l; ++i)\n    {\n        dinic.add_edge(s,i,1);\n    }\n    for(int i = 0;\
    \ i < r; ++i)\n    {\n        dinic.add_edge(i+l,t,1);\n    }\n\n    printf(\"\
    %d\\n\",dinic.max_flow(s,t));\n\n    for(int i = 0; i < l; ++i)\n    {\n     \
    \   for(const auto &e: dinic[i])\n        {\n            if(!e.cap and e.dst<l+r)\n\
    \            {\n                printf(\"%d %d\\n\", i, e.dst-l);\n          \
    \  }\n        }\n    }\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: test/library-checker/bipartitematching.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/library-checker/bipartitematching.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/bipartitematching.test.cpp
- /verify/test/library-checker/bipartitematching.test.cpp.html
title: test/library-checker/bipartitematching.test.cpp
---
