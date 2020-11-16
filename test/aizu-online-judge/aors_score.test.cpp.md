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
  code: "#define PROBLEM \\\n  \"https://onlinejudge.u-aizu.ac.jp/challenges/sources/VPC/RUPC/2815?year=2017\"\
    \n#include \"graph/directed/flow/min_cost_flow.hpp\"\n#include \"utils/io.hpp\"\
    \nusing namespace workspace;\n\nint main() {\n  const int n = read<int>(), m =\
    \ read<int>(), k = read<int>();\n  const int total = n + m + 3;\n  const int dst\
    \ = total - 1;\n  const int dst2 = total - 2;\n  const int dst3 = total - 3;\n\
    \  min_cost_flow<int, int> mcf(total);\n  mcf.supply(dst, -n);\n  mcf.add_edge(dst2,\
    \ dst, n, 0);\n  mcf.add_edge(dst3, dst, n - k, 0);\n  for (int i = 0; i < n;\
    \ ++i) {\n    mcf.supply(i, 1);\n    mcf.add_edge(i, dst2, 1, -read<int>());\n\
    \  }\n  for (int j = 0; j < m; j++) {\n    for (int i = 0; i < n; i++) {\n   \
    \   mcf.add_edge(i, j + n, 1, -read<int>());\n    }\n  }\n  for (int j = 0; j\
    \ < m; j++) {\n    mcf.add_edge(j + n, dst3, read<int>(), 0);\n  }\n  std::cout\
    \ << -mcf.optimal() << \"\\n\";\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: test/aizu-online-judge/aors_score.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/aizu-online-judge/aors_score.test.cpp
layout: document
redirect_from:
- /verify/test/aizu-online-judge/aors_score.test.cpp
- /verify/test/aizu-online-judge/aors_score.test.cpp.html
title: test/aizu-online-judge/aors_score.test.cpp
---
