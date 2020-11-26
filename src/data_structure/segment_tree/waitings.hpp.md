---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/data_structure/segment_tree/waitings.hpp\"\n#include\
    \ <queue>\n\nnamespace workspace {\n\nnamespace internal {\n\nstruct waitings\
    \ : std::queue<size_t> {\n  waitings(size_t n) : in(n) {}\n\n  bool push(size_t\
    \ index) {\n    assert(index < in.size());\n    if (in[index]) return false;\n\
    \    emplace(index);\n    return (in[index] = true);\n  }\n\n  size_t pop() {\n\
    \    assert(!empty());\n    auto index = front();\n    std::queue<size_t>::pop();\n\
    \    in[index] = false;\n    return index;\n  }\n\n private:\n  std::vector<int_least8_t>\
    \ in;\n};\n\n}  // namespace internal\n\n}  // namespace workspace\n"
  code: "#pragma once\n#include <queue>\n\nnamespace workspace {\n\nnamespace internal\
    \ {\n\nstruct waitings : std::queue<size_t> {\n  waitings(size_t n) : in(n) {}\n\
    \n  bool push(size_t index) {\n    assert(index < in.size());\n    if (in[index])\
    \ return false;\n    emplace(index);\n    return (in[index] = true);\n  }\n\n\
    \  size_t pop() {\n    assert(!empty());\n    auto index = front();\n    std::queue<size_t>::pop();\n\
    \    in[index] = false;\n    return index;\n  }\n\n private:\n  std::vector<int_least8_t>\
    \ in;\n};\n\n}  // namespace internal\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/data_structure/segment_tree/waitings.hpp
  requiredBy: []
  timestamp: '2020-11-22 05:28:28+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/data_structure/segment_tree/waitings.hpp
layout: document
redirect_from:
- /library/src/data_structure/segment_tree/waitings.hpp
- /library/src/data_structure/segment_tree/waitings.hpp.html
title: src/data_structure/segment_tree/waitings.hpp
---
