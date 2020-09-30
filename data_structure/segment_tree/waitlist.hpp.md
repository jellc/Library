---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: data_structure/segment_tree/basic.hpp
    title: data_structure/segment_tree/basic.hpp
  - icon: ':heavy_check_mark:'
    path: data_structure/segment_tree/lazy.hpp
    title: data_structure/segment_tree/lazy.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/do_use_segment_tree.test.cpp
    title: test/aizu-online-judge/do_use_segment_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/range_minimum_query.test.cpp
    title: test/aizu-online-judge/range_minimum_query.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/point_set_range_composite.test.cpp
    title: test/library-checker/point_set_range_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/range_affine_range_sum.test.cpp
    title: test/library-checker/range_affine_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/static_range_inversions_query.test.cpp
    title: test/library-checker/static_range_inversions_query.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"data_structure/segment_tree/waitlist.hpp\"\n#include <queue>\n\
    \nnamespace internal {\nstruct waitlist : std::queue<size_t> {\n  waitlist(size_t\
    \ n) : in(n) {}\n\n  bool push(size_t index) {\n    assert(index < in.size());\n\
    \    if (in[index]) return false;\n    emplace(index);\n    return (in[index]\
    \ = true);\n  }\n\n  size_t pop() {\n    assert(!empty());\n    auto index = front();\n\
    \    std::queue<size_t>::pop();\n    in[index] = false;\n    return index;\n \
    \ }\n\n private:\n  std::vector<int_least8_t> in;\n};\n}\n"
  code: "#pragma once\n#include <queue>\n\nnamespace internal {\nstruct waitlist :\
    \ std::queue<size_t> {\n  waitlist(size_t n) : in(n) {}\n\n  bool push(size_t\
    \ index) {\n    assert(index < in.size());\n    if (in[index]) return false;\n\
    \    emplace(index);\n    return (in[index] = true);\n  }\n\n  size_t pop() {\n\
    \    assert(!empty());\n    auto index = front();\n    std::queue<size_t>::pop();\n\
    \    in[index] = false;\n    return index;\n  }\n\n private:\n  std::vector<int_least8_t>\
    \ in;\n};\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/segment_tree/waitlist.hpp
  requiredBy:
  - data_structure/segment_tree/lazy.hpp
  - data_structure/segment_tree/basic.hpp
  timestamp: '2020-09-27 00:42:26+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/static_range_inversions_query.test.cpp
  - test/library-checker/range_affine_range_sum.test.cpp
  - test/library-checker/point_set_range_composite.test.cpp
  - test/aizu-online-judge/do_use_segment_tree.test.cpp
  - test/aizu-online-judge/range_minimum_query.test.cpp
documentation_of: data_structure/segment_tree/waitlist.hpp
layout: document
redirect_from:
- /library/data_structure/segment_tree/waitlist.hpp
- /library/data_structure/segment_tree/waitlist.hpp.html
title: data_structure/segment_tree/waitlist.hpp
---
