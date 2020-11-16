---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algebra/system/monoid.hpp
    title: algebra/system/monoid.hpp
  - icon: ':heavy_check_mark:'
    path: src/data_structure/Mo.hpp
    title: Mo's Algorithm
  - icon: ':heavy_check_mark:'
    path: src/data_structure/segment_tree/basic.hpp
    title: src/data_structure/segment_tree/basic.hpp
  - icon: ':heavy_check_mark:'
    path: src/data_structure/segment_tree/waitlist.hpp
    title: src/data_structure/segment_tree/waitlist.hpp
  - icon: ':heavy_check_mark:'
    path: src/utils/coordinate_compression.hpp
    title: src/utils/coordinate_compression.hpp
  - icon: ':heavy_check_mark:'
    path: src/utils/sfinae.hpp
    title: src/utils/sfinae.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/static_range_inversions_query
    links:
    - https://judge.yosupo.jp/problem/static_range_inversions_query
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 193, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 310, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ src/data_structure/Mo.hpp: line 6: #pragma once found in a non-first line\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_inversions_query\"\
    \n\n#include <cstdio>\n\n#include \"src/data_structure/Mo.hpp\"\n#include \"src/data_structure/segment_tree/basic.hpp\"\
    \n#include \"src/utils/coordinate_compression.hpp\"\n\nint main() {\n  using i64\
    \ = int64_t;\n  int n, q;\n  scanf(\"%d%d\", &n, &q);\n  std::vector<int> a(n);\n\
    \  for (int &x : a) scanf(\"%d\", &x);\n  coordinate_compression ccmp(a);\n  std::vector<int>\
    \ cnt(ccmp.count());\n  segment_tree<int> seg(n);\n  i64 invs = 0;\n  auto addl\
    \ = [&](int i) -> auto {\n    i = ccmp[i];\n    invs += seg.fold(0, i);\n    seg[i]++;\n\
    \  };\n  auto addr = [&](int i) -> auto {\n    i = ccmp[i];\n    invs += seg.fold(i\
    \ + 1, n);\n    seg[i]++;\n  };\n  auto dell = [&](int i) -> auto {\n    i = ccmp[i];\n\
    \    invs -= seg.fold(0, i);\n    seg[i]--;\n  };\n  auto delr = [&](int i) ->\
    \ auto {\n    i = ccmp[i];\n    invs -= seg.fold(i + 1, n);\n    seg[i]--;\n \
    \ };\n  workspace::Mo mo(addl, dell, addr, delr);\n  for (int i = 0; i < q; i++)\
    \ {\n    int l, r;\n    scanf(\"%d%d\", &l, &r);\n    mo.set(l, r);\n  }\n  mo.make();\n\
    \  std::vector<i64> ans(q);\n  for (int i = 0; i < q; i++) {\n    int id = mo.process();\n\
    \    ans[id] = invs;\n  }\n  for (i64 x : ans) printf(\"%lld\\n\", x);\n}\n"
  dependsOn:
  - src/data_structure/Mo.hpp
  - src/data_structure/segment_tree/basic.hpp
  - src/utils/sfinae.hpp
  - algebra/system/monoid.hpp
  - src/data_structure/segment_tree/waitlist.hpp
  - src/utils/coordinate_compression.hpp
  isVerificationFile: true
  path: test/library-checker/static_range_inversions_query.test.cpp
  requiredBy: []
  timestamp: '2020-11-16 22:30:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/static_range_inversions_query.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/static_range_inversions_query.test.cpp
- /verify/test/library-checker/static_range_inversions_query.test.cpp.html
title: test/library-checker/static_range_inversions_query.test.cpp
---
