---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: template.cpp
    title: Code template
  - icon: ':warning:'
    path: utils.hpp
    title: all headers in utlis
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Ejection from try block
    links: []
  bundledCode: "#line 2 \"utils/ejection.hpp\"\n\n/*\n * @file ejection.hpp\n * @brief\
    \ Ejection from try block\n */\n\n#include <iostream>\n\nnamespace workspace {\n\
    \n/*\n * @brief eject from a try block, throw nullptr\n * @param arg output\n\
    \ */\ntemplate <class Tp> void eject(Tp const &arg) {\n  std::cout << arg << \"\
    \\n\";\n  throw nullptr;\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file ejection.hpp\n * @brief Ejection from try block\n\
    \ */\n\n#include <iostream>\n\nnamespace workspace {\n\n/*\n * @brief eject from\
    \ a try block, throw nullptr\n * @param arg output\n */\ntemplate <class Tp> void\
    \ eject(Tp const &arg) {\n  std::cout << arg << \"\\n\";\n  throw nullptr;\n}\n\
    \n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/ejection.hpp
  requiredBy:
  - template.cpp
  - utils.hpp
  timestamp: '2020-11-07 14:25:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils/ejection.hpp
layout: document
redirect_from:
- /library/utils/ejection.hpp
- /library/utils/ejection.hpp.html
title: Ejection from try block
---
