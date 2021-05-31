---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: src/utils/py-like/enumerate.hpp
    title: Enumerate
  - icon: ':warning:'
    path: src/utils/py-like/range.hpp
    title: Range
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Reversed
    links: []
  bundledCode: "#line 2 \"src/utils/py-like/reversed.hpp\"\n\n/**\n * @file reversed.hpp\n\
    \ * @brief Reversed\n */\n\n#include <initializer_list>\n#include <iterator>\n\
    \nnamespace workspace {\n\nnamespace _reversed_impl {\n\ntemplate <class _Container>\
    \ class reversed {\n  _Container __cont;\n\n public:\n  constexpr reversed(_Container\
    \ &&__cont) noexcept : __cont(__cont) {}\n\n  constexpr decltype(auto) begin()\
    \ noexcept { return std::rbegin(__cont); }\n  constexpr decltype(auto) begin()\
    \ const noexcept {\n    return std::rbegin(__cont);\n  }\n\n  constexpr decltype(auto)\
    \ end() noexcept { return std::rend(__cont); }\n  constexpr decltype(auto) end()\
    \ const noexcept { return std::rend(__cont); }\n\n  constexpr decltype(auto) size()\
    \ const noexcept {\n    return\n#if __cplusplus < 201703L\n        __cont.size();\n\
    #else\n        std::size(__cont);\n#endif\n  }\n};\n\n}  // namespace _reversed_impl\n\
    \ntemplate <class _Container>\nconstexpr decltype(auto) reversed(_Container &&__cont)\
    \ noexcept {\n  return _reversed_impl::reversed<_Container>{std::forward<_Container>(__cont)};\n\
    }\n\ntemplate <class _Tp>\nconstexpr decltype(auto) reversed(\n    std::initializer_list<_Tp>\
    \ &&__cont) noexcept {\n  return _reversed_impl::reversed<std::initializer_list<_Tp>>{\n\
    \      std::forward<std::initializer_list<_Tp>>(__cont)};\n}\n\n}  // namespace\
    \ workspace\n"
  code: "#pragma once\n\n/**\n * @file reversed.hpp\n * @brief Reversed\n */\n\n#include\
    \ <initializer_list>\n#include <iterator>\n\nnamespace workspace {\n\nnamespace\
    \ _reversed_impl {\n\ntemplate <class _Container> class reversed {\n  _Container\
    \ __cont;\n\n public:\n  constexpr reversed(_Container &&__cont) noexcept : __cont(__cont)\
    \ {}\n\n  constexpr decltype(auto) begin() noexcept { return std::rbegin(__cont);\
    \ }\n  constexpr decltype(auto) begin() const noexcept {\n    return std::rbegin(__cont);\n\
    \  }\n\n  constexpr decltype(auto) end() noexcept { return std::rend(__cont);\
    \ }\n  constexpr decltype(auto) end() const noexcept { return std::rend(__cont);\
    \ }\n\n  constexpr decltype(auto) size() const noexcept {\n    return\n#if __cplusplus\
    \ < 201703L\n        __cont.size();\n#else\n        std::size(__cont);\n#endif\n\
    \  }\n};\n\n}  // namespace _reversed_impl\n\ntemplate <class _Container>\nconstexpr\
    \ decltype(auto) reversed(_Container &&__cont) noexcept {\n  return _reversed_impl::reversed<_Container>{std::forward<_Container>(__cont)};\n\
    }\n\ntemplate <class _Tp>\nconstexpr decltype(auto) reversed(\n    std::initializer_list<_Tp>\
    \ &&__cont) noexcept {\n  return _reversed_impl::reversed<std::initializer_list<_Tp>>{\n\
    \      std::forward<std::initializer_list<_Tp>>(__cont)};\n}\n\n}  // namespace\
    \ workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/py-like/reversed.hpp
  requiredBy:
  - src/utils/py-like/range.hpp
  - src/utils/py-like/enumerate.hpp
  timestamp: '2021-05-31 22:43:54+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/py-like/reversed.hpp
layout: document
redirect_from:
- /library/src/utils/py-like/reversed.hpp
- /library/src/utils/py-like/reversed.hpp.html
title: Reversed
---
