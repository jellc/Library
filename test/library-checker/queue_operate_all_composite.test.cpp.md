---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/deque_aggregation.hpp
    title: data_structure/deque_aggregation.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/queue_operate_all_composite
    links:
    - https://judge.yosupo.jp/problem/queue_operate_all_composite
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 310, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ modulus/modint.hpp: line 6: #pragma once found in a non-first line\n"
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
  dependsOn:
  - data_structure/deque_aggregation.hpp
  - modulus/modint.hpp
  - utils/sfinae.hpp
  isVerificationFile: true
  path: test/library-checker/queue_operate_all_composite.test.cpp
  requiredBy: []
  timestamp: '2020-11-04 18:12:33+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/queue_operate_all_composite.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/queue_operate_all_composite.test.cpp
- /verify/test/library-checker/queue_operate_all_composite.test.cpp.html
title: test/library-checker/queue_operate_all_composite.test.cpp
---
