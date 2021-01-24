---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/graph/directed/flow/base.hpp
    title: Flow Graph
  - icon: ':heavy_check_mark:'
    path: src/graph/directed/flow/min_cost_flow.hpp
    title: Minimum Cost Flow
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_B
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_B
  bundledCode: "#line 1 \"test/aizu-online-judge/GRL_6_B.test.cpp\"\n#define PROBLEM\
    \ \"https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_B\"\n\n#include <cstdio>\n\
    \n#line 2 \"src/graph/directed/flow/min_cost_flow.hpp\"\n\n/**\n * @file min_cost_flow.hpp\n\
    \ * @brief Minimum Cost Flow\n * @date 2021-01-15\n *\n *\n */\n\n#include <algorithm>\n\
    #include <optional>\n#include <queue>\n\n#line 2 \"src/graph/directed/flow/base.hpp\"\
    \n\n/**\n * @file base.hpp\n * @brief Flow Graph\n * @date 2021-01-15\n *\n *\n\
    \ */\n\n#include <cassert>\n#include <numeric>\n#include <tuple>\n#include <vector>\n\
    \nnamespace workspace {\n\ntemplate <class Cap, class Cost = void> class flow_graph\
    \ {\n protected:\n  class adjacency_impl;\n\n public:\n  using container_type\
    \ = std::vector<adjacency_impl>;\n  using size_type = typename container_type::size_type;\n\
    \n  class unweighted_edge {\n   public:\n    size_type src;  // Source\n    size_type\
    \ dst;  // Destination\n    Cap cap;        // Capacity\n    Cap flow = 0;   //\
    \ Flow\n\n    unweighted_edge(size_type __s, size_type __d, const Cap &__u = 1)\n\
    \        : src(__s), dst(__d), cap(__u) {\n      assert(!(cap < static_cast<Cap>(0)));\n\
    \    }\n\n    /**\n     * @brief Source, Destination, Capacity, Flow\n     */\n\
    \    template <class Os>\n    friend Os &operator<<(Os &__os, unweighted_edge\
    \ const &__e) {\n      return __os << __e.src << ' ' << __e.dst << ' ' << __e.cap\
    \ << ' '\n                  << __e.flow;\n    }\n\n   protected:\n    unweighted_edge()\
    \ = default;\n\n    unweighted_edge(size_type __s, size_type __d, const Cap &__u,\n\
    \                    const Cap &__f)\n        : src(__s), dst(__d), cap(__u),\
    \ flow(__f) {}\n\n    unweighted_edge make_rev() const { return {dst, src, flow,\
    \ cap}; }\n  };\n\n  class weighted_edge : public unweighted_edge {\n   public:\n\
    \    Cost cost;  // Cost\n\n    weighted_edge(const unweighted_edge &__e, const\
    \ Cost &__c = 0)\n        : unweighted_edge(__e), cost(__c) {}\n\n    weighted_edge(size_type\
    \ __s, size_type __d, const Cap &__u = 1,\n                  const Cost &__c =\
    \ 0)\n        : unweighted_edge(__s, __d, __u), cost(__c) {}\n\n    /**\n    \
    \ * @brief Source, Destination, Capacity, Flow, Cost\n     */\n    template <class\
    \ Os>\n    friend Os &operator<<(Os &__os, weighted_edge const &__e) {\n     \
    \ return __os << static_cast<unweighted_edge>(__e) << ' ' << __e.cost;\n    }\n\
    \n   protected:\n    weighted_edge() = default;\n\n    weighted_edge make_rev()\
    \ const {\n      return {unweighted_edge::make_rev(), -cost};\n    }\n  };\n\n\
    \  using edge = typename std::conditional<std::is_void<Cost>::value,\n       \
    \                                  unweighted_edge, weighted_edge>::type;\n\n\
    \ protected:\n  struct edge_impl : edge {\n    bool aux = false;\n    edge_impl\
    \ *rev = nullptr;\n\n    edge_impl() = default;\n\n    edge_impl(const edge_impl\
    \ &__e) = default;\n    edge_impl &operator=(const edge_impl &__e) = default;\n\
    \n    edge_impl(edge_impl &&__e) = default;\n    edge_impl &operator=(edge_impl\
    \ &&__e) = default;\n\n    edge_impl(const edge &__e) : edge(__e) {}\n    edge_impl(edge\
    \ &&__e) : edge(__e) {}\n\n    void push(Cap __f) {\n      edge::cap -= __f;\n\
    \      edge::flow += __f;\n      if (rev) {\n        rev->cap += __f;\n      \
    \  rev->flow -= __f;\n      }\n    }\n\n    edge_impl make_rev() {\n      edge_impl\
    \ __e = edge::make_rev();\n      __e.aux = true;\n      __e.rev = this;\n    \
    \  return __e;\n    }\n  };\n\n public:\n  class adjacency {\n   public:\n   \
    \ using value_type = edge;\n    using reference = edge &;\n    using const_reference\
    \ = edge const &;\n    using pointer = edge *;\n    using const_pointer = const\
    \ edge *;\n\n    class iterator {\n      edge_impl *__p;\n\n     public:\n   \
    \   iterator(edge_impl *__p = nullptr) : __p(__p) {}\n\n      bool operator!=(iterator\
    \ const &__x) const { return __p != __x.__p; }\n\n      iterator &operator++()\
    \ {\n        do\n          ++__p;\n        while (__p->rev && __p->aux);\n   \
    \     return *this;\n      }\n\n      pointer operator->() const { return __p;\
    \ }\n\n      reference operator*() const { return *__p; }\n    };\n\n    class\
    \ const_iterator {\n      const edge_impl *__p;\n\n     public:\n      const_iterator(const\
    \ edge_impl *__p = nullptr) : __p(__p) {}\n\n      bool operator!=(const_iterator\
    \ const &__x) const {\n        return __p != __x.__p;\n      }\n\n      const_iterator\
    \ &operator++() {\n        do\n          ++__p;\n        while (__p->rev && __p->aux);\n\
    \        return *this;\n      }\n\n      const_pointer operator->() const { return\
    \ __p; }\n\n      const_reference operator*() const { return *__p; }\n    };\n\
    \n    adjacency()\n        : first(new edge_impl[2]), last(first + 1), __s(first),\
    \ __t(first) {}\n\n    ~adjacency() { delete[] first; }\n\n    const_reference\
    \ operator[](size_type i) const {\n      assert(i < size());\n      return *(first\
    \ + i);\n    }\n\n    size_type size() const { return __t - first; }\n\n    auto\
    \ begin() { return iterator{__s}; }\n    auto begin() const { return const_iterator{__s};\
    \ }\n\n    auto end() { return iterator{__t}; }\n    auto end() const { return\
    \ const_iterator{__t}; }\n\n    /**\n     * @brief Construct a new adjacency object\n\
    \     *\n     * @param __x Rvalue reference to another object\n     */\n    adjacency(adjacency\
    \ &&__x) : first(nullptr) { operator=(std::move(__x)); }\n\n    /**\n     * @brief\
    \ Assignment operator.\n     *\n     * @param __x Rvalue reference to another\
    \ object\n     * @return Reference to this object.\n     */\n    adjacency &operator=(adjacency\
    \ &&__x) {\n      std::swap(first, __x.first);\n      last = __x.last;\n     \
    \ __s = __x.__s;\n      __t = __x.__t;\n      return *this;\n    }\n\n   protected:\n\
    \    edge_impl *first, *last, *__s, *__t;\n  };\n\n  using value_type = adjacency;\n\
    \  using reference = adjacency &;\n  using const_reference = adjacency const &;\n\
    \n protected:\n  class adjacency_impl : public adjacency {\n   public:\n    using\
    \ base = adjacency;\n    using base::__s;\n    using base::__t;\n    using base::first;\n\
    \    using base::last;\n\n    using iterator = edge_impl *;\n\n    iterator _push(edge_impl\
    \ &&__e) {\n      if (__t == last) {\n        size_type __n(last - first);\n \
    \       iterator loc = new edge_impl[__n << 1 | 1];\n        __s += loc - first;\n\
    \        __t = loc;\n        for (iterator __p{first}; __p != last; ++__p, ++__t)\
    \ {\n          *__t = *__p;\n          if (__p->rev) __p->rev->rev = __t;\n  \
    \      }\n        delete[] first;\n        first = loc;\n        last = __t +\
    \ __n;\n      }\n      *__t = std::move(__e);\n      if (__s->aux) ++__s;\n  \
    \    return __t++;\n    }\n\n    iterator begin() const { return first; }\n\n\
    \    iterator end() const { return __t; }\n  };\n\n  /**\n   * @brief The only\
    \ member variable.\n   */\n  container_type graph;\n\n public:\n  /**\n   * @brief\
    \ Construct a new flow graph object\n   *\n   * @param __n Number of vertices\n\
    \   */\n  flow_graph(size_type __n = 0) : graph(__n) {}\n\n  /**\n   * @brief\
    \ Construct a new flow graph object\n   *\n   * @param __x Const reference to\
    \ another object\n   */\n  flow_graph(const flow_graph &__x) : graph(__x.size())\
    \ {\n    for (auto &&__adj : __x)\n      for (auto &&__e : __adj) add_edge(__e);\n\
    \  }\n\n  /**\n   * @brief Construct a new flow graph object\n   *\n   * @param\
    \ __x Rvalue reference to another object\n   */\n  flow_graph(flow_graph &&__x)\
    \ : graph(std::move(__x.graph)) {}\n\n  /**\n   * @brief Assignment operator.\n\
    \   *\n   * @param __x Const reference to another object\n   * @return Reference\
    \ to this object.\n   */\n  flow_graph &operator=(const flow_graph &__x) {\n \
    \   return operator=(std::move(flow_graph{__x}));\n  }\n\n  /**\n   * @brief Assignment\
    \ operator.\n   *\n   * @param __x Rvalue reference to another object\n   * @return\
    \ Reference to this object.\n   */\n  flow_graph &operator=(flow_graph &&__x)\
    \ {\n    graph = std::move(__x.graph);\n    return *this;\n  }\n\n  /**\n   *\
    \ @return Number of nodes.\n   */\n  size_type size() const { return graph.size();\
    \ }\n\n  /**\n   * @param node Node\n   * @return Referece to the adjacency list\
    \ of the node.\n   */\n  reference operator[](size_type node) {\n    assert(node\
    \ < size());\n    return graph[node];\n  }\n\n  /**\n   * @param node Node\n \
    \  * @return Const referece to the adjacency list of the node.\n   */\n  const_reference\
    \ operator[](size_type node) const {\n    assert(node < size());\n    return graph[node];\n\
    \  }\n\n  class iterator : public container_type::iterator {\n    using base =\
    \ typename container_type::iterator;\n\n   public:\n    using reference = adjacency\
    \ &;\n    using pointer = adjacency *;\n\n    iterator(base const &__i) : base(__i)\
    \ {}\n\n    pointer operator->() const { return base::operator->(); }\n\n    reference\
    \ operator*() const { return base::operator*(); }\n  };\n\n  class const_iterator\
    \ : public container_type::const_iterator {\n    using base = typename container_type::const_iterator;\n\
    \n   public:\n    using const_reference = const adjacency &;\n    using const_pointer\
    \ = const adjacency *;\n\n    const_iterator(base const &__i) : base(__i) {}\n\
    \n    const_pointer operator->() const { return base::operator->(); }\n\n    const_reference\
    \ operator*() const { return base::operator*(); }\n  };\n\n  auto begin() { return\
    \ iterator{graph.begin()}; }\n  auto begin() const { return const_iterator{graph.begin()};\
    \ }\n\n  auto end() { return iterator{graph.end()}; }\n  auto end() const { return\
    \ const_iterator{graph.end()}; }\n\n  /**\n   * @brief Add a node to the graph.\n\
    \   *\n   * @return Index of the node.\n   */\n  size_type add_node() { return\
    \ add_nodes(1).front(); }\n\n  /**\n   * @brief Add some nodes to the graph.\n\
    \   *\n   * @param __n Number of nodes added\n   * @return List of indices of\
    \ the nodes.\n   */\n  virtual std::vector<size_type> add_nodes(size_type __n)\
    \ {\n    std::vector<size_type> __nds(__n);\n    std::iota(__nds.begin(), __nds.end(),\
    \ graph.size());\n    __n += graph.size();\n    if (__n > graph.capacity()) {\n\
    \      flow_graph __x(__n);\n      for (auto &&adj : graph)\n        for (auto\
    \ &&__e : adj)\n          if (!__e.aux) __x.add_edge(__e);\n      graph = std::move(__x.graph);\n\
    \    } else\n      graph.resize(__n);\n    return __nds;\n  }\n\n  /**\n   * @brief\
    \ Add a directed edge to the graph.\n   *\n   * @return Reference to the edge.\n\
    \   */\n  template <class... Args>\n  typename std::enable_if<std::is_constructible<edge,\
    \ Args...>::value,\n                          edge &>::type\n  add_edge(Args &&...\
    \ __args) {\n    edge_impl __e = edge(std::forward<Args>(__args)...);\n    assert(__e.src\
    \ < size());\n    assert(__e.dst < size());\n    edge_impl *__p = graph[__e.src]._push(std::move(__e));\n\
    \    // Careful with a self loop.\n    if (__e.src != __e.dst) __p->rev = graph[__e.dst]._push(__p->make_rev());\n\
    \    return *__p;\n  }\n\n  /**\n   * @brief Add a directed edge to the graph.\n\
    \   *\n   * @return Reference to the edge.\n   */\n  template <class Tp>\n  typename\
    \ std::enable_if<\n      (std::tuple_size<typename std::decay<Tp>::type>::value\
    \ >= 0),\n      edge &>::type\n  add_edge(Tp &&__t) {\n    return _unpack_directed(std::forward<Tp>(__t));\n\
    \  }\n\n  /**\n   * @brief Add an undirected edge to the graph. Its cost must\
    \ be non-negative.\n   *\n   * @return Reference to the edge.\n   */\n  template\
    \ <class... Args> edge &add_undirected_edge(Args &&... __args) {\n    edge_impl\
    \ __e = edge(std::forward<Args>(__args)...);\n    assert(__e.src < size());\n\
    \    assert(__e.dst < size());\n    (__e.flow += __e.flow) += __e.cap;\n    edge_impl\
    \ *__p = graph[__e.src]._push(std::move(__e));\n    // Careful with a self loop.\n\
    \    if (__e.src != __e.dst) {\n      edge_impl __r = __p->make_rev();\n     \
    \ __r.aux = false;\n      __p->rev = graph[__e.dst]._push(std::move(__r));\n \
    \   }\n    return *__p;\n  }\n\n  /**\n   * @brief Add an undirected edge to the\
    \ graph. Its cost must be non-negative.\n   *\n   * @return Reference to the edge.\n\
    \   */\n  template <class Tp>\n  typename std::enable_if<\n      (std::tuple_size<typename\
    \ std::decay<Tp>::type>::value >= 0),\n      edge &>::type\n  add_undirected_edge(Tp\
    \ &&__t) {\n    return _unpack_undirected(std::forward<Tp>(__t));\n  }\n\n protected:\n\
    \  // internal\n  template <class Tp, size_t N = 0, class... Args>\n  decltype(auto)\
    \ _unpack_directed(Tp &&__t, Args &&... __args) {\n    if constexpr (N == std::tuple_size<typename\
    \ std::decay<Tp>::type>::value)\n      return add_edge(std::forward<Args>(__args)...);\n\
    \    else\n      return _unpack_directed<Tp, N + 1>(std::forward<Tp>(__t),\n \
    \                                        std::forward<Args>(__args)...,\n    \
    \                                     std::get<N>(__t));\n  }\n\n  // internal\n\
    \  template <class Tp, size_t N = 0, class... Args>\n  decltype(auto) _unpack_undirected(Tp\
    \ &&__t, Args &&... __args) {\n    if constexpr (N == std::tuple_size<typename\
    \ std::decay<Tp>::type>::value)\n      return add_undirected_edge(std::forward<Args>(__args)...);\n\
    \    else\n      return _unpack_undirected<Tp, N + 1>(std::forward<Tp>(__t),\n\
    \                                           std::forward<Args>(__args)...,\n \
    \                                          std::get<N>(__t));\n  }\n\n  template\
    \ <class Os> friend Os &operator<<(Os &__os, flow_graph const &__g) {\n    for\
    \ (const auto &adj : __g)\n      for (const auto &e : adj) __os << e << \"\\n\"\
    ;\n    return __os;\n  }\n};\n\n}  // namespace workspace\n#line 2 \"lib/limits\"\
    \n\n#include <limits>\n\nnamespace std {\n\n#if defined(__STRICT_ANSI__) && defined(__SIZEOF_INT128__)\n\
    \ntemplate <> struct numeric_limits<__uint128_t> {\n  constexpr static __uint128_t\
    \ max() { return ~__uint128_t(0); }\n  constexpr static __uint128_t min() { return\
    \ 0; }\n};\n\ntemplate <> struct numeric_limits<__int128_t> {\n  constexpr static\
    \ __int128_t max() {\n    return numeric_limits<__uint128_t>::max() >> 1;\n  }\n\
    \  constexpr static __int128_t min() { return -max() - 1; }\n};\n\n#endif\n\n\
    }  // namespace std\n#line 17 \"src/graph/directed/flow/min_cost_flow.hpp\"\n\n\
    namespace workspace {\n\n/**\n * @brief Successive Shortest Path Algorithm.\n\
    \ *\n * @tparam Cap Capacity type\n * @tparam Cost Cost type\n * @tparam Density_tag\
    \ Whether the graph is dense\n */\ntemplate <class Cap, class Cost = Cap, bool\
    \ Density_tag = false>\nclass min_cost_flow : public flow_graph<Cap, Cost> {\n\
    \  using base = flow_graph<Cap, Cost>;\n  using edge_impl = typename base::edge_impl;\n\
    \n public:\n  using edge = typename base::edge;\n  using size_type = typename\
    \ base::size_type;\n  using base::size;\n\n  /**\n   * @brief Construct a new\
    \ min_cost_flow object\n   *\n   * @param __n Number of vertices\n   */\n  min_cost_flow(size_type\
    \ __n = 0) : base::flow_graph(__n), b(__n) {}\n\n  std::vector<size_type> add_nodes(size_type\
    \ __n) override {\n    auto __nds = base::add_nodes(__n);\n    b.resize(size());\n\
    \    return __nds;\n  }\n\n  using base::add_edge;\n\n  /**\n   * @brief Add a\
    \ directed edge to the graph.\n   *\n   * @param __s Source\n   * @param __d Destination\n\
    \   * @param __l Lower bound of flow\n   * @param __u Upper bound of flow\n  \
    \ * @param __c Cost\n   * @return Reference to the edge.\n   */\n  edge &add_edge(size_type\
    \ __s, size_type __d, const Cap &__l, const Cap &__u,\n                 const\
    \ Cost &__c) {\n    assert(!(__u < __l));\n    b[__s] -= __l;\n    b[__d] += __l;\n\
    \    auto &__e = base::add_edge(__s, __d, __u - __l, __c);\n    __e.flow = __l;\n\
    \    return __e;\n  }\n\n  /**\n   * @brief Add an undirected edge to the graph.\n\
    \   *\n   * @return Reference to the edge.\n   */\n  template <class... Args>\
    \ edge &add_undirected_edge(Args &&... __args) {\n    auto &__e = static_cast<edge_impl\
    \ &>(\n        base::add_undirected_edge(std::forward<Args>(__args)...));\n  \
    \  assert(!(__e.cost < 0));\n    __e.rev->cost = __e.cost;\n    return __e;\n\
    \  }\n\n  /**\n   * @brief Increase the balance of a node.\n   *\n   * @param\
    \ node\n   * @param vol Default: 1\n   */\n  void supply(size_type node, const\
    \ Cap &vol = 1) {\n    assert(node < size());\n    b[node] += vol;\n  }\n\n  /**\n\
    \   * @brief Decrease the balance of a node.\n   *\n   * @param node\n   * @param\
    \ vol Default: 1\n   */\n  void demand(size_type node, const Cap &vol = 1) {\n\
    \    assert(node < size());\n    b[node] -= vol;\n  }\n\n  /**\n   * @return Balance\
    \ of the graph.\n   */\n  const auto &balance() const { return b; }\n\n  /**\n\
    \   * @param node Node\n   * @return Balance of the node.\n   */\n  Cap balance(size_type\
    \ node) const { return b[node]; }\n\n  /**\n   * @return Potential of the graph.\n\
    \   */\n  const auto &potential() const { return p; }\n\n  /**\n   * @param node\
    \ Node\n   * @return Potential of the node.\n   */\n  Cost potential(size_type\
    \ node) const { return p[node]; }\n\n  /**\n   * @return Cost of current flow.\n\
    \   */\n  Cost cost() const { return current; }\n\n  /**\n   * @brief Run Successive\
    \ Shortest Path Algorithm.\n   *\n   * @return Whether a balanced flow exists.\n\
    \   */\n  bool run() {\n    // Saturate negative edges.\n    for (auto &&__adj\
    \ : base::graph)\n      for (auto &&__e : __adj)\n        if (__e.cost < static_cast<Cost>(0)\
    \ && static_cast<Cap>(0) < __e.cap) {\n          b[__e.src] -= __e.cap;\n    \
    \      b[__e.dst] += __e.cap;\n          __e.push(__e.cap);\n        }\n\n   \
    \ sources.clear();\n    sinks.clear();\n    for (size_type __i = 0; __i != b.size();\
    \ ++__i)\n      if (b[__i] != static_cast<Cap>(0))\n        (static_cast<Cap>(0)\
    \ < b[__i] ? sources : sinks).emplace_back(__i);\n\n    p.resize(size());\n  \
    \  parent.resize(size());\n\n    // Primal-Dual\n    while (dual()) {\n      primal();\n\
    \      sources.erase(std::remove_if(sources.begin(), sources.end(),\n        \
    \                           [&](auto __v) {\n                                \
    \     return b[__v] == static_cast<Cap>(0);\n                                \
    \   }),\n                    sources.end());\n      sinks.erase(std::remove_if(\n\
    \                      sinks.begin(), sinks.end(),\n                      [&](auto\
    \ __v) { return b[__v] == static_cast<Cap>(0); }),\n                  sinks.end());\n\
    \    }\n\n    current = 0;\n    for (auto &&adj : base::graph)\n      for (auto\
    \ &&__e : adj)\n        if (!__e.aux) current += __e.cost * __e.flow;\n\n    return\
    \ sources.empty() && sinks.empty();\n  }\n\n protected:\n  // Cost of flow.\n\
    \  Cost current;\n\n  // Balance\n  std::vector<Cap> b;\n\n  // The dual solution.\n\
    \  std::vector<Cost> p;\n\n  std::vector<edge_impl *> parent;\n  std::vector<size_type>\
    \ sources, sinks;\n\n  // Augment along the dual solution.\n  void primal() {\n\
    \    for (auto __t : sinks)\n      if (parent[__t]) {\n        auto __f = -b[__t];\n\
    \        auto __s = __t;\n        while (parent[__s])\n          __f = std::min(__f,\
    \ parent[__s]->cap), __s = parent[__s]->src;\n        if (static_cast<Cap>(0)\
    \ < b[__s]) {\n          __f = std::min(__f, b[__s]);\n          b[__s] -= __f;\n\
    \          b[__t] += __f;\n          for (auto *__p = parent[__t]; __p; __p =\
    \ parent[__p->src]) {\n            __p->push(__f);\n            if (__p->cap ==\
    \ static_cast<Cap>(0)) parent[__p->dst] = nullptr;\n          }\n        }\n \
    \     }\n  }\n\n  // Improve the dual solution.\n  bool dual() {\n    std::fill(parent.begin(),\
    \ parent.end(), nullptr);\n\n    constexpr Cost infty = std::numeric_limits<Cost>::max();\n\
    \    std::vector<Cost> __nx(size(), infty);\n    size_type reachable = 0;\n\n\
    \    if constexpr (Density_tag) {  // O(V^2)\n      constexpr static size_type\
    \ nil = -1;\n      std::vector<bool> used(size());\n\n      for (auto __s : sources)\
    \ {\n        used[__s] = true;\n        __nx[__s] = 0;\n        for (auto &__e\
    \ : base::graph[__s])\n          if (static_cast<Cap>(0) < __e.cap && __e.cost\
    \ < __nx[__e.dst])\n            __nx[__e.dst] = __e.cost, parent[__e.dst] = &__e;\n\
    \      }\n\n      while (true) {\n        size_type __v{nil};\n        Cost __sd{infty};\n\
    \n        for (size_type __i{}; __i != size(); ++__i) {\n          if (used[__i]\
    \ || __nx[__i] == infty) continue;\n          if (Cost __d = __nx[__i] - p[__i];\
    \ __d < __sd) __sd = __d, __v = __i;\n        }\n\n        if (__v == nil) break;\n\
    \        used[__v] = true;\n        if (b[__v] < static_cast<Cap>(0))\n      \
    \    if (++reachable == sinks.size()) break;\n\n        for (auto &__e : base::graph[__v])\n\
    \          if (Cost __d = __nx[__v] + __e.cost;\n              static_cast<Cap>(0)\
    \ < __e.cap && __d < __nx[__e.dst]) {\n            __nx[__e.dst] = __d;\n    \
    \        parent[__e.dst] = &__e;\n          }\n      }\n    }\n\n    else {  //\
    \ O((V + E)logV)\n      struct state {\n        size_type __v;\n        Cost __d;\n\
    \        state(size_type __v, Cost __d) : __v(__v), __d(__d) {}\n        bool\
    \ operator<(const state &__x) const { return __x.__d < __d; }\n      };\n\n  \
    \    std::priority_queue<state> __q;\n      for (auto __v : sources) {\n     \
    \   __nx[__v] = 0;\n        for (auto &__e : base::graph[__v])\n          if (static_cast<Cap>(0)\
    \ < __e.cap && __e.cost < __nx[__e.dst])\n            __q.emplace(__e.dst, (__nx[__e.dst]\
    \ = __e.cost) - p[__e.dst]),\n                parent[__e.dst] = &__e;\n      }\n\
    \n      while (!__q.empty()) {\n        auto [__v, __d] = __q.top();\n       \
    \ __q.pop();\n        if (__d + p[__v] != __nx[__v]) continue;\n        if (b[__v]\
    \ < static_cast<Cap>(0))\n          if (++reachable == sinks.size()) break;\n\
    \        for (auto &__e : base::graph[__v])\n          if (auto __d = __nx[__v]\
    \ + __e.cost;\n              static_cast<Cap>(0) < __e.cap && __d < __nx[__e.dst])\
    \ {\n            __q.emplace(__e.dst, (__nx[__e.dst] = __d) - p[__e.dst]);\n \
    \           parent[__e.dst] = &__e;\n          }\n      }\n    }\n\n    if (reachable)\
    \ p = std::move(__nx);\n    return reachable;\n  }\n\n};  // namespace workspace\n\
    \n/**\n * @brief Successive Shortest Path Algorithm.\n *\n * @tparam Cap Capacity\
    \ type\n * @tparam Gain Gain type\n * @tparam Density_tag Whether the graph is\
    \ dense\n */\ntemplate <class Cap, class Gain = Cap, bool Density_tag = false>\n\
    class max_gain_flow : public min_cost_flow<Cap, Gain, Density_tag> {\n  using\
    \ base = min_cost_flow<Cap, Gain, Density_tag>;\n  using base::cost;\n\n public:\n\
    \  using base::min_cost_flow;\n  using edge = typename base::edge;\n\n  /**\n\
    \   * @brief Add a directed edge to the graph. The default capacity is 1.\n  \
    \ *\n   * @return Reference to the edge.\n   */\n  template <class... Args> decltype(auto)\
    \ add_edge(Args &&... __args) {\n    return add_edge(std::tuple{std::forward<Args>(__args)...});\n\
    \  }\n\n  /**\n   * @brief Add a directed edge to the graph. The default capacity\
    \ is 1.\n   *\n   * @return Reference to the edge.\n   */\n  template <class Tp>\n\
    \  typename std::enable_if<\n      (std::tuple_size<typename std::decay<Tp>::type>::value\
    \ >= 0),\n      const edge &>::type\n  add_edge(Tp __t) {\n    std::get<std::tuple_size<decltype(__t)>::value\
    \ - 1>(__t) *=\n        -1;  // Flip the sign of cost.\n    return base::add_edge(std::move(__t));\n\
    \  }\n\n  /**\n   * @return Gain of current flow.\n   */\n  Gain gain() const\
    \ { return -cost(); }\n};\n\n}  // namespace workspace\n#line 6 \"test/aizu-online-judge/GRL_6_B.test.cpp\"\
    \n\nint main() {\n  int n, m, f;\n  scanf(\"%d%d%d\", &n, &m, &f);\n  workspace::min_cost_flow<int>\
    \ mcf(n);\n  mcf.supply(0, f);\n  mcf.demand(n - 1, f);\n  while (m--) {\n   \
    \ int u, v, c, d;\n    scanf(\"%d%d%d%d\", &u, &v, &c, &d);\n    mcf.add_edge(u,\
    \ v, c, d);\n  }\n  if (mcf.run()) {\n    printf(\"%d\\n\", mcf.cost());\n  }\
    \ else\n    puts(\"-1\");\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_B\"\n\n\
    #include <cstdio>\n\n#include \"src/graph/directed/flow/min_cost_flow.hpp\"\n\n\
    int main() {\n  int n, m, f;\n  scanf(\"%d%d%d\", &n, &m, &f);\n  workspace::min_cost_flow<int>\
    \ mcf(n);\n  mcf.supply(0, f);\n  mcf.demand(n - 1, f);\n  while (m--) {\n   \
    \ int u, v, c, d;\n    scanf(\"%d%d%d%d\", &u, &v, &c, &d);\n    mcf.add_edge(u,\
    \ v, c, d);\n  }\n  if (mcf.run()) {\n    printf(\"%d\\n\", mcf.cost());\n  }\
    \ else\n    puts(\"-1\");\n}\n"
  dependsOn:
  - src/graph/directed/flow/min_cost_flow.hpp
  - src/graph/directed/flow/base.hpp
  isVerificationFile: true
  path: test/aizu-online-judge/GRL_6_B.test.cpp
  requiredBy: []
  timestamp: '2021-01-24 20:57:39+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aizu-online-judge/GRL_6_B.test.cpp
layout: document
redirect_from:
- /verify/test/aizu-online-judge/GRL_6_B.test.cpp
- /verify/test/aizu-online-judge/GRL_6_B.test.cpp.html
title: test/aizu-online-judge/GRL_6_B.test.cpp
---
