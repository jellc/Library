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
    \n\n/**\n * @file heavy_light_decomposition.hpp\n * @brief Heavy-Light Decomposition\n\
    \ */\n\n#include <cassert>\n#include <numeric>\n#include <vector>\n\nclass heavy_light_decomposition\
    \ {\n  constexpr static size_t __nil = -1;\n\n  std::vector<std::vector<size_t>>\
    \ __tree;\n  std::vector<size_t> __sorted, __in, __out, __head, __depth;\n\n \
    \ size_t sort_children(size_t node, size_t prev) {\n    size_t sum = 1, max_size\
    \ = 0;\n\n    for (size_t &to : __tree[node]) {\n      if (to == prev) continue;\n\
    \      __depth[to] = __depth[node] + 1;\n      size_t child_size = sort_children(to,\
    \ node);\n      sum += child_size;\n      if (max_size < child_size) {\n     \
    \   max_size = child_size;\n        std::swap(__tree[node].front(), to);\n   \
    \   }\n    }\n\n    return sum;\n  }\n\n  void traverse(size_t node, size_t prev)\
    \ {\n    __in[node] = __sorted.size();\n    __sorted.emplace_back(node);\n\n \
    \   if (!__tree[node].empty() && __tree[node].front() != prev) {\n      for (const\
    \ size_t to : __tree[node])\n        if (to != prev) __head[to] = node + size();\n\
    \      __head[__tree[node].front()] =\n          __head[node] < size() ? __head[node]\
    \ : node;\n      for (const size_t to : __tree[node])\n        if (to != prev)\
    \ traverse(to, node);\n    }\n\n    __out[node] = __sorted.size();\n  }\n\n  bool\
    \ made() const { return !__sorted.empty(); }\n\n public:\n  using interval = std::pair<size_t,\
    \ size_t>;\n\n  heavy_light_decomposition() = default;\n\n  heavy_light_decomposition(size_t\
    \ __n) : __tree(__n) {}\n\n  /**\n   * @return The size of the __tree.\n   */\n\
    \  size_t size() const { return __tree.size(); }\n\n  /**\n   * @param node The\
    \ root of the subtree\n   * @return The size of the subtree.\n   */\n  size_t\
    \ size(size_t node) const {\n    assert(made());\n    return __out[node] - __in[node];\n\
    \  }\n\n  void add_edge(size_t __u, size_t __v) {\n    assert(__u < size());\n\
    \    assert(__v < size());\n    __tree[__u].emplace_back(__v);\n    __tree[__v].emplace_back(__u);\n\
    \  }\n\n  const decltype(__tree) &tree() const { return __tree; }\n\n  /**\n \
    \  * @brief Run HLD with given root __in linear time.\n   * @param root The root\
    \ node.\n   */\n  void make(size_t __root) {\n    __sorted.clear(), __in.resize(size()),\
    \ __out.resize(size()),\n        __head.resize(size()), __depth.resize(size());\n\
    \    __head[__root] = __root + size(), __depth[__root] = 0;\n    sort_children(__root,\
    \ __nil);\n    traverse(__root, __root);\n  }\n\n  size_t prev_node(size_t node)\
    \ const {\n    assert(made());\n    return __in[node] ? __sorted[__in[node] -\
    \ 1] : __nil;\n  }\n\n  size_t next_node(size_t node) const {\n    assert(made());\n\
    \    return __in[node] + 1 < size() ? __sorted[__in[node] + 1] : __nil;\n  }\n\
    \n  size_t index(size_t node) const {\n    assert(made());\n    return __in[node];\n\
    \  }\n\n  size_t node(size_t __i) const {\n    assert(made());\n    return __sorted[__i];\n\
    \  }\n\n  /**\n   * @return The current root of the __tree.\n   */\n  size_t root()\
    \ const {\n    assert(made());\n    return __sorted.front();\n  }\n\n  /**\n \
    \  * @param root The root of the subtree.\n   * @return The interval representing\
    \ the subtree.\n   */\n  interval subtree(size_t __v) const {\n    assert(made());\n\
    \    return {__in[__v], __out[__v]};\n  }\n\n  /**\n   * @param __v\n   * @return\
    \ Return v if v is the root.\n   */\n  size_t parent(size_t __v) const {\n   \
    \ assert(made());\n    return __head[__v] < size() ? prev_node(__v) : __head[__v]\
    \ - size();\n  }\n\n  size_t top(size_t __v) const {\n    assert(made());\n  \
    \  return __head[__v] < size() ? __head[__v] : __v;\n  }\n\n  /**\n   * @brief\
    \ Get LCA in O(log(size)) time.\n   * @param __u 1st node\n   * @param __v 2nd\
    \ node\n   * @return Lowest Common Ancestor of the two.\n   */\n  size_t lca(size_t\
    \ __u, size_t __v) const {\n    assert(made());\n    if (__in[__v] < __in[__u])\
    \ std::swap(__u, __v);\n    if (__in[__v] < __out[__u]) return __u;\n    while\
    \ (__in[__u] < __in[__v]) __v = parent(top(__v));\n    return __v;\n  }\n\n  /**\n\
    \   * @brief Ancestor.\n   * @return k-th ancestor of v.\n   */\n  size_t ancestor(size_t\
    \ __v, size_t __k) const {\n    assert(made());\n    while (__k) {\n      assert(__in[__v]);\n\
    \      auto __t = top(__v);\n      auto __d = __in[__v] - __in[__t];\n      if\
    \ (__d < __k) {\n        __k -= __d + 1;\n        __v = __head[__t] - size();\n\
    \      } else {\n        __v = __sorted[__in[__v] - __k];\n        __k = 0;\n\
    \      }\n    }\n    return __v;\n  }\n\n  size_t depth(size_t __v) const { return\
    \ __depth[__v]; }\n\n  size_t distance(size_t __u, size_t __v) const {\n    return\
    \ __depth[__u] + __depth[__v] - __depth[lca(__u, __v)] * 2;\n  }\n\n  /**\n  \
    \ * @brief Split a path into O(log(size)) paths.\n   * @return Pair of list of\
    \ ascending paths. first.back() is the index of\n   * lca(u, v).\n   */\n  auto\
    \ split_path(size_t __u, size_t __v) const {\n    assert(made());\n    if (__in[__v]\
    \ < __in[__u]) std::swap(__u, __v);\n    std::vector<std::pair<size_t, size_t>>\
    \ left, right;\n    auto utop = top(__u), vtop = top(__v);\n    while (utop !=\
    \ vtop) {\n      left.emplace_back(__in[vtop], __in[__v] + 1);\n      vtop = top(__v\
    \ = parent(vtop));\n      if (__in[__v] < __in[__u]) {\n        std::swap(__u,\
    \ __v);\n        std::swap(utop, vtop);\n        std::swap(left, right);\n   \
    \   }\n    }\n    left.emplace_back(__in[__u], __in[__v] + 1);\n    return std::make_pair(left,\
    \ right);\n  }\n\n  /**\n   * @brief Split a path upto root() into O(log(size))\
    \ paths.\n   * @return List of ascending paths. back() is the index of lca(root(),\
    \ v).\n   */\n  auto split_path(size_t __v) const {\n    assert(made());\n   \
    \ auto [left, right] = split_path(root(), __v);\n    right.insert(right.begin(),\
    \ left.begin(), left.end());\n    return right;\n  }\n};\n"
  code: "#pragma once\n\n/**\n * @file heavy_light_decomposition.hpp\n * @brief Heavy-Light\
    \ Decomposition\n */\n\n#include <cassert>\n#include <numeric>\n#include <vector>\n\
    \nclass heavy_light_decomposition {\n  constexpr static size_t __nil = -1;\n\n\
    \  std::vector<std::vector<size_t>> __tree;\n  std::vector<size_t> __sorted, __in,\
    \ __out, __head, __depth;\n\n  size_t sort_children(size_t node, size_t prev)\
    \ {\n    size_t sum = 1, max_size = 0;\n\n    for (size_t &to : __tree[node])\
    \ {\n      if (to == prev) continue;\n      __depth[to] = __depth[node] + 1;\n\
    \      size_t child_size = sort_children(to, node);\n      sum += child_size;\n\
    \      if (max_size < child_size) {\n        max_size = child_size;\n        std::swap(__tree[node].front(),\
    \ to);\n      }\n    }\n\n    return sum;\n  }\n\n  void traverse(size_t node,\
    \ size_t prev) {\n    __in[node] = __sorted.size();\n    __sorted.emplace_back(node);\n\
    \n    if (!__tree[node].empty() && __tree[node].front() != prev) {\n      for\
    \ (const size_t to : __tree[node])\n        if (to != prev) __head[to] = node\
    \ + size();\n      __head[__tree[node].front()] =\n          __head[node] < size()\
    \ ? __head[node] : node;\n      for (const size_t to : __tree[node])\n       \
    \ if (to != prev) traverse(to, node);\n    }\n\n    __out[node] = __sorted.size();\n\
    \  }\n\n  bool made() const { return !__sorted.empty(); }\n\n public:\n  using\
    \ interval = std::pair<size_t, size_t>;\n\n  heavy_light_decomposition() = default;\n\
    \n  heavy_light_decomposition(size_t __n) : __tree(__n) {}\n\n  /**\n   * @return\
    \ The size of the __tree.\n   */\n  size_t size() const { return __tree.size();\
    \ }\n\n  /**\n   * @param node The root of the subtree\n   * @return The size\
    \ of the subtree.\n   */\n  size_t size(size_t node) const {\n    assert(made());\n\
    \    return __out[node] - __in[node];\n  }\n\n  void add_edge(size_t __u, size_t\
    \ __v) {\n    assert(__u < size());\n    assert(__v < size());\n    __tree[__u].emplace_back(__v);\n\
    \    __tree[__v].emplace_back(__u);\n  }\n\n  const decltype(__tree) &tree() const\
    \ { return __tree; }\n\n  /**\n   * @brief Run HLD with given root __in linear\
    \ time.\n   * @param root The root node.\n   */\n  void make(size_t __root) {\n\
    \    __sorted.clear(), __in.resize(size()), __out.resize(size()),\n        __head.resize(size()),\
    \ __depth.resize(size());\n    __head[__root] = __root + size(), __depth[__root]\
    \ = 0;\n    sort_children(__root, __nil);\n    traverse(__root, __root);\n  }\n\
    \n  size_t prev_node(size_t node) const {\n    assert(made());\n    return __in[node]\
    \ ? __sorted[__in[node] - 1] : __nil;\n  }\n\n  size_t next_node(size_t node)\
    \ const {\n    assert(made());\n    return __in[node] + 1 < size() ? __sorted[__in[node]\
    \ + 1] : __nil;\n  }\n\n  size_t index(size_t node) const {\n    assert(made());\n\
    \    return __in[node];\n  }\n\n  size_t node(size_t __i) const {\n    assert(made());\n\
    \    return __sorted[__i];\n  }\n\n  /**\n   * @return The current root of the\
    \ __tree.\n   */\n  size_t root() const {\n    assert(made());\n    return __sorted.front();\n\
    \  }\n\n  /**\n   * @param root The root of the subtree.\n   * @return The interval\
    \ representing the subtree.\n   */\n  interval subtree(size_t __v) const {\n \
    \   assert(made());\n    return {__in[__v], __out[__v]};\n  }\n\n  /**\n   * @param\
    \ __v\n   * @return Return v if v is the root.\n   */\n  size_t parent(size_t\
    \ __v) const {\n    assert(made());\n    return __head[__v] < size() ? prev_node(__v)\
    \ : __head[__v] - size();\n  }\n\n  size_t top(size_t __v) const {\n    assert(made());\n\
    \    return __head[__v] < size() ? __head[__v] : __v;\n  }\n\n  /**\n   * @brief\
    \ Get LCA in O(log(size)) time.\n   * @param __u 1st node\n   * @param __v 2nd\
    \ node\n   * @return Lowest Common Ancestor of the two.\n   */\n  size_t lca(size_t\
    \ __u, size_t __v) const {\n    assert(made());\n    if (__in[__v] < __in[__u])\
    \ std::swap(__u, __v);\n    if (__in[__v] < __out[__u]) return __u;\n    while\
    \ (__in[__u] < __in[__v]) __v = parent(top(__v));\n    return __v;\n  }\n\n  /**\n\
    \   * @brief Ancestor.\n   * @return k-th ancestor of v.\n   */\n  size_t ancestor(size_t\
    \ __v, size_t __k) const {\n    assert(made());\n    while (__k) {\n      assert(__in[__v]);\n\
    \      auto __t = top(__v);\n      auto __d = __in[__v] - __in[__t];\n      if\
    \ (__d < __k) {\n        __k -= __d + 1;\n        __v = __head[__t] - size();\n\
    \      } else {\n        __v = __sorted[__in[__v] - __k];\n        __k = 0;\n\
    \      }\n    }\n    return __v;\n  }\n\n  size_t depth(size_t __v) const { return\
    \ __depth[__v]; }\n\n  size_t distance(size_t __u, size_t __v) const {\n    return\
    \ __depth[__u] + __depth[__v] - __depth[lca(__u, __v)] * 2;\n  }\n\n  /**\n  \
    \ * @brief Split a path into O(log(size)) paths.\n   * @return Pair of list of\
    \ ascending paths. first.back() is the index of\n   * lca(u, v).\n   */\n  auto\
    \ split_path(size_t __u, size_t __v) const {\n    assert(made());\n    if (__in[__v]\
    \ < __in[__u]) std::swap(__u, __v);\n    std::vector<std::pair<size_t, size_t>>\
    \ left, right;\n    auto utop = top(__u), vtop = top(__v);\n    while (utop !=\
    \ vtop) {\n      left.emplace_back(__in[vtop], __in[__v] + 1);\n      vtop = top(__v\
    \ = parent(vtop));\n      if (__in[__v] < __in[__u]) {\n        std::swap(__u,\
    \ __v);\n        std::swap(utop, vtop);\n        std::swap(left, right);\n   \
    \   }\n    }\n    left.emplace_back(__in[__u], __in[__v] + 1);\n    return std::make_pair(left,\
    \ right);\n  }\n\n  /**\n   * @brief Split a path upto root() into O(log(size))\
    \ paths.\n   * @return List of ascending paths. back() is the index of lca(root(),\
    \ v).\n   */\n  auto split_path(size_t __v) const {\n    assert(made());\n   \
    \ auto [left, right] = split_path(root(), __v);\n    right.insert(right.begin(),\
    \ left.begin(), left.end());\n    return right;\n  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/graph/undirected/tree/heavy_light_decomposition.hpp
  requiredBy: []
  timestamp: '2021-11-30 23:00:42+09:00'
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
