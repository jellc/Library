---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes: {}
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  [Previous line repeated 1 more time]\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: src\\utils\\sfinae.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/find_linear_recurrence\"\
    \n\n#include \"src/algebra/berlekamp_massey.hpp\"\n#include \"src/algebra/modint.hpp\"\
    \n#include \"src/utils/io/istream.hpp\"\n#include \"src/utils/io/ostream.hpp\"\
    \n\nint main() {\n  using namespace workspace;\n  using mint = modint<998244353>;\n\
    \n  int n;\n  cin >> n;\n  polynomial<mint> a(n);\n  cin >> a;\n  auto b = a;\n\
    \  a = Berlekamp_Massey(a.begin(), a.end());\n  a.pop_back();\n  for (auto &&x\
    \ : a) x = -x;\n  std::reverse(a.begin(), a.end());\n  std::cout << a.size() <<\
    \ \"\\n\";\n  std::cout << a << \"\\n\";\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: test/library-checker/find_linear_recurrence.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/library-checker/find_linear_recurrence.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/find_linear_recurrence.test.cpp
- /verify/test/library-checker/find_linear_recurrence.test.cpp.html
title: test/library-checker/find_linear_recurrence.test.cpp
---
