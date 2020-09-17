---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"algebra/system/endomorphism.hpp\"\nstruct endo\n{\n    //\
    \ compose.\n    void operator*=(const endo& rhs);\n\n    // apply self to an element\
    \ of X.\n    template <class X>\n    void apply(X &rhs) const;\n};\n"
  code: "struct endo\n{\n    // compose.\n    void operator*=(const endo& rhs);\n\n\
    \    // apply self to an element of X.\n    template <class X>\n    void apply(X\
    \ &rhs) const;\n};"
  dependsOn: []
  isVerificationFile: false
  path: algebra/system/endomorphism.hpp
  requiredBy: []
  timestamp: '2020-07-08 02:50:45+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: algebra/system/endomorphism.hpp
layout: document
redirect_from:
- /library/algebra/system/endomorphism.hpp
- /library/algebra/system/endomorphism.hpp.html
title: algebra/system/endomorphism.hpp
---
