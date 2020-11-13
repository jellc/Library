---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Ejection
    links: []
  bundledCode: "#line 2 \"utils/ejection.hpp\"\n\n/*\n * @file ejection.hpp\n * @brief\
    \ Ejection\n */\n\n#include <iostream>\n\nnamespace workspace {\n\n/*\n * @brief\
    \ eject from a try block, throw nullptr\n * @param arg output\n */\ntemplate <class\
    \ Tp> void eject(Tp const &arg) {\n  std::cout << arg << \"\\n\";\n  throw nullptr;\n\
    }\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file ejection.hpp\n * @brief Ejection\n */\n\n#include\
    \ <iostream>\n\nnamespace workspace {\n\n/*\n * @brief eject from a try block,\
    \ throw nullptr\n * @param arg output\n */\ntemplate <class Tp> void eject(Tp\
    \ const &arg) {\n  std::cout << arg << \"\\n\";\n  throw nullptr;\n}\n\n}  //\
    \ namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/ejection.hpp
  requiredBy: []
  timestamp: '2020-11-14 01:17:16+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils/ejection.hpp
layout: document
redirect_from:
- /library/utils/ejection.hpp
- /library/utils/ejection.hpp.html
title: Ejection
---
