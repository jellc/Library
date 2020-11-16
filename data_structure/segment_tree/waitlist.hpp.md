---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
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
  requiredBy: []
  timestamp: '2020-09-27 00:42:26+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/segment_tree/waitlist.hpp
layout: document
redirect_from:
- /library/data_structure/segment_tree/waitlist.hpp
- /library/data_structure/segment_tree/waitlist.hpp.html
title: data_structure/segment_tree/waitlist.hpp
---
