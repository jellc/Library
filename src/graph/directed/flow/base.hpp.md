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
    #include <numeric>\n#include <vector>\n\nnamespace workspace {\n\ntemplate <class\
    \ Cap, class Cost = void> class flow_graph {\n protected:\n  class adjacency_impl;\n\
    \n public:\n  using container_type = std::vector<adjacency_impl>;\n  using size_type\
    \ = typename container_type::size_type;\n\n  class unweighted_edge {\n   public:\n\
    \    size_type src, dst;\n    Cap cap;\n\n    unweighted_edge(size_type src, size_type\
    \ dst, const Cap &cap = 1)\n        : src(src), dst(dst), cap(cap) {\n      assert(!(cap\
    \ < static_cast<Cap>(0)));\n    }\n\n    template <class Os>\n    friend Os &operator<<(Os\
    \ &__os, unweighted_edge const &__e) {\n      return __os << __e.src << \" \"\
    \ << __e.dst << \" \" << __e.cap;\n    }\n\n   protected:\n    unweighted_edge()\
    \ = default;\n\n    unweighted_edge make_rev() const { return {dst, src, 0}; }\n\
    \n    unweighted_edge make_ud_rev() const { return {dst, src, cap}; }\n  };\n\n\
    \  class weighted_edge : public unweighted_edge {\n   public:\n    Cost cost;\n\
    \n    weighted_edge(const unweighted_edge &__e, const Cost &__c)\n        : unweighted_edge(__e),\
    \ cost(__c) {}\n\n    weighted_edge(size_type src, size_type dst, const Cap &cap,\n\
    \                  const Cost &cost)\n        : unweighted_edge(src, dst, cap),\
    \ cost(cost) {}\n\n    template <class Os>\n    friend Os &operator<<(Os &__os,\
    \ weighted_edge const &__e) {\n      return __os << static_cast<unweighted_edge>(__e)\
    \ << \" \" << __e.cost;\n    }\n\n   protected:\n    weighted_edge() = default;\n\
    \n    weighted_edge make_rev() const {\n      return {unweighted_edge::make_rev(),\
    \ -cost};\n    }\n\n    weighted_edge make_ud_rev() const {\n      return {unweighted_edge::make_ud_rev(),\
    \ -cost};\n    }\n  };\n\n  using edge = typename std::conditional<std::is_void<Cost>::value,\n\
    \                                         unweighted_edge, weighted_edge>::type;\n\
    \n protected:\n  struct edge_impl : edge {\n    bool aux = false;\n    edge_impl\
    \ *rev = nullptr;\n\n    edge_impl() = default;\n\n    edge_impl(const edge_impl\
    \ &__e) = default;\n\n    edge_impl(const edge &__e) : edge(__e) {}\n\n    void\
    \ flow(const Cap &__f) { edge::cap -= __f, rev->cap += __f; }\n\n    edge_impl\
    \ rev_cp() {\n      edge_impl __e;\n      if (rev)\n        __e = *rev;\n    \
    \  else {\n        __e = edge::make_rev();\n        __e.aux = true;\n      }\n\
    \      __e.rev = this;\n      return __e;\n    }\n\n    edge_impl ud_rev_cp()\
    \ {\n      edge_impl __e = rev ? *rev : edge::make_ud_rev();\n      __e.rev =\
    \ this;\n      return __e;\n    }\n  };\n\n public:\n  class adjacency {\n   public:\n\
    \    using value_type = edge;\n    using reference = edge &;\n    using const_reference\
    \ = edge const &;\n    using pointer = edge *;\n    using const_pointer = const\
    \ edge *;\n\n    class const_iterator {\n     public:\n      const edge_impl *__p;\n\
    \n      bool operator!=(const_iterator const &__x) const {\n        return __p\
    \ != __x.__p;\n      }\n\n      const_iterator &operator++() {\n        do\n \
    \         ++__p;\n        while (__p->rev && __p->aux);\n        return *this;\n\
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
    \ for (auto &&__e : __adj) _add_edge(__e);\n  }\n\n  /**\n   * @brief Construct\
    \ a new flow graph object\n   *\n   * @param __x Rvalue reference to another object\n\
    \   */\n  flow_graph(flow_graph &&__x) : graph(std::move(__x.graph)) {}\n\n  /**\n\
    \   * @brief Assignment operator.\n   *\n   * @param __x Const reference to another\
    \ object\n   * @return Reference to this object.\n   */\n  flow_graph &operator=(const\
    \ flow_graph &__x) {\n    return operator=(std::move(flow_graph{__x}));\n  }\n\
    \n  /**\n   * @brief Assignment operator.\n   *\n   * @param __x Rvalue reference\
    \ to another object\n   * @return Reference to this object.\n   */\n  flow_graph\
    \ &operator=(flow_graph &&__x) {\n    graph = std::move(__x.graph);\n    return\
    \ *this;\n  }\n\n  /**\n   * @return Number of nodes.\n   */\n  size_type size()\
    \ const { return graph.size(); }\n\n  reference operator[](size_type node) {\n\
    \    assert(node < size());\n    return graph[node];\n  }\n\n  const_reference\
    \ &operator[](size_type node) const {\n    assert(node < size());\n    return\
    \ graph[node];\n  }\n\n  class const_iterator : public container_type::const_iterator\
    \ {\n   public:\n    using base = typename container_type::const_iterator;\n \
    \   using const_reference = const adjacency &;\n    using const_pointer = const\
    \ adjacency *;\n\n    const_iterator(base const &__i) : base(__i) {}\n\n    const_pointer\
    \ operator->() const { return base::operator->(); }\n\n    const_reference operator*()\
    \ const { return base::operator*(); }\n  };\n\n  auto begin() const { return const_iterator{graph.begin()};\
    \ }\n  auto end() const { return const_iterator{graph.end()}; }\n\n  size_type\
    \ add_node() { return add_nodes(1).front(); }\n\n  virtual std::vector<size_type>\
    \ add_nodes(size_type __n) {\n    std::vector<size_type> __nds(__n);\n    std::iota(__nds.begin(),\
    \ __nds.end(), graph.size());\n    __n += graph.size();\n    if (__n > graph.capacity())\
    \ {\n      flow_graph __x(__n);\n      for (auto &&adj : graph)\n        for (auto\
    \ &&__e : adj)\n          if (!__e.aux) __x._add_edge(__e);\n      graph = std::move(__x.graph);\n\
    \    } else\n      graph.resize(__n);\n    return __nds;\n  }\n\n  /**\n   * @brief\
    \ Add an directed edge to the graph. The default capacity is 1.\n   *\n   * @return\
    \ Reference to the edge.\n   */\n  template <class... Args> const edge &add_edge(Args\
    \ &&... args) {\n    return *_add_edge(edge(args...));\n  }\n\n  /**\n   * @brief\
    \ Add an undirected edge to the graph. The default capacity is 1.\n   *\n   *\
    \ @return Reference to the edge.\n   */\n  template <class... Args> const edge\
    \ &add_undirected_edge(Args &&... args) {\n    return *_add_ud_edge(edge(args...));\n\
    \  }\n\n protected:\n  template <class... Args> edge_impl *_add_edge(Args &&...\
    \ args) {\n    edge_impl __e(args...);\n    assert(__e.src < size());\n    assert(__e.dst\
    \ < size());\n    auto __p = graph[__e.src].emplace(__e);\n    __p->rev = graph[__e.dst].emplace(__p->rev_cp());\n\
    \    return __p;\n  }\n\n  template <class... Args> edge_impl *_add_ud_edge(Args\
    \ &&... args) {\n    edge_impl __e(args...);\n    assert(__e.src < size());\n\
    \    assert(__e.dst < size());\n    auto __p = graph[__e.src].emplace(__e);\n\
    \    __p->rev = graph[__e.dst].emplace(__p->ud_rev_cp());\n    return __p;\n \
    \ }\n\n  constexpr static size_type nil = -1;\n  container_type graph;\n\n  template\
    \ <class Os> friend Os &operator<<(Os &__os, flow_graph const &__g) {\n    for\
    \ (const auto &adj : __g)\n      for (const auto &e : adj) __os << e << \"\\n\"\
    ;\n    return __os;\n  }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file base.hpp\n * @brief Flow Graph\n * @date 2021-01-15\n\
    \ *\n *\n */\n\n#include <cassert>\n#include <numeric>\n#include <vector>\n\n\
    namespace workspace {\n\ntemplate <class Cap, class Cost = void> class flow_graph\
    \ {\n protected:\n  class adjacency_impl;\n\n public:\n  using container_type\
    \ = std::vector<adjacency_impl>;\n  using size_type = typename container_type::size_type;\n\
    \n  class unweighted_edge {\n   public:\n    size_type src, dst;\n    Cap cap;\n\
    \n    unweighted_edge(size_type src, size_type dst, const Cap &cap = 1)\n    \
    \    : src(src), dst(dst), cap(cap) {\n      assert(!(cap < static_cast<Cap>(0)));\n\
    \    }\n\n    template <class Os>\n    friend Os &operator<<(Os &__os, unweighted_edge\
    \ const &__e) {\n      return __os << __e.src << \" \" << __e.dst << \" \" <<\
    \ __e.cap;\n    }\n\n   protected:\n    unweighted_edge() = default;\n\n    unweighted_edge\
    \ make_rev() const { return {dst, src, 0}; }\n\n    unweighted_edge make_ud_rev()\
    \ const { return {dst, src, cap}; }\n  };\n\n  class weighted_edge : public unweighted_edge\
    \ {\n   public:\n    Cost cost;\n\n    weighted_edge(const unweighted_edge &__e,\
    \ const Cost &__c)\n        : unweighted_edge(__e), cost(__c) {}\n\n    weighted_edge(size_type\
    \ src, size_type dst, const Cap &cap,\n                  const Cost &cost)\n \
    \       : unweighted_edge(src, dst, cap), cost(cost) {}\n\n    template <class\
    \ Os>\n    friend Os &operator<<(Os &__os, weighted_edge const &__e) {\n     \
    \ return __os << static_cast<unweighted_edge>(__e) << \" \" << __e.cost;\n   \
    \ }\n\n   protected:\n    weighted_edge() = default;\n\n    weighted_edge make_rev()\
    \ const {\n      return {unweighted_edge::make_rev(), -cost};\n    }\n\n    weighted_edge\
    \ make_ud_rev() const {\n      return {unweighted_edge::make_ud_rev(), -cost};\n\
    \    }\n  };\n\n  using edge = typename std::conditional<std::is_void<Cost>::value,\n\
    \                                         unweighted_edge, weighted_edge>::type;\n\
    \n protected:\n  struct edge_impl : edge {\n    bool aux = false;\n    edge_impl\
    \ *rev = nullptr;\n\n    edge_impl() = default;\n\n    edge_impl(const edge_impl\
    \ &__e) = default;\n\n    edge_impl(const edge &__e) : edge(__e) {}\n\n    void\
    \ flow(const Cap &__f) { edge::cap -= __f, rev->cap += __f; }\n\n    edge_impl\
    \ rev_cp() {\n      edge_impl __e;\n      if (rev)\n        __e = *rev;\n    \
    \  else {\n        __e = edge::make_rev();\n        __e.aux = true;\n      }\n\
    \      __e.rev = this;\n      return __e;\n    }\n\n    edge_impl ud_rev_cp()\
    \ {\n      edge_impl __e = rev ? *rev : edge::make_ud_rev();\n      __e.rev =\
    \ this;\n      return __e;\n    }\n  };\n\n public:\n  class adjacency {\n   public:\n\
    \    using value_type = edge;\n    using reference = edge &;\n    using const_reference\
    \ = edge const &;\n    using pointer = edge *;\n    using const_pointer = const\
    \ edge *;\n\n    class const_iterator {\n     public:\n      const edge_impl *__p;\n\
    \n      bool operator!=(const_iterator const &__x) const {\n        return __p\
    \ != __x.__p;\n      }\n\n      const_iterator &operator++() {\n        do\n \
    \         ++__p;\n        while (__p->rev && __p->aux);\n        return *this;\n\
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
    \ for (auto &&__e : __adj) _add_edge(__e);\n  }\n\n  /**\n   * @brief Construct\
    \ a new flow graph object\n   *\n   * @param __x Rvalue reference to another object\n\
    \   */\n  flow_graph(flow_graph &&__x) : graph(std::move(__x.graph)) {}\n\n  /**\n\
    \   * @brief Assignment operator.\n   *\n   * @param __x Const reference to another\
    \ object\n   * @return Reference to this object.\n   */\n  flow_graph &operator=(const\
    \ flow_graph &__x) {\n    return operator=(std::move(flow_graph{__x}));\n  }\n\
    \n  /**\n   * @brief Assignment operator.\n   *\n   * @param __x Rvalue reference\
    \ to another object\n   * @return Reference to this object.\n   */\n  flow_graph\
    \ &operator=(flow_graph &&__x) {\n    graph = std::move(__x.graph);\n    return\
    \ *this;\n  }\n\n  /**\n   * @return Number of nodes.\n   */\n  size_type size()\
    \ const { return graph.size(); }\n\n  reference operator[](size_type node) {\n\
    \    assert(node < size());\n    return graph[node];\n  }\n\n  const_reference\
    \ &operator[](size_type node) const {\n    assert(node < size());\n    return\
    \ graph[node];\n  }\n\n  class const_iterator : public container_type::const_iterator\
    \ {\n   public:\n    using base = typename container_type::const_iterator;\n \
    \   using const_reference = const adjacency &;\n    using const_pointer = const\
    \ adjacency *;\n\n    const_iterator(base const &__i) : base(__i) {}\n\n    const_pointer\
    \ operator->() const { return base::operator->(); }\n\n    const_reference operator*()\
    \ const { return base::operator*(); }\n  };\n\n  auto begin() const { return const_iterator{graph.begin()};\
    \ }\n  auto end() const { return const_iterator{graph.end()}; }\n\n  size_type\
    \ add_node() { return add_nodes(1).front(); }\n\n  virtual std::vector<size_type>\
    \ add_nodes(size_type __n) {\n    std::vector<size_type> __nds(__n);\n    std::iota(__nds.begin(),\
    \ __nds.end(), graph.size());\n    __n += graph.size();\n    if (__n > graph.capacity())\
    \ {\n      flow_graph __x(__n);\n      for (auto &&adj : graph)\n        for (auto\
    \ &&__e : adj)\n          if (!__e.aux) __x._add_edge(__e);\n      graph = std::move(__x.graph);\n\
    \    } else\n      graph.resize(__n);\n    return __nds;\n  }\n\n  /**\n   * @brief\
    \ Add an directed edge to the graph. The default capacity is 1.\n   *\n   * @return\
    \ Reference to the edge.\n   */\n  template <class... Args> const edge &add_edge(Args\
    \ &&... args) {\n    return *_add_edge(edge(args...));\n  }\n\n  /**\n   * @brief\
    \ Add an undirected edge to the graph. The default capacity is 1.\n   *\n   *\
    \ @return Reference to the edge.\n   */\n  template <class... Args> const edge\
    \ &add_undirected_edge(Args &&... args) {\n    return *_add_ud_edge(edge(args...));\n\
    \  }\n\n protected:\n  template <class... Args> edge_impl *_add_edge(Args &&...\
    \ args) {\n    edge_impl __e(args...);\n    assert(__e.src < size());\n    assert(__e.dst\
    \ < size());\n    auto __p = graph[__e.src].emplace(__e);\n    __p->rev = graph[__e.dst].emplace(__p->rev_cp());\n\
    \    return __p;\n  }\n\n  template <class... Args> edge_impl *_add_ud_edge(Args\
    \ &&... args) {\n    edge_impl __e(args...);\n    assert(__e.src < size());\n\
    \    assert(__e.dst < size());\n    auto __p = graph[__e.src].emplace(__e);\n\
    \    __p->rev = graph[__e.dst].emplace(__p->ud_rev_cp());\n    return __p;\n \
    \ }\n\n  constexpr static size_type nil = -1;\n  container_type graph;\n\n  template\
    \ <class Os> friend Os &operator<<(Os &__os, flow_graph const &__g) {\n    for\
    \ (const auto &adj : __g)\n      for (const auto &e : adj) __os << e << \"\\n\"\
    ;\n    return __os;\n  }\n};\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/graph/directed/flow/base.hpp
  requiredBy:
  - src/graph/directed/flow/min_cost_flow.hpp
  - src/graph/directed/flow/Dinic.hpp
  timestamp: '2021-01-21 02:26:42+09:00'
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
