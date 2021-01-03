---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/sys/ejection.hpp
    title: Ejection
  - icon: ':heavy_check_mark:'
    path: src/sys/iteration.hpp
    title: Case Iteration
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/ITP1_3_B
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/ITP1_3_B
  bundledCode: "#line 1 \"test/aizu-online-judge/ITP1_3_B.test.cpp\"\n#define PROBLEM\
    \ \"https://onlinejudge.u-aizu.ac.jp/problems/ITP1_3_B\"\n\n#line 2 \"src/sys/iteration.hpp\"\
    \n\n/*\n * @file iteration.hpp\n * @brief Case Iteration\n */\n\n#include <cassert>\n\
    \n#line 2 \"src/sys/ejection.hpp\"\n\n/*\n * @file ejection.hpp\n * @brief Ejection\n\
    \ */\n\n#include <iostream>\n\nnamespace workspace {\n\nstruct ejection {\n  bool\
    \ exit = 0;\n};\n\n/*\n * @brief eject from a try block, throw nullptr\n * @param\
    \ arg output\n */\ntemplate <class Tp> void eject(Tp const &arg) {\n  std::cout\
    \ << arg << \"\\n\";\n  throw ejection{};\n}\n\nvoid exit() { throw ejection{true};\
    \ }\n\n}  // namespace workspace\n#line 11 \"src/sys/iteration.hpp\"\n\nnamespace\
    \ workspace {\n\nvoid main();\n\nstruct {\n  // 1-indexed\n  unsigned current{0};\n\
    \  unsigned total{1};\n\n  void read() { (std::cin >> total).ignore(); }\n\n \
    \ int iterate() {\n    static bool once = false;\n    assert(!once);\n    once\
    \ = true;\n    while (current++ < total) {\n      try {\n        main();\n   \
    \   } catch (ejection const& status) {\n        if (status.exit) break;\n    \
    \  }\n    }\n    return 0;\n  }\n} case_info;\n\n}  // namespace workspace\n#line\
    \ 4 \"test/aizu-online-judge/ITP1_3_B.test.cpp\"\n\nnamespace workspace {\n\n\
    void main() {\n  int x;\n  std::cin >> x;\n  if (!x) exit();\n  std::cout << \"\
    Case \" << case_info.current << \": \" << x << std::endl;\n}\n\n}  // namespace\
    \ workspace\n\nint main() {\n  workspace::case_info.total = -1;\n  return workspace::case_info.iterate();\n\
    }\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ITP1_3_B\"\n\n\
    #include \"src/sys/iteration.hpp\"\n\nnamespace workspace {\n\nvoid main() {\n\
    \  int x;\n  std::cin >> x;\n  if (!x) exit();\n  std::cout << \"Case \" << case_info.current\
    \ << \": \" << x << std::endl;\n}\n\n}  // namespace workspace\n\nint main() {\n\
    \  workspace::case_info.total = -1;\n  return workspace::case_info.iterate();\n\
    }\n"
  dependsOn:
  - src/sys/iteration.hpp
  - src/sys/ejection.hpp
  isVerificationFile: true
  path: test/aizu-online-judge/ITP1_3_B.test.cpp
  requiredBy: []
  timestamp: '2021-01-03 22:35:23+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aizu-online-judge/ITP1_3_B.test.cpp
layout: document
redirect_from:
- /verify/test/aizu-online-judge/ITP1_3_B.test.cpp
- /verify/test/aizu-online-judge/ITP1_3_B.test.cpp.html
title: test/aizu-online-judge/ITP1_3_B.test.cpp
---
