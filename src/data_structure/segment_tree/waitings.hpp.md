---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':question:'
    path: src/data_structure/segment_tree/lazy.hpp
    title: Lazy Segment Tree
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/aizu-online-judge/2450.test.cpp
    title: test/aizu-online-judge/2450.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/range_affine_range_sum.test.cpp
    title: test/library-checker/range_affine_range_sum.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/data_structure/segment_tree/waitings.hpp\"\n\n#include\
    \ <cstdint>\n#include <queue>\n\nnamespace workspace {\n\nnamespace internal {\n\
    \nstruct waitings : std::queue<size_t> {\n  waitings(size_t n) : in(n) {}\n\n\
    \  bool push(size_t index) {\n    // assert(index < in.size());\n    if (in[index])\
    \ return false;\n    emplace(index);\n    return (in[index] = true);\n  }\n\n\
    \  size_t pop() {\n    // assert(!empty());\n    auto index = front();\n    std::queue<size_t>::pop();\n\
    \    in[index] = false;\n    return index;\n  }\n\n private:\n  std::vector<int_least8_t>\
    \ in;\n};\n\n}  // namespace internal\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n#include <cstdint>\n#include <queue>\n\nnamespace workspace\
    \ {\n\nnamespace internal {\n\nstruct waitings : std::queue<size_t> {\n  waitings(size_t\
    \ n) : in(n) {}\n\n  bool push(size_t index) {\n    // assert(index < in.size());\n\
    \    if (in[index]) return false;\n    emplace(index);\n    return (in[index]\
    \ = true);\n  }\n\n  size_t pop() {\n    // assert(!empty());\n    auto index\
    \ = front();\n    std::queue<size_t>::pop();\n    in[index] = false;\n    return\
    \ index;\n  }\n\n private:\n  std::vector<int_least8_t> in;\n};\n\n}  // namespace\
    \ internal\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/data_structure/segment_tree/waitings.hpp
  requiredBy:
  - src/data_structure/segment_tree/lazy.hpp
  timestamp: '2020-12-25 02:08:14+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/library-checker/range_affine_range_sum.test.cpp
  - test/aizu-online-judge/2450.test.cpp
documentation_of: src/data_structure/segment_tree/waitings.hpp
layout: document
redirect_from:
- /library/src/data_structure/segment_tree/waitings.hpp
- /library/src/data_structure/segment_tree/waitings.hpp.html
title: src/data_structure/segment_tree/waitings.hpp
---
