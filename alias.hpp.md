---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: template.cpp
    title: Template
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Alias
    links: []
  bundledCode: "#line 2 \"alias.hpp\"\n\n/*\n * @file alias.hpp\n * @brief Alias\n\
    \ */\n\n#include <cstdint>\n#include <functional>\n#include <queue>\n#include\
    \ <stack>\n#include <vector>\n\nnamespace workspace {\n\nconstexpr char eol =\
    \ '\\n';\n\nusing namespace std;\n\nusing i32 = int_least32_t;\nusing i64 = int_least64_t;\n\
    using i128 = __int128_t;\nusing u32 = uint_least32_t;\nusing u64 = uint_least64_t;\n\
    using u128 = __uint128_t;\n\ntemplate <class T, class Comp = less<T>>\nusing priority_queue\
    \ = std::priority_queue<T, vector<T>, Comp>;\n\ntemplate <class T> using stack\
    \ = std::stack<T, vector<T>>;\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file alias.hpp\n * @brief Alias\n */\n\n#include\
    \ <cstdint>\n#include <functional>\n#include <queue>\n#include <stack>\n#include\
    \ <vector>\n\nnamespace workspace {\n\nconstexpr char eol = '\\n';\n\nusing namespace\
    \ std;\n\nusing i32 = int_least32_t;\nusing i64 = int_least64_t;\nusing i128 =\
    \ __int128_t;\nusing u32 = uint_least32_t;\nusing u64 = uint_least64_t;\nusing\
    \ u128 = __uint128_t;\n\ntemplate <class T, class Comp = less<T>>\nusing priority_queue\
    \ = std::priority_queue<T, vector<T>, Comp>;\n\ntemplate <class T> using stack\
    \ = std::stack<T, vector<T>>;\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: alias.hpp
  requiredBy:
  - template.cpp
  timestamp: '2020-11-07 14:25:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: alias.hpp
layout: document
redirect_from:
- /library/alias.hpp
- /library/alias.hpp.html
title: Alias
---
