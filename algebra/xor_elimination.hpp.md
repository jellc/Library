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
  bundledCode: "#line 1 \"algebra/xor_elimination.hpp\"\n#include <vector>\n\ntemplate\
    \ <class expr>\nstruct xor_elimination\n{\n    std::vector<expr> base;\n    bool\
    \ add(expr e)\n    {\n        for(const expr &b : base) if((b ^ e) < e) e ^= b;\n\
    \        if(e) base.emplace_back(e);\n        return e;\n    }\n    size_t dim()\
    \ const { return base.size(); }\n};\n"
  code: "#include <vector>\n\ntemplate <class expr>\nstruct xor_elimination\n{\n \
    \   std::vector<expr> base;\n    bool add(expr e)\n    {\n        for(const expr\
    \ &b : base) if((b ^ e) < e) e ^= b;\n        if(e) base.emplace_back(e);\n  \
    \      return e;\n    }\n    size_t dim() const { return base.size(); }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: algebra/xor_elimination.hpp
  requiredBy: []
  timestamp: '2020-08-06 01:13:39+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: algebra/xor_elimination.hpp
layout: document
redirect_from:
- /library/algebra/xor_elimination.hpp
- /library/algebra/xor_elimination.hpp.html
title: algebra/xor_elimination.hpp
---
