---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/graph/base.h
    title: Base
  - icon: ':heavy_check_mark:'
    path: src/graph/edge.h
    title: Edge
  - icon: ':heavy_check_mark:'
    path: src/graph/queue.h
    title: Queue
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: src/graph/scc.h
    title: Strongly Connected Component
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/GRL_1_A.test.cpp
    title: test/aizu-online-judge/GRL_1_A.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/GRL_3_C.test.cpp
    title: test/aizu-online-judge/GRL_3_C.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/GRL_4_A.test.cpp
    title: test/aizu-online-judge/GRL_4_A.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/scc.test.cpp
    title: test/library-checker/scc.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/shortest_path.test.cpp
    title: test/library-checker/shortest_path.test.cpp
  _isVerificationFailed: false
  _pathExtension: h
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Digraph
    links: []
  bundledCode: "#line 2 \"src/graph/digraph.h\"\n\n/**\n * @file digraph.h\n * @brief\
    \ Digraph\n */\n\n#line 2 \"src/graph/base.h\"\n\n/**\n * @file base.h\n * @brief\
    \ Base\n */\n\n#include <algorithm>\n#include <cassert>\n#include <list>\n#include\
    \ <numeric>\n#include <vector>\n\n#line 2 \"src/graph/edge.h\"\n\n/**\n * @file\
    \ edge.h\n * @brief Edge\n */\n\n#line 2 \"lib/cxx17\"\n\n#line 2 \"lib/cxx14\"\
    \n\n#ifndef _CXX14_CONSTEXPR\n#if __cplusplus >= 201402L\n#define _CXX14_CONSTEXPR\
    \ constexpr\n#else\n#define _CXX14_CONSTEXPR\n#endif\n#endif\n#line 4 \"lib/cxx17\"\
    \n\n#ifndef _CXX17_CONSTEXPR\n#if __cplusplus >= 201703L\n#define _CXX17_CONSTEXPR\
    \ constexpr\n#else\n#define _CXX17_CONSTEXPR\n#endif\n#endif\n\n#ifndef _CXX17_STATIC_ASSERT\n\
    #if __cplusplus >= 201703L\n#define _CXX17_STATIC_ASSERT static_assert\n#else\n\
    #define _CXX17_STATIC_ASSERT assert\n#endif\n#endif\n\n#include <iterator>\n\n\
    #if __cplusplus < 201703L\n\nnamespace std {\n\n/**\n *  @brief  Return the size\
    \ of a container.\n *  @param  __cont  Container.\n */\ntemplate <typename _Container>\n\
    constexpr auto size(const _Container& __cont) noexcept(noexcept(__cont.size()))\n\
    \    -> decltype(__cont.size()) {\n  return __cont.size();\n}\n\n/**\n *  @brief\
    \  Return the size of an array.\n */\ntemplate <typename _Tp, size_t _Nm>\nconstexpr\
    \ size_t size(const _Tp (&)[_Nm]) noexcept {\n  return _Nm;\n}\n\n/**\n *  @brief\
    \  Return whether a container is empty.\n *  @param  __cont  Container.\n */\n\
    template <typename _Container>\n[[nodiscard]] constexpr auto empty(const _Container&\
    \ __cont) noexcept(\n    noexcept(__cont.empty())) -> decltype(__cont.empty())\
    \ {\n  return __cont.empty();\n}\n\n/**\n *  @brief  Return whether an array is\
    \ empty (always false).\n */\ntemplate <typename _Tp, size_t _Nm>\n[[nodiscard]]\
    \ constexpr bool empty(const _Tp (&)[_Nm]) noexcept {\n  return false;\n}\n\n\
    /**\n *  @brief  Return whether an initializer_list is empty.\n *  @param  __il\
    \  Initializer list.\n */\ntemplate <typename _Tp>\n[[nodiscard]] constexpr bool\
    \ empty(initializer_list<_Tp> __il) noexcept {\n  return __il.size() == 0;\n}\n\
    \nstruct monostate {};\n\n}  // namespace std\n\n#else\n\n#include <variant>\n\
    \n#endif\n#line 9 \"src/graph/edge.h\"\n\nnamespace workspace {\n\nnamespace _graph_impl\
    \ {\n\n// Default edge attribute.\nstruct null {};\n\n}  // namespace _graph_impl\n\
    \ntemplate <class _Weight, class _Attr = _graph_impl::null>\nstruct weighted_edge\
    \ : _Attr {\n  using attribute = _Attr;\n  using value_type = _Weight;\n  using\
    \ node_type = size_t;\n\n  node_type tail, head;\n  value_type weight{};\n\n \
    \ constexpr weighted_edge() = default;\n\n  template <class... _Args>\n  constexpr\
    \ weighted_edge(node_type __u, node_type __v, value_type __c = 0,\n          \
    \                _Args &&...__args) noexcept\n      : _Attr{std::forward<_Args>(__args)...},\n\
    \        tail(__u),\n        head(__v),\n        weight(__c) {}\n\n  constexpr\
    \ bool operator<(const weighted_edge &__e) const noexcept {\n    return weight\
    \ < __e.weight;\n  }\n  constexpr bool operator<=(const weighted_edge &__e) const\
    \ noexcept {\n    return weight <= __e.weight;\n  }\n  constexpr bool operator>(const\
    \ weighted_edge &__e) const noexcept {\n    return weight > __e.weight;\n  }\n\
    \  constexpr bool operator>=(const weighted_edge &__e) const noexcept {\n    return\
    \ weight >= __e.weight;\n  }\n};\n\ntemplate <class _Attr = _graph_impl::null>\n\
    struct edge : weighted_edge<int, _Attr> {\n  using base_type = weighted_edge<int,\
    \ _Attr>;\n\n  using typename base_type::node_type;\n  using base_type::operator<;\n\
    \  using base_type::operator>;\n\n  constexpr edge() = default;\n\n  template\
    \ <class... _Args>\n  constexpr edge(node_type __u, node_type __v, _Args &&...__args)\
    \ noexcept\n      : base_type(__u, __v, __u != __v, std::forward<_Args>(__args)...)\
    \ {}\n};\n\ntemplate <size_t _Nm, class _Attr>\nconstexpr std::tuple_element_t<_Nm,\
    \ edge<_Attr>> &get(\n    edge<_Attr> &__e) noexcept {\n  if _CXX17_CONSTEXPR\
    \ (_Nm > 1)\n    return __e;\n  else if _CXX17_CONSTEXPR (_Nm)\n    return __e.head;\n\
    \  else\n    return __e.tail;\n}\n\ntemplate <size_t _Nm, class _Attr>\nconstexpr\
    \ const std::tuple_element_t<_Nm, edge<_Attr>> &get(\n    const edge<_Attr> &__e)\
    \ noexcept {\n  if _CXX17_CONSTEXPR (_Nm > 1)\n    return __e;\n  else if _CXX17_CONSTEXPR\
    \ (_Nm)\n    return __e.head;\n  else\n    return __e.tail;\n}\n\ntemplate <size_t\
    \ _Nm, class _Attr>\nconstexpr std::tuple_element_t<_Nm, edge<_Attr>> &&get(\n\
    \    edge<_Attr> &&__e) noexcept {\n  return std::move(get<_Nm>(__e));\n}\n\n\
    template <size_t _Nm, class _Weight, class _Attr>\nconstexpr const std::tuple_element_t<_Nm,\
    \ weighted_edge<_Weight, _Attr>> &get(\n    const weighted_edge<_Weight, _Attr>\
    \ &__e) noexcept {\n  if _CXX17_CONSTEXPR (_Nm > 2)\n    return __e;\n  else if\
    \ _CXX17_CONSTEXPR (_Nm > 1)\n    return __e.weight;\n  else if _CXX17_CONSTEXPR\
    \ (_Nm)\n    return __e.head;\n  else\n    return __e.tail;\n}\n\ntemplate <size_t\
    \ _Nm, class _Weight, class _Attr>\nconstexpr std::tuple_element_t<_Nm, weighted_edge<_Weight,\
    \ _Attr>> &get(\n    weighted_edge<_Weight, _Attr> &__e) noexcept {\n  if _CXX17_CONSTEXPR\
    \ (_Nm > 2)\n    return __e;\n  else if _CXX17_CONSTEXPR (_Nm > 1)\n    return\
    \ __e.weight;\n  else if _CXX17_CONSTEXPR (_Nm)\n    return __e.head;\n  else\n\
    \    return __e.tail;\n}\n\ntemplate <size_t _Nm, class _Weight, class _Attr>\n\
    constexpr std::tuple_element_t<_Nm, weighted_edge<_Weight, _Attr>> &&get(\n  \
    \  weighted_edge<_Weight, _Attr> &&__e) noexcept {\n  return std::move(get<_Nm>(__e));\n\
    }\n\n}  // namespace workspace\n\nnamespace std {\n\ntemplate <class _Attr>\n\
    struct tuple_size<workspace::edge<_Attr>> : integral_constant<size_t, 3> {};\n\
    \ntemplate <>\nstruct tuple_size<workspace::edge<>> : integral_constant<size_t,\
    \ 2> {};\n\ntemplate <class _Weight, class _Attr>\nstruct tuple_size<workspace::weighted_edge<_Weight,\
    \ _Attr>>\n    : integral_constant<size_t, 4> {};\n\ntemplate <class _Weight>\n\
    struct tuple_size<workspace::weighted_edge<_Weight>>\n    : integral_constant<size_t,\
    \ 3> {};\n\ntemplate <size_t _Nm, class _Attr>\nstruct tuple_element<_Nm, workspace::edge<_Attr>>\
    \ {\n  using type = std::conditional_t<(_Nm < 2), size_t, _Attr>;\n};\n\ntemplate\
    \ <size_t _Nm, class _Weight, class _Attr>\nstruct tuple_element<_Nm, workspace::weighted_edge<_Weight,\
    \ _Attr>> {\n  using type = std::conditional_t<(_Nm < 2), size_t,\n          \
    \                        std::conditional_t<_Nm == 2, _Weight, _Attr>>;\n};\n\n\
    }  // namespace std\n#line 2 \"src/graph/queue.h\"\n\n/**\n * @file queue.h\n\
    \ * @brief Queue\n */\n\n#include <queue>\n#include <stack>\n\nnamespace workspace\
    \ {\n\nnamespace _graph_impl {\n\ntemplate <class _Base, class = void> struct\
    \ stl_queue : _Base {\n  auto pop() noexcept {\n    auto __tmp = std::move(_Base::front());\n\
    \    _Base::pop();\n    return __tmp;\n  }\n};\n\ntemplate <class _Base>\nstruct\
    \ stl_queue<_Base, std::__void_t<decltype(std::declval<_Base>().top())>>\n   \
    \ : _Base {\n  auto pop() noexcept {\n    auto __tmp = std::move(_Base::top());\n\
    \    _Base::pop();\n    return __tmp;\n  }\n};\n\n}  // namespace _graph_impl\n\
    \n}  // namespace workspace\n#line 16 \"src/graph/base.h\"\n\nnamespace workspace\
    \ {\n\ntemplate <class _Attr = _graph_impl::null,\n          class _List = std::vector<edge<_Attr>>>\n\
    class graph_base : public std::vector<_List> {\n public:\n  using container_type\
    \ = std::vector<_List>;\n  using typename container_type::size_type;\n\n  using\
    \ container_type::size;\n  using container_type::operator[];\n\n  using node_type\
    \ = size_type;\n  using edge_type = typename _List::value_type;\n  using weight_type\
    \ = typename edge_type::value_type;\n\n  graph_base(size_type __n = 0) : container_type(__n)\
    \ {}\n\n  /**\n   * @brief Add some nodes to the graph.\n   * @param __n Number\
    \ of nodes added\n   * @return List of indices of the nodes.\n   */\n  auto add_nodes(size_type\
    \ __n) noexcept {\n    std::vector<node_type> __ret(__n);\n    std::iota(__ret.begin(),\
    \ __ret.end(), size());\n    container_type::resize(__n + size());\n    return\
    \ __ret;\n  }\n\n  node_type add_node() noexcept { return add_nodes(1).front();\
    \ }\n\n  template <class... _Args>\n  decltype(auto) add_edge(node_type __u, node_type\
    \ __v,\n                          _Args &&...__args) noexcept {\n    assert(__u\
    \ < size()), assert(__v < size());\n    return operator[](__u).emplace_back(__u,\
    \ __v,\n                                        std::forward<_Args>(__args)...)\n\
    \n#if __cplusplus <= 201402L\n               ,\n               operator[](__u).back()\n\
    #endif\n        ;\n  }\n\n  decltype(auto) add_edge(const edge_type &__e) noexcept\
    \ {\n    assert(__e.tail < size()), assert(__e.head < size());\n    return operator[](__e.tail).emplace_back(__e)\n\
    #if __cplusplus <= 201402L\n               ,\n               operator[](__e.tail).back()\n\
    #endif\n        ;\n  }\n\n  /**\n   * @brief Single-source DFS.\n   * @return\
    \ Edges of DFS-tree in the search order.\n   */\n  decltype(auto) dfs(node_type\
    \ __r) const noexcept {\n    node_type __a[]{__r};\n    return dfs(__a, __a +\
    \ 1);\n  }\n\n  /**\n   * @brief Multi-source DFS.\n   * @return Edges of DFS-tree\
    \ in the search order.\n   */\n  template <class _Iterator>\n  decltype(auto)\
    \ dfs(_Iterator __first, _Iterator __last) const noexcept {\n    return search<std::stack<edge_type,\
    \ std::vector<edge_type>>>(__first,\n                                        \
    \                         __last);\n  }\n\n  /**\n   * @brief Single-source DFS\
    \ in the complement graph.\n   * @return Edges of DFS-tree in the search order.\n\
    \   */\n  decltype(auto) compl_dfs(node_type __r) const noexcept {\n    node_type\
    \ __a[]{__r};\n    return compl_dfs(__a, __a + 1);\n  }\n\n  /**\n   * @brief\
    \ Multi-source DFS in the complement graph.\n   * @return Edges of DFS-tree in\
    \ the search order.\n   */\n  template <class _Iterator>\n  decltype(auto) compl_dfs(_Iterator\
    \ __first, _Iterator __last) const noexcept {\n    return compl_search<std::stack<edge_type,\
    \ std::vector<edge_type>>>(__first,\n                                        \
    \                               __last);\n  }\n\n  /**\n   * @brief Single-source\
    \ BFS.\n   * @return Edges of BFS-tree in the search order.\n   */\n  decltype(auto)\
    \ bfs(node_type __r) const noexcept {\n    node_type __a[]{__r};\n    return bfs(__a,\
    \ __a + 1);\n  }\n\n  /**\n   * @brief Multi-source BFS.\n   * @return Edges of\
    \ BFS-tree in the search order.\n   */\n  template <class _Iterator>\n  decltype(auto)\
    \ bfs(_Iterator __first, _Iterator __last) const noexcept {\n    return search<std::queue<edge_type>>(__first,\
    \ __last);\n  }\n\n  /**\n   * @brief Single-source BFS in the complement graph.\n\
    \   * @return Edges of BFS-tree in the search order.\n   */\n  decltype(auto)\
    \ compl_bfs(node_type __r) const noexcept {\n    node_type __a[]{__r};\n    return\
    \ compl_bfs(__a, __a + 1);\n  }\n\n  /**\n   * @brief Multi-source BFS in the\
    \ complement graph.\n   * @return Edges of BFS-tree in the search order.\n   */\n\
    \  template <class _Iterator>\n  decltype(auto) compl_bfs(_Iterator __first, _Iterator\
    \ __last) const noexcept {\n    return compl_search<std::queue<edge_type>>(__first,\
    \ __last);\n  }\n\n  /**\n   * @brief Single-source Dijkstra's algorithm.\n  \
    \ * @return Edges of shortest path tree in the search order.\n   */\n  decltype(auto)\
    \ dijkstra(node_type __r) const noexcept {\n    node_type __a[]{__r};\n    return\
    \ dijkstra(__a, __a + 1);\n  }\n\n  /**\n   * @brief Multi-source Dijkstra's algorithm.\n\
    \   * @return Edges of shortest path tree in the search order.\n   */\n  template\
    \ <class _Iterator>\n  decltype(auto) dijkstra(_Iterator __first, _Iterator __last)\
    \ const noexcept {\n    return distance_from<std::priority_queue<edge_type, std::vector<edge_type>,\n\
    \                                             std::greater<edge_type>>>(__first,\n\
    \                                                                       __last);\n\
    \  }\n\n  /**\n   * @brief Single-source Bellman-Ford algorithm.\n   * @return\
    \ Edges of shortest path tree in the search order.\n   */\n  decltype(auto) bellman_ford()\
    \ const noexcept {\n    std::vector<node_type> __a(size());\n    return bellman_ford(__a.begin(),\
    \ __a.end());\n  }\n\n  /**\n   * @brief Multi-source Bellman-Ford algorithm.\n\
    \   * @return Edges of shortest path tree in the search order.\n   */\n  decltype(auto)\
    \ bellman_ford(node_type __r) const noexcept {\n    node_type __a[]{__r};\n  \
    \  return bellman_ford(__a, __a + 1);\n  }\n\n  template <class _Iterator>\n \
    \ decltype(auto) bellman_ford(_Iterator __first,\n                           \
    \   _Iterator __last) const noexcept {\n    return distance_from<std::queue<edge_type>>(__first,\
    \ __last);\n  }\n\n  decltype(auto) warshall_floyd(node_type __r) const noexcept;\n\
    \n protected:\n  /**\n   * @brief Search from given vertex set.\n   * @tparam\
    \ _Container Queue.\n   */\n  template <class _Container, class _Iterator>\n \
    \ auto search(_Iterator __first, _Iterator __last) const noexcept {\n    static\
    \ std::vector<int_fast8_t> __visited;\n    __visited.resize(size());\n\n    std::vector<edge_type>\
    \ __tree;\n    static _graph_impl::stl_queue<_Container> __queue;\n\n    for (auto\
    \ __s = __first; __s != __last; __visited[*__s++] = true)\n      for (auto &&__e\
    \ : operator[](*__s)) __queue.emplace(__e);\n\n    while (!__queue.empty()) {\n\
    \      auto &&__p = __queue.pop();\n\n      if (__visited[__p.head]) continue;\n\
    \      __visited[__p.head] = true;\n\n      for (auto &&__e : operator[](__p.head))\
    \ __queue.emplace(__e);\n      __tree.emplace_back(std::move(__p));\n    }\n\n\
    \    while (__first != __last) __visited[*__first++] = false;\n    for (auto &&__e\
    \ : __tree) __visited[__e.head] = false;\n\n    return __tree;\n  }\n\n  template\
    \ <class _Container, class _Iterator>\n  auto compl_search(_Iterator __first,\
    \ _Iterator __last) const noexcept;\n\n  /**\n   * @brief Get distance from given\
    \ vertex set.\n   * @tparam _Container Queue.\n   */\n  template <class _Container,\
    \ class _Iterator>\n  auto distance_from(_Iterator __first, _Iterator __last)\
    \ const noexcept {\n    struct dist_type {\n      bool nil = true;\n      weight_type\
    \ value;\n\n      bool update(const weight_type &__x) noexcept {\n        return\
    \ nil || __x < value ? nil = false, value = __x, true : false;\n      }\n    };\n\
    \n    static _graph_impl::stl_queue<_Container> __queue;\n\n    static std::vector<dist_type>\
    \ __dist;\n    __dist.resize(size());\n\n    std::vector<edge_type> __tree;\n\n\
    \    for (; __first != __last; ++__first) __queue.emplace(*__first, *__first);\n\
    \n    while (!__queue.empty()) {\n      auto &&__p = __queue.pop();\n\n      if\
    \ (__dist[__p.head].update(__p.weight)) {\n        for (auto __e : operator[](__p.head))\n\
    \          __e.weight = __p.weight + __e.weight, __queue.emplace(std::move(__e));\n\
    \n        if (__p.tail != __p.head) __tree.emplace_back(std::move(__p));\n   \
    \   }\n    }\n\n    for (auto &&__e : __tree)\n      __dist[__e.head].nil = __dist[__e.tail].nil\
    \ = true;\n\n    __tree.erase(std::remove_if(__tree.begin(), __tree.end(),\n \
    \                               [&](auto &&__e) {\n                          \
    \        return __dist[__e.head].value < __e.weight;\n                       \
    \         }),\n                 __tree.end());\n\n    return __tree;\n  }\n};\n\
    \n}  // namespace workspace\n#line 9 \"src/graph/digraph.h\"\n\nnamespace workspace\
    \ {\n\ntemplate <class _Attr = _graph_impl::null,\n          class _List = std::vector<edge<_Attr>>>\n\
    class digraph : public graph_base<_Attr, _List> {\n public:\n  using base_type\
    \ = graph_base<_Attr, _List>;\n\n  using typename base_type::edge_type;\n  using\
    \ typename base_type::node_type;\n  using typename base_type::size_type;\n\n \
    \ using base_type::size;\n  using base_type::operator[];\n\n  digraph(size_type\
    \ __n = 0) : base_type(__n) {}\n\n  auto scc() const noexcept;\n};\n\ntemplate\
    \ <class _Weight, class _Attr = _graph_impl::null,\n          class _List = std::vector<weighted_edge<_Weight,\
    \ _Attr>>>\nusing weighted_digraph = digraph<_Attr, _List>;\n\n}  // namespace\
    \ workspace\n"
  code: "#pragma once\n\n/**\n * @file digraph.h\n * @brief Digraph\n */\n\n#include\
    \ \"base.h\"\n\nnamespace workspace {\n\ntemplate <class _Attr = _graph_impl::null,\n\
    \          class _List = std::vector<edge<_Attr>>>\nclass digraph : public graph_base<_Attr,\
    \ _List> {\n public:\n  using base_type = graph_base<_Attr, _List>;\n\n  using\
    \ typename base_type::edge_type;\n  using typename base_type::node_type;\n  using\
    \ typename base_type::size_type;\n\n  using base_type::size;\n  using base_type::operator[];\n\
    \n  digraph(size_type __n = 0) : base_type(__n) {}\n\n  auto scc() const noexcept;\n\
    };\n\ntemplate <class _Weight, class _Attr = _graph_impl::null,\n          class\
    \ _List = std::vector<weighted_edge<_Weight, _Attr>>>\nusing weighted_digraph\
    \ = digraph<_Attr, _List>;\n\n}  // namespace workspace\n"
  dependsOn:
  - src/graph/base.h
  - src/graph/edge.h
  - src/graph/queue.h
  isVerificationFile: false
  path: src/graph/digraph.h
  requiredBy:
  - src/graph/scc.h
  timestamp: '2021-11-30 17:55:32+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/scc.test.cpp
  - test/library-checker/shortest_path.test.cpp
  - test/aizu-online-judge/GRL_1_A.test.cpp
  - test/aizu-online-judge/GRL_3_C.test.cpp
  - test/aizu-online-judge/GRL_4_A.test.cpp
documentation_of: src/graph/digraph.h
layout: document
redirect_from:
- /library/src/graph/digraph.h
- /library/src/graph/digraph.h.html
title: Digraph
---
