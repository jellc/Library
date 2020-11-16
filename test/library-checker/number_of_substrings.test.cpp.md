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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: string/suffix_array.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/number_of_substrings\"\n\
    #include <iostream>\n\n#include \"string/suffix_array.hpp\"\n\nint main() {\n\
    \  std::string s;\n  std::cin >> s;\n  workspace::suffix_array sa(s);\n  long\
    \ long ans = 0;\n  for (size_t i = 0; i < s.size(); i++) {\n    ans += s.size()\
    \ - sa[i] - sa.lcp_array()[i];\n  }\n  printf(\"%lld\\n\", ans);\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: test/library-checker/number_of_substrings.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/library-checker/number_of_substrings.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/number_of_substrings.test.cpp
- /verify/test/library-checker/number_of_substrings.test.cpp.html
title: test/library-checker/number_of_substrings.test.cpp
---
