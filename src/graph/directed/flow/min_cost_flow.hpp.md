---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/graph/directed/flow/base.hpp
    title: Flow Graph
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/1615.2.test.cpp
    title: test/aizu-online-judge/1615.2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/1615.test.cpp
    title: test/aizu-online-judge/1615.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/2815.test.cpp
    title: test/aizu-online-judge/2815.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/GRL_6_B.test.cpp
    title: test/aizu-online-judge/GRL_6_B.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/assignment.test.cpp
    title: test/library-checker/assignment.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/min_cost_b_flow.test.cpp
    title: test/library-checker/min_cost_b_flow.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Minimum Cost Flow
    links: []
  bundledCode: "#line 2 \"src/graph/directed/flow/min_cost_flow.hpp\"\n\n/**\n * @file\
    \ min_cost_flow.hpp\n * @brief Minimum Cost Flow\n */\n\n#include <algorithm>\n\
    #include <queue>\n\n#line 2 \"src/graph/directed/flow/base.hpp\"\n\n/**\n * @file\
    \ base.hpp\n * @brief Flow Graph\n * @date 2021-01-15\n *\n *\n */\n\n#include\
    \ <cassert>\n#include <numeric>\n#include <tuple>\n#include <vector>\n\nnamespace\
    \ workspace {\n\ntemplate <class _Cap, class _Cost = void> class flow_graph {\n\
    \ protected:\n  class adjacency_impl;\n\n public:\n  using container_type = std::vector<adjacency_impl>;\n\
    \  using size_type = typename container_type::size_type;\n\n  class unweighted_edge\
    \ {\n   public:\n    size_type src;  // Source\n    size_type dst;  // Destination\n\
    \    _Cap cap;       // Capacity\n    _Cap flow = 0;  // Flow\n\n    unweighted_edge(size_type\
    \ __s, size_type __d, const _Cap &__u = 1)\n        : src(__s), dst(__d), cap(__u)\
    \ {\n      assert(!(cap < static_cast<_Cap>(0)));\n    }\n\n    /**\n     * @brief\
    \ Source, Destination, Capacity, Flow\n     */\n    template <class _Os>\n   \
    \ friend _Os &operator<<(_Os &__os, const unweighted_edge &__e) {\n      return\
    \ __os << __e.src << ' ' << __e.dst << ' ' << __e.cap << ' '\n               \
    \   << __e.flow;\n    }\n\n   protected:\n    unweighted_edge() = default;\n\n\
    \    unweighted_edge(size_type __s, size_type __d, const _Cap &__u,\n        \
    \            const _Cap &__f)\n        : src(__s), dst(__d), cap(__u), flow(__f)\
    \ {}\n\n    unweighted_edge make_rev() const { return {dst, src, flow, cap}; }\n\
    \  };\n\n  class weighted_edge : public unweighted_edge {\n   public:\n    _Cost\
    \ cost;  // _Cost\n\n    weighted_edge(const unweighted_edge &__e, const _Cost\
    \ &__c = 0)\n        : unweighted_edge(__e), cost(__c) {}\n\n    weighted_edge(size_type\
    \ __s, size_type __d, const _Cap &__u = 1,\n                  const _Cost &__c\
    \ = 0)\n        : unweighted_edge(__s, __d, __u), cost(__c) {}\n\n    /**\n  \
    \   * @brief Source, Destination, Capacity, Flow, _Cost\n     */\n    template\
    \ <class _Os>\n    friend _Os &operator<<(_Os &__os, const weighted_edge &__e)\
    \ {\n      return __os << static_cast<unweighted_edge>(__e) << ' ' << __e.cost;\n\
    \    }\n\n   protected:\n    weighted_edge() = default;\n\n    weighted_edge make_rev()\
    \ const {\n      return {unweighted_edge::make_rev(), -cost};\n    }\n  };\n\n\
    \  using edge = std::conditional_t<std::is_void<_Cost>::value, unweighted_edge,\n\
    \                                  weighted_edge>;\n\n protected:\n  struct edge_impl\
    \ : edge {\n    bool aux = false;\n    edge_impl *rev = nullptr;\n\n    edge_impl()\
    \ = default;\n\n    edge_impl(const edge_impl &__e) = default;\n    edge_impl\
    \ &operator=(const edge_impl &__e) = default;\n\n    edge_impl(edge_impl &&__e)\
    \ = default;\n    edge_impl &operator=(edge_impl &&__e) = default;\n\n    edge_impl(const\
    \ edge &__e) : edge(__e) {}\n    edge_impl(edge &&__e) : edge(__e) {}\n\n    void\
    \ push(_Cap __f) {\n      edge::cap -= __f;\n      edge::flow += __f;\n      if\
    \ (rev) {\n        rev->cap += __f;\n        rev->flow -= __f;\n      }\n    }\n\
    \n    edge_impl make_rev() {\n      edge_impl __e = edge::make_rev();\n      __e.aux\
    \ = true;\n      __e.rev = this;\n      return __e;\n    }\n  };\n\n public:\n\
    \  class adjacency {\n   public:\n    using value_type = edge;\n    using reference\
    \ = edge &;\n    using const_reference = edge const &;\n    using pointer = edge\
    \ *;\n    using const_pointer = const edge *;\n\n    class iterator {\n      edge_impl\
    \ *__p;\n\n     public:\n      iterator(edge_impl *__p = nullptr) : __p(__p) {}\n\
    \n      bool operator!=(const iterator &__x) const { return __p != __x.__p; }\n\
    \n      bool operator==(const iterator &__x) const { return __p == __x.__p; }\n\
    \n      iterator &operator++() {\n        do ++__p;\n        while (__p->rev &&\
    \ __p->aux);\n        return *this;\n      }\n\n      iterator operator++(int)\
    \ {\n        auto __cp = *this;\n        do ++__p;\n        while (__p->rev &&\
    \ __p->aux);\n        return __cp;\n      }\n\n      iterator &operator--() {\n\
    \        do --__p;\n        while (__p->aux);\n        return *this;\n      }\n\
    \n      iterator operator--(int) {\n        auto __cp = *this;\n        do --__p;\n\
    \        while (__p->aux);\n        return __cp;\n      }\n\n      pointer operator->()\
    \ const { return __p; }\n\n      reference operator*() const { return *__p; }\n\
    \    };\n\n    class const_iterator {\n      const edge_impl *__p;\n\n     public:\n\
    \      const_iterator(const edge_impl *__p = nullptr) : __p(__p) {}\n\n      bool\
    \ operator!=(const const_iterator &__x) const {\n        return __p != __x.__p;\n\
    \      }\n\n      bool operator==(const const_iterator &__x) const {\n       \
    \ return __p == __x.__p;\n      }\n\n      const_iterator &operator++() {\n  \
    \      do ++__p;\n        while (__p->rev && __p->aux);\n        return *this;\n\
    \      }\n\n      const_iterator operator++(int) {\n        auto __cp = *this;\n\
    \        do ++__p;\n        while (__p->rev && __p->aux);\n        return __cp;\n\
    \      }\n\n      const_iterator &operator--() {\n        do --__p;\n        while\
    \ (__p->aux);\n        return *this;\n      }\n\n      const_iterator operator--(int)\
    \ {\n        auto __cp = *this;\n        do --__p;\n        while (__p->aux);\n\
    \        return __cp;\n      }\n\n      const_pointer operator->() const { return\
    \ __p; }\n\n      const_reference operator*() const { return *__p; }\n    };\n\
    \n    adjacency()\n        : first(new edge_impl[2]), last(first + 1), __s(first),\
    \ __t(first) {}\n\n    ~adjacency() { delete[] first; }\n\n    const_reference\
    \ operator[](size_type __i) const {\n      assert(__i < size());\n      return\
    \ *(first + __i);\n    }\n\n    size_type size() const { return __t - first; }\n\
    \n    auto begin() { return iterator{__s}; }\n    auto begin() const { return\
    \ const_iterator{__s}; }\n\n    auto end() { return iterator{__t}; }\n    auto\
    \ end() const { return const_iterator{__t}; }\n\n    /**\n     * @brief Construct\
    \ a new adjacency object\n     *\n     * @param __x Rvalue reference to another\
    \ object\n     */\n    adjacency(adjacency &&__x) : first(nullptr) { operator=(std::move(__x));\
    \ }\n\n    /**\n     * @brief Assignment operator.\n     *\n     * @param __x\
    \ Rvalue reference to another object\n     * @return Reference to this object.\n\
    \     */\n    adjacency &operator=(adjacency &&__x) {\n      std::swap(first,\
    \ __x.first);\n      last = __x.last;\n      __s = __x.__s;\n      __t = __x.__t;\n\
    \      return *this;\n    }\n\n   protected:\n    edge_impl *first, *last, *__s,\
    \ *__t;\n  };\n\n  using value_type = adjacency;\n  using reference = adjacency\
    \ &;\n  using const_reference = adjacency const &;\n\n protected:\n  class adjacency_impl\
    \ : public adjacency {\n   public:\n    using base = adjacency;\n    using base::__s;\n\
    \    using base::__t;\n    using base::first;\n    using base::last;\n\n    using\
    \ iterator = edge_impl *;\n\n    iterator _push(edge_impl &&__e) {\n      if (__t\
    \ == last) {\n        size_type __n(last - first);\n        iterator loc = new\
    \ edge_impl[__n << 1 | 1];\n        __s += loc - first;\n        __t = loc;\n\
    \        for (iterator __p{first}; __p != last; ++__p, ++__t) {\n          *__t\
    \ = *__p;\n          if (__p->rev) __p->rev->rev = __t;\n        }\n        delete[]\
    \ first;\n        first = loc;\n        last = __t + __n;\n      }\n      *__t\
    \ = std::move(__e);\n      if (__s->aux) ++__s;\n      return __t++;\n    }\n\n\
    \    iterator begin() const { return first; }\n\n    iterator end() const { return\
    \ __t; }\n  };\n\n  /**\n   * @brief The only member variable.\n   */\n  container_type\
    \ graph;\n\n public:\n  /**\n   * @brief Construct a new flow graph object\n \
    \  *\n   * @param __n Number of vertices\n   */\n  flow_graph(size_type __n =\
    \ 0) : graph(__n) {}\n\n  /**\n   * @brief Construct a new flow graph object\n\
    \   *\n   * @param __x Const reference to another object\n   */\n  flow_graph(const\
    \ flow_graph &__x) : graph(__x.size()) {\n    for (auto &&__adj : __x)\n     \
    \ for (auto &&__e : __adj) add_edge(__e);\n  }\n\n  /**\n   * @brief Construct\
    \ a new flow graph object\n   *\n   * @param __x Rvalue reference to another object\n\
    \   */\n  flow_graph(flow_graph &&__x) : graph(std::move(__x.graph)) {}\n\n  /**\n\
    \   * @brief Assignment operator.\n   *\n   * @param __x Const reference to another\
    \ object\n   * @return Reference to this object.\n   */\n  flow_graph &operator=(const\
    \ flow_graph &__x) {\n    return operator=(std::move(flow_graph{__x}));\n  }\n\
    \n  /**\n   * @brief Assignment operator.\n   *\n   * @param __x Rvalue reference\
    \ to another object\n   * @return Reference to this object.\n   */\n  flow_graph\
    \ &operator=(flow_graph &&__x) {\n    graph = std::move(__x.graph);\n    return\
    \ *this;\n  }\n\n  /**\n   * @return Whether the graph is empty.\n   */\n  bool\
    \ empty() const { return graph.empty(); }\n\n  /**\n   * @return Number of nodes.\n\
    \   */\n  size_type size() const { return graph.size(); }\n\n  /**\n   * @param\
    \ node Node\n   * @return Referece to the adjacency list of the node.\n   */\n\
    \  reference operator[](size_type node) {\n    assert(node < size());\n    return\
    \ graph[node];\n  }\n\n  /**\n   * @param node Node\n   * @return Const referece\
    \ to the adjacency list of the node.\n   */\n  const_reference operator[](size_type\
    \ node) const {\n    assert(node < size());\n    return graph[node];\n  }\n\n\
    \  class iterator : public container_type::iterator {\n    using base = typename\
    \ container_type::iterator;\n\n   public:\n    using reference = adjacency &;\n\
    \    using pointer = adjacency *;\n\n    iterator(const base &__i) : base(__i)\
    \ {}\n\n    pointer operator->() const { return base::operator->(); }\n\n    reference\
    \ operator*() const { return base::operator*(); }\n  };\n\n  class const_iterator\
    \ : public container_type::const_iterator {\n    using base = typename container_type::const_iterator;\n\
    \n   public:\n    using const_reference = const adjacency &;\n    using const_pointer\
    \ = const adjacency *;\n\n    const_iterator(const base &__i) : base(__i) {}\n\
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
    \   */\n  template <class... _Args>\n  typename std::enable_if<std::is_constructible<edge,\
    \ _Args...>::value,\n                          edge &>::type\n  add_edge(_Args\
    \ &&...__args) {\n    edge_impl __e = edge(std::forward<_Args>(__args)...);\n\
    \    assert(__e.src < size());\n    assert(__e.dst < size());\n    edge_impl *__p\
    \ = graph[__e.src]._push(std::move(__e));\n    // Careful with a self loop.\n\
    \    if (__e.src != __e.dst) __p->rev = graph[__e.dst]._push(__p->make_rev());\n\
    \    return *__p;\n  }\n\n  /**\n   * @brief Add a directed edge to the graph.\n\
    \   *\n   * @return Reference to the edge.\n   */\n  template <class _Tp>\n  typename\
    \ std::enable_if<(std::tuple_size<std::decay_t<_Tp>>::value >= 0),\n         \
    \                 edge &>::type\n  add_edge(_Tp &&__t) {\n    return _unpack_directed(std::forward<_Tp>(__t));\n\
    \  }\n\n  /**\n   * @brief Add an undirected edge to the graph. Its cost must\
    \ be non-negative.\n   *\n   * @return Reference to the edge.\n   */\n  template\
    \ <class... _Args> edge &add_undirected_edge(_Args &&...__args) {\n    edge_impl\
    \ __e = edge(std::forward<_Args>(__args)...);\n    assert(__e.src < size());\n\
    \    assert(__e.dst < size());\n    (__e.flow += __e.flow) += __e.cap;\n    edge_impl\
    \ *__p = graph[__e.src]._push(std::move(__e));\n    // Careful with a self loop.\n\
    \    if (__e.src != __e.dst) {\n      edge_impl __r = __p->make_rev();\n     \
    \ __r.aux = false;\n      __p->rev = graph[__e.dst]._push(std::move(__r));\n \
    \   }\n    return *__p;\n  }\n\n  /**\n   * @brief Add an undirected edge to the\
    \ graph. Its cost must be non-negative.\n   *\n   * @return Reference to the edge.\n\
    \   */\n  template <class _Tp>\n  typename std::enable_if<(std::tuple_size<std::decay_t<_Tp>>::value\
    \ >= 0),\n                          edge &>::type\n  add_undirected_edge(_Tp &&__t)\
    \ {\n    return _unpack_undirected(std::forward<_Tp>(__t));\n  }\n\n protected:\n\
    \  // internal\n  template <class _Tp, size_t _Nm = 0, class... _Args>\n  decltype(auto)\
    \ _unpack_directed(_Tp &&__t, _Args &&...__args) {\n    if constexpr (_Nm == std::tuple_size<std::decay_t<_Tp>>::value)\n\
    \      return add_edge(std::forward<_Args>(__args)...);\n    else\n      return\
    \ _unpack_directed<_Tp, _Nm + 1>(std::forward<_Tp>(__t),\n                   \
    \                         std::forward<_Args>(__args)...,\n                  \
    \                          std::get<_Nm>(__t));\n  }\n\n  // internal\n  template\
    \ <class _Tp, size_t _Nm = 0, class... _Args>\n  decltype(auto) _unpack_undirected(_Tp\
    \ &&__t, _Args &&...__args) {\n    if constexpr (_Nm == std::tuple_size<std::decay_t<_Tp>>::value)\n\
    \      return add_undirected_edge(std::forward<_Args>(__args)...);\n    else\n\
    \      return _unpack_undirected<_Tp, _Nm + 1>(std::forward<_Tp>(__t),\n     \
    \                                         std::forward<_Args>(__args)...,\n  \
    \                                            std::get<_Nm>(__t));\n  }\n\n  template\
    \ <class _Os>\n  friend _Os &operator<<(_Os &__os, flow_graph const &__g) {\n\
    \    for (const auto &adj : __g)\n      for (const auto &e : adj) __os << e <<\
    \ \"\\n\";\n    return __os;\n  }\n};\n\n}  // namespace workspace\n#line 2 \"\
    lib/limits\"\n\n#include <limits>\n\nnamespace workspace {\n\ntemplate <class\
    \ _Tp> struct numeric_limits : std::numeric_limits<_Tp> {};\n\n#ifdef __SIZEOF_INT128__\n\
    \ntemplate <> struct numeric_limits<__uint128_t> {\n  constexpr static __uint128_t\
    \ max() { return ~__uint128_t(0); }\n  constexpr static __uint128_t min() { return\
    \ 0; }\n};\n\ntemplate <> struct numeric_limits<__int128_t> {\n  constexpr static\
    \ __int128_t max() {\n    return numeric_limits<__uint128_t>::max() >> 1;\n  }\n\
    \  constexpr static __int128_t min() { return -max() - 1; }\n};\n\n#endif\n\n\
    }  // namespace workspace\n#line 13 \"src/graph/directed/flow/min_cost_flow.hpp\"\
    \n\nnamespace workspace {\n\n/**\n * @brief Capacity Scaling Algorithm.\n *\n\
    \ * @tparam _Cap Capacity type\n * @tparam _Cost Cost type\n */\ntemplate <class\
    \ _Cap, class _Cost = _Cap>\nclass min_cost_flow : public flow_graph<_Cap, _Cost>\
    \ {\n  using base = flow_graph<_Cap, _Cost>;\n  using edge_impl = typename base::edge_impl;\n\
    \n public:\n  using edge = typename base::edge;\n  using size_type = typename\
    \ base::size_type;\n\n  /**\n   * @brief Construct a new min_cost_flow object\n\
    \   *\n   * @param __n Number of vertices\n   */\n  min_cost_flow(size_type __n\
    \ = 0) : base::flow_graph(__n), b(__n) {}\n\n  std::vector<size_type> add_nodes(size_type\
    \ __n) override {\n    b.resize(b.size() + __n);\n    return base::add_nodes(__n);\n\
    \  }\n\n  using base::add_edge;\n\n  /**\n   * @brief Add a directed edge to the\
    \ graph.\n   *\n   * @param __s Source\n   * @param __d Destination\n   * @param\
    \ __l Lower bound of flow\n   * @param __u Upper bound of flow\n   * @param __c\
    \ _Cost\n   * @return Reference to the edge.\n   */\n  edge &add_edge(size_type\
    \ __s, size_type __d, _Cap __l, _Cap __u, _Cost __c) {\n    assert(!(__u < __l));\n\
    \    b[__s] -= __l;\n    b[__d] += __l;\n    auto &__e = base::add_edge(__s, __d,\
    \ __u - __l, __c);\n    __e.flow = __l;\n    return __e;\n  }\n\n  /**\n   * @brief\
    \ Add an undirected edge to the graph.\n   *\n   * @return Reference to the edge.\n\
    \   */\n  template <class... _Args> edge &add_undirected_edge(_Args &&...__args)\
    \ {\n    auto &__e = static_cast<edge_impl &>(\n        base::add_undirected_edge(std::forward<_Args>(__args)...));\n\
    \    assert(!(__e.cost < 0));\n    __e.rev->cost = __e.cost;\n    return __e;\n\
    \  }\n\n  /**\n   * @brief Increase the balance of a node.\n   *\n   * @param\
    \ node\n   * @param __f Default: 1\n   */\n  void supply(size_type node, _Cap\
    \ __f = 1) {\n    assert(node < b.size());\n    b[node] += __f;\n  }\n\n  /**\n\
    \   * @brief Decrease the balance of a node.\n   *\n   * @param node\n   * @param\
    \ __f Default: 1\n   */\n  void demand(size_type node, _Cap __f = 1) {\n    assert(node\
    \ < b.size());\n    b[node] -= __f;\n  }\n\n  /**\n   * @return Balance.\n   */\n\
    \  const auto &balance() const { return b; }\n\n  /**\n   * @param node Node\n\
    \   * @return Balance of the node.\n   */\n  _Cap balance(size_type node) const\
    \ { return b[node]; }\n\n  /**\n   * @return Potential. The dual solution.\n \
    \  */\n  const auto &potential() const { return p; }\n\n  /**\n   * @param node\
    \ Node\n   * @return Potential of the node.\n   */\n  _Cost potential(size_type\
    \ node) const { return p[node]; }\n\n  /**\n   * @return _Cost of current flow.\n\
    \   */\n  _Cost cost() const { return current; }\n\n  /**\n   * @brief Run Capacity\
    \ Scaling Algorithm.\n   *\n   * @return Whether a balanced flow exists.\n   */\n\
    \  bool run() {\n    p.resize(b.size());\n\n    _Cap delta = 0;\n    for (auto\
    \ &&__adj : base::graph)\n      for (auto &&__e : __adj) delta = std::max(delta,\
    \ __e.cap);\n    if (delta == static_cast<_Cap>(0))\n      return std::all_of(b.begin(),\
    \ b.end(),\n                         [](_Cap __x) { return __x == static_cast<_Cap>(0);\
    \ });\n\n    parent.resize(b.size());\n\n    while (static_cast<_Cap>(0) < delta)\
    \ {\n      delta /= 2;\n\n      for (auto &&__adj : base::graph)\n        for\
    \ (auto &&__e : __adj)\n          if (delta < __e.cap && __e.cost < p[__e.dst]\
    \ - p[__e.src]) {\n            b[__e.src] -= __e.cap;\n            b[__e.dst]\
    \ += __e.cap;\n            __e.push(__e.cap);\n          }\n\n      sources.clear();\n\
    \      sinks.clear();\n      for (size_type __v = 0; __v != b.size(); ++__v)\n\
    \        if (delta < b[__v])\n          sources.emplace_back(__v);\n        else\
    \ if (b[__v] < -delta)\n          sinks.emplace_back(__v);\n\n      while (dual(delta))\
    \ {\n        primal(delta);\n        sources.erase(\n            std::remove_if(sources.begin(),\
    \ sources.end(),\n                           [&](auto __v) { return !(delta <\
    \ b[__v]); }),\n            sources.end());\n        sinks.erase(\n          \
    \  std::remove_if(sinks.begin(), sinks.end(),\n                           [&](auto\
    \ __v) { return !(b[__v] < -delta); }),\n            sinks.end());\n      }\n\
    \    }\n\n    current = 0;\n    for (auto &&__adj : base::graph)\n      for (auto\
    \ &&__e : __adj)\n        if (!__e.aux) current += __e.cost * __e.flow;\n\n  \
    \  return sources.empty() && sinks.empty();\n  }\n\n protected:\n  // _Cost of\
    \ flow.\n  _Cost current{};\n\n  // Balance\n  std::vector<_Cap> b;\n\n  // The\
    \ dual solution.\n  std::vector<_Cost> p;\n\n  std::vector<edge_impl *> parent;\n\
    \  std::vector<size_type> sources, sinks;\n\n  // Augment along the dual solution.\n\
    \  void primal(_Cap delta) {\n    for (auto __t : sinks)\n      if (parent[__t])\
    \ {\n        auto __f = -b[__t];\n        auto __s = __t;\n        while (parent[__s])\n\
    \          __f = std::min(__f, parent[__s]->cap), __s = parent[__s]->src;\n  \
    \      if (delta < b[__s]) {\n          __f = std::min(__f, b[__s]);\n       \
    \   b[__s] -= __f;\n          b[__t] += __f;\n          for (auto *__p = parent[__t];\
    \ __p; __p = parent[__p->src]) {\n            __p->push(__f);\n            parent[__p->dst]\
    \ = nullptr;\n          }\n        }\n      }\n  }\n\n  // Improve the dual solution.\n\
    \  bool dual(_Cap delta) {\n    std::fill(parent.begin(), parent.end(), nullptr);\n\
    \    size_type reachable = 0;\n\n    struct state {\n      size_type __v;\n  \
    \    _Cost __d;\n      state(size_type __v, _Cost __d) : __v(__v), __d(__d) {}\n\
    \      bool operator<(const state &__x) const { return __x.__d < __d; }\n    };\n\
    \n    std::priority_queue<state> __q;\n    decltype(p) __nx(p.size(), numeric_limits<_Cost>::max());\n\
    \    _Cost __ld = 0;\n\n    for (auto __v : sources) {\n      __nx[__v] = p[__v];\n\
    \      __q.emplace(__v, 0);\n    }\n\n    while (!__q.empty()) {\n      auto [__v,\
    \ __d] = __q.top();\n      __q.pop();\n      if (__d + p[__v] != __nx[__v]) continue;\n\
    \      __ld = __d;\n      if (b[__v] < -delta && ++reachable == sinks.size())\
    \ break;\n      for (auto &__e : base::graph[__v])\n        if (delta < __e.cap\
    \ && (__d = __nx[__v] + __e.cost) < __nx[__e.dst]) {\n          __q.emplace(__e.dst,\
    \ (__nx[__e.dst] = __d) - p[__e.dst]);\n          parent[__e.dst] = &__e;\n  \
    \      }\n    }\n\n    for (size_type __v = 0; __v != p.size(); ++__v)\n     \
    \ p[__v] = std::min(__nx[__v], p[__v] += __ld);\n\n    return reachable;\n  }\n\
    \n};  // namespace workspace\n\n/**\n * @brief Capacity Scaling Algorithm.\n *\n\
    \ * @tparam _Cap Capacity type\n * @tparam _Gain Gain type\n */\ntemplate <class\
    \ _Cap, class _Gain = _Cap>\nclass max_gain_flow : public min_cost_flow<_Cap,\
    \ _Gain> {\n  using base = min_cost_flow<_Cap, _Gain>;\n  using base::cost;\n\n\
    \ public:\n  using base::min_cost_flow;\n  using edge = typename base::edge;\n\
    \n  /**\n   * @brief Add a directed edge to the graph. The default capacity is\
    \ 1.\n   *\n   * @return Reference to the edge.\n   */\n  template <class... _Args>\
    \ decltype(auto) add_edge(_Args &&...__args) {\n    return add_edge(std::tuple<_Args...>{std::forward<_Args>(__args)...});\n\
    \  }\n\n  /**\n   * @brief Add a directed edge to the graph. The default capacity\
    \ is 1.\n   *\n   * @return Reference to the edge.\n   */\n  template <class _Tp>\n\
    \  typename std::enable_if<(std::tuple_size<std::decay_t<_Tp>>::value >= 0),\n\
    \                          const edge &>::type\n  add_edge(_Tp __t) {\n    std::get<std::tuple_size<decltype(__t)>::value\
    \ - 1>(__t) *=\n        -1;  // Flip the sign of cost.\n    return base::add_edge(std::move(__t));\n\
    \  }\n\n  /**\n   * @return _Gain of current flow.\n   */\n  _Gain gain() const\
    \ { return -cost(); }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file min_cost_flow.hpp\n * @brief Minimum Cost Flow\n\
    \ */\n\n#include <algorithm>\n#include <queue>\n\n#include \"base.hpp\"\n#include\
    \ \"lib/limits\"\n\nnamespace workspace {\n\n/**\n * @brief Capacity Scaling Algorithm.\n\
    \ *\n * @tparam _Cap Capacity type\n * @tparam _Cost Cost type\n */\ntemplate\
    \ <class _Cap, class _Cost = _Cap>\nclass min_cost_flow : public flow_graph<_Cap,\
    \ _Cost> {\n  using base = flow_graph<_Cap, _Cost>;\n  using edge_impl = typename\
    \ base::edge_impl;\n\n public:\n  using edge = typename base::edge;\n  using size_type\
    \ = typename base::size_type;\n\n  /**\n   * @brief Construct a new min_cost_flow\
    \ object\n   *\n   * @param __n Number of vertices\n   */\n  min_cost_flow(size_type\
    \ __n = 0) : base::flow_graph(__n), b(__n) {}\n\n  std::vector<size_type> add_nodes(size_type\
    \ __n) override {\n    b.resize(b.size() + __n);\n    return base::add_nodes(__n);\n\
    \  }\n\n  using base::add_edge;\n\n  /**\n   * @brief Add a directed edge to the\
    \ graph.\n   *\n   * @param __s Source\n   * @param __d Destination\n   * @param\
    \ __l Lower bound of flow\n   * @param __u Upper bound of flow\n   * @param __c\
    \ _Cost\n   * @return Reference to the edge.\n   */\n  edge &add_edge(size_type\
    \ __s, size_type __d, _Cap __l, _Cap __u, _Cost __c) {\n    assert(!(__u < __l));\n\
    \    b[__s] -= __l;\n    b[__d] += __l;\n    auto &__e = base::add_edge(__s, __d,\
    \ __u - __l, __c);\n    __e.flow = __l;\n    return __e;\n  }\n\n  /**\n   * @brief\
    \ Add an undirected edge to the graph.\n   *\n   * @return Reference to the edge.\n\
    \   */\n  template <class... _Args> edge &add_undirected_edge(_Args &&...__args)\
    \ {\n    auto &__e = static_cast<edge_impl &>(\n        base::add_undirected_edge(std::forward<_Args>(__args)...));\n\
    \    assert(!(__e.cost < 0));\n    __e.rev->cost = __e.cost;\n    return __e;\n\
    \  }\n\n  /**\n   * @brief Increase the balance of a node.\n   *\n   * @param\
    \ node\n   * @param __f Default: 1\n   */\n  void supply(size_type node, _Cap\
    \ __f = 1) {\n    assert(node < b.size());\n    b[node] += __f;\n  }\n\n  /**\n\
    \   * @brief Decrease the balance of a node.\n   *\n   * @param node\n   * @param\
    \ __f Default: 1\n   */\n  void demand(size_type node, _Cap __f = 1) {\n    assert(node\
    \ < b.size());\n    b[node] -= __f;\n  }\n\n  /**\n   * @return Balance.\n   */\n\
    \  const auto &balance() const { return b; }\n\n  /**\n   * @param node Node\n\
    \   * @return Balance of the node.\n   */\n  _Cap balance(size_type node) const\
    \ { return b[node]; }\n\n  /**\n   * @return Potential. The dual solution.\n \
    \  */\n  const auto &potential() const { return p; }\n\n  /**\n   * @param node\
    \ Node\n   * @return Potential of the node.\n   */\n  _Cost potential(size_type\
    \ node) const { return p[node]; }\n\n  /**\n   * @return _Cost of current flow.\n\
    \   */\n  _Cost cost() const { return current; }\n\n  /**\n   * @brief Run Capacity\
    \ Scaling Algorithm.\n   *\n   * @return Whether a balanced flow exists.\n   */\n\
    \  bool run() {\n    p.resize(b.size());\n\n    _Cap delta = 0;\n    for (auto\
    \ &&__adj : base::graph)\n      for (auto &&__e : __adj) delta = std::max(delta,\
    \ __e.cap);\n    if (delta == static_cast<_Cap>(0))\n      return std::all_of(b.begin(),\
    \ b.end(),\n                         [](_Cap __x) { return __x == static_cast<_Cap>(0);\
    \ });\n\n    parent.resize(b.size());\n\n    while (static_cast<_Cap>(0) < delta)\
    \ {\n      delta /= 2;\n\n      for (auto &&__adj : base::graph)\n        for\
    \ (auto &&__e : __adj)\n          if (delta < __e.cap && __e.cost < p[__e.dst]\
    \ - p[__e.src]) {\n            b[__e.src] -= __e.cap;\n            b[__e.dst]\
    \ += __e.cap;\n            __e.push(__e.cap);\n          }\n\n      sources.clear();\n\
    \      sinks.clear();\n      for (size_type __v = 0; __v != b.size(); ++__v)\n\
    \        if (delta < b[__v])\n          sources.emplace_back(__v);\n        else\
    \ if (b[__v] < -delta)\n          sinks.emplace_back(__v);\n\n      while (dual(delta))\
    \ {\n        primal(delta);\n        sources.erase(\n            std::remove_if(sources.begin(),\
    \ sources.end(),\n                           [&](auto __v) { return !(delta <\
    \ b[__v]); }),\n            sources.end());\n        sinks.erase(\n          \
    \  std::remove_if(sinks.begin(), sinks.end(),\n                           [&](auto\
    \ __v) { return !(b[__v] < -delta); }),\n            sinks.end());\n      }\n\
    \    }\n\n    current = 0;\n    for (auto &&__adj : base::graph)\n      for (auto\
    \ &&__e : __adj)\n        if (!__e.aux) current += __e.cost * __e.flow;\n\n  \
    \  return sources.empty() && sinks.empty();\n  }\n\n protected:\n  // _Cost of\
    \ flow.\n  _Cost current{};\n\n  // Balance\n  std::vector<_Cap> b;\n\n  // The\
    \ dual solution.\n  std::vector<_Cost> p;\n\n  std::vector<edge_impl *> parent;\n\
    \  std::vector<size_type> sources, sinks;\n\n  // Augment along the dual solution.\n\
    \  void primal(_Cap delta) {\n    for (auto __t : sinks)\n      if (parent[__t])\
    \ {\n        auto __f = -b[__t];\n        auto __s = __t;\n        while (parent[__s])\n\
    \          __f = std::min(__f, parent[__s]->cap), __s = parent[__s]->src;\n  \
    \      if (delta < b[__s]) {\n          __f = std::min(__f, b[__s]);\n       \
    \   b[__s] -= __f;\n          b[__t] += __f;\n          for (auto *__p = parent[__t];\
    \ __p; __p = parent[__p->src]) {\n            __p->push(__f);\n            parent[__p->dst]\
    \ = nullptr;\n          }\n        }\n      }\n  }\n\n  // Improve the dual solution.\n\
    \  bool dual(_Cap delta) {\n    std::fill(parent.begin(), parent.end(), nullptr);\n\
    \    size_type reachable = 0;\n\n    struct state {\n      size_type __v;\n  \
    \    _Cost __d;\n      state(size_type __v, _Cost __d) : __v(__v), __d(__d) {}\n\
    \      bool operator<(const state &__x) const { return __x.__d < __d; }\n    };\n\
    \n    std::priority_queue<state> __q;\n    decltype(p) __nx(p.size(), numeric_limits<_Cost>::max());\n\
    \    _Cost __ld = 0;\n\n    for (auto __v : sources) {\n      __nx[__v] = p[__v];\n\
    \      __q.emplace(__v, 0);\n    }\n\n    while (!__q.empty()) {\n      auto [__v,\
    \ __d] = __q.top();\n      __q.pop();\n      if (__d + p[__v] != __nx[__v]) continue;\n\
    \      __ld = __d;\n      if (b[__v] < -delta && ++reachable == sinks.size())\
    \ break;\n      for (auto &__e : base::graph[__v])\n        if (delta < __e.cap\
    \ && (__d = __nx[__v] + __e.cost) < __nx[__e.dst]) {\n          __q.emplace(__e.dst,\
    \ (__nx[__e.dst] = __d) - p[__e.dst]);\n          parent[__e.dst] = &__e;\n  \
    \      }\n    }\n\n    for (size_type __v = 0; __v != p.size(); ++__v)\n     \
    \ p[__v] = std::min(__nx[__v], p[__v] += __ld);\n\n    return reachable;\n  }\n\
    \n};  // namespace workspace\n\n/**\n * @brief Capacity Scaling Algorithm.\n *\n\
    \ * @tparam _Cap Capacity type\n * @tparam _Gain Gain type\n */\ntemplate <class\
    \ _Cap, class _Gain = _Cap>\nclass max_gain_flow : public min_cost_flow<_Cap,\
    \ _Gain> {\n  using base = min_cost_flow<_Cap, _Gain>;\n  using base::cost;\n\n\
    \ public:\n  using base::min_cost_flow;\n  using edge = typename base::edge;\n\
    \n  /**\n   * @brief Add a directed edge to the graph. The default capacity is\
    \ 1.\n   *\n   * @return Reference to the edge.\n   */\n  template <class... _Args>\
    \ decltype(auto) add_edge(_Args &&...__args) {\n    return add_edge(std::tuple<_Args...>{std::forward<_Args>(__args)...});\n\
    \  }\n\n  /**\n   * @brief Add a directed edge to the graph. The default capacity\
    \ is 1.\n   *\n   * @return Reference to the edge.\n   */\n  template <class _Tp>\n\
    \  typename std::enable_if<(std::tuple_size<std::decay_t<_Tp>>::value >= 0),\n\
    \                          const edge &>::type\n  add_edge(_Tp __t) {\n    std::get<std::tuple_size<decltype(__t)>::value\
    \ - 1>(__t) *=\n        -1;  // Flip the sign of cost.\n    return base::add_edge(std::move(__t));\n\
    \  }\n\n  /**\n   * @return _Gain of current flow.\n   */\n  _Gain gain() const\
    \ { return -cost(); }\n};\n\n}  // namespace workspace\n"
  dependsOn:
  - src/graph/directed/flow/base.hpp
  isVerificationFile: false
  path: src/graph/directed/flow/min_cost_flow.hpp
  requiredBy: []
  timestamp: '2021-04-05 00:56:51+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/assignment.test.cpp
  - test/library-checker/min_cost_b_flow.test.cpp
  - test/aizu-online-judge/GRL_6_B.test.cpp
  - test/aizu-online-judge/1615.2.test.cpp
  - test/aizu-online-judge/1615.test.cpp
  - test/aizu-online-judge/2815.test.cpp
documentation_of: src/graph/directed/flow/min_cost_flow.hpp
layout: document
redirect_from:
- /library/src/graph/directed/flow/min_cost_flow.hpp
- /library/src/graph/directed/flow/min_cost_flow.hpp.html
title: Minimum Cost Flow
---
