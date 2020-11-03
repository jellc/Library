---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: template.cpp
    title: template.cpp
  - icon: ':warning:'
    path: utils.hpp
    title: utils.hpp
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: eject from a try block, throw nullptr
    links: []
  bundledCode: "#line 2 \"utils/ejection.hpp\"\n#include <iostream>\n\nnamespace workspace\
    \ {\n\n/*\n * @brief eject from a try block, throw nullptr\n * @param arg output\n\
    \ */\ntemplate <class Tp> void eject(Tp const &arg) {\n  std::cout << arg << \"\
    \\n\";\n  throw nullptr;\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n#include <iostream>\n\nnamespace workspace {\n\n/*\n * @brief\
    \ eject from a try block, throw nullptr\n * @param arg output\n */\ntemplate <class\
    \ Tp> void eject(Tp const &arg) {\n  std::cout << arg << \"\\n\";\n  throw nullptr;\n\
    }\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/ejection.hpp
  requiredBy:
  - template.cpp
  - utils.hpp
  timestamp: '2020-11-03 22:14:56+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils/ejection.hpp
layout: document
redirect_from:
- /library/utils/ejection.hpp
- /library/utils/ejection.hpp.html
title: eject from a try block, throw nullptr
---
