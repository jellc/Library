---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Reversed
    links: []
  bundledCode: "#line 2 \"src/utils/py-like/reversed.hpp\"\n\n/*\n * @file reversed.hpp\n\
    \ * @brief Reversed\n */\n\n#include <initializer_list>\n#include <iterator>\n\
    \nnamespace workspace {\n\ntemplate <class Container> class reversal {\n  Container\
    \ cont;\n\n public:\n  constexpr reversal(Container &&cont) : cont(cont) {}\n\n\
    \  constexpr auto begin() { return std::rbegin(cont); }\n  constexpr auto end()\
    \ { return std::rend(cont); }\n};\n\ntemplate <class Container> constexpr auto\
    \ reversed(Container &&cont) noexcept {\n  return reversal<Container>{std::forward<Container>(cont)};\n\
    }\n\ntemplate <class Tp>\nconstexpr auto reversed(std::initializer_list<Tp> &&cont)\
    \ noexcept {\n  return reversal<std::initializer_list<Tp>>{\n      std::forward<std::initializer_list<Tp>>(cont)};\n\
    }\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file reversed.hpp\n * @brief Reversed\n */\n\n#include\
    \ <initializer_list>\n#include <iterator>\n\nnamespace workspace {\n\ntemplate\
    \ <class Container> class reversal {\n  Container cont;\n\n public:\n  constexpr\
    \ reversal(Container &&cont) : cont(cont) {}\n\n  constexpr auto begin() { return\
    \ std::rbegin(cont); }\n  constexpr auto end() { return std::rend(cont); }\n};\n\
    \ntemplate <class Container> constexpr auto reversed(Container &&cont) noexcept\
    \ {\n  return reversal<Container>{std::forward<Container>(cont)};\n}\n\ntemplate\
    \ <class Tp>\nconstexpr auto reversed(std::initializer_list<Tp> &&cont) noexcept\
    \ {\n  return reversal<std::initializer_list<Tp>>{\n      std::forward<std::initializer_list<Tp>>(cont)};\n\
    }\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/py-like/reversed.hpp
  requiredBy: []
  timestamp: '2020-12-04 00:31:11+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/py-like/reversed.hpp
layout: document
redirect_from:
- /library/src/utils/py-like/reversed.hpp
- /library/src/utils/py-like/reversed.hpp.html
title: Reversed
---
