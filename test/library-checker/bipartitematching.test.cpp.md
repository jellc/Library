---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/graph/directed/flow/Dinic.hpp
    title: Dinic's Algorithm
  - icon: ':heavy_check_mark:'
    path: src/graph/directed/flow/base.hpp
    title: Flow Graph
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/bipartitematching
    links:
    - https://judge.yosupo.jp/problem/bipartitematching
  bundledCode: "#line 1 \"test/library-checker/bipartitematching.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/bipartitematching\"\n\n#include <cstdio>\n\
    \n#line 2 \"src/graph/directed/flow/Dinic.hpp\"\n\n/**\n * @file Dinic.hpp\n *\
    \ @brief Dinic's Algorithm\n * @date 2021-01-15\n *\n *\n */\n\n#line 2 \"src/graph/directed/flow/base.hpp\"\
    \n\n/**\n * @file base.hpp\n * @brief Flow Graph\n * @date 2021-01-15\n *\n *\n\
    \ */\n\n#include <cassert>\n#include <numeric>\n#include <vector>\n\nnamespace\
    \ workspace {\n\ntemplate <class Cap, class Cost = void> class flow_graph {\n\
    \ protected:\n  class adjacency_impl;\n\n public:\n  using container_type = std::vector<adjacency_impl>;\n\
    \  using size_type = typename container_type::size_type;\n\n  class unweighted_edge\
    \ {\n   public:\n    size_type src, dst;\n    Cap cap;\n\n    unweighted_edge()\
    \ = default;\n\n    unweighted_edge(size_type src, size_type dst, const Cap &cap)\n\
    \        : src(src), dst(dst), cap(cap) {\n      assert(!(cap < static_cast<Cap>(0)));\n\
    \    }\n\n    template <class Os>\n    friend Os &operator<<(Os &__os, unweighted_edge\
    \ const &__e) {\n      return __os << __e.src << \" \" << __e.dst << \" \" <<\
    \ __e.cap;\n    }\n\n   protected:\n    unweighted_edge make_rev() { return {dst,\
    \ src, 0}; }\n  };\n\n  class weighted_edge : public unweighted_edge {\n   public:\n\
    \    Cost cost;\n\n    weighted_edge() = default;\n\n    weighted_edge(size_type\
    \ src, size_type dst, const Cap &cap,\n                  const Cost &cost)\n \
    \       : unweighted_edge(src, dst, cap), cost(cost) {}\n\n    template <class\
    \ Os>\n    friend Os &operator<<(Os &__os, weighted_edge const &__e) {\n     \
    \ return __os << static_cast<unweighted_edge>(__e) << \" \" << __e.cost;\n   \
    \ }\n\n   protected:\n    weighted_edge make_rev() {\n      return {unweighted_edge::dst,\
    \ unweighted_edge::src, 0, -cost};\n    }\n  };\n\n  using edge = typename std::conditional<std::is_void<Cost>::value,\n\
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
    \ 12 \"src/graph/directed/flow/Dinic.hpp\"\n\nnamespace workspace {\n\n/**\n *\
    \ @brief Compute the maximum flow.\n *\n * @tparam Cap Capacity type\n */\ntemplate\
    \ <class Cap> class Dinic : public flow_graph<Cap> {\n  using base = flow_graph<Cap>;\n\
    \  using base::nil;\n\n public:\n  using size_type = typename base::size_type;\n\
    \n protected:\n  std::vector<size_type> level;\n  std::vector<typename base::container_type::value_type::iterator>\
    \ iter;\n\n  Cap dfs(size_type src, size_type dst, Cap bound) {\n    if (src ==\
    \ dst || bound == 0) return bound;\n    Cap flow(0);\n    for (auto &e{iter[dst]};\
    \ e != base::graph[dst].end(); ++e)\n      if (static_cast<Cap>(0) < e->rev->cap\
    \ && level[e->dst] < level[dst])\n        if (Cap achv = dfs(src, e->dst, std::min(bound,\
    \ e->rev->cap));\n            achv > 0) {\n          e->rev->flow(achv);\n   \
    \       flow += achv, bound -= achv;\n          if (bound == 0) break;\n     \
    \   }\n    return flow;\n  }\n\n public:\n  /**\n   * @brief Construct a new Dinic\
    \ object\n   *\n   * @param __n Number of nodes\n   */\n  Dinic(size_type __n\
    \ = 0)\n      : base::flow_graph(__n), level(__n, nil), iter(__n) {}\n\n  std::vector<size_type>\
    \ add_nodes(size_type __n) override {\n    auto __nds = base::add_nodes(__n);\n\
    \    level.resize(base::size(), nil);\n    iter.resize(base::size());\n    return\
    \ __nds;\n  }\n\n  /**\n   * @brief Add an edge to the graph.\n   *\n   * @param\
    \ src Source\n   * @param dst Destination\n   * @param cap Capacity(defalut: 1)\n\
    \   * @return Reference to the edge.\n   */\n  typename base::edge const &add_edge(size_type\
    \ src, size_type dst,\n                                      const Cap &cap =\
    \ 1) {\n    return base::add_edge(src, dst, cap);\n  }\n\n  // void add_undirected_edge(size_type\
    \ src, size_type dst, Cap cap) {\n  //   base::add_undirected_edge(src, dst, cap,\
    \ false);\n  // }\n\n  /**\n   * @brief Run Dinic's algorithm.\n   *\n   * @param\
    \ src Source\n   * @param dst Destination\n   * @return Maximum flow.\n   */\n\
    \  Cap flow(size_type src, size_type dst) {\n    assert(src < base::size());\n\
    \    assert(dst < base::size());\n    Cap flow(0), bound(0);\n    for (const auto\
    \ &e : base::graph[src]) bound += e.cap;\n    for (std::vector<size_type> que(base::size());;\n\
    \         std::fill(level.begin(), level.end(), nil)) {\n      level[que.front()\
    \ = src] = 0;\n      for (auto ql{que.begin()}, qr{std::next(ql)};\n         \
    \  level[dst] == nil && ql != qr; ++ql)\n        for (const auto &e : base::graph[*ql])\n\
    \          if (static_cast<Cap>(0) < e.cap && level[e.dst] == nil)\n         \
    \   level[ *qr++ = e.dst] = level[*ql] + 1;\n      if (level[dst] == nil) break;\n\
    \      for (size_type node{}; node != base::size(); ++node)\n        iter[node]\
    \ = base::graph[node].begin();\n      flow += dfs(src, dst, bound);\n    }\n \
    \   return flow;\n  }\n};\n\n}  // namespace workspace\n#line 6 \"test/library-checker/bipartitematching.test.cpp\"\
    \n\nint main() {\n  using namespace workspace;\n\n  int l, r, m;\n  scanf(\"%d%d%d\"\
    , &l, &r, &m);\n  Dinic<int> dinic(l + r + 2);\n  const int s = l + r, t = s +\
    \ 1;\n\n  for (int i = 0, a, b; i < m; ++i) {\n    scanf(\"%d%d\", &a, &b);\n\
    \    dinic.add_edge(a, b + l);\n  }\n  for (int i = 0; i < l; ++i) {\n    dinic.add_edge(s,\
    \ i);\n  }\n  for (int i = 0; i < r; ++i) {\n    dinic.add_edge(i + l, t);\n \
    \ }\n\n  printf(\"%d\\n\", dinic.flow(s, t));\n\n  for (int i = 0; i < l; ++i)\
    \ {\n    for (const auto &e : dinic[i]) {\n      if (!e.cap) {\n        printf(\"\
    %d %d\\n\", i, e.dst - l);\n      }\n    }\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/bipartitematching\"\n\n\
    #include <cstdio>\n\n#include \"src/graph/directed/flow/Dinic.hpp\"\n\nint main()\
    \ {\n  using namespace workspace;\n\n  int l, r, m;\n  scanf(\"%d%d%d\", &l, &r,\
    \ &m);\n  Dinic<int> dinic(l + r + 2);\n  const int s = l + r, t = s + 1;\n\n\
    \  for (int i = 0, a, b; i < m; ++i) {\n    scanf(\"%d%d\", &a, &b);\n    dinic.add_edge(a,\
    \ b + l);\n  }\n  for (int i = 0; i < l; ++i) {\n    dinic.add_edge(s, i);\n \
    \ }\n  for (int i = 0; i < r; ++i) {\n    dinic.add_edge(i + l, t);\n  }\n\n \
    \ printf(\"%d\\n\", dinic.flow(s, t));\n\n  for (int i = 0; i < l; ++i) {\n  \
    \  for (const auto &e : dinic[i]) {\n      if (!e.cap) {\n        printf(\"%d\
    \ %d\\n\", i, e.dst - l);\n      }\n    }\n  }\n}\n"
  dependsOn:
  - src/graph/directed/flow/Dinic.hpp
  - src/graph/directed/flow/base.hpp
  isVerificationFile: true
  path: test/library-checker/bipartitematching.test.cpp
  requiredBy: []
  timestamp: '2021-01-19 16:21:33+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/bipartitematching.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/bipartitematching.test.cpp
- /verify/test/library-checker/bipartitematching.test.cpp.html
title: test/library-checker/bipartitematching.test.cpp
---
