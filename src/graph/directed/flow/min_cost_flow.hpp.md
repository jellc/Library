---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/graph/directed/flow/base.hpp
    title: Flow Graph
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/2815.test.cpp
    title: test/aizu-online-judge/2815.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/assignment.test.cpp
    title: test/library-checker/assignment.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Minimum Cost Flow
    links: []
  bundledCode: "#line 2 \"src/graph/directed/flow/min_cost_flow.hpp\"\n\n/**\n * @file\
    \ min_cost_flow.hpp\n * @brief Minimum Cost Flow\n * @date 2021-01-15\n *\n *\n\
    \ */\n\n#include <algorithm>\n#include <optional>\n#include <queue>\n\n#line 2\
    \ \"src/graph/directed/flow/base.hpp\"\n\n/**\n * @file base.hpp\n * @brief Flow\
    \ Graph\n * @date 2021-01-15\n *\n *\n */\n\n#include <cassert>\n#include <vector>\n\
    \nnamespace workspace {\n\ntemplate <class Cap, class Cost> class flow_graph {\n\
    \ protected:\n  class adjacency;\n\n public:\n  using value_type = adjacency;\n\
    \  using reference = adjacency &;\n  using const_reference = adjacency const &;\n\
    \  using container_type = std::vector<value_type>;\n  using size_type = typename\
    \ container_type::size_type;\n\n protected:\n  /**\n   * @brief Edge of flow graph.\n\
    \   *\n   */\n  class edge {\n   public:\n    size_type src, dst;\n    Cap cap;\n\
    \    Cost cost;\n    edge *rev;\n\n    edge() = default;\n\n    edge(size_type\
    \ src, size_type dst, const Cap &cap, edge *rev)\n        : src(src), dst(dst),\
    \ cap(cap), rev(rev) {}\n\n    edge(size_type src, size_type dst, const Cap &cap,\
    \ const Cost &cost,\n         edge *rev)\n        : src(src), dst(dst), cap(cap),\
    \ cost(cost), rev(rev) {}\n\n    const Cap &flow(const Cap &f = 0) { return cap\
    \ -= f, rev->cap += f; }\n  };\n\n  class adjacency {\n    edge *first, *iter,\
    \ *last;\n\n   public:\n    using value_type = edge;\n    using reference = edge\
    \ &;\n    using const_reference = edge const &;\n    using pointer = edge *;\n\
    \    using const_pointer = const edge *;\n\n    adjacency() : first(new edge[1]),\
    \ iter(first), last(first + 1) {}\n    ~adjacency() { delete[] first; }\n\n  \
    \  template <class... Args> pointer emplace(Args &&... args) {\n      if (iter\
    \ == last) {\n        size_type len(last - first);\n        edge *nfst = iter\
    \ = new edge[len << 1];\n        for (edge *p{first}; p != last; ++p, ++iter)\n\
    \          p->rev->rev = iter, *iter = *p;\n        delete[] first;\n        first\
    \ = nfst;\n        last = iter + len;\n      }\n      *iter = edge(args...);\n\
    \      return iter++;\n    }\n\n    reference operator[](size_type i) {\n    \
    \  assert(i < size());\n      return *(first + i);\n    }\n\n    const_reference\
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
    #line 16 \"src/graph/directed/flow/min_cost_flow.hpp\"\n\nnamespace workspace\
    \ {\n\n/**\n * @brief Successive Shortest Path Algorithm.\n *\n * @tparam Cap\
    \ Capacity type\n * @tparam Cost Cost type\n * @tparam Density_tag Whether the\
    \ graph is dense.\n */\ntemplate <class Cap, class Cost, bool Density_tag = false>\n\
    class min_cost_flow : public flow_graph<Cap, Cost> {\n  using base = flow_graph<Cap,\
    \ Cost>;\n  using base::nil;\n\n public:\n  using edge = typename base::edge;\n\
    \  using size_type = typename base::size_type;\n\n protected:\n  Cost min_cost,\
    \ cost_bound;\n  std::vector<Cap> supp;\n  std::vector<Cost> ptnl;\n\n  void copy(const\
    \ min_cost_flow &other) {\n    min_cost = other.min_cost;\n    cost_bound = other.cost_bound;\n\
    \    supp = other.supp;\n    ptnl = other.ptnl;\n  }\n\n  void Dijkstra(std::vector<edge\
    \ *> &last) {\n    const Cost infty(cost_bound + 1);\n    std::vector<Cost> nptnl(size(),\
    \ infty);\n    if constexpr (Density_tag) {  // O(V^2)\n      std::vector<bool>\
    \ used(size());\n      for (size_type src{}; src != size(); ++src) {\n       \
    \ if (static_cast<Cap>(0) < supp[src]) {\n          used[src] = true;\n      \
    \    nptnl[src] = 0;\n          for (edge &e : base::graph[src]) {\n         \
    \   if (static_cast<Cap>(0) < supp[e.dst]) continue;\n            if (e.avbl()\
    \ && e.cost < nptnl[e.dst]) {\n              nptnl[e.dst] = e.cost;\n        \
    \      last[e.dst] = &e;\n            }\n          }\n        }\n      }\n   \
    \   for (;;) {\n        size_type src{nil};\n        Cost sp{infty};\n       \
    \ for (size_type node{}; node != size(); ++node) {\n          if (used[node] ||\
    \ nptnl[node] == infty) continue;\n          Cost dist{nptnl[node] - ptnl[node]};\n\
    \          if (dist < sp) {\n            sp = dist;\n            src = node;\n\
    \          }\n        }\n        if (src == nil) break;\n        used[src] = true;\n\
    \        for (edge &e : base::graph[src]) {\n          if (e.avbl() && nptnl[src]\
    \ + e.cost < nptnl[e.dst]) {\n            nptnl[e.dst] = nptnl[src] + e.cost;\n\
    \            last[e.dst] = &e;\n          }\n        }\n      }\n    } else {\
    \  // O((V + E)logV)\n      struct sp_node {\n        size_type id;\n        Cost\
    \ dist;\n        sp_node(size_type id, Cost dist) : id(id), dist(dist) {}\n  \
    \      bool operator<(const sp_node &rhs) const { return rhs.dist < dist; }\n\
    \      };\n\n      std::priority_queue<sp_node> que;\n\n      for (size_type src{};\
    \ src != size(); ++src)\n        if (supp[src] > static_cast<Cap>(0)) {\n    \
    \      nptnl[src] = 0;\n          for (edge &e : base::graph[src])\n         \
    \   if (!(static_cast<Cap>(0) < supp[e.dst]) &&\n                static_cast<Cap>(0)\
    \ < e.cap && nptnl[e.dst] > e.cost) {\n              que.emplace(e.dst, (nptnl[e.dst]\
    \ = e.cost) - ptnl[e.dst]);\n              last[e.dst] = &e;\n            }\n\
    \        }\n\n      while (!que.empty()) {\n        auto [src, ndist] = que.top();\n\
    \        que.pop();\n        if (ndist + ptnl[src] != nptnl[src]) continue;\n\
    \        for (edge &e : base::graph[src])\n          if (static_cast<Cap>(0) <\
    \ e.cap &&\n              nptnl[e.dst] > nptnl[src] + e.cost) {\n            que.emplace(e.dst,\n\
    \                        (nptnl[e.dst] = nptnl[src] + e.cost) - ptnl[e.dst]);\n\
    \            last[e.dst] = &e;\n          }\n      }\n    }\n\n    ptnl.swap(nptnl);\n\
    \  }\n\n public:\n  using base::size;\n\n  /**\n   * @brief Construct a new object\n\
    \   *\n   * @param n Number of vertices.\n   */\n  min_cost_flow(size_type n =\
    \ 0)\n      : base::flow_graph(n), min_cost(0), cost_bound(0), supp(n), ptnl(n)\
    \ {}\n\n  min_cost_flow(const min_cost_flow &other) : base::flow_graph(other)\
    \ {\n    copy(other);\n  }\n\n  min_cost_flow &operator=(const min_cost_flow &other)\
    \ {\n    base::operator=(other);\n    copy(other);\n    return *this;\n  }\n\n\
    \  // infinity capatity\n  // edge *add_edge(size_type src, size_type dst, const\
    \ Cost &cost);\n\n  /**\n   * @brief Add an edge to the graph.\n   *\n   * @param\
    \ src Source\n   * @param dst Destination\n   * @param cap Capacity\n   * @param\
    \ cost Cost\n   * @return Pointer to the edge.\n   */\n  typename base::adjacency::pointer\
    \ add_edge(size_type src, size_type dst,\n                                   \
    \          const Cap &cap,\n                                             const\
    \ Cost &cost) override {\n    assert(src != dst);\n    if (cost < static_cast<Cost>(0))\
    \ {\n      supp[src] -= cap;\n      supp[dst] += cap;\n      min_cost += cap *\
    \ cost;\n      cost_bound -= cap * cost;\n      return base::add_edge(dst, src,\
    \ cap, -cost);\n    }\n    cost_bound += cap * cost;\n    return base::add_edge(src,\
    \ dst, cap, cost);\n  }\n\n  /**\n   * @brief Add an edge to the graph.\n   *\n\
    \   * @param src Source\n   * @param dst Destination\n   * @param lower Lower\
    \ bound of flow\n   * @param upper Upper bound of flow\n   * @param cost Cost\n\
    \   * @return Pointer to the edge.\n   */\n  typename base::adjacency::pointer\
    \ add_edge(size_type src, size_type dst,\n                                   \
    \          const Cap &lower, const Cap &upper,\n                             \
    \                const Cost &cost) {\n    assert(!(upper < lower));\n    supp[src]\
    \ -= lower;\n    supp[dst] += lower;\n    min_cost += lower * cost;\n    return\
    \ add_edge(src, dst, upper - lower, cost);\n  }\n\n  /**\n   * @brief Increase\
    \ the balance of a node.\n   *\n   * @param node\n   * @param vol\n   */\n  void\
    \ supply(size_type node, const Cap &vol) {\n    assert(node < size());\n    supp[node]\
    \ += vol;\n  }\n\n  /**\n   * @brief Decrease the balance of a node.\n   *\n \
    \  * @param node\n   * @param vol\n   */\n  void demand(size_type node, const\
    \ Cap &vol) { supply(node, -vol); }\n\n  /**\n   * @param node\n   * @return Balance\
    \ of the node\n   */\n  Cap balance(size_type node) { return supp[node]; }\n\n\
    \  /**\n   * @return Cost of current flow.\n   */\n  Cost cost() const { return\
    \ min_cost; }\n\n  /**\n   * @brief Run Successive Shortest Path Algorithm.\n\
    \   *\n   * @return Whether a balanced flow exists.\n   */\n  bool flow() {\n\
    \    for (bool aug = true; aug;) {\n      aug = false;\n      std::vector<edge\
    \ *> last(size());\n      Dijkstra(last);\n      std::vector<bool> shut(size());\n\
    \      for (size_type dst{}; dst != size(); ++dst) {\n        if (supp[dst] <\
    \ static_cast<Cap>(0) and last[dst]) {\n          Cap resid{-supp[dst]};\n   \
    \       size_type src{dst}, block{nil};\n          while (last[src] && !shut[src])\
    \ {\n            if (!(resid < last[src]->cap)) resid = last[block = src]->cap;\n\
    \            src = last[src]->src;\n          }\n          if (shut[src])\n  \
    \          block = src;\n          else {\n            if (!(resid < supp[src]))\
    \ resid = supp[block = src];\n            for (edge *e{last[dst]}; e; e = last[e->src])\
    \ {\n              e->cap -= resid;\n              e->rev->cap += resid;\n   \
    \         }\n            supp[src] -= resid;\n            supp[dst] += resid;\n\
    \            min_cost += ptnl[dst] * resid;\n            aug = true;\n       \
    \   }\n          if (~block) {\n            for (size_type node{dst};; node =\
    \ last[node]->src) {\n              shut[node] = true;\n              if (node\
    \ == block) break;\n            }\n          }\n        }\n      }\n    }\n  \
    \  return std::none_of(begin(supp), end(supp), [](const Cap &s) {\n      return\
    \ s < static_cast<Cap>(0) || static_cast<Cap>(0) < s;\n    });\n  }\n};\n\n} \
    \ // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file min_cost_flow.hpp\n * @brief Minimum Cost Flow\n\
    \ * @date 2021-01-15\n *\n *\n */\n\n#include <algorithm>\n#include <optional>\n\
    #include <queue>\n\n#include \"base.hpp\"\n\nnamespace workspace {\n\n/**\n *\
    \ @brief Successive Shortest Path Algorithm.\n *\n * @tparam Cap Capacity type\n\
    \ * @tparam Cost Cost type\n * @tparam Density_tag Whether the graph is dense.\n\
    \ */\ntemplate <class Cap, class Cost, bool Density_tag = false>\nclass min_cost_flow\
    \ : public flow_graph<Cap, Cost> {\n  using base = flow_graph<Cap, Cost>;\n  using\
    \ base::nil;\n\n public:\n  using edge = typename base::edge;\n  using size_type\
    \ = typename base::size_type;\n\n protected:\n  Cost min_cost, cost_bound;\n \
    \ std::vector<Cap> supp;\n  std::vector<Cost> ptnl;\n\n  void copy(const min_cost_flow\
    \ &other) {\n    min_cost = other.min_cost;\n    cost_bound = other.cost_bound;\n\
    \    supp = other.supp;\n    ptnl = other.ptnl;\n  }\n\n  void Dijkstra(std::vector<edge\
    \ *> &last) {\n    const Cost infty(cost_bound + 1);\n    std::vector<Cost> nptnl(size(),\
    \ infty);\n    if constexpr (Density_tag) {  // O(V^2)\n      std::vector<bool>\
    \ used(size());\n      for (size_type src{}; src != size(); ++src) {\n       \
    \ if (static_cast<Cap>(0) < supp[src]) {\n          used[src] = true;\n      \
    \    nptnl[src] = 0;\n          for (edge &e : base::graph[src]) {\n         \
    \   if (static_cast<Cap>(0) < supp[e.dst]) continue;\n            if (e.avbl()\
    \ && e.cost < nptnl[e.dst]) {\n              nptnl[e.dst] = e.cost;\n        \
    \      last[e.dst] = &e;\n            }\n          }\n        }\n      }\n   \
    \   for (;;) {\n        size_type src{nil};\n        Cost sp{infty};\n       \
    \ for (size_type node{}; node != size(); ++node) {\n          if (used[node] ||\
    \ nptnl[node] == infty) continue;\n          Cost dist{nptnl[node] - ptnl[node]};\n\
    \          if (dist < sp) {\n            sp = dist;\n            src = node;\n\
    \          }\n        }\n        if (src == nil) break;\n        used[src] = true;\n\
    \        for (edge &e : base::graph[src]) {\n          if (e.avbl() && nptnl[src]\
    \ + e.cost < nptnl[e.dst]) {\n            nptnl[e.dst] = nptnl[src] + e.cost;\n\
    \            last[e.dst] = &e;\n          }\n        }\n      }\n    } else {\
    \  // O((V + E)logV)\n      struct sp_node {\n        size_type id;\n        Cost\
    \ dist;\n        sp_node(size_type id, Cost dist) : id(id), dist(dist) {}\n  \
    \      bool operator<(const sp_node &rhs) const { return rhs.dist < dist; }\n\
    \      };\n\n      std::priority_queue<sp_node> que;\n\n      for (size_type src{};\
    \ src != size(); ++src)\n        if (supp[src] > static_cast<Cap>(0)) {\n    \
    \      nptnl[src] = 0;\n          for (edge &e : base::graph[src])\n         \
    \   if (!(static_cast<Cap>(0) < supp[e.dst]) &&\n                static_cast<Cap>(0)\
    \ < e.cap && nptnl[e.dst] > e.cost) {\n              que.emplace(e.dst, (nptnl[e.dst]\
    \ = e.cost) - ptnl[e.dst]);\n              last[e.dst] = &e;\n            }\n\
    \        }\n\n      while (!que.empty()) {\n        auto [src, ndist] = que.top();\n\
    \        que.pop();\n        if (ndist + ptnl[src] != nptnl[src]) continue;\n\
    \        for (edge &e : base::graph[src])\n          if (static_cast<Cap>(0) <\
    \ e.cap &&\n              nptnl[e.dst] > nptnl[src] + e.cost) {\n            que.emplace(e.dst,\n\
    \                        (nptnl[e.dst] = nptnl[src] + e.cost) - ptnl[e.dst]);\n\
    \            last[e.dst] = &e;\n          }\n      }\n    }\n\n    ptnl.swap(nptnl);\n\
    \  }\n\n public:\n  using base::size;\n\n  /**\n   * @brief Construct a new object\n\
    \   *\n   * @param n Number of vertices.\n   */\n  min_cost_flow(size_type n =\
    \ 0)\n      : base::flow_graph(n), min_cost(0), cost_bound(0), supp(n), ptnl(n)\
    \ {}\n\n  min_cost_flow(const min_cost_flow &other) : base::flow_graph(other)\
    \ {\n    copy(other);\n  }\n\n  min_cost_flow &operator=(const min_cost_flow &other)\
    \ {\n    base::operator=(other);\n    copy(other);\n    return *this;\n  }\n\n\
    \  // infinity capatity\n  // edge *add_edge(size_type src, size_type dst, const\
    \ Cost &cost);\n\n  /**\n   * @brief Add an edge to the graph.\n   *\n   * @param\
    \ src Source\n   * @param dst Destination\n   * @param cap Capacity\n   * @param\
    \ cost Cost\n   * @return Pointer to the edge.\n   */\n  typename base::adjacency::pointer\
    \ add_edge(size_type src, size_type dst,\n                                   \
    \          const Cap &cap,\n                                             const\
    \ Cost &cost) override {\n    assert(src != dst);\n    if (cost < static_cast<Cost>(0))\
    \ {\n      supp[src] -= cap;\n      supp[dst] += cap;\n      min_cost += cap *\
    \ cost;\n      cost_bound -= cap * cost;\n      return base::add_edge(dst, src,\
    \ cap, -cost);\n    }\n    cost_bound += cap * cost;\n    return base::add_edge(src,\
    \ dst, cap, cost);\n  }\n\n  /**\n   * @brief Add an edge to the graph.\n   *\n\
    \   * @param src Source\n   * @param dst Destination\n   * @param lower Lower\
    \ bound of flow\n   * @param upper Upper bound of flow\n   * @param cost Cost\n\
    \   * @return Pointer to the edge.\n   */\n  typename base::adjacency::pointer\
    \ add_edge(size_type src, size_type dst,\n                                   \
    \          const Cap &lower, const Cap &upper,\n                             \
    \                const Cost &cost) {\n    assert(!(upper < lower));\n    supp[src]\
    \ -= lower;\n    supp[dst] += lower;\n    min_cost += lower * cost;\n    return\
    \ add_edge(src, dst, upper - lower, cost);\n  }\n\n  /**\n   * @brief Increase\
    \ the balance of a node.\n   *\n   * @param node\n   * @param vol\n   */\n  void\
    \ supply(size_type node, const Cap &vol) {\n    assert(node < size());\n    supp[node]\
    \ += vol;\n  }\n\n  /**\n   * @brief Decrease the balance of a node.\n   *\n \
    \  * @param node\n   * @param vol\n   */\n  void demand(size_type node, const\
    \ Cap &vol) { supply(node, -vol); }\n\n  /**\n   * @param node\n   * @return Balance\
    \ of the node\n   */\n  Cap balance(size_type node) { return supp[node]; }\n\n\
    \  /**\n   * @return Cost of current flow.\n   */\n  Cost cost() const { return\
    \ min_cost; }\n\n  /**\n   * @brief Run Successive Shortest Path Algorithm.\n\
    \   *\n   * @return Whether a balanced flow exists.\n   */\n  bool flow() {\n\
    \    for (bool aug = true; aug;) {\n      aug = false;\n      std::vector<edge\
    \ *> last(size());\n      Dijkstra(last);\n      std::vector<bool> shut(size());\n\
    \      for (size_type dst{}; dst != size(); ++dst) {\n        if (supp[dst] <\
    \ static_cast<Cap>(0) and last[dst]) {\n          Cap resid{-supp[dst]};\n   \
    \       size_type src{dst}, block{nil};\n          while (last[src] && !shut[src])\
    \ {\n            if (!(resid < last[src]->cap)) resid = last[block = src]->cap;\n\
    \            src = last[src]->src;\n          }\n          if (shut[src])\n  \
    \          block = src;\n          else {\n            if (!(resid < supp[src]))\
    \ resid = supp[block = src];\n            for (edge *e{last[dst]}; e; e = last[e->src])\
    \ {\n              e->cap -= resid;\n              e->rev->cap += resid;\n   \
    \         }\n            supp[src] -= resid;\n            supp[dst] += resid;\n\
    \            min_cost += ptnl[dst] * resid;\n            aug = true;\n       \
    \   }\n          if (~block) {\n            for (size_type node{dst};; node =\
    \ last[node]->src) {\n              shut[node] = true;\n              if (node\
    \ == block) break;\n            }\n          }\n        }\n      }\n    }\n  \
    \  return std::none_of(begin(supp), end(supp), [](const Cap &s) {\n      return\
    \ s < static_cast<Cap>(0) || static_cast<Cap>(0) < s;\n    });\n  }\n};\n\n} \
    \ // namespace workspace\n"
  dependsOn:
  - src/graph/directed/flow/base.hpp
  isVerificationFile: false
  path: src/graph/directed/flow/min_cost_flow.hpp
  requiredBy: []
  timestamp: '2021-01-16 02:48:49+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/assignment.test.cpp
  - test/aizu-online-judge/2815.test.cpp
documentation_of: src/graph/directed/flow/min_cost_flow.hpp
layout: document
redirect_from:
- /library/src/graph/directed/flow/min_cost_flow.hpp
- /library/src/graph/directed/flow/min_cost_flow.hpp.html
title: Minimum Cost Flow
---
