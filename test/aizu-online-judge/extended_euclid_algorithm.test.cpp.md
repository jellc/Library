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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: number_theory/ext_gcd.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \\\n  \"https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_E\"\
    \n#include \"number_theory/ext_gcd.hpp\"\n#include \"utils/io.hpp\"\n\nint main()\
    \ {\n  int a, b;\n  std::cin >> a >> b;\n  __int128_t _a = a, _b = b;\n  auto\
    \ [x, y] = workspace::ext_gcd(_a, b);\n  if (x > 0) x -= b, y += a;\n  if ((y\
    \ - x) * 2 > a + b) x += b, y -= a;\n  a = x, b = y;\n  std::cout << std::tie(a,\
    \ b) << \"\\n\";\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: test/aizu-online-judge/extended_euclid_algorithm.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/aizu-online-judge/extended_euclid_algorithm.test.cpp
layout: document
redirect_from:
- /verify/test/aizu-online-judge/extended_euclid_algorithm.test.cpp
- /verify/test/aizu-online-judge/extended_euclid_algorithm.test.cpp.html
title: test/aizu-online-judge/extended_euclid_algorithm.test.cpp
---
