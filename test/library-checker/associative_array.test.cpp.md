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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: utils/hash.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/associative_array\"\n#include\
    \ \"utils/hash.hpp\"\n\nusing namespace workspace;\n\nint main() {\n  int q;\n\
    \  scanf(\"%d\", &q);\n  unordered_map<long long, long long> a;\n  gp_hash_table<long\
    \ long, long long> b;\n  cc_hash_table<long long, long long> c;\n\n  while (q--)\
    \ {\n    int t;\n    long long k, v;\n    scanf(\"%d%lld\", &t, &k);\n    if (t)\
    \ {\n      printf(\"%lld\\n\", a[k]);\n      assert(a[k] == b[k] && a[k] == c[k]);\n\
    \    } else {\n      scanf(\"%lld\", &v);\n      a[k] = b[k] = c[k] = v;\n   \
    \ }\n  }\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: test/library-checker/associative_array.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/library-checker/associative_array.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/associative_array.test.cpp
- /verify/test/library-checker/associative_array.test.cpp.html
title: test/library-checker/associative_array.test.cpp
---
