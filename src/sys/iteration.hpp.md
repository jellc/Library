---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/sys/ejection.hpp
    title: Ejection
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/ITP1_3_B.test.cpp
    title: test/aizu-online-judge/ITP1_3_B.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Case Iteration
    links: []
  bundledCode: "#line 2 \"src/sys/iteration.hpp\"\n\n/**\n * @file iteration.hpp\n\
    \ * @brief Case Iteration\n */\n\n#include <cassert>\n\n#line 2 \"src/sys/ejection.hpp\"\
    \n\n/**\n * @file ejection.hpp\n * @brief Ejection\n */\n\n#include <iostream>\n\
    \nnamespace workspace {\n\nnamespace internal {\n\nstruct ejection {\n  bool exit\
    \ = 0;\n};\n\n}  // namespace internal\n\n/**\n * @brief eject from a try block,\
    \ throw nullptr\n * @param arg output\n */\ntemplate <class Tp> void eject(Tp\
    \ const &arg) {\n  std::cout << arg << \"\\n\";\n  throw internal::ejection{};\n\
    }\n\nvoid exit() { throw internal::ejection{true}; }\n\n}  // namespace workspace\n\
    #line 11 \"src/sys/iteration.hpp\"\n\nnamespace workspace {\n\nvoid main();\n\n\
    struct {\n  // 1-indexed\n  unsigned current{0};\n  unsigned total{1};\n\n  void\
    \ read() { (std::cin >> total).ignore(); }\n\n  int iterate() {\n    static bool\
    \ once = false;\n    assert(!once);\n    once = true;\n    while (current++ <\
    \ total) {\n      try {\n        main();\n      } catch (internal::ejection const&\
    \ status) {\n        if (status.exit) break;\n      }\n    }\n    return 0;\n\
    \  }\n} case_info;\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file iteration.hpp\n * @brief Case Iteration\n */\n\
    \n#include <cassert>\n\n#include \"ejection.hpp\"\n\nnamespace workspace {\n\n\
    void main();\n\nstruct {\n  // 1-indexed\n  unsigned current{0};\n  unsigned total{1};\n\
    \n  void read() { (std::cin >> total).ignore(); }\n\n  int iterate() {\n    static\
    \ bool once = false;\n    assert(!once);\n    once = true;\n    while (current++\
    \ < total) {\n      try {\n        main();\n      } catch (internal::ejection\
    \ const& status) {\n        if (status.exit) break;\n      }\n    }\n    return\
    \ 0;\n  }\n} case_info;\n\n}  // namespace workspace\n"
  dependsOn:
  - src/sys/ejection.hpp
  isVerificationFile: false
  path: src/sys/iteration.hpp
  requiredBy: []
  timestamp: '2021-01-08 00:38:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aizu-online-judge/ITP1_3_B.test.cpp
documentation_of: src/sys/iteration.hpp
layout: document
redirect_from:
- /library/src/sys/iteration.hpp
- /library/src/sys/iteration.hpp.html
title: Case Iteration
---
