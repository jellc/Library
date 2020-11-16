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
  bundledCode: "#line 2 \"src/utils/ejection.hpp\"\n\n/*\n * @file ejection.hpp\n\
    \ * @brief Ejection\n */\n\n#include <iostream>\n\nnamespace workspace {\n\n/*\n\
    \ * @brief eject from a try block, throw nullptr\n * @param arg output\n */\n\
    template <class Tp> void eject(Tp const &arg) {\n  std::cout << arg << \"\\n\"\
    ;\n  throw nullptr;\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file ejection.hpp\n * @brief Ejection\n */\n\n#include\
    \ <iostream>\n\nnamespace workspace {\n\n/*\n * @brief eject from a try block,\
    \ throw nullptr\n * @param arg output\n */\ntemplate <class Tp> void eject(Tp\
    \ const &arg) {\n  std::cout << arg << \"\\n\";\n  throw nullptr;\n}\n\n}  //\
    \ namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/ejection.hpp
  requiredBy: []
  timestamp: '2020-11-16 14:21:51+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/ejection.hpp
layout: document
redirect_from:
- /library/src/utils/ejection.hpp
- /library/src/utils/ejection.hpp.html
title: Ejection
---
