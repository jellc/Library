---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/graph/directed/flow/base.hpp
    title: Flow Graph
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/GRL_6_A.test.cpp
    title: test/aizu-online-judge/GRL_6_A.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/bipartitematching.test.cpp
    title: test/library-checker/bipartitematching.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Dinic's Algorithm
    links: []
  bundledCode: "#line 2 \"src/graph/directed/flow/Dinic.hpp\"\n\n/**\n * @file Dinic.hpp\n\
    \ * @brief Dinic's Algorithm\n * @date 2021-01-15\n *\n *\n */\n\n#include <limits>\n\
    \n#line 2 \"src/graph/directed/flow/base.hpp\"\n\n/**\n * @file base.hpp\n * @brief\
    \ Flow Graph\n * @date 2021-01-15\n *\n *\n */\n\n#include <cassert>\n#include\
    \ <numeric>\n#include <tuple>\n#include <vector>\n\nnamespace workspace {\n\n\
    template <class Cap, class Cost = void> class flow_graph {\n protected:\n  class\
    \ adjacency_impl;\n\n public:\n  using container_type = std::vector<adjacency_impl>;\n\
    \  using size_type = typename container_type::size_type;\n\n  class unweighted_edge\
    \ {\n   public:\n    size_type src;  // Source\n    size_type dst;  // Destination\n\
    \    Cap cap;        // Capacity\n    Cap flow = 0;   // Flow\n\n    unweighted_edge(size_type\
    \ __s, size_type __d, const Cap &__u = 1)\n        : src(__s), dst(__d), cap(__u)\
    \ {\n      assert(!(cap < static_cast<Cap>(0)));\n    }\n\n    /**\n     * @brief\
    \ Source, Destination, Capacity, Flow\n     */\n    template <class Os>\n    friend\
    \ Os &operator<<(Os &__os, unweighted_edge const &__e) {\n      return __os <<\
    \ __e.src << ' ' << __e.dst << ' ' << __e.cap << ' '\n                  << __e.flow;\n\
    \    }\n\n   protected:\n    unweighted_edge() = default;\n\n    unweighted_edge(size_type\
    \ __s, size_type __d, const Cap &__u,\n                    const Cap &__f)\n \
    \       : src(__s), dst(__d), cap(__u), flow(__f) {}\n\n    unweighted_edge make_rev()\
    \ const { return {dst, src, flow, cap}; }\n  };\n\n  class weighted_edge : public\
    \ unweighted_edge {\n   public:\n    Cost cost;  // Cost\n\n    weighted_edge(const\
    \ unweighted_edge &__e, const Cost &__c = 0)\n        : unweighted_edge(__e),\
    \ cost(__c) {}\n\n    weighted_edge(size_type __s, size_type __d, const Cap &__u\
    \ = 1,\n                  const Cost &__c = 0)\n        : unweighted_edge(__s,\
    \ __d, __u), cost(__c) {}\n\n    /**\n     * @brief Source, Destination, Capacity,\
    \ Flow, Cost\n     */\n    template <class Os>\n    friend Os &operator<<(Os &__os,\
    \ weighted_edge const &__e) {\n      return __os << static_cast<unweighted_edge>(__e)\
    \ << ' ' << __e.cost;\n    }\n\n   protected:\n    weighted_edge() = default;\n\
    \n    weighted_edge make_rev() const {\n      return {unweighted_edge::make_rev(),\
    \ -cost};\n    }\n  };\n\n  using edge = typename std::conditional<std::is_void<Cost>::value,\n\
    \                                         unweighted_edge, weighted_edge>::type;\n\
    \n protected:\n  struct edge_impl : edge {\n    bool aux = false;\n    edge_impl\
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
    \ @return Whether the graph is empty.\n   */\n  bool empty() const { return graph.empty();\
    \ }\n\n  /**\n   * @return Number of nodes.\n   */\n  size_type size() const {\
    \ return graph.size(); }\n\n  /**\n   * @param node Node\n   * @return Referece\
    \ to the adjacency list of the node.\n   */\n  reference operator[](size_type\
    \ node) {\n    assert(node < size());\n    return graph[node];\n  }\n\n  /**\n\
    \   * @param node Node\n   * @return Const referece to the adjacency list of the\
    \ node.\n   */\n  const_reference operator[](size_type node) const {\n    assert(node\
    \ < size());\n    return graph[node];\n  }\n\n  class iterator : public container_type::iterator\
    \ {\n    using base = typename container_type::iterator;\n\n   public:\n    using\
    \ reference = adjacency &;\n    using pointer = adjacency *;\n\n    iterator(base\
    \ const &__i) : base(__i) {}\n\n    pointer operator->() const { return base::operator->();\
    \ }\n\n    reference operator*() const { return base::operator*(); }\n  };\n\n\
    \  class const_iterator : public container_type::const_iterator {\n    using base\
    \ = typename container_type::const_iterator;\n\n   public:\n    using const_reference\
    \ = const adjacency &;\n    using const_pointer = const adjacency *;\n\n    const_iterator(base\
    \ const &__i) : base(__i) {}\n\n    const_pointer operator->() const { return\
    \ base::operator->(); }\n\n    const_reference operator*() const { return base::operator*();\
    \ }\n  };\n\n  auto begin() { return iterator{graph.begin()}; }\n  auto begin()\
    \ const { return const_iterator{graph.begin()}; }\n\n  auto end() { return iterator{graph.end()};\
    \ }\n  auto end() const { return const_iterator{graph.end()}; }\n\n  /**\n   *\
    \ @brief Add a node to the graph.\n   *\n   * @return Index of the node.\n   */\n\
    \  size_type add_node() { return add_nodes(1).front(); }\n\n  /**\n   * @brief\
    \ Add some nodes to the graph.\n   *\n   * @param __n Number of nodes added\n\
    \   * @return List of indices of the nodes.\n   */\n  virtual std::vector<size_type>\
    \ add_nodes(size_type __n) {\n    std::vector<size_type> __nds(__n);\n    std::iota(__nds.begin(),\
    \ __nds.end(), graph.size());\n    __n += graph.size();\n    if (__n > graph.capacity())\
    \ {\n      flow_graph __x(__n);\n      for (auto &&adj : graph)\n        for (auto\
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
    ;\n    return __os;\n  }\n};\n\n}  // namespace workspace\n#line 14 \"src/graph/directed/flow/Dinic.hpp\"\
    \n\nnamespace workspace {\n\n/**\n * @brief Compute the maximum flow.\n *\n *\
    \ @tparam Cap Capacity type\n */\ntemplate <class Cap> class Dinic : public flow_graph<Cap>\
    \ {\n  using base = flow_graph<Cap>;\n\n public:\n  using size_type = typename\
    \ base::size_type;\n\n protected:\n  constexpr static size_type nil = -1;\n\n\
    \  std::vector<size_type> level;\n  std::vector<typename base::container_type::value_type::iterator>\
    \ iter;\n\n  Cap dfs(size_type __s, size_type __d, Cap bound) {\n    if (__s ==\
    \ __d) return bound;\n    Cap flow(0);\n    for (auto &e{iter[__d]}; e != base::graph[__d].end();\
    \ ++e)\n      if (static_cast<Cap>(0) < e->flow && level[e->dst] < level[__d])\n\
    \        if (Cap achv = dfs(__s, e->dst, std::min(bound, e->flow));\n        \
    \    static_cast<Cap>(0) < achv) {\n          e->push(-achv);\n          flow\
    \ += achv, bound -= achv;\n          if (bound == static_cast<Cap>(0)) break;\n\
    \        }\n    return flow;\n  }\n\n public:\n  /**\n   * @brief Construct a\
    \ new Dinic object\n   *\n   * @param __n Number of nodes\n   */\n  Dinic(size_type\
    \ __n = 0)\n      : base::flow_graph(__n), level(__n, nil), iter(__n) {}\n\n \
    \ /**\n   * @brief Add some nodes to the graph.\n   *\n   * @param __n Number\
    \ of nodes added\n   * @return List of indices of the nodes.\n   */\n  std::vector<size_type>\
    \ add_nodes(size_type __n) override {\n    auto __nds = base::add_nodes(__n);\n\
    \    level.resize(base::size(), nil);\n    iter.resize(base::size());\n    return\
    \ __nds;\n  }\n\n  /**\n   * @brief Run Dinic's algorithm.\n   *\n   * @param\
    \ __s Source\n   * @param __d Destination\n   * @return Maximum flow.\n   */\n\
    \  Cap run(size_type __s, size_type __d) {\n    assert(__s < base::size());\n\
    \    assert(__d < base::size());\n    assert(__s != __d);\n    Cap flow = 0, bound\
    \ = std::numeric_limits<Cap>::max();\n    for (std::vector<size_type> que(base::size());;\n\
    \         std::fill(level.begin(), level.end(), nil)) {\n      level[que.front()\
    \ = __s] = 0;\n      for (auto ql{que.begin()}, qr{std::next(ql)};\n         \
    \  level[__d] == nil && ql != qr; ++ql)\n        for (const auto &e : base::graph[*ql])\n\
    \          if (static_cast<Cap>(0) < e.cap && level[e.dst] == nil)\n         \
    \   level[ *qr++ = e.dst] = level[*ql] + 1;\n      if (level[__d] == nil) break;\n\
    \      for (size_type node{}; node != base::size(); ++node)\n        iter[node]\
    \ = base::graph[node].begin();\n      flow += dfs(__s, __d, bound);\n    }\n \
    \   return flow;\n  }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file Dinic.hpp\n * @brief Dinic's Algorithm\n *\
    \ @date 2021-01-15\n *\n *\n */\n\n#include <limits>\n\n#include \"base.hpp\"\n\
    \nnamespace workspace {\n\n/**\n * @brief Compute the maximum flow.\n *\n * @tparam\
    \ Cap Capacity type\n */\ntemplate <class Cap> class Dinic : public flow_graph<Cap>\
    \ {\n  using base = flow_graph<Cap>;\n\n public:\n  using size_type = typename\
    \ base::size_type;\n\n protected:\n  constexpr static size_type nil = -1;\n\n\
    \  std::vector<size_type> level;\n  std::vector<typename base::container_type::value_type::iterator>\
    \ iter;\n\n  Cap dfs(size_type __s, size_type __d, Cap bound) {\n    if (__s ==\
    \ __d) return bound;\n    Cap flow(0);\n    for (auto &e{iter[__d]}; e != base::graph[__d].end();\
    \ ++e)\n      if (static_cast<Cap>(0) < e->flow && level[e->dst] < level[__d])\n\
    \        if (Cap achv = dfs(__s, e->dst, std::min(bound, e->flow));\n        \
    \    static_cast<Cap>(0) < achv) {\n          e->push(-achv);\n          flow\
    \ += achv, bound -= achv;\n          if (bound == static_cast<Cap>(0)) break;\n\
    \        }\n    return flow;\n  }\n\n public:\n  /**\n   * @brief Construct a\
    \ new Dinic object\n   *\n   * @param __n Number of nodes\n   */\n  Dinic(size_type\
    \ __n = 0)\n      : base::flow_graph(__n), level(__n, nil), iter(__n) {}\n\n \
    \ /**\n   * @brief Add some nodes to the graph.\n   *\n   * @param __n Number\
    \ of nodes added\n   * @return List of indices of the nodes.\n   */\n  std::vector<size_type>\
    \ add_nodes(size_type __n) override {\n    auto __nds = base::add_nodes(__n);\n\
    \    level.resize(base::size(), nil);\n    iter.resize(base::size());\n    return\
    \ __nds;\n  }\n\n  /**\n   * @brief Run Dinic's algorithm.\n   *\n   * @param\
    \ __s Source\n   * @param __d Destination\n   * @return Maximum flow.\n   */\n\
    \  Cap run(size_type __s, size_type __d) {\n    assert(__s < base::size());\n\
    \    assert(__d < base::size());\n    assert(__s != __d);\n    Cap flow = 0, bound\
    \ = std::numeric_limits<Cap>::max();\n    for (std::vector<size_type> que(base::size());;\n\
    \         std::fill(level.begin(), level.end(), nil)) {\n      level[que.front()\
    \ = __s] = 0;\n      for (auto ql{que.begin()}, qr{std::next(ql)};\n         \
    \  level[__d] == nil && ql != qr; ++ql)\n        for (const auto &e : base::graph[*ql])\n\
    \          if (static_cast<Cap>(0) < e.cap && level[e.dst] == nil)\n         \
    \   level[ *qr++ = e.dst] = level[*ql] + 1;\n      if (level[__d] == nil) break;\n\
    \      for (size_type node{}; node != base::size(); ++node)\n        iter[node]\
    \ = base::graph[node].begin();\n      flow += dfs(__s, __d, bound);\n    }\n \
    \   return flow;\n  }\n};\n\n}  // namespace workspace\n"
  dependsOn:
  - src/graph/directed/flow/base.hpp
  isVerificationFile: false
  path: src/graph/directed/flow/Dinic.hpp
  requiredBy: []
  timestamp: '2021-01-25 15:52:38+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/bipartitematching.test.cpp
  - test/aizu-online-judge/GRL_6_A.test.cpp
documentation_of: src/graph/directed/flow/Dinic.hpp
layout: document
redirect_from:
- /library/src/graph/directed/flow/Dinic.hpp
- /library/src/graph/directed/flow/Dinic.hpp.html
title: Dinic's Algorithm
---
