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
    \ Graph\n * @date 2021-01-15\n *\n *\n */\n\n#include <cassert>\n#include <numeric>\n\
    #include <vector>\n\nnamespace workspace {\n\ntemplate <class Cap, class Cost\
    \ = void> class flow_graph {\n protected:\n  class adjacency_impl;\n\n public:\n\
    \  using container_type = std::vector<adjacency_impl>;\n  using size_type = typename\
    \ container_type::size_type;\n\n  class unweighted_edge {\n   public:\n    size_type\
    \ src, dst;\n    Cap cap;\n\n    unweighted_edge() = default;\n\n    unweighted_edge(size_type\
    \ src, size_type dst, const Cap &cap)\n        : src(src), dst(dst), cap(cap)\
    \ {\n      assert(!(cap < static_cast<Cap>(0)));\n    }\n\n    template <class\
    \ Os>\n    friend Os &operator<<(Os &__os, unweighted_edge const &__e) {\n   \
    \   return __os << __e.src << \" \" << __e.dst << \" \" << __e.cap;\n    }\n\n\
    \   protected:\n    unweighted_edge make_rev() { return {dst, src, 0}; }\n  };\n\
    \n  class weighted_edge : public unweighted_edge {\n   public:\n    Cost cost;\n\
    \n    weighted_edge() = default;\n\n    weighted_edge(size_type src, size_type\
    \ dst, const Cap &cap,\n                  const Cost &cost)\n        : unweighted_edge(src,\
    \ dst, cap), cost(cost) {}\n\n    template <class Os>\n    friend Os &operator<<(Os\
    \ &__os, weighted_edge const &__e) {\n      return __os << static_cast<unweighted_edge>(__e)\
    \ << \" \" << __e.cost;\n    }\n\n   protected:\n    weighted_edge make_rev()\
    \ {\n      return {unweighted_edge::dst, unweighted_edge::src, 0, -cost};\n  \
    \  }\n  };\n\n  using edge = typename std::conditional<std::is_void<Cost>::value,\n\
    \                                         unweighted_edge, weighted_edge>::type;\n\
    \n protected:\n  struct edge_impl : edge {\n    bool aux = false;\n    edge_impl\
    \ *rev = nullptr;\n\n    edge_impl() = default;\n\n    edge_impl(const edge_impl\
    \ &__e) = default;\n\n    edge_impl(const edge &__e) : edge(__e) {}\n\n    void\
    \ flow(const Cap &f) { edge::cap -= f, rev->cap += f; }\n\n    edge_impl rev_cp()\
    \ {\n      edge_impl __e;\n      if (rev)\n        __e = *rev;\n      else {\n\
    \        __e = edge::make_rev();\n        __e.aux = true;\n      }\n      __e.rev\
    \ = this;\n      return __e;\n    }\n  };\n\n public:\n  class adjacency {\n \
    \  public:\n    using value_type = edge;\n    using reference = edge &;\n    using\
    \ const_reference = edge const &;\n    using pointer = edge *;\n    using const_pointer\
    \ = const edge *;\n\n    class const_iterator {\n     public:\n      const edge_impl\
    \ *__p;\n\n      bool operator!=(const_iterator const &__x) const {\n        return\
    \ __p != __x.__p;\n      }\n\n      const_iterator &operator++() {\n        do\n\
    \          ++__p;\n        while (__p->rev && __p->aux);\n        return *this;\n\
    \      }\n\n      const_pointer operator->() const { return __p; }\n\n      const_reference\
    \ operator*() const { return *__p; }\n    };\n\n    adjacency()\n        : first(new\
    \ edge_impl[2]), last(first + 1), __s(first), __t(first) {}\n\n    ~adjacency()\
    \ { delete[] first; }\n\n    const_reference operator[](size_type i) const {\n\
    \      assert(i < size());\n      return *(first + i);\n    }\n\n    size_type\
    \ size() const { return __t - first; }\n\n    auto begin() const { return const_iterator{__s};\
    \ }\n    auto end() const { return const_iterator{__t}; }\n\n    /**\n     * @brief\
    \ Construct a new adjacency object\n     *\n     * @param __x Rvalue reference\
    \ to another object\n     */\n    adjacency(adjacency &&__x) : first(nullptr)\
    \ { operator=(std::move(__x)); }\n\n    /**\n     * @brief Assignment operator.\n\
    \     *\n     * @param __x Rvalue reference to another object\n     * @return\
    \ Reference to this object.\n     */\n    adjacency &operator=(adjacency &&__x)\
    \ {\n      std::swap(first, __x.first);\n      last = __x.last;\n      __s = __x.__s;\n\
    \      __t = __x.__t;\n      return *this;\n    }\n\n   protected:\n    edge_impl\
    \ *first, *last, *__s, *__t;\n  };\n\n  using value_type = adjacency;\n  using\
    \ reference = adjacency &;\n  using const_reference = adjacency const &;\n\n protected:\n\
    \  class adjacency_impl : public adjacency {\n   public:\n    using base = adjacency;\n\
    \    using base::__s;\n    using base::__t;\n    using base::first;\n    using\
    \ base::last;\n\n    template <class... Args> auto emplace(Args &&... args) {\n\
    \      if (__t == last) {\n        size_type __n(last - first);\n        edge_impl\
    \ *loc = new edge_impl[__n << 1 | 1];\n        __s += loc - first;\n        __t\
    \ = loc;\n        for (edge_impl *__p{first}; __p != last; ++__p, ++__t)\n   \
    \       __p->rev->rev = __t, *__t = *__p;\n        delete[] first;\n        first\
    \ = loc;\n        last = __t + __n;\n      }\n      *__t = edge_impl(args...);\n\
    \      if (__s->aux) ++__s;\n      return __t++;\n    }\n\n    using iterator\
    \ = edge_impl *;\n    auto begin() const { return first; }\n    auto end() const\
    \ { return __t; }\n  };\n\n public:\n  /**\n   * @brief Construct a new flow graph\
    \ object\n   *\n   * @param __n Number of vertices\n   */\n  flow_graph(size_type\
    \ __n = 0) : graph(__n) {}\n\n  /**\n   * @brief Construct a new flow graph object\n\
    \   *\n   * @param __x Const reference to another object\n   */\n  flow_graph(const\
    \ flow_graph &__x) : graph(__x.size()) {\n    for (auto &&__adj : __x)\n     \
    \ for (auto &&__e : __adj) _add_edge(__e);\n  }\n\n  /**\n   * @brief Assignment\
    \ operator.\n   *\n   * @param __x Rvalue reference to another object\n   * @return\
    \ Reference to this object.\n   */\n  flow_graph &operator=(flow_graph &&__x)\
    \ {\n    graph.swap(__x.graph);\n    return *this;\n  }\n\n  /**\n   * @return\
    \ Number of nodes.\n   */\n  size_type size() const { return graph.size(); }\n\
    \n  reference operator[](size_type node) {\n    assert(node < size());\n    return\
    \ graph[node];\n  }\n\n  const_reference &operator[](size_type node) const {\n\
    \    assert(node < size());\n    return graph[node];\n  }\n\n  class const_iterator\
    \ : public container_type::const_iterator {\n   public:\n    using base = typename\
    \ container_type::const_iterator;\n    using const_reference = const adjacency\
    \ &;\n    using const_pointer = const adjacency *;\n\n    const_iterator(base\
    \ const &__i) : base(__i) {}\n\n    const_pointer operator->() const { return\
    \ base::operator->(); }\n\n    const_reference operator*() const { return base::operator*();\
    \ }\n  };\n\n  auto begin() const { return const_iterator{graph.begin()}; }\n\
    \  auto end() const { return const_iterator{graph.end()}; }\n\n  size_type add_node()\
    \ { return add_nodes(1).front(); }\n\n  virtual std::vector<size_type> add_nodes(size_type\
    \ __n) {\n    std::vector<size_type> __nds(__n);\n    std::iota(__nds.begin(),\
    \ __nds.end(), graph.size());\n    __n += graph.size();\n    if (__n > graph.capacity())\
    \ {\n      flow_graph __x(__n);\n      for (auto &&adj : graph)\n        for (auto\
    \ &&__e : adj)\n          if (!__e.aux) __x._add_edge(__e);\n      graph.swap(__x.graph);\n\
    \    } else\n      graph.resize(__n);\n    return __nds;\n  }\n\n  template <class...\
    \ Args> const edge &add_edge(Args &&... args) {\n    return *_add_edge(edge(args...));\n\
    \  }\n\n protected:\n  template <class... Args> edge_impl *_add_edge(Args &&...\
    \ args) {\n    edge_impl __e(args...);\n    assert(__e.src < size());\n    assert(__e.dst\
    \ < size());\n    auto __p = graph[__e.src].emplace(__e);\n    __p->rev = graph[__e.dst].emplace(__p->rev_cp());\n\
    \    return __p;\n  }\n\n  constexpr static size_type nil = -1;\n  container_type\
    \ graph;\n\n  template <class Os> friend Os &operator<<(Os &__os, flow_graph const\
    \ &__g) {\n    for (const auto &adj : __g)\n      for (const auto &e : adj) __os\
    \ << e << \"\\n\";\n    return __os;\n  }\n};\n\n}  // namespace workspace\n#line\
    \ 16 \"src/graph/directed/flow/min_cost_flow.hpp\"\n\nnamespace workspace {\n\n\
    /**\n * @brief Successive Shortest Path Algorithm.\n *\n * @tparam Cap Capacity\
    \ type\n * @tparam Cost Cost type\n * @tparam Density_tag Whether the graph is\
    \ dense.\n */\ntemplate <class Cap, class Cost = Cap, bool Density_tag = false>\n\
    class min_cost_flow : public flow_graph<Cap, Cost> {\n  using base = flow_graph<Cap,\
    \ Cost>;\n  using edge_impl = typename base::edge_impl;\n  using base::nil;\n\n\
    \ public:\n  using size_type = typename base::size_type;\n  using base::size;\n\
    \n  /**\n   * @brief Construct a new min_cost_flow object\n   *\n   * @param __n\
    \ Number of vertices\n   */\n  min_cost_flow(size_type __n = 0)\n      : base::flow_graph(__n),\
    \ current(0), abs_sum(0), b(__n), p(__n) {}\n\n  std::vector<size_type> add_nodes(size_type\
    \ __n) override {\n    auto __nds = base::add_nodes(__n);\n    b.resize(size());\n\
    \    p.resize(size());\n    return __nds;\n  }\n\n  /**\n   * @brief Add an edge\
    \ with a unit capacity to the graph.\n   *\n   * @param src Source\n   * @param\
    \ dst Destination\n   * @param cost Cost\n   * @return Reference to the edge.\n\
    \   */\n  auto &add_edge(size_type src, size_type dst, const Cost &cost) {\n \
    \   return add_edge(src, dst, 1, cost);\n  }\n\n  /**\n   * @brief Add an edge\
    \ to the graph.\n   *\n   * @param src Source\n   * @param dst Destination\n \
    \  * @param cap Capacity\n   * @param cost Cost\n   * @return Reference to the\
    \ edge.\n   */\n  typename base::edge const &add_edge(size_type src, size_type\
    \ dst,\n                                      const Cap &cap, const Cost &cost)\
    \ {\n    edge_impl *__p = base::_add_edge(typename base::edge(src, dst, cap, cost));\n\
    \    if (cost < static_cast<Cost>(0)) {\n      __p->flow(cap);\n      b[src] -=\
    \ cap;\n      b[dst] += cap;\n      current += cap * cost;\n      abs_sum -= cap\
    \ * cost;\n    } else\n      abs_sum += cap * cost;\n    return *__p;\n  }\n\n\
    \  /**\n   * @brief Add an edge to the graph.\n   *\n   * @param src Source\n\
    \   * @param dst Destination\n   * @param lower Lower bound of flow\n   * @param\
    \ upper Upper bound of flow\n   * @param cost Cost\n   * @return Reference to\
    \ the edge.\n   */\n  auto &add_edge(size_type src, size_type dst, const Cap &lower,\n\
    \                 const Cap &upper, const Cost &cost) {\n    assert(!(upper <\
    \ lower));\n    b[src] -= lower;\n    b[dst] += lower;\n    current += lower *\
    \ cost;\n    return add_edge(src, dst, upper - lower, cost);\n  }\n\n  /**\n \
    \  * @brief Increase the balance of a node.\n   *\n   * @param node\n   * @param\
    \ vol Default: 1\n   */\n  void supply(size_type node, const Cap &vol = 1) {\n\
    \    assert(node < size());\n    b[node] += vol;\n  }\n\n  /**\n   * @brief Decrease\
    \ the balance of a node.\n   *\n   * @param node\n   * @param vol Default: 1\n\
    \   */\n  void demand(size_type node, const Cap &vol = 1) {\n    assert(node <\
    \ size());\n    b[node] -= vol;\n  }\n\n  /**\n   * @param node\n   * @return\
    \ Balance of the node\n   */\n  Cap balance(size_type node) { return b[node];\
    \ }\n\n  /**\n   * @return Cost of current flow.\n   */\n  Cost cost() const {\
    \ return current; }\n\n  /**\n   * @brief Run Successive Shortest Path Algorithm.\n\
    \   *\n   * @return Whether a balanced flow exists.\n   */\n  bool flow() {\n\
    \    for (bool aug = true; aug;) {\n      aug = false;\n      std::vector<edge_impl\
    \ *> last(size());\n      Dijkstra(last);\n      std::vector<bool> shut(size());\n\
    \      for (size_type dst{}; dst != size(); ++dst) {\n        if (b[dst] < static_cast<Cap>(0)\
    \ && last[dst]) {\n          Cap resid{-b[dst]};\n          size_type src{dst},\
    \ block{nil};\n          while (last[src] && !shut[src]) {\n            if (!(resid\
    \ < last[src]->cap)) resid = last[block = src]->cap;\n            src = last[src]->src;\n\
    \          }\n          if (shut[src])\n            block = src;\n          else\
    \ {\n            if (!(resid < b[src])) resid = b[block = src];\n            for\
    \ (edge_impl *e{last[dst]}; e; e = last[e->src]) {\n              e->cap -= resid;\n\
    \              e->rev->cap += resid;\n            }\n            b[src] -= resid;\n\
    \            b[dst] += resid;\n            current += p[dst] * resid;\n      \
    \      aug = true;\n          }\n          if (block != nil)\n            for\
    \ (size_type node{dst};; node = last[node]->src) {\n              shut[node] =\
    \ true;\n              if (node == block) break;\n            }\n        }\n \
    \     }\n    }\n    return std::none_of(begin(b), end(b), [](const Cap &s) {\n\
    \      return s < static_cast<Cap>(0) || static_cast<Cap>(0) < s;\n    });\n \
    \ }\n\n protected:\n  Cost current, abs_sum;\n  std::vector<Cap> b;\n  std::vector<Cost>\
    \ p;\n\n  void Dijkstra(std::vector<edge_impl *> &last) {\n    const Cost infty(abs_sum\
    \ + 1);\n    std::vector<Cost> newp(size(), infty);\n\n    if constexpr (Density_tag)\
    \ {  // O(V^2)\n      std::vector<bool> used(size());\n\n      for (size_type\
    \ src{}; src != size(); ++src)\n        if (static_cast<Cap>(0) < b[src]) {\n\
    \          used[src] = true;\n          newp[src] = 0;\n\n          for (auto\
    \ &e : base::graph[src])\n            if (static_cast<Cap>(0) < e.cap && e.cost\
    \ < newp[e.dst])\n              newp[e.dst] = e.cost, last[e.dst] = &e;\n    \
    \    }\n\n      for (;;) {\n        size_type src{nil};\n        Cost sp{infty};\n\
    \n        for (size_type node{}; node != size(); ++node) {\n          if (used[node]\
    \ || newp[node] == infty) continue;\n          if (Cost __d = newp[node] - p[node];\
    \ __d < sp) sp = __d, src = node;\n        }\n\n        if (src == nil) break;\n\
    \        used[src] = true;\n\n        for (auto &e : base::graph[src])\n     \
    \     if (static_cast<Cap>(0) < e.cap && newp[src] + e.cost < newp[e.dst]) {\n\
    \            newp[e.dst] = newp[src] + e.cost;\n            last[e.dst] = &e;\n\
    \          }\n      }\n    }\n\n    else {  // O((V + E)logV)\n      struct sp_node\
    \ {\n        size_type id;\n        Cost __d;\n        sp_node(size_type id, Cost\
    \ __d) : id(id), __d(__d) {}\n        bool operator<(const sp_node &rhs) const\
    \ { return rhs.__d < __d; }\n      };\n\n      std::priority_queue<sp_node> __q;\n\
    \      for (size_type src{}; src != size(); ++src)\n        if (b[src] > static_cast<Cap>(0))\
    \ {\n          newp[src] = 0;\n          for (auto &e : base::graph[src])\n  \
    \          if (static_cast<Cap>(0) < e.cap && e.cost < newp[e.dst]) {\n      \
    \        __q.emplace(e.dst, (newp[e.dst] = e.cost) - p[e.dst]);\n            \
    \  last[e.dst] = &e;\n            }\n        }\n\n      while (!__q.empty()) {\n\
    \        auto [src, __d] = __q.top();\n        __q.pop();\n        if (__d + p[src]\
    \ != newp[src]) continue;\n        for (auto &e : base::graph[src])\n        \
    \  if (auto __d = newp[src] + e.cost;\n              static_cast<Cap>(0) < e.cap\
    \ && __d < newp[e.dst]) {\n            __q.emplace(e.dst, (newp[e.dst] = __d)\
    \ - p[e.dst]);\n            last[e.dst] = &e;\n          }\n      }\n    }\n\n\
    \    p.swap(newp);\n  }\n};\n\ntemplate <class Cap, class Gain = Cap, bool Density_tag\
    \ = false>\nclass max_gain_flow : public min_cost_flow<Cap, Gain, Density_tag>\
    \ {\n  using base = min_cost_flow<Cap, Gain, Density_tag>;\n  using base::cost;\n\
    \n public:\n  using base::min_cost_flow;\n  using size_type = typename base::size_type;\n\
    \n  /**\n   * @brief Add an edge with a unit capacity to the graph.\n   *\n  \
    \ * @param src Source\n   * @param dst Destination\n   * @param gain Gain\n  \
    \ * @return Reference to the edge.\n   */\n  auto &add_edge(size_type src, size_type\
    \ dst, const Gain &gain) {\n    return add_edge(src, dst, 1, gain);\n  }\n\n \
    \ /**\n   * @brief Add an edge to the graph.\n   *\n   * @param src Source\n \
    \  * @param dst Destination\n   * @param cap Capacity\n   * @param gain Gain\n\
    \   * @return Reference to the edge.\n   */\n  auto &add_edge(size_type src, size_type\
    \ dst, const Cap &cap,\n                 const Gain &gain) {\n    return base::add_edge(src,\
    \ dst, cap, -gain);\n  }\n\n  /**\n   * @brief Add an edge to the graph.\n   *\n\
    \   * @param src Source\n   * @param dst Destination\n   * @param lower Lower\
    \ bound of flow\n   * @param upper Upper bound of flow\n   * @param gain Gain\n\
    \   * @return Reference to the edge.\n   */\n  auto &add_edge(size_type src, size_type\
    \ dst, const Cap &lower,\n                 const Cap &upper, const Gain &gain)\
    \ {\n    return base::add_edge(src, dst, lower, upper, -gain);\n  }\n\n  /**\n\
    \   * @return Gain of current flow.\n   */\n  Gain gain() const { return -base::current;\
    \ }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file min_cost_flow.hpp\n * @brief Minimum Cost Flow\n\
    \ * @date 2021-01-15\n *\n *\n */\n\n#include <algorithm>\n#include <optional>\n\
    #include <queue>\n\n#include \"base.hpp\"\n\nnamespace workspace {\n\n/**\n *\
    \ @brief Successive Shortest Path Algorithm.\n *\n * @tparam Cap Capacity type\n\
    \ * @tparam Cost Cost type\n * @tparam Density_tag Whether the graph is dense.\n\
    \ */\ntemplate <class Cap, class Cost = Cap, bool Density_tag = false>\nclass\
    \ min_cost_flow : public flow_graph<Cap, Cost> {\n  using base = flow_graph<Cap,\
    \ Cost>;\n  using edge_impl = typename base::edge_impl;\n  using base::nil;\n\n\
    \ public:\n  using size_type = typename base::size_type;\n  using base::size;\n\
    \n  /**\n   * @brief Construct a new min_cost_flow object\n   *\n   * @param __n\
    \ Number of vertices\n   */\n  min_cost_flow(size_type __n = 0)\n      : base::flow_graph(__n),\
    \ current(0), abs_sum(0), b(__n), p(__n) {}\n\n  std::vector<size_type> add_nodes(size_type\
    \ __n) override {\n    auto __nds = base::add_nodes(__n);\n    b.resize(size());\n\
    \    p.resize(size());\n    return __nds;\n  }\n\n  /**\n   * @brief Add an edge\
    \ with a unit capacity to the graph.\n   *\n   * @param src Source\n   * @param\
    \ dst Destination\n   * @param cost Cost\n   * @return Reference to the edge.\n\
    \   */\n  auto &add_edge(size_type src, size_type dst, const Cost &cost) {\n \
    \   return add_edge(src, dst, 1, cost);\n  }\n\n  /**\n   * @brief Add an edge\
    \ to the graph.\n   *\n   * @param src Source\n   * @param dst Destination\n \
    \  * @param cap Capacity\n   * @param cost Cost\n   * @return Reference to the\
    \ edge.\n   */\n  typename base::edge const &add_edge(size_type src, size_type\
    \ dst,\n                                      const Cap &cap, const Cost &cost)\
    \ {\n    edge_impl *__p = base::_add_edge(typename base::edge(src, dst, cap, cost));\n\
    \    if (cost < static_cast<Cost>(0)) {\n      __p->flow(cap);\n      b[src] -=\
    \ cap;\n      b[dst] += cap;\n      current += cap * cost;\n      abs_sum -= cap\
    \ * cost;\n    } else\n      abs_sum += cap * cost;\n    return *__p;\n  }\n\n\
    \  /**\n   * @brief Add an edge to the graph.\n   *\n   * @param src Source\n\
    \   * @param dst Destination\n   * @param lower Lower bound of flow\n   * @param\
    \ upper Upper bound of flow\n   * @param cost Cost\n   * @return Reference to\
    \ the edge.\n   */\n  auto &add_edge(size_type src, size_type dst, const Cap &lower,\n\
    \                 const Cap &upper, const Cost &cost) {\n    assert(!(upper <\
    \ lower));\n    b[src] -= lower;\n    b[dst] += lower;\n    current += lower *\
    \ cost;\n    return add_edge(src, dst, upper - lower, cost);\n  }\n\n  /**\n \
    \  * @brief Increase the balance of a node.\n   *\n   * @param node\n   * @param\
    \ vol Default: 1\n   */\n  void supply(size_type node, const Cap &vol = 1) {\n\
    \    assert(node < size());\n    b[node] += vol;\n  }\n\n  /**\n   * @brief Decrease\
    \ the balance of a node.\n   *\n   * @param node\n   * @param vol Default: 1\n\
    \   */\n  void demand(size_type node, const Cap &vol = 1) {\n    assert(node <\
    \ size());\n    b[node] -= vol;\n  }\n\n  /**\n   * @param node\n   * @return\
    \ Balance of the node\n   */\n  Cap balance(size_type node) { return b[node];\
    \ }\n\n  /**\n   * @return Cost of current flow.\n   */\n  Cost cost() const {\
    \ return current; }\n\n  /**\n   * @brief Run Successive Shortest Path Algorithm.\n\
    \   *\n   * @return Whether a balanced flow exists.\n   */\n  bool flow() {\n\
    \    for (bool aug = true; aug;) {\n      aug = false;\n      std::vector<edge_impl\
    \ *> last(size());\n      Dijkstra(last);\n      std::vector<bool> shut(size());\n\
    \      for (size_type dst{}; dst != size(); ++dst) {\n        if (b[dst] < static_cast<Cap>(0)\
    \ && last[dst]) {\n          Cap resid{-b[dst]};\n          size_type src{dst},\
    \ block{nil};\n          while (last[src] && !shut[src]) {\n            if (!(resid\
    \ < last[src]->cap)) resid = last[block = src]->cap;\n            src = last[src]->src;\n\
    \          }\n          if (shut[src])\n            block = src;\n          else\
    \ {\n            if (!(resid < b[src])) resid = b[block = src];\n            for\
    \ (edge_impl *e{last[dst]}; e; e = last[e->src]) {\n              e->cap -= resid;\n\
    \              e->rev->cap += resid;\n            }\n            b[src] -= resid;\n\
    \            b[dst] += resid;\n            current += p[dst] * resid;\n      \
    \      aug = true;\n          }\n          if (block != nil)\n            for\
    \ (size_type node{dst};; node = last[node]->src) {\n              shut[node] =\
    \ true;\n              if (node == block) break;\n            }\n        }\n \
    \     }\n    }\n    return std::none_of(begin(b), end(b), [](const Cap &s) {\n\
    \      return s < static_cast<Cap>(0) || static_cast<Cap>(0) < s;\n    });\n \
    \ }\n\n protected:\n  Cost current, abs_sum;\n  std::vector<Cap> b;\n  std::vector<Cost>\
    \ p;\n\n  void Dijkstra(std::vector<edge_impl *> &last) {\n    const Cost infty(abs_sum\
    \ + 1);\n    std::vector<Cost> newp(size(), infty);\n\n    if constexpr (Density_tag)\
    \ {  // O(V^2)\n      std::vector<bool> used(size());\n\n      for (size_type\
    \ src{}; src != size(); ++src)\n        if (static_cast<Cap>(0) < b[src]) {\n\
    \          used[src] = true;\n          newp[src] = 0;\n\n          for (auto\
    \ &e : base::graph[src])\n            if (static_cast<Cap>(0) < e.cap && e.cost\
    \ < newp[e.dst])\n              newp[e.dst] = e.cost, last[e.dst] = &e;\n    \
    \    }\n\n      for (;;) {\n        size_type src{nil};\n        Cost sp{infty};\n\
    \n        for (size_type node{}; node != size(); ++node) {\n          if (used[node]\
    \ || newp[node] == infty) continue;\n          if (Cost __d = newp[node] - p[node];\
    \ __d < sp) sp = __d, src = node;\n        }\n\n        if (src == nil) break;\n\
    \        used[src] = true;\n\n        for (auto &e : base::graph[src])\n     \
    \     if (static_cast<Cap>(0) < e.cap && newp[src] + e.cost < newp[e.dst]) {\n\
    \            newp[e.dst] = newp[src] + e.cost;\n            last[e.dst] = &e;\n\
    \          }\n      }\n    }\n\n    else {  // O((V + E)logV)\n      struct sp_node\
    \ {\n        size_type id;\n        Cost __d;\n        sp_node(size_type id, Cost\
    \ __d) : id(id), __d(__d) {}\n        bool operator<(const sp_node &rhs) const\
    \ { return rhs.__d < __d; }\n      };\n\n      std::priority_queue<sp_node> __q;\n\
    \      for (size_type src{}; src != size(); ++src)\n        if (b[src] > static_cast<Cap>(0))\
    \ {\n          newp[src] = 0;\n          for (auto &e : base::graph[src])\n  \
    \          if (static_cast<Cap>(0) < e.cap && e.cost < newp[e.dst]) {\n      \
    \        __q.emplace(e.dst, (newp[e.dst] = e.cost) - p[e.dst]);\n            \
    \  last[e.dst] = &e;\n            }\n        }\n\n      while (!__q.empty()) {\n\
    \        auto [src, __d] = __q.top();\n        __q.pop();\n        if (__d + p[src]\
    \ != newp[src]) continue;\n        for (auto &e : base::graph[src])\n        \
    \  if (auto __d = newp[src] + e.cost;\n              static_cast<Cap>(0) < e.cap\
    \ && __d < newp[e.dst]) {\n            __q.emplace(e.dst, (newp[e.dst] = __d)\
    \ - p[e.dst]);\n            last[e.dst] = &e;\n          }\n      }\n    }\n\n\
    \    p.swap(newp);\n  }\n};\n\ntemplate <class Cap, class Gain = Cap, bool Density_tag\
    \ = false>\nclass max_gain_flow : public min_cost_flow<Cap, Gain, Density_tag>\
    \ {\n  using base = min_cost_flow<Cap, Gain, Density_tag>;\n  using base::cost;\n\
    \n public:\n  using base::min_cost_flow;\n  using size_type = typename base::size_type;\n\
    \n  /**\n   * @brief Add an edge with a unit capacity to the graph.\n   *\n  \
    \ * @param src Source\n   * @param dst Destination\n   * @param gain Gain\n  \
    \ * @return Reference to the edge.\n   */\n  auto &add_edge(size_type src, size_type\
    \ dst, const Gain &gain) {\n    return add_edge(src, dst, 1, gain);\n  }\n\n \
    \ /**\n   * @brief Add an edge to the graph.\n   *\n   * @param src Source\n \
    \  * @param dst Destination\n   * @param cap Capacity\n   * @param gain Gain\n\
    \   * @return Reference to the edge.\n   */\n  auto &add_edge(size_type src, size_type\
    \ dst, const Cap &cap,\n                 const Gain &gain) {\n    return base::add_edge(src,\
    \ dst, cap, -gain);\n  }\n\n  /**\n   * @brief Add an edge to the graph.\n   *\n\
    \   * @param src Source\n   * @param dst Destination\n   * @param lower Lower\
    \ bound of flow\n   * @param upper Upper bound of flow\n   * @param gain Gain\n\
    \   * @return Reference to the edge.\n   */\n  auto &add_edge(size_type src, size_type\
    \ dst, const Cap &lower,\n                 const Cap &upper, const Gain &gain)\
    \ {\n    return base::add_edge(src, dst, lower, upper, -gain);\n  }\n\n  /**\n\
    \   * @return Gain of current flow.\n   */\n  Gain gain() const { return -base::current;\
    \ }\n};\n\n}  // namespace workspace\n"
  dependsOn:
  - src/graph/directed/flow/base.hpp
  isVerificationFile: false
  path: src/graph/directed/flow/min_cost_flow.hpp
  requiredBy: []
  timestamp: '2021-01-19 16:29:02+09:00'
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
