---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/rolling_hash.hpp
    title: Rolling hash
  - icon: ':heavy_check_mark:'
    path: utils/binary_search.hpp
    title: Binary_search
  - icon: ':heavy_check_mark:'
    path: utils/random_number_generator.hpp
    title: utils/random_number_generator.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/zalgorithm
    links:
    - https://judge.yosupo.jp/problem/zalgorithm
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 310, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ string/rolling_hash.hpp: line 6: #pragma once found in a non-first line\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/zalgorithm\"\n#include\
    \ <iostream>\n#include <string>\n\n#include \"string/rolling_hash.hpp\"\n#include\
    \ \"utils/binary_search.hpp\"\n\nint main() {\n  std::string s;\n  std::cin >>\
    \ s;\n  workspace::rolling_hash_table hash(s);\n  for (size_t i = 0; i < size(s);\
    \ ++i) {\n    if (i) std::cout << \" \";\n    std::cout << workspace::binary_search(\n\
    \        size_t(0), size(s) + 1, [&](size_t len) -> bool {\n          return hash.substr(0,\
    \ len) == hash.substr(i, len);\n        });\n  }\n  std::cout << \"\\n\";\n}\n"
  dependsOn:
  - string/rolling_hash.hpp
  - utils/binary_search.hpp
  - utils/random_number_generator.hpp
  isVerificationFile: true
  path: test/library-checker/zalgorithm_2.test.cpp
  requiredBy: []
  timestamp: '2020-11-04 17:56:57+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/zalgorithm_2.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/zalgorithm_2.test.cpp
- /verify/test/library-checker/zalgorithm_2.test.cpp.html
title: test/library-checker/zalgorithm_2.test.cpp
---
