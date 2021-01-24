---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/2450.test.cpp
    title: test/aizu-online-judge/2450.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/lowest_common_ancestor.test.cpp
    title: test/library-checker/lowest_common_ancestor.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Heavy-Light Decomposition
    links: []
  bundledCode: "#line 2 \"src/graph/undirected/tree/heavy_light_decomposition.hpp\"\
    \n\n/*\n * @file heavy_light_decomposition.hpp\n * @brief Heavy-Light Decomposition\n\
    \ */\n\n#include <cassert>\n#include <numeric>\n#include <vector>\n\nclass heavy_light_decomposition\
    \ {\n  std::vector<std::vector<size_t>> tree;\n  std::vector<size_t> sorted, in,\
    \ out, head;\n\n  size_t sort_children(size_t node, size_t prev) {\n    size_t\
    \ sum = 0, max_size = 0;\n    for (size_t &to : tree[node]) {\n      if (to ==\
    \ prev) continue;\n      size_t child_size = sort_children(to, node);\n      sum\
    \ += child_size;\n      if (max_size < child_size) {\n        max_size = child_size;\n\
    \        std::swap(tree[node].front(), to);\n      }\n    }\n    return sum +\
    \ 1;\n  }\n\n  void traverse(size_t node, size_t prev) {\n    in[node] = sorted.size();\n\
    \    sorted.emplace_back(node);\n    if (tree[node].front() != prev) {\n     \
    \ for (const size_t to : tree[node])\n        if (to != prev) head[to] = node\
    \ + size();\n      head[tree[node].front()] = head[node] < size() ? head[node]\
    \ : node;\n      for (const size_t to : tree[node])\n        if (to != prev) traverse(to,\
    \ node);\n    }\n    out[node] = sorted.size();\n  }\n\n  bool made() const {\
    \ return !sorted.empty(); }\n\n public:\n  using interval = std::pair<size_t,\
    \ size_t>;\n\n  heavy_light_decomposition(size_t n = 0) : tree(n), in(n), out(n),\
    \ head(n) {}\n\n  /*\n   * @fn size\n   * @return The size of the tree.\n   */\n\
    \  size_t size() const { return tree.size(); }\n\n  /*\n   * @fn size\n   * @param\
    \ node The root of the subtree\n   * @return The size of the subtree.\n   */\n\
    \  size_t size(size_t node) const {\n    assert(made());\n    return out[node]\
    \ - in[node];\n  }\n\n  void add_edge(size_t u, size_t v) {\n    assert(u < size());\n\
    \    assert(v < size());\n    tree[u].emplace_back(v);\n    tree[v].emplace_back(u);\n\
    \  }\n\n  const decltype(tree) &graph() const { return tree; }\n\n  /*\n   * @fn\
    \ make\n   * @brief Run HLD with given root in linear time.\n   * @param root\
    \ The root node.\n   */\n  void make(size_t root) {\n    sorted.clear();\n   \
    \ sort_children(root, root);\n    traverse(root, root);\n  }\n\n  size_t prev_node(size_t\
    \ node) const {\n    assert(made());\n    assert(in[node]);\n    return sorted[in[node]\
    \ - 1];\n  }\n\n  size_t next_node(size_t node) const {\n    assert(made());\n\
    \    assert(in[node] + 1 < size());\n    return sorted[in[node] + 1];\n  }\n\n\
    \  size_t index(size_t node) const {\n    assert(made());\n    return in[node];\n\
    \  }\n\n  size_t node(size_t index) const {\n    assert(made());\n    return sorted[index];\n\
    \  }\n\n  /*\n   * @fn root\n   * @return The current root of the tree.\n   */\n\
    \  size_t root() const {\n    assert(made());\n    return sorted.front();\n  }\n\
    \n  /*\n   * @fn subtree\n   * @param root The root of the subtree.\n   * @return\
    \ The interval representing the subtree.\n   */\n  interval subtree(size_t root)\
    \ const {\n    assert(made());\n    return {in[root], out[root]};\n  }\n\n  size_t\
    \ parent(size_t node) const {\n    assert(made());\n    return head[node] < size()\
    \ ? prev_node(node) : head[node] - size();\n  }\n\n  size_t top(size_t node) const\
    \ {\n    assert(made());\n    return head[node] < size() ? head[node] : node;\n\
    \  }\n\n  /*\n   * @fn lca\n   * @brief Get LCA in O(log(size)) time.\n   * @param\
    \ u 1st node\n   * @param v 2nd node\n   * @return Lowest Common Ancestor of the\
    \ two.\n   */\n  size_t lca(size_t u, size_t v) {\n    assert(made());\n    if\
    \ (in[v] < in[u]) std::swap(u, v);\n    if (in[v] < out[u]) return u;\n    while\
    \ (in[u] < in[v]) v = parent(top(v));\n    return v;\n  }\n\n  // O(log(n))\n\
    \  std::pair<std::vector<interval>, std::vector<interval>> path_decomposition(\n\
    \      size_t u, size_t v) const {\n    assert(made());\n    if (in[v] < in[u])\
    \ std::swap(u, v);\n    std::vector<interval> left, right;\n    size_t utop =\
    \ top(u), vtop = top(v);\n    while (utop != vtop) {\n      left.emplace_back(in[vtop],\
    \ in[v] + 1);\n      vtop = top(v = parent(vtop));\n      if (in[v] < in[u]) {\n\
    \        std::swap(u, v);\n        std::swap(utop, vtop);\n        std::swap(left,\
    \ right);\n      }\n    }\n    left.emplace_back(in[u], in[v] + 1);\n    return\
    \ std::make_pair(left, right);\n  }\n\n  // O(log(n))\n  std::vector<interval>\
    \ path_decomposition(size_t node) const {\n    assert(made());\n    auto [left,\
    \ right] = path_decomposition(root(), node);\n    assert(left.size() == 1);\n\
    \    right.insert(right.begin(), left.front());\n    return right;\n  }\n};\n"
  code: "#pragma once\n\n/*\n * @file heavy_light_decomposition.hpp\n * @brief Heavy-Light\
    \ Decomposition\n */\n\n#include <cassert>\n#include <numeric>\n#include <vector>\n\
    \nclass heavy_light_decomposition {\n  std::vector<std::vector<size_t>> tree;\n\
    \  std::vector<size_t> sorted, in, out, head;\n\n  size_t sort_children(size_t\
    \ node, size_t prev) {\n    size_t sum = 0, max_size = 0;\n    for (size_t &to\
    \ : tree[node]) {\n      if (to == prev) continue;\n      size_t child_size =\
    \ sort_children(to, node);\n      sum += child_size;\n      if (max_size < child_size)\
    \ {\n        max_size = child_size;\n        std::swap(tree[node].front(), to);\n\
    \      }\n    }\n    return sum + 1;\n  }\n\n  void traverse(size_t node, size_t\
    \ prev) {\n    in[node] = sorted.size();\n    sorted.emplace_back(node);\n   \
    \ if (tree[node].front() != prev) {\n      for (const size_t to : tree[node])\n\
    \        if (to != prev) head[to] = node + size();\n      head[tree[node].front()]\
    \ = head[node] < size() ? head[node] : node;\n      for (const size_t to : tree[node])\n\
    \        if (to != prev) traverse(to, node);\n    }\n    out[node] = sorted.size();\n\
    \  }\n\n  bool made() const { return !sorted.empty(); }\n\n public:\n  using interval\
    \ = std::pair<size_t, size_t>;\n\n  heavy_light_decomposition(size_t n = 0) :\
    \ tree(n), in(n), out(n), head(n) {}\n\n  /*\n   * @fn size\n   * @return The\
    \ size of the tree.\n   */\n  size_t size() const { return tree.size(); }\n\n\
    \  /*\n   * @fn size\n   * @param node The root of the subtree\n   * @return The\
    \ size of the subtree.\n   */\n  size_t size(size_t node) const {\n    assert(made());\n\
    \    return out[node] - in[node];\n  }\n\n  void add_edge(size_t u, size_t v)\
    \ {\n    assert(u < size());\n    assert(v < size());\n    tree[u].emplace_back(v);\n\
    \    tree[v].emplace_back(u);\n  }\n\n  const decltype(tree) &graph() const {\
    \ return tree; }\n\n  /*\n   * @fn make\n   * @brief Run HLD with given root in\
    \ linear time.\n   * @param root The root node.\n   */\n  void make(size_t root)\
    \ {\n    sorted.clear();\n    sort_children(root, root);\n    traverse(root, root);\n\
    \  }\n\n  size_t prev_node(size_t node) const {\n    assert(made());\n    assert(in[node]);\n\
    \    return sorted[in[node] - 1];\n  }\n\n  size_t next_node(size_t node) const\
    \ {\n    assert(made());\n    assert(in[node] + 1 < size());\n    return sorted[in[node]\
    \ + 1];\n  }\n\n  size_t index(size_t node) const {\n    assert(made());\n   \
    \ return in[node];\n  }\n\n  size_t node(size_t index) const {\n    assert(made());\n\
    \    return sorted[index];\n  }\n\n  /*\n   * @fn root\n   * @return The current\
    \ root of the tree.\n   */\n  size_t root() const {\n    assert(made());\n   \
    \ return sorted.front();\n  }\n\n  /*\n   * @fn subtree\n   * @param root The\
    \ root of the subtree.\n   * @return The interval representing the subtree.\n\
    \   */\n  interval subtree(size_t root) const {\n    assert(made());\n    return\
    \ {in[root], out[root]};\n  }\n\n  size_t parent(size_t node) const {\n    assert(made());\n\
    \    return head[node] < size() ? prev_node(node) : head[node] - size();\n  }\n\
    \n  size_t top(size_t node) const {\n    assert(made());\n    return head[node]\
    \ < size() ? head[node] : node;\n  }\n\n  /*\n   * @fn lca\n   * @brief Get LCA\
    \ in O(log(size)) time.\n   * @param u 1st node\n   * @param v 2nd node\n   *\
    \ @return Lowest Common Ancestor of the two.\n   */\n  size_t lca(size_t u, size_t\
    \ v) {\n    assert(made());\n    if (in[v] < in[u]) std::swap(u, v);\n    if (in[v]\
    \ < out[u]) return u;\n    while (in[u] < in[v]) v = parent(top(v));\n    return\
    \ v;\n  }\n\n  // O(log(n))\n  std::pair<std::vector<interval>, std::vector<interval>>\
    \ path_decomposition(\n      size_t u, size_t v) const {\n    assert(made());\n\
    \    if (in[v] < in[u]) std::swap(u, v);\n    std::vector<interval> left, right;\n\
    \    size_t utop = top(u), vtop = top(v);\n    while (utop != vtop) {\n      left.emplace_back(in[vtop],\
    \ in[v] + 1);\n      vtop = top(v = parent(vtop));\n      if (in[v] < in[u]) {\n\
    \        std::swap(u, v);\n        std::swap(utop, vtop);\n        std::swap(left,\
    \ right);\n      }\n    }\n    left.emplace_back(in[u], in[v] + 1);\n    return\
    \ std::make_pair(left, right);\n  }\n\n  // O(log(n))\n  std::vector<interval>\
    \ path_decomposition(size_t node) const {\n    assert(made());\n    auto [left,\
    \ right] = path_decomposition(root(), node);\n    assert(left.size() == 1);\n\
    \    right.insert(right.begin(), left.front());\n    return right;\n  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/graph/undirected/tree/heavy_light_decomposition.hpp
  requiredBy: []
  timestamp: '2020-11-16 23:30:10+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/lowest_common_ancestor.test.cpp
  - test/aizu-online-judge/2450.test.cpp
documentation_of: src/graph/undirected/tree/heavy_light_decomposition.hpp
layout: document
redirect_from:
- /library/src/graph/undirected/tree/heavy_light_decomposition.hpp
- /library/src/graph/undirected/tree/heavy_light_decomposition.hpp.html
title: Heavy-Light Decomposition
---
