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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: algebra/formal_power_series/all.hpp:\
    \ line -1: no such header\n"
  code: "#define IGNORE\n#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod\"\
    \n#include \"algebra/formal_power_series/all.hpp\"\n#include \"modulus/modint.hpp\"\
    \n#include \"utils/stream.hpp\"\n\nint main() {\n  int n, m;\n  std::cin >> n\
    \ >> m;\n  FormalPowerSeries<LazyMontgomeryModInt<998244353>> a(n), b(m);\n  std::cin\
    \ >> a >> b;\n  std::cout << a * b << '\\n';\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: test/library-checker/convolution_mod.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/library-checker/convolution_mod.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/convolution_mod.test.cpp
- /verify/test/library-checker/convolution_mod.test.cpp.html
title: test/library-checker/convolution_mod.test.cpp
---
