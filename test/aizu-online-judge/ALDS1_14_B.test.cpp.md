---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/string/kmp.hpp
    title: Knuth-Morris-Pratt Algorithm
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
    #include <cassert>\n#include <iostream>\n\n#line 1 \"src/string/kmp.hpp\"\n/**\n\
    \ * @file kmp.hpp\n * @brief Knuth-Morris-Pratt Algorithm\n * @date 2021-01-08\n\
    \ */\n\n#include <vector>\n\nnamespace workspace {\n\n/**\n * @brief Morris-Pratt\
    \ algorithm.\n *\n * @param __s String\n * @return The border array of given string.\n\
    \ */\ntemplate <class _Str> std::vector<size_t> mp_algorithm(_Str const& __s)\
    \ {\n  std::vector<size_t> __b(std::size(__s) + 1);\n  for (size_t __p{__b[0]\
    \ = -1}, __q{}; __q != __s.size(); __b[++__q] = ++__p)\n    while (~__p && __s[__p]\
    \ != __s[__q]) __p = __b[__p];\n  return __b;\n}\n\n/**\n * @brief Knuth-Morris-Pratt\
    \ algorithm.\n *\n * @param __s String\n * @return The strong-border array of\
    \ given string.\n */\ntemplate <class _Str> std::vector<size_t> kmp_algorithm(_Str\
    \ const& __s) {\n  auto __b = mp_algorithm(__s);\n  for (size_t __i{1}; __i !=\
    \ __s.size(); ++__i)\n    if (__s[__i] == __s[__b[__i]]) __b[__i] = __b[__b[__i]];\n\
    \  return __b;\n}\n\n}  // namespace workspace\n#line 8 \"test/aizu-online-judge/ALDS1_14_B.test.cpp\"\
    \n\nint main() {\n  using namespace workspace;\n\n  std::string t, p;\n  std::cin\
    \ >> t >> p;\n  auto b = mp_algorithm(p + '$' + t);\n  auto sb = kmp_algorithm(p\
    \ + '$' + t);\n  for (size_t i = 0, j = p.size() * 2 + 1; j < b.size(); ++i, ++j)\n\
    \    if (b[j] == p.size()) {\n      assert(sb[j] == p.size());\n      std::cout\
    \ << i << \"\\n\";\n    } else\n      assert(sb[j] != p.size());\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B\"\n\
    \n#include <algorithm>\n#include <cassert>\n#include <iostream>\n\n#include \"\
    src/string/kmp.hpp\"\n\nint main() {\n  using namespace workspace;\n\n  std::string\
    \ t, p;\n  std::cin >> t >> p;\n  auto b = mp_algorithm(p + '$' + t);\n  auto\
    \ sb = kmp_algorithm(p + '$' + t);\n  for (size_t i = 0, j = p.size() * 2 + 1;\
    \ j < b.size(); ++i, ++j)\n    if (b[j] == p.size()) {\n      assert(sb[j] ==\
    \ p.size());\n      std::cout << i << \"\\n\";\n    } else\n      assert(sb[j]\
    \ != p.size());\n}\n"
  dependsOn:
  - src/string/kmp.hpp
  isVerificationFile: true
  path: test/aizu-online-judge/ALDS1_14_B.test.cpp
  requiredBy: []
  timestamp: '2021-01-11 15:54:41+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aizu-online-judge/ALDS1_14_B.test.cpp
layout: document
redirect_from:
- /verify/test/aizu-online-judge/ALDS1_14_B.test.cpp
- /verify/test/aizu-online-judge/ALDS1_14_B.test.cpp.html
title: test/aizu-online-judge/ALDS1_14_B.test.cpp
---
