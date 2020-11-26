---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: XOR Elimination
    links: []
  bundledCode: "#line 2 \"src/algebra/linear/xor_elimination.hpp\"\n\n/*\n * @file\
    \ xor_elimination.hpp\n * @brief XOR Elimination\n */\n\n#include <vector>\n\n\
    namespace workspace {\n\ntemplate <class Expr> struct xor_elimination {\n  std::vector<Expr>\
    \ base;\n  bool add(Expr e) {\n    for (const Expr &b : base)\n      if ((b ^\
    \ e) < e) e ^= b;\n    if (e) base.emplace_back(e);\n    return e;\n  }\n  size_t\
    \ dim() const { return base.size(); }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file xor_elimination.hpp\n * @brief XOR Elimination\n\
    \ */\n\n#include <vector>\n\nnamespace workspace {\n\ntemplate <class Expr> struct\
    \ xor_elimination {\n  std::vector<Expr> base;\n  bool add(Expr e) {\n    for\
    \ (const Expr &b : base)\n      if ((b ^ e) < e) e ^= b;\n    if (e) base.emplace_back(e);\n\
    \    return e;\n  }\n  size_t dim() const { return base.size(); }\n};\n\n}  //\
    \ namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/algebra/linear/xor_elimination.hpp
  requiredBy: []
  timestamp: '2020-11-26 16:42:40+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/algebra/linear/xor_elimination.hpp
layout: document
redirect_from:
- /library/src/algebra/linear/xor_elimination.hpp
- /library/src/algebra/linear/xor_elimination.hpp.html
title: XOR Elimination
---
