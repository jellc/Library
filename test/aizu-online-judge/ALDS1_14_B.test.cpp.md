---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B
  bundledCode: "#line 1 \"test/aizu-online-judge/ALDS1_14_B.test.cpp\"\n#define PROBLEM\
    \ \"https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B\"\n\n#include <algorithm>\n\
    #include <iostream>\n\n#line 1 \"src/string/kmp.hh\"\n/**\n * @file kmp.hh\n *\
    \ @brief Knuth-Morris-Pratt Algorithm\n * @date 2021-01-08\n */\n\n#include <vector>\n\
    \nnamespace workspace {\n\n/**\n * @brief Knuth-Morris-Pratt Algorithm.\n *\n\
    \ * @param __s A string\n * @return i-th element(1-indexed) describes the prefix\
    \ of length i.\n */\ntemplate <class Str> std::vector<size_t> kmp_algorithm(Str\
    \ const& __s) {\n  std::vector<size_t> __k(std::size(__s));\n  if (!__k.empty())\n\
    \    for (size_t __p{}, __q{1}; __q != __k.size(); __k[__q++] = ++__p)\n     \
    \ while (__s[__p] != __s[__q]) {\n        if (!__p--) break;\n        __p = __k[__p];\n\
    \      }\n  return __k;\n}\n\n}  // namespace workspace\n#line 7 \"test/aizu-online-judge/ALDS1_14_B.test.cpp\"\
    \n\nint main() {\n  using namespace workspace;\n\n  std::string t, p;\n  std::cin\
    \ >> t >> p;\n  auto k = kmp_algorithm(p + '$' + t);\n  for (size_t i = 0, j =\
    \ p.size() * 2; j < k.size(); ++i, ++j)\n    if (k[j] == p.size()) std::cout <<\
    \ i << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B\"\n\
    \n#include <algorithm>\n#include <iostream>\n\n#include \"src/string/kmp.hh\"\n\
    \nint main() {\n  using namespace workspace;\n\n  std::string t, p;\n  std::cin\
    \ >> t >> p;\n  auto k = kmp_algorithm(p + '$' + t);\n  for (size_t i = 0, j =\
    \ p.size() * 2; j < k.size(); ++i, ++j)\n    if (k[j] == p.size()) std::cout <<\
    \ i << \"\\n\";\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: test/aizu-online-judge/ALDS1_14_B.test.cpp
  requiredBy: []
  timestamp: '2021-01-08 21:57:26+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aizu-online-judge/ALDS1_14_B.test.cpp
layout: document
redirect_from:
- /verify/test/aizu-online-judge/ALDS1_14_B.test.cpp
- /verify/test/aizu-online-judge/ALDS1_14_B.test.cpp.html
title: test/aizu-online-judge/ALDS1_14_B.test.cpp
---
