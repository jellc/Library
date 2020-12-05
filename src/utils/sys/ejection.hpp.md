---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: src/utils/sys/iteration.hpp
    title: Case Iteration
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/ITP1_3_B.test.cpp
    title: test/aizu-online-judge/ITP1_3_B.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Ejection
    links: []
  bundledCode: "#line 2 \"src/utils/sys/ejection.hpp\"\n\n/*\n * @file ejection.hpp\n\
    \ * @brief Ejection\n */\n\n#include <iostream>\n\nnamespace workspace {\n\nstruct\
    \ ejection {\n  bool exit = 0;\n};\n\n/*\n * @brief eject from a try block, throw\
    \ nullptr\n * @param arg output\n */\ntemplate <class Tp> void eject(Tp const\
    \ &arg) {\n  std::cout << arg << \"\\n\";\n  throw ejection{};\n}\n\nvoid exit()\
    \ { throw ejection{true}; }\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file ejection.hpp\n * @brief Ejection\n */\n\n#include\
    \ <iostream>\n\nnamespace workspace {\n\nstruct ejection {\n  bool exit = 0;\n\
    };\n\n/*\n * @brief eject from a try block, throw nullptr\n * @param arg output\n\
    \ */\ntemplate <class Tp> void eject(Tp const &arg) {\n  std::cout << arg << \"\
    \\n\";\n  throw ejection{};\n}\n\nvoid exit() { throw ejection{true}; }\n\n} \
    \ // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/sys/ejection.hpp
  requiredBy:
  - src/utils/sys/iteration.hpp
  timestamp: '2020-12-05 14:35:22+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aizu-online-judge/ITP1_3_B.test.cpp
documentation_of: src/utils/sys/ejection.hpp
layout: document
redirect_from:
- /library/src/utils/sys/ejection.hpp
- /library/src/utils/sys/ejection.hpp.html
title: Ejection
---
