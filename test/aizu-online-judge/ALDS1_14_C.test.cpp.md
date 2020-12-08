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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: src/utils/binary_search.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_C\"\n\
    \n#include <iostream>\n\n#include \"src/string/rolling_hash.hpp\"\n\nint main()\
    \ {\n  size_t h, w, r, c;\n\n  std::cin >> h >> w;\n  std::string transposed(h\
    \ * w, '?');\n  for (size_t i = 0; i < h; ++i) {\n    for (size_t j = 0; j < w;\
    \ ++j) {\n      std::cin >> transposed[j * h + i];\n    }\n  }\n\n  std::cin >>\
    \ r >> c;\n  std::string oneln(r * c, '?');\n  for (size_t i = 0; i < r; ++i)\
    \ {\n    for (size_t j = c; j--;) {\n      std::cin >> oneln[j * r + i];\n   \
    \ }\n  }\n\n  workspace::rolling_hash_table grid_hash_table(transposed);\n  auto\
    \ pattern_hash = workspace::rolling_hash_table(oneln).substr();\n\n  for (size_t\
    \ i = 0; i + r <= h; ++i) {\n    workspace::rolling_hashed hash;\n    for (size_t\
    \ j = 0; j < w; ++j) {\n      hash = grid_hash_table.substr(h * j + i, r) + hash;\n\
    \      if (j >= c) {\n        hash -= grid_hash_table.substr(h * (j - c) + i,\
    \ r);\n      }\n      if (hash == pattern_hash) std::cout << i << \" \" << j -\
    \ c + 1 << \"\\n\";\n    }\n  }\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: test/aizu-online-judge/ALDS1_14_C.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/aizu-online-judge/ALDS1_14_C.test.cpp
layout: document
redirect_from:
- /verify/test/aizu-online-judge/ALDS1_14_C.test.cpp
- /verify/test/aizu-online-judge/ALDS1_14_C.test.cpp.html
title: test/aizu-online-judge/ALDS1_14_C.test.cpp
---
