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
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: utils/stream.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/2450\"\n#include\
    \ <algorithm>\n\n#include \"data_structure/segment_tree/lazy.hpp\"\n#include \"\
    graph/undirected/tree/heavy_light_decomposition.hpp\"\n#include \"utils/stream.hpp\"\
    \n\nint main() {\n  struct endo {\n    bool assign = false;\n    int value;\n\
    \    endo() = default;\n    endo(int v) : assign(true), value(v) {}\n    endo\
    \ operator*(endo rhs) {\n      if (rhs.assign) return rhs;\n      return *this;\n\
    \    }\n  };\n  struct mono {\n    int cnt = 0;\n    int sum = 0;\n    int left\
    \ = 0;\n    int right = 0;\n    int max = 0;\n    int best = -10000;\n    mono\
    \ operator+(mono rhs) {\n      return {cnt + rhs.cnt,\n              sum + rhs.sum,\n\
    \              std::max(left, sum + rhs.left),\n              std::max(right +\
    \ rhs.sum, rhs.right),\n              std::max({max, rhs.max, right + rhs.left}),\n\
    \              std::max(best, rhs.best)};\n    }\n    mono operator*(endo rhs)\
    \ {\n      mono ret = *this;\n      if (rhs.assign) {\n        if (rhs.value <\
    \ 0) {\n          ret.sum = rhs.value * cnt;\n          ret.left = ret.right =\
    \ ret.max = 0;\n        } else {\n          ret.sum = ret.left = ret.right = ret.max\
    \ = cnt * rhs.value;\n        }\n        ret.best = rhs.value;\n      }\n    \
    \  return ret;\n    }\n  };\n\n  int n, q;\n  std::cin >> n >> q;\n  std::vector<int>\
    \ w(n);\n  std::cin >> w;\n  heavy_light_decomposition hld(n);\n  for (auto e\
    \ = 1; e != n; ++e) {\n    int u, v;\n    std::cin >> u >> v;\n    --u, --v;\n\
    \    hld.add_edge(u, v);\n  }\n  hld.make(0);\n  lazy_segment_tree<mono, endo>\
    \ seg(n);\n  for (auto v = 0; v != n; ++v) {\n    auto &now = seg[hld.index(v)];\n\
    \    now.cnt = 1;\n    now = now * endo{w[v]};\n  }\n  while (q--) {\n    int\
    \ tp, a, b, c;\n    std::cin >> tp >> a >> b >> c;\n    --a, --b;\n    auto [left,\
    \ right] = hld.path_decomposition(a, b);\n    if (tp == 1) {\n      for (auto\
    \ &&[l, r] : left) {\n        seg.update(l, r, c);\n      }\n      for (auto &&[l,\
    \ r] : right) {\n        seg.update(l, r, c);\n      }\n    } else {\n      mono\
    \ lv;\n      for (auto &&[l, r] : left) {\n        lv = seg.fold(l, r) + lv;\n\
    \      }\n      mono rv;\n      for (auto &&[l, r] : right) {\n        rv = seg.fold(l,\
    \ r) + rv;\n      }\n      std::swap(lv.left, lv.right);\n      auto all = lv\
    \ + rv;\n      if (all.max)\n        std::cout << all.max << '\\n';\n      else\n\
    \        std::cout << all.best << '\\n';\n    }\n  }\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: test/aizu-online-judge/do_use_segment_tree.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/aizu-online-judge/do_use_segment_tree.test.cpp
layout: document
redirect_from:
- /verify/test/aizu-online-judge/do_use_segment_tree.test.cpp
- /verify/test/aizu-online-judge/do_use_segment_tree.test.cpp.html
title: test/aizu-online-judge/do_use_segment_tree.test.cpp
---
