---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/lowest_common_ancestor.test.cpp
    title: test/library-checker/lowest_common_ancestor.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 2 \"graph/undirected/tree/lowest_common_ancestor.hpp\"\n#include\
    \ <cassert>\n#include <vector>\n\nclass lowest_common_ancestor {\n  std::vector<std::vector<size_t>>\
    \ tree, table;\n  std::vector<size_t> &sorted, index;\n\n  void tour(const size_t\
    \ node, const size_t prev) {\n    index[node] = sorted.size();\n    sorted.emplace_back(node);\n\
    \    for (const size_t to : tree[node]) {\n      if (to != prev) {\n        tour(to,\
    \ node);\n        sorted.emplace_back(node);\n      }\n    }\n  }\n\n  void make_table()\
    \ {\n    const size_t len = sorted.size();\n    for (size_t w = 2; w < len; w\
    \ <<= 1) {\n      std::vector<size_t> &crt(table.back()), nxt(crt);\n      for\
    \ (size_t i = 0, j = w >> 1; j != len; ++i, ++j)\n        if (index[crt[j]] <\
    \ index[crt[i]]) nxt[i] = crt[j];\n      table.emplace_back(nxt);\n    }\n  }\n\
    \n public:\n  lowest_common_ancestor(const size_t n = 0)\n      : tree(n), table(1),\
    \ sorted(table.front()), index(n) {}\n\n  size_t size() const { return tree.size();\
    \ }\n\n  void add_edge(const size_t u, const size_t v) {\n    assert(u < size());\n\
    \    assert(v < size());\n    tree[u].emplace_back(v);\n    tree[v].emplace_back(u);\n\
    \  }\n\n  // O(n log(n))\n  void make(const size_t root) {\n    assert(root <\
    \ size());\n    tour(root, root);\n    make_table();\n  }\n\n  // O(1)\n  size_t\
    \ query(size_t u, size_t v) const {\n    assert(u < size());\n    assert(v < size());\n\
    \    if (u == v) return u;\n    if ((v = index[v]) < (u = index[u])) std::swap(u,\
    \ v);\n    size_t h = std::__lg(v - u);\n    return std::min(table[h][u], table[h][v\
    \ - (1 << h)]);\n  }\n};  // class lowest_common_ancestor\n"
  code: "#pragma once\n#include <cassert>\n#include <vector>\n\nclass lowest_common_ancestor\
    \ {\n  std::vector<std::vector<size_t>> tree, table;\n  std::vector<size_t> &sorted,\
    \ index;\n\n  void tour(const size_t node, const size_t prev) {\n    index[node]\
    \ = sorted.size();\n    sorted.emplace_back(node);\n    for (const size_t to :\
    \ tree[node]) {\n      if (to != prev) {\n        tour(to, node);\n        sorted.emplace_back(node);\n\
    \      }\n    }\n  }\n\n  void make_table() {\n    const size_t len = sorted.size();\n\
    \    for (size_t w = 2; w < len; w <<= 1) {\n      std::vector<size_t> &crt(table.back()),\
    \ nxt(crt);\n      for (size_t i = 0, j = w >> 1; j != len; ++i, ++j)\n      \
    \  if (index[crt[j]] < index[crt[i]]) nxt[i] = crt[j];\n      table.emplace_back(nxt);\n\
    \    }\n  }\n\n public:\n  lowest_common_ancestor(const size_t n = 0)\n      :\
    \ tree(n), table(1), sorted(table.front()), index(n) {}\n\n  size_t size() const\
    \ { return tree.size(); }\n\n  void add_edge(const size_t u, const size_t v) {\n\
    \    assert(u < size());\n    assert(v < size());\n    tree[u].emplace_back(v);\n\
    \    tree[v].emplace_back(u);\n  }\n\n  // O(n log(n))\n  void make(const size_t\
    \ root) {\n    assert(root < size());\n    tour(root, root);\n    make_table();\n\
    \  }\n\n  // O(1)\n  size_t query(size_t u, size_t v) const {\n    assert(u <\
    \ size());\n    assert(v < size());\n    if (u == v) return u;\n    if ((v = index[v])\
    \ < (u = index[u])) std::swap(u, v);\n    size_t h = std::__lg(v - u);\n    return\
    \ std::min(table[h][u], table[h][v - (1 << h)]);\n  }\n};  // class lowest_common_ancestor\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/undirected/tree/lowest_common_ancestor.hpp
  requiredBy: []
  timestamp: '2020-09-25 14:52:32+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/lowest_common_ancestor.test.cpp
documentation_of: graph/undirected/tree/lowest_common_ancestor.hpp
layout: document
redirect_from:
- /library/graph/undirected/tree/lowest_common_ancestor.hpp
- /library/graph/undirected/tree/lowest_common_ancestor.hpp.html
title: graph/undirected/tree/lowest_common_ancestor.hpp
---
