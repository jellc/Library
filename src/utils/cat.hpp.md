---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Cat
    links: []
  bundledCode: "#line 2 \"src/utils/cat.hpp\"\n\n/**\n * @file cat.hpp\n * @brief\
    \ Cat\n */\n\n#include <iterator>\n\nnamespace workspace {\n\ntemplate <class\
    \ C1, class C2>\nconstexpr C1 &&cat(C1 &&__c1, C2 const &__c2) noexcept {\n  __c1.insert(__c1.end(),\
    \ std::begin(__c2), std::end(__c2));\n  return __c1;\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file cat.hpp\n * @brief Cat\n */\n\n#include <iterator>\n\
    \nnamespace workspace {\n\ntemplate <class C1, class C2>\nconstexpr C1 &&cat(C1\
    \ &&__c1, C2 const &__c2) noexcept {\n  __c1.insert(__c1.end(), std::begin(__c2),\
    \ std::end(__c2));\n  return __c1;\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/cat.hpp
  requiredBy: []
  timestamp: '2020-12-23 01:53:27+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/cat.hpp
layout: document
redirect_from:
- /library/src/utils/cat.hpp
- /library/src/utils/cat.hpp.html
title: Cat
---
