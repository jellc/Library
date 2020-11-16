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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: modulus/modint.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/queue_operate_all_composite\"\
    \n#include <cstdio>\n\n#include \"data_structure/deque_aggregation.hpp\"\n#include\
    \ \"modulus/modint.hpp\"\n\nint main() {\n  using mint = workspace::modint<998244353>;\n\
    \  struct mono {\n    mint a = 1, b;\n    mono operator+(const mono& rhs) const\
    \ {\n      auto [c, d] = rhs;\n      return {a * c, b * c + d};\n    }\n  };\n\
    \  deque_aggregation<mono> deq;\n  int q;\n  scanf(\"%d\", &q);\n  while (q--)\
    \ {\n    int t;\n    scanf(\"%d\", &t);\n    if (t == 0) {\n      int a, b;\n\
    \      scanf(\"%d%d\", &a, &b);\n      deq.push_back({a, b});\n    } else if (t\
    \ == 1) {\n      deq.pop_front();\n    } else {\n      int x;\n      scanf(\"\
    %d\", &x);\n      auto [a, b] = deq.fold();\n      printf(\"%d\\n\", a * x + b);\n\
    \    }\n  }\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: test/library-checker/queue_operate_all_composite.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/library-checker/queue_operate_all_composite.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/queue_operate_all_composite.test.cpp
- /verify/test/library-checker/queue_operate_all_composite.test.cpp.html
title: test/library-checker/queue_operate_all_composite.test.cpp
---
