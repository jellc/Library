---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/graph/undirected/tree/lowest_common_ancestor.hpp\"\n\
    #include <cassert>\n#include <vector>\n\nclass lowest_common_ancestor {\n  std::vector<std::vector<size_t>>\
    \ tree, table;\n  std::vector<size_t> index;\n\n  void tour(const size_t node,\
    \ const size_t prev) {\n    index[node] = table.front().size();\n    table.front().emplace_back(node);\n\
    \    for (const size_t to : tree[node]) {\n      if (to != prev) {\n        tour(to,\
    \ node);\n        table.front().emplace_back(node);\n      }\n    }\n  }\n\n \
    \ void make_table() {\n    for (size_t w = 1; w < size(); w <<= 1) {\n      auto\
    \ &curr(table.back()), next(curr);\n      for (size_t i = 0, j = w; j != curr.size();\
    \ ++i, ++j)\n        if (index[curr[j]] < index[curr[i]]) next[i] = curr[j];\n\
    \      table.emplace_back(next);\n    }\n  }\n\n public:\n  lowest_common_ancestor(const\
    \ size_t n = 0) : tree(n), table(1), index(n) {}\n\n  size_t size() const { return\
    \ tree.size(); }\n\n  void add_edge(const size_t u, const size_t v) {\n    assert(u\
    \ < size());\n    assert(v < size());\n    tree[u].emplace_back(v);\n    tree[v].emplace_back(u);\n\
    \  }\n\n  // O(n log(n))\n  void make(const size_t root) {\n    assert(root <\
    \ size());\n    tour(root, root);\n    make_table();\n  }\n\n  // O(1)\n  size_t\
    \ query(size_t u, size_t v) const {\n    assert(u < size());\n    assert(v < size());\n\
    \    if (u == v) return u;\n    if ((v = index[v]) < (u = index[u])) std::swap(u,\
    \ v);\n    size_t h = std::__lg(v - u);\n    return std::min(table[h][u], table[h][v\
    \ - (1 << h)]);\n  }\n};  // class lowest_common_ancestor\n"
  code: "#pragma once\n#include <cassert>\n#include <vector>\n\nclass lowest_common_ancestor\
    \ {\n  std::vector<std::vector<size_t>> tree, table;\n  std::vector<size_t> index;\n\
    \n  void tour(const size_t node, const size_t prev) {\n    index[node] = table.front().size();\n\
    \    table.front().emplace_back(node);\n    for (const size_t to : tree[node])\
    \ {\n      if (to != prev) {\n        tour(to, node);\n        table.front().emplace_back(node);\n\
    \      }\n    }\n  }\n\n  void make_table() {\n    for (size_t w = 1; w < size();\
    \ w <<= 1) {\n      auto &curr(table.back()), next(curr);\n      for (size_t i\
    \ = 0, j = w; j != curr.size(); ++i, ++j)\n        if (index[curr[j]] < index[curr[i]])\
    \ next[i] = curr[j];\n      table.emplace_back(next);\n    }\n  }\n\n public:\n\
    \  lowest_common_ancestor(const size_t n = 0) : tree(n), table(1), index(n) {}\n\
    \n  size_t size() const { return tree.size(); }\n\n  void add_edge(const size_t\
    \ u, const size_t v) {\n    assert(u < size());\n    assert(v < size());\n   \
    \ tree[u].emplace_back(v);\n    tree[v].emplace_back(u);\n  }\n\n  // O(n log(n))\n\
    \  void make(const size_t root) {\n    assert(root < size());\n    tour(root,\
    \ root);\n    make_table();\n  }\n\n  // O(1)\n  size_t query(size_t u, size_t\
    \ v) const {\n    assert(u < size());\n    assert(v < size());\n    if (u == v)\
    \ return u;\n    if ((v = index[v]) < (u = index[u])) std::swap(u, v);\n    size_t\
    \ h = std::__lg(v - u);\n    return std::min(table[h][u], table[h][v - (1 << h)]);\n\
    \  }\n};  // class lowest_common_ancestor\n"
  dependsOn: []
  isVerificationFile: false
  path: src/graph/undirected/tree/lowest_common_ancestor.hpp
  requiredBy: []
  timestamp: '2020-11-16 14:21:51+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/graph/undirected/tree/lowest_common_ancestor.hpp
layout: document
redirect_from:
- /library/src/graph/undirected/tree/lowest_common_ancestor.hpp
- /library/src/graph/undirected/tree/lowest_common_ancestor.hpp.html
title: src/graph/undirected/tree/lowest_common_ancestor.hpp
---
