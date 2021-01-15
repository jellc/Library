---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/graph/directed/flow/base.hpp
    title: Flow Graph
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/bipartitematching.test.cpp
    title: test/library-checker/bipartitematching.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Dinic's Algorithm
    links: []
  bundledCode: "#line 2 \"src/graph/directed/flow/Dinic.hpp\"\n\n/**\n * @file Dinic.hpp\n\
    \ * @brief Dinic's Algorithm\n * @date 2021-01-15\n *\n *\n */\n\n#line 2 \"src/graph/directed/flow/base.hpp\"\
    \n\n/**\n * @file base.hpp\n * @brief Flow Graph\n * @date 2021-01-15\n *\n *\n\
    \ */\n\n#include <cassert>\n#include <vector>\n\nnamespace workspace {\n\ntemplate\
    \ <class Cap, class Cost> class flow_graph {\n protected:\n  class adjacency;\n\
    \n public:\n  using value_type = adjacency;\n  using reference = adjacency &;\n\
    \  using const_reference = adjacency const &;\n  using container_type = std::vector<value_type>;\n\
    \  using size_type = typename container_type::size_type;\n\n protected:\n  /**\n\
    \   * @brief Edge of flow graph.\n   *\n   */\n  class edge {\n   public:\n  \
    \  size_type src, dst;\n    Cap cap;\n    Cost cost;\n    edge *rev;\n\n    edge()\
    \ = default;\n\n    edge(size_type src, size_type dst, const Cap &cap, edge *rev)\n\
    \        : src(src), dst(dst), cap(cap), rev(rev) {}\n\n    edge(size_type src,\
    \ size_type dst, const Cap &cap, const Cost &cost,\n         edge *rev)\n    \
    \    : src(src), dst(dst), cap(cap), cost(cost), rev(rev) {}\n\n    const Cap\
    \ &flow(const Cap &f = 0) { return cap -= f, rev->cap += f; }\n  };\n\n  class\
    \ adjacency {\n    edge *first, *iter, *last;\n\n   public:\n    using value_type\
    \ = edge;\n    using reference = edge &;\n    using const_reference = edge const\
    \ &;\n    using pointer = edge *;\n    using const_pointer = const edge *;\n\n\
    \    adjacency() : first(new edge[1]), iter(first), last(first + 1) {}\n    ~adjacency()\
    \ { delete[] first; }\n\n    template <class... Args> pointer emplace(Args &&...\
    \ args) {\n      if (iter == last) {\n        size_type len(last - first);\n \
    \       edge *nfst = iter = new edge[len << 1];\n        for (edge *p{first};\
    \ p != last; ++p, ++iter)\n          p->rev->rev = iter, *iter = *p;\n       \
    \ delete[] first;\n        first = nfst;\n        last = iter + len;\n      }\n\
    \      *iter = edge(args...);\n      return iter++;\n    }\n\n    reference operator[](size_type\
    \ i) {\n      assert(i < size());\n      return *(first + i);\n    }\n\n    const_reference\
    \ operator[](size_type i) const {\n      assert(i < size());\n      return *(first\
    \ + i);\n    }\n\n    size_type size() const { return iter - first; }\n\n    pointer\
    \ begin() { return first; }\n    const_pointer begin() const { return first; }\n\
    \n    pointer end() { return iter; }\n    const_pointer end() const { return iter;\
    \ }\n  };\n\n public:\n  /**\n   * @brief Construct a new flow base object\n \
    \  *\n   * @param n Number of vertices\n   */\n  flow_graph(size_type n = 0) :\
    \ graph(n) {}\n\n  flow_graph(const flow_graph &other) : graph(other.size()) {\n\
    \    for (size_type node{}; node != size(); ++node)\n      for (const auto &[src,\
    \ dst, cap, cost, rev] : other[node])\n        if (src == node) {\n          edge\
    \ *ptr = graph[src].emplace(src, dst, cap, cost, nullptr);\n          ptr->rev\
    \ = graph[dst].emplace(dst, src, rev->cap, -cost, ptr);\n          rev->src =\
    \ nil;\n        } else {\n          rev->rev->src = node;\n        }\n  }\n\n\
    \  flow_graph &operator=(const flow_graph &rhs) {\n    if (this != &rhs) graph.swap(flow_graph(rhs).graph);\n\
    \    return *this;\n  }\n\n  /**\n   * @return Number of vertices.\n   */\n  size_type\
    \ size() const { return graph.size(); }\n\n  reference operator[](size_type node)\
    \ {\n    assert(node < size());\n    return graph[node];\n  }\n\n  const_reference\
    \ &operator[](size_type node) const {\n    assert(node < size());\n    return\
    \ graph[node];\n  }\n\n  typename container_type::iterator begin() { return graph.begin();\
    \ }\n\n  typename container_type::iterator end() { return graph.end(); }\n\n \
    \ typename container_type::const_iterator begin() const {\n    return graph.begin();\n\
    \  }\n\n  typename container_type::const_iterator end() const { return graph.end();\
    \ }\n\n  virtual typename adjacency::pointer add_edge(size_type src, size_type\
    \ dst,\n                                               const Cap &cap,\n     \
    \                                          const Cost &cost) {\n    assert(src\
    \ < size());\n    assert(dst < size());\n    assert(!(cap < static_cast<Cap>(0)));\n\
    \    if (!(static_cast<Cap>(0) < cap) || src == dst) return nullptr;\n    auto\
    \ ptr = graph[src].emplace(src, dst, cap, cost, nullptr);\n    ptr->rev = graph[dst].emplace(dst,\
    \ src, 0, -cost, ptr);\n    return ptr;\n  }\n\n protected:\n  constexpr static\
    \ size_type nil = -1;\n  container_type graph;\n};\n\n}  // namespace workspace\n\
    #line 12 \"src/graph/directed/flow/Dinic.hpp\"\n\nnamespace workspace {\n\n/**\n\
    \ * @brief Compute the maximum flow.\n *\n * @tparam Cap Capacity type\n */\n\
    template <class Cap = int> class Dinic : public flow_graph<Cap, bool> {\n  using\
    \ base = flow_graph<Cap, bool>;\n  using base::add_edge;\n  using base::graph;\n\
    \  using base::nil;\n\n public:\n  using edge = typename base::edge;\n  using\
    \ size_type = typename base::size_type;\n\n protected:\n  std::vector<size_type>\
    \ level;\n  std::vector<edge *> itr;\n\n  Cap dfs(size_type src, size_type dst,\
    \ Cap bound) {\n    if (src == dst || bound == 0) return bound;\n    Cap flow(0);\n\
    \    for (edge *&e{itr[dst]}; e != graph[dst].end(); ++e)\n      if (static_cast<Cap>(0)\
    \ < e->rev->cap && level[e->dst] < level[dst])\n        if (Cap achv = dfs(src,\
    \ e->dst, std::min(bound, e->rev->cap));\n            achv > 0) {\n          e->rev->flow(achv);\n\
    \          flow += achv, bound -= achv;\n          if (bound == 0) break;\n  \
    \      }\n    return flow;\n  }\n\n public:\n  /**\n   * @brief Construct a new\
    \ Dinic object\n   *\n   * @param n Number of nodes.\n   */\n  Dinic(size_type\
    \ n = 0) : base::flow_graph(n), level(n, nil), itr(n) {}\n\n  Dinic(const Dinic\
    \ &other)\n      : base::flow_graph(other), level(other.level), itr(other.itr)\
    \ {}\n\n  Dinic &operator=(const Dinic &rhs) {\n    if (this != &rhs) base::operator=(rhs),\
    \ level = rhs.level, itr = rhs.itr;\n    return *this;\n  }\n\n  /**\n   * @brief\
    \ Add an edge to the graph.\n   *\n   * @param src Source\n   * @param dst Destination\n\
    \   * @param cap Capacity\n   * @return Pointer to the edge.\n   */\n  typename\
    \ base::adjacency::pointer add_edge(size_type src, size_type dst,\n          \
    \                                   Cap cap) {\n    return add_edge(src, dst,\
    \ cap, false);\n  }\n\n  // void add_undirected_edge(size_type src, size_type\
    \ dst, Cap cap) {\n  //   base::add_undirected_edge(src, dst, cap, false);\n \
    \ // }\n\n  /**\n   * @brief Run Dinic's algorithm.\n   *\n   * @param src Source\n\
    \   * @param dst Destination\n   * @return Maximum flow.\n   */\n  Cap max_flow(size_type\
    \ src, size_type dst) {\n    assert(src < base::size());\n    assert(dst < base::size());\n\
    \    Cap flow(0), bound(0);\n    for (const edge &e : graph[src]) bound += e.cap;\n\
    \    for (std::vector<size_type> que(base::size());;\n         std::fill(level.begin(),\
    \ level.end(), nil)) {\n      level[que.front() = src] = 0;\n      for (auto ql{que.begin()},\
    \ qr{std::next(ql)};\n           level[dst] == nil && ql != qr; ++ql)\n      \
    \  for (const edge &e : graph[*ql])\n          if (static_cast<Cap>(0) < e.cap\
    \ && level[e.dst] == nil)\n            level[ *qr++ = e.dst] = level[*ql] + 1;\n\
    \      if (level[dst] == nil) break;\n      for (size_type node{}; node != base::size();\
    \ ++node)\n        itr[node] = graph[node].begin();\n      flow += dfs(src, dst,\
    \ bound);\n    }\n    return flow;\n  }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file Dinic.hpp\n * @brief Dinic's Algorithm\n *\
    \ @date 2021-01-15\n *\n *\n */\n\n#include \"base.hpp\"\n\nnamespace workspace\
    \ {\n\n/**\n * @brief Compute the maximum flow.\n *\n * @tparam Cap Capacity type\n\
    \ */\ntemplate <class Cap = int> class Dinic : public flow_graph<Cap, bool> {\n\
    \  using base = flow_graph<Cap, bool>;\n  using base::add_edge;\n  using base::graph;\n\
    \  using base::nil;\n\n public:\n  using edge = typename base::edge;\n  using\
    \ size_type = typename base::size_type;\n\n protected:\n  std::vector<size_type>\
    \ level;\n  std::vector<edge *> itr;\n\n  Cap dfs(size_type src, size_type dst,\
    \ Cap bound) {\n    if (src == dst || bound == 0) return bound;\n    Cap flow(0);\n\
    \    for (edge *&e{itr[dst]}; e != graph[dst].end(); ++e)\n      if (static_cast<Cap>(0)\
    \ < e->rev->cap && level[e->dst] < level[dst])\n        if (Cap achv = dfs(src,\
    \ e->dst, std::min(bound, e->rev->cap));\n            achv > 0) {\n          e->rev->flow(achv);\n\
    \          flow += achv, bound -= achv;\n          if (bound == 0) break;\n  \
    \      }\n    return flow;\n  }\n\n public:\n  /**\n   * @brief Construct a new\
    \ Dinic object\n   *\n   * @param n Number of nodes.\n   */\n  Dinic(size_type\
    \ n = 0) : base::flow_graph(n), level(n, nil), itr(n) {}\n\n  Dinic(const Dinic\
    \ &other)\n      : base::flow_graph(other), level(other.level), itr(other.itr)\
    \ {}\n\n  Dinic &operator=(const Dinic &rhs) {\n    if (this != &rhs) base::operator=(rhs),\
    \ level = rhs.level, itr = rhs.itr;\n    return *this;\n  }\n\n  /**\n   * @brief\
    \ Add an edge to the graph.\n   *\n   * @param src Source\n   * @param dst Destination\n\
    \   * @param cap Capacity\n   * @return Pointer to the edge.\n   */\n  typename\
    \ base::adjacency::pointer add_edge(size_type src, size_type dst,\n          \
    \                                   Cap cap) {\n    return add_edge(src, dst,\
    \ cap, false);\n  }\n\n  // void add_undirected_edge(size_type src, size_type\
    \ dst, Cap cap) {\n  //   base::add_undirected_edge(src, dst, cap, false);\n \
    \ // }\n\n  /**\n   * @brief Run Dinic's algorithm.\n   *\n   * @param src Source\n\
    \   * @param dst Destination\n   * @return Maximum flow.\n   */\n  Cap max_flow(size_type\
    \ src, size_type dst) {\n    assert(src < base::size());\n    assert(dst < base::size());\n\
    \    Cap flow(0), bound(0);\n    for (const edge &e : graph[src]) bound += e.cap;\n\
    \    for (std::vector<size_type> que(base::size());;\n         std::fill(level.begin(),\
    \ level.end(), nil)) {\n      level[que.front() = src] = 0;\n      for (auto ql{que.begin()},\
    \ qr{std::next(ql)};\n           level[dst] == nil && ql != qr; ++ql)\n      \
    \  for (const edge &e : graph[*ql])\n          if (static_cast<Cap>(0) < e.cap\
    \ && level[e.dst] == nil)\n            level[ *qr++ = e.dst] = level[*ql] + 1;\n\
    \      if (level[dst] == nil) break;\n      for (size_type node{}; node != base::size();\
    \ ++node)\n        itr[node] = graph[node].begin();\n      flow += dfs(src, dst,\
    \ bound);\n    }\n    return flow;\n  }\n};\n\n}  // namespace workspace\n"
  dependsOn:
  - src/graph/directed/flow/base.hpp
  isVerificationFile: false
  path: src/graph/directed/flow/Dinic.hpp
  requiredBy: []
  timestamp: '2021-01-16 02:48:49+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/bipartitematching.test.cpp
documentation_of: src/graph/directed/flow/Dinic.hpp
layout: document
redirect_from:
- /library/src/graph/directed/flow/Dinic.hpp
- /library/src/graph/directed/flow/Dinic.hpp.html
title: Dinic's Algorithm
---
