---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/graph/undirected/tree/heavy_light_decomposition.hpp
    title: Heavy-Light Decomposition
  - icon: ':heavy_check_mark:'
    path: src/graph/undirected/tree/lowest_common_ancestor.hpp
    title: src/graph/undirected/tree/lowest_common_ancestor.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/lca
    links:
    - https://judge.yosupo.jp/problem/lca
  bundledCode: "#line 1 \"test/library-checker/lowest_common_ancestor.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\n\n#line 2 \"src/graph/undirected/tree/lowest_common_ancestor.hpp\"\
    \n#include <cassert>\n#include <vector>\n\nclass lowest_common_ancestor {\n  std::vector<std::vector<size_t>>\
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
    \ - (1 << h)]);\n  }\n};  // class lowest_common_ancestor\n#line 4 \"test/library-checker/lowest_common_ancestor.test.cpp\"\
    \n\n#include <cstdio>\n\n#line 2 \"src/graph/undirected/tree/heavy_light_decomposition.hpp\"\
    \n\n/**\n * @file heavy_light_decomposition.hpp\n * @brief Heavy-Light Decomposition\n\
    \ */\n\n#line 9 \"src/graph/undirected/tree/heavy_light_decomposition.hpp\"\n\
    #include <numeric>\n#line 11 \"src/graph/undirected/tree/heavy_light_decomposition.hpp\"\
    \n\nclass heavy_light_decomposition {\n  constexpr static size_t __nil = -1;\n\
    \n  std::vector<std::vector<size_t>> __tree;\n  std::vector<size_t> __sorted,\
    \ __in, __out, __head, __depth;\n\n  size_t sort_children(size_t node, size_t\
    \ prev) {\n    size_t sum = 1, max_size = 0;\n\n    for (size_t &to : __tree[node])\
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
    \ left.begin(), left.end());\n    return right;\n  }\n};\n#line 8 \"test/library-checker/lowest_common_ancestor.test.cpp\"\
    \n\nint main() {\n  int n, q;\n  scanf(\"%d%d\", &n, &q);\n  lowest_common_ancestor\
    \ lca(n);\n  heavy_light_decomposition hld(n);\n  for (int i = 1, p; i < n; i++)\
    \ {\n    scanf(\"%d\", &p);\n    lca.add_edge(i, p);\n    hld.add_edge(i, p);\n\
    \  }\n  lca.make(0);\n  hld.make(0);\n  for (int u, v; q--;) {\n    scanf(\"%d%d\"\
    , &u, &v);\n    auto [left, right] = hld.split_path(u, v);\n    auto x = lca.query(u,\
    \ v);\n    auto y = hld.lca(u, v);\n    assert(x == y);\n    assert(x == hld.node(left.back().first));\n\
    \    printf(\"%d\\n\", x);\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\n\n#include \"src/graph/undirected/tree/lowest_common_ancestor.hpp\"\
    \n\n#include <cstdio>\n\n#include \"src/graph/undirected/tree/heavy_light_decomposition.hpp\"\
    \n\nint main() {\n  int n, q;\n  scanf(\"%d%d\", &n, &q);\n  lowest_common_ancestor\
    \ lca(n);\n  heavy_light_decomposition hld(n);\n  for (int i = 1, p; i < n; i++)\
    \ {\n    scanf(\"%d\", &p);\n    lca.add_edge(i, p);\n    hld.add_edge(i, p);\n\
    \  }\n  lca.make(0);\n  hld.make(0);\n  for (int u, v; q--;) {\n    scanf(\"%d%d\"\
    , &u, &v);\n    auto [left, right] = hld.split_path(u, v);\n    auto x = lca.query(u,\
    \ v);\n    auto y = hld.lca(u, v);\n    assert(x == y);\n    assert(x == hld.node(left.back().first));\n\
    \    printf(\"%d\\n\", x);\n  }\n}\n"
  dependsOn:
  - src/graph/undirected/tree/heavy_light_decomposition.hpp
  - src/graph/undirected/tree/lowest_common_ancestor.hpp
  isVerificationFile: true
  path: test/library-checker/lowest_common_ancestor.test.cpp
  requiredBy: []
  timestamp: '2020-11-16 23:30:10+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/lowest_common_ancestor.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/lowest_common_ancestor.test.cpp
- /verify/test/library-checker/lowest_common_ancestor.test.cpp.html
title: test/library-checker/lowest_common_ancestor.test.cpp
---
