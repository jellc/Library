---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/rolling_hash.hpp
    title: Rolling hash
  - icon: ':heavy_check_mark:'
    path: utils/binary_search.hpp
    title: Binary search
  - icon: ':heavy_check_mark:'
    path: utils/random_number_generator.hpp
    title: utils/random_number_generator.hpp
  - icon: ':heavy_check_mark:'
    path: utils/sfinae.hpp
    title: utils/sfinae.hpp
  - icon: ':heavy_check_mark:'
    path: utils/stream.hpp
    title: utils/stream.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_C
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_C
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 310, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ string/rolling_hash.hpp: line 6: #pragma once found in a non-first line\n"
  code: "#define PROBLEM \\\n  \"https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_C\"\
    \n#include \"string/rolling_hash.hpp\"\n#include \"utils/stream.hpp\"\n\nint main()\
    \ {\n  std::ios::sync_with_stdio(0);\n  std::cin.tie(0);\n\n  size_t h, w, r,\
    \ c;\n\n  std::cin >> h >> w;\n  std::string transposed(h * w, '?');\n  for (size_t\
    \ i = 0; i < h; ++i) {\n    for (size_t j = 0; j < w; ++j) {\n      std::cin >>\
    \ transposed[j * h + i];\n    }\n  }\n\n  std::cin >> r >> c;\n  std::string oneln(r\
    \ * c, '?');\n  for (size_t i = 0; i < r; ++i) {\n    for (size_t j = c; j--;)\
    \ {\n      std::cin >> oneln[j * r + i];\n    }\n  }\n\n  workspace::rolling_hash_table\
    \ grid_hash_table(transposed);\n  auto pattern_hash = workspace::rolling_hash_table(oneln).substr();\n\
    \n  for (size_t i = 0; i + r <= h; ++i) {\n    workspace::rolling_hashed hash;\n\
    \    for (size_t j = 0; j < w; ++j) {\n      hash = grid_hash_table.substr(h *\
    \ j + i, r) + hash;\n      if (j >= c) {\n        hash -= grid_hash_table.substr(h\
    \ * (j - c) + i, r);\n      }\n      if (hash == pattern_hash) std::cout << i\
    \ << \" \" << j - c + 1 << \"\\n\";\n    }\n  }\n}\n"
  dependsOn:
  - string/rolling_hash.hpp
  - utils/binary_search.hpp
  - utils/random_number_generator.hpp
  - utils/stream.hpp
  - utils/sfinae.hpp
  isVerificationFile: true
  path: test/aizu-online-judge/pattern_search.test.cpp
  requiredBy: []
  timestamp: '2020-11-04 18:14:03+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aizu-online-judge/pattern_search.test.cpp
layout: document
redirect_from:
- /verify/test/aizu-online-judge/pattern_search.test.cpp
- /verify/test/aizu-online-judge/pattern_search.test.cpp.html
title: test/aizu-online-judge/pattern_search.test.cpp
---
