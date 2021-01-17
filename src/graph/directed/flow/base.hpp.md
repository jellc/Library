---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: src/graph/directed/flow/Dinic.hpp
    title: Dinic's Algorithm
  - icon: ':heavy_check_mark:'
    path: src/graph/directed/flow/min_cost_flow.hpp
    title: Minimum Cost Flow
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/2815.test.cpp
    title: test/aizu-online-judge/2815.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/assignment.test.cpp
    title: test/library-checker/assignment.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/bipartitematching.test.cpp
    title: test/library-checker/bipartitematching.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Flow Graph
    links: []
  bundledCode: "#line 2 \"src/graph/directed/flow/base.hpp\"\n\n/**\n * @file base.hpp\n\
    \ * @brief Flow Graph\n * @date 2021-01-15\n *\n *\n */\n\n#include <cassert>\n\
    #include <vector>\n\nnamespace workspace {\n\ntemplate <class Cap, class Cost\
    \ = void> class flow_graph {\n public:\n  class adjacency;\n  using value_type\
    \ = adjacency;\n  using reference = adjacency &;\n  using const_reference = adjacency\
    \ const &;\n  using container_type = std::vector<value_type>;\n  using size_type\
    \ = typename container_type::size_type;\n\n  class unweighted_edge {\n   public:\n\
    \    size_type src, dst;\n    Cap cap;\n    unweighted_edge *rev;\n\n    unweighted_edge()\
    \ = default;\n\n    unweighted_edge(size_type src, size_type dst, const Cap &cap,\n\
    \                    unweighted_edge *rev)\n        : src(src), dst(dst), cap(cap),\
    \ rev(rev) {\n      assert(!(cap < static_cast<Cap>(0)));\n    }\n\n    const\
    \ Cap &flow(const Cap &f = 0) { return cap -= f, rev->cap += f; }\n\n    unweighted_edge\
    \ make_rev() { return {dst, src, 0, this}; }\n  };\n\n  class weighted_edge :\
    \ public unweighted_edge {\n   public:\n    Cost cost;\n\n    weighted_edge()\
    \ = default;\n\n    weighted_edge(size_type src, size_type dst, const Cap &cap,\n\
    \                  const Cost &cost, weighted_edge *rev)\n        : unweighted_edge(src,\
    \ dst, cap, rev), cost(cost) {}\n\n    weighted_edge make_rev() {\n      return\
    \ {unweighted_edge::dst, unweighted_edge::src, 0, -cost, this};\n    }\n  };\n\
    \n  using edge = typename std::conditional<std::is_void<Cost>::value,\n      \
    \                                   unweighted_edge, weighted_edge>::type;\n\n\
    \  class adjacency {\n   public:\n    using value_type = edge;\n    using reference\
    \ = edge &;\n    using const_reference = edge const &;\n    using pointer = edge\
    \ *;\n    using const_pointer = const edge *;\n\n    adjacency() : first(new edge[1]),\
    \ iter(first), last(first + 1) {}\n    ~adjacency() { delete[] first; }\n\n  \
    \  template <class... Args> reference emplace(Args &&... args) {\n      if (iter\
    \ == last) {\n        size_type len(last - first);\n        edge *nfst = iter\
    \ = new edge[len << 1];\n        for (edge *p{first}; p != last; ++p, ++iter)\n\
    \          p->rev->rev = iter, *iter = *p;\n        delete[] first;\n        first\
    \ = nfst;\n        last = iter + len;\n      }\n      return *iter++ = edge(args...);\n\
    \    }\n\n    reference operator[](size_type i) {\n      assert(i < size());\n\
    \      return *(first + i);\n    }\n    const_reference operator[](size_type i)\
    \ const {\n      assert(i < size());\n      return *(first + i);\n    }\n\n  \
    \  size_type size() const { return iter - first; }\n\n    pointer begin() { return\
    \ first; }\n    const_pointer begin() const { return first; }\n\n    pointer end()\
    \ { return iter; }\n    const_pointer end() const { return iter; }\n\n   protected:\n\
    \    pointer first, iter, last;\n  };\n\n  /**\n   * @brief Construct a new flow\
    \ base object\n   *\n   * @param n Number of vertices\n   */\n  flow_graph(size_type\
    \ n = 0) : graph(n) {}\n\n  flow_graph(const flow_graph &other) : graph(other.size())\
    \ {\n    for (size_type node = 0; node != size(); ++node)\n      for (edge cp\
    \ : other[node])\n        if (cp.src == node) {\n          edge rcp = *cp.rev;\n\
    \          cp.rev->src = nil;\n          edge &ref = graph[node].emplace(cp);\n\
    \          rcp.rev = &ref;\n          ref.rev = &graph[cp.dst].emplace(rcp);\n\
    \        } else\n          cp.rev->rev->src = node;\n  }\n\n  flow_graph &operator=(const\
    \ flow_graph &rhs) {\n    if (this != &rhs) graph.swap(flow_graph(rhs).graph);\n\
    \    return *this;\n  }\n\n  /**\n   * @return Number of vertices.\n   */\n  size_type\
    \ size() const { return graph.size(); }\n\n  reference operator[](size_type node)\
    \ {\n    assert(node < size());\n    return graph[node];\n  }\n\n  const_reference\
    \ &operator[](size_type node) const {\n    assert(node < size());\n    return\
    \ graph[node];\n  }\n\n  typename container_type::iterator begin() { return graph.begin();\
    \ }\n\n  typename container_type::iterator end() { return graph.end(); }\n\n \
    \ typename container_type::const_iterator begin() const {\n    return graph.begin();\n\
    \  }\n\n  typename container_type::const_iterator end() const { return graph.end();\
    \ }\n\n  template <class... Args>\n  typename adjacency::reference add_edge(size_type\
    \ src, size_type dst,\n                                         Args &&... args)\
    \ {\n    assert(src < size());\n    assert(dst < size());\n    auto &ref = graph[src].emplace(src,\
    \ dst, args..., nullptr);\n    ref.rev = &graph[dst].emplace(ref.make_rev());\n\
    \    return ref;\n  }\n\n protected:\n  constexpr static size_type nil = -1;\n\
    \  container_type graph;\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file base.hpp\n * @brief Flow Graph\n * @date 2021-01-15\n\
    \ *\n *\n */\n\n#include <cassert>\n#include <vector>\n\nnamespace workspace {\n\
    \ntemplate <class Cap, class Cost = void> class flow_graph {\n public:\n  class\
    \ adjacency;\n  using value_type = adjacency;\n  using reference = adjacency &;\n\
    \  using const_reference = adjacency const &;\n  using container_type = std::vector<value_type>;\n\
    \  using size_type = typename container_type::size_type;\n\n  class unweighted_edge\
    \ {\n   public:\n    size_type src, dst;\n    Cap cap;\n    unweighted_edge *rev;\n\
    \n    unweighted_edge() = default;\n\n    unweighted_edge(size_type src, size_type\
    \ dst, const Cap &cap,\n                    unweighted_edge *rev)\n        : src(src),\
    \ dst(dst), cap(cap), rev(rev) {\n      assert(!(cap < static_cast<Cap>(0)));\n\
    \    }\n\n    const Cap &flow(const Cap &f = 0) { return cap -= f, rev->cap +=\
    \ f; }\n\n    unweighted_edge make_rev() { return {dst, src, 0, this}; }\n  };\n\
    \n  class weighted_edge : public unweighted_edge {\n   public:\n    Cost cost;\n\
    \n    weighted_edge() = default;\n\n    weighted_edge(size_type src, size_type\
    \ dst, const Cap &cap,\n                  const Cost &cost, weighted_edge *rev)\n\
    \        : unweighted_edge(src, dst, cap, rev), cost(cost) {}\n\n    weighted_edge\
    \ make_rev() {\n      return {unweighted_edge::dst, unweighted_edge::src, 0, -cost,\
    \ this};\n    }\n  };\n\n  using edge = typename std::conditional<std::is_void<Cost>::value,\n\
    \                                         unweighted_edge, weighted_edge>::type;\n\
    \n  class adjacency {\n   public:\n    using value_type = edge;\n    using reference\
    \ = edge &;\n    using const_reference = edge const &;\n    using pointer = edge\
    \ *;\n    using const_pointer = const edge *;\n\n    adjacency() : first(new edge[1]),\
    \ iter(first), last(first + 1) {}\n    ~adjacency() { delete[] first; }\n\n  \
    \  template <class... Args> reference emplace(Args &&... args) {\n      if (iter\
    \ == last) {\n        size_type len(last - first);\n        edge *nfst = iter\
    \ = new edge[len << 1];\n        for (edge *p{first}; p != last; ++p, ++iter)\n\
    \          p->rev->rev = iter, *iter = *p;\n        delete[] first;\n        first\
    \ = nfst;\n        last = iter + len;\n      }\n      return *iter++ = edge(args...);\n\
    \    }\n\n    reference operator[](size_type i) {\n      assert(i < size());\n\
    \      return *(first + i);\n    }\n    const_reference operator[](size_type i)\
    \ const {\n      assert(i < size());\n      return *(first + i);\n    }\n\n  \
    \  size_type size() const { return iter - first; }\n\n    pointer begin() { return\
    \ first; }\n    const_pointer begin() const { return first; }\n\n    pointer end()\
    \ { return iter; }\n    const_pointer end() const { return iter; }\n\n   protected:\n\
    \    pointer first, iter, last;\n  };\n\n  /**\n   * @brief Construct a new flow\
    \ base object\n   *\n   * @param n Number of vertices\n   */\n  flow_graph(size_type\
    \ n = 0) : graph(n) {}\n\n  flow_graph(const flow_graph &other) : graph(other.size())\
    \ {\n    for (size_type node = 0; node != size(); ++node)\n      for (edge cp\
    \ : other[node])\n        if (cp.src == node) {\n          edge rcp = *cp.rev;\n\
    \          cp.rev->src = nil;\n          edge &ref = graph[node].emplace(cp);\n\
    \          rcp.rev = &ref;\n          ref.rev = &graph[cp.dst].emplace(rcp);\n\
    \        } else\n          cp.rev->rev->src = node;\n  }\n\n  flow_graph &operator=(const\
    \ flow_graph &rhs) {\n    if (this != &rhs) graph.swap(flow_graph(rhs).graph);\n\
    \    return *this;\n  }\n\n  /**\n   * @return Number of vertices.\n   */\n  size_type\
    \ size() const { return graph.size(); }\n\n  reference operator[](size_type node)\
    \ {\n    assert(node < size());\n    return graph[node];\n  }\n\n  const_reference\
    \ &operator[](size_type node) const {\n    assert(node < size());\n    return\
    \ graph[node];\n  }\n\n  typename container_type::iterator begin() { return graph.begin();\
    \ }\n\n  typename container_type::iterator end() { return graph.end(); }\n\n \
    \ typename container_type::const_iterator begin() const {\n    return graph.begin();\n\
    \  }\n\n  typename container_type::const_iterator end() const { return graph.end();\
    \ }\n\n  template <class... Args>\n  typename adjacency::reference add_edge(size_type\
    \ src, size_type dst,\n                                         Args &&... args)\
    \ {\n    assert(src < size());\n    assert(dst < size());\n    auto &ref = graph[src].emplace(src,\
    \ dst, args..., nullptr);\n    ref.rev = &graph[dst].emplace(ref.make_rev());\n\
    \    return ref;\n  }\n\n protected:\n  constexpr static size_type nil = -1;\n\
    \  container_type graph;\n};\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/graph/directed/flow/base.hpp
  requiredBy:
  - src/graph/directed/flow/Dinic.hpp
  - src/graph/directed/flow/min_cost_flow.hpp
  timestamp: '2021-01-18 04:02:07+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/bipartitematching.test.cpp
  - test/library-checker/assignment.test.cpp
  - test/aizu-online-judge/2815.test.cpp
documentation_of: src/graph/directed/flow/base.hpp
layout: document
redirect_from:
- /library/src/graph/directed/flow/base.hpp
- /library/src/graph/directed/flow/base.hpp.html
title: Flow Graph
---
