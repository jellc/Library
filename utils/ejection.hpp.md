---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utils/ejection.hpp\"\n#include <iostream>\n\nnamespace workspace\
    \ {\n// print arg, then throw nullptr.\ntemplate <class Tp> void eject(Tp const\
    \ &arg) {\n  std::cout << arg << \"\\n\";\n  throw nullptr;\n}\n}\n"
  code: "#pragma once\n#include <iostream>\n\nnamespace workspace {\n// print arg,\
    \ then throw nullptr.\ntemplate <class Tp> void eject(Tp const &arg) {\n  std::cout\
    \ << arg << \"\\n\";\n  throw nullptr;\n}\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/ejection.hpp
  requiredBy: []
  timestamp: '2020-11-03 02:57:31+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils/ejection.hpp
layout: document
redirect_from:
- /library/utils/ejection.hpp
- /library/utils/ejection.hpp.html
title: utils/ejection.hpp
---
