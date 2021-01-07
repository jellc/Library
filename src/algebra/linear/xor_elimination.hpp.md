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
  bundledCode: "#line 2 \"src/algebra/linear/xor_elimination.hpp\"\n\n/**\n * @file\
    \ xor_elimination.hpp\n * @brief XOR Elimination\n */\n\n#include <vector>\n\n\
    namespace workspace {\n\ntemplate <class Expr> class xor_elimination : std::vector<Expr>\
    \ {\n  using base = std::vector<Expr>;\n public:\n  using base::begin;\n  using\
    \ base::end;\n  using base::size;\n\n  bool add(Expr __e) {\n    for (auto __i\
    \ = begin(); __i != end(); ++__i)\n      if ((*__i ^ __e) < __e) __e ^= *__i;\n\
    \    if (__e) base::emplace_back(__e);\n    return __e;\n  }\n};\n\n}  // namespace\
    \ workspace\n"
  code: "#pragma once\n\n/**\n * @file xor_elimination.hpp\n * @brief XOR Elimination\n\
    \ */\n\n#include <vector>\n\nnamespace workspace {\n\ntemplate <class Expr> class\
    \ xor_elimination : std::vector<Expr> {\n  using base = std::vector<Expr>;\n public:\n\
    \  using base::begin;\n  using base::end;\n  using base::size;\n\n  bool add(Expr\
    \ __e) {\n    for (auto __i = begin(); __i != end(); ++__i)\n      if ((*__i ^\
    \ __e) < __e) __e ^= *__i;\n    if (__e) base::emplace_back(__e);\n    return\
    \ __e;\n  }\n};\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/algebra/linear/xor_elimination.hpp
  requiredBy: []
  timestamp: '2021-01-07 23:55:43+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/algebra/linear/xor_elimination.hpp
layout: document
redirect_from:
- /library/src/algebra/linear/xor_elimination.hpp
- /library/src/algebra/linear/xor_elimination.hpp.html
title: XOR Elimination
---
