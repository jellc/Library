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
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: algebra/system/monoid.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_A\"\n\n\
    #include <iostream>\n\n#include \"../../src/data_structure/segment_tree/basic.hpp\"\
    \n\nint main() {\n  using mono = workspace::min_monoid<int>;\n  mono::max = std::numeric_limits<int>::max();\n\
    \  int n, q;\n  std::cin >> n >> q;\n  workspace::segment_tree<mono> seg(n);\n\
    \  while (q--) {\n    int tp, x, y;\n    std::cin >> tp >> x >> y;\n    if (tp)\
    \ {\n      std::cout << seg.fold(x, y + 1) << '\\n';\n    } else {\n      seg[x]\
    \ = y;\n    }\n  }\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: test/aizu-online-judge/DSL_2_A.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/aizu-online-judge/DSL_2_A.test.cpp
layout: document
redirect_from:
- /verify/test/aizu-online-judge/DSL_2_A.test.cpp
- /verify/test/aizu-online-judge/DSL_2_A.test.cpp.html
title: test/aizu-online-judge/DSL_2_A.test.cpp
---
