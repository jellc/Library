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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: data_structure/convex_hull_trick/Li_Chao_tree.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/line_add_get_min\"\n#include\
    \ <cstdio>\n\n#include \"data_structure/convex_hull_trick/Li_Chao_tree.hpp\"\n\
    using i64 = int64_t;\n\nint main() {\n  int n, q;\n  scanf(\"%d%d\", &n, &q);\n\
    \  Li_Chao_tree<i64> cht(-1e9, 1e9 + 1);\n  while (n--) {\n    int a;\n    i64\
    \ b;\n    scanf(\"%d%lld\", &a, &b);\n    cht.insert(a, b);\n  }\n  while (q--)\
    \ {\n    int t;\n    scanf(\"%d\", &t);\n    if (t) {\n      int p;\n      scanf(\"\
    %d\", &p);\n      printf(\"%lld\\n\", cht.get(p));\n    } else {\n      int a;\n\
    \      i64 b;\n      scanf(\"%d%lld\", &a, &b);\n      cht.insert(a, b);\n   \
    \ }\n  }\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: test/library-checker/line_add_get_min.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/library-checker/line_add_get_min.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/line_add_get_min.test.cpp
- /verify/test/library-checker/line_add_get_min.test.cpp.html
title: test/library-checker/line_add_get_min.test.cpp
---
