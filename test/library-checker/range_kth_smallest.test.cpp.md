---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/Mo.hpp
    title: Mo's algorithm
  - icon: ':heavy_check_mark:'
    path: utils/coordinate_compression.hpp
    title: utils/coordinate_compression.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_kth_smallest
    links:
    - https://judge.yosupo.jp/problem/range_kth_smallest
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 310, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ data_structure/Mo.hpp: line 6: #pragma once found in a non-first line\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\
    #include <cstdio>\n\n#include \"data_structure/Mo.hpp\"\n#include \"utils/coordinate_compression.hpp\"\
    \n\nint main() {\n  int n, q;\n  scanf(\"%d%d\", &n, &q);\n  std::vector<int>\
    \ a(n);\n  for (int &e : a) scanf(\"%d\", &e);\n  coordinate_compression ccmp(a);\n\
    \  int bsize = std::sqrt(ccmp.count()) + 1;\n  std::vector<int> cnt(ccmp.count()),\
    \ bcnt(bsize);\n  auto add = [&](int i) {\n    int now = ccmp[i];\n    cnt[now]++;\n\
    \    bcnt[now / bsize]++;\n  };\n  auto del = [&](int i) {\n    int now = ccmp[i];\n\
    \    cnt[now]--;\n    bcnt[now / bsize]--;\n  };\n  workspace::Mo mo(add, del);\n\
    \  std::vector<int> k(q), ans(q);\n  for (int l, r, i = 0; i < q; i++) {\n   \
    \ scanf(\"%d%d%d\", &l, &r, &k[i]);\n    mo.set(l, r);\n  }\n  mo.make();\n  for\
    \ (int t = 0; t < q; t++) {\n    int qid = mo.process();\n    for (int i = 0,\
    \ j = 0, nk = k[qid]; i < bsize; i++, j += bsize) {\n      if (bcnt[i] > nk) {\n\
    \        int h;\n        for (h = j; nk >= cnt[h]; h++) {\n          nk -= cnt[h];\n\
    \        }\n        ans[qid] = ccmp.value(h);\n        break;\n      } else {\n\
    \        nk -= bcnt[i];\n      }\n    }\n  }\n  for (int e : ans) printf(\"%d\\\
    n\", e);\n}\n"
  dependsOn:
  - data_structure/Mo.hpp
  - utils/coordinate_compression.hpp
  isVerificationFile: true
  path: test/library-checker/range_kth_smallest.test.cpp
  requiredBy: []
  timestamp: '2020-11-04 17:24:45+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/range_kth_smallest.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/range_kth_smallest.test.cpp
- /verify/test/library-checker/range_kth_smallest.test.cpp.html
title: test/library-checker/range_kth_smallest.test.cpp
---
