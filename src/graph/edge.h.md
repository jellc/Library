---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: src/graph/base.h
    title: Base
  - icon: ':heavy_check_mark:'
    path: src/graph/digraph.h
    title: Digraph
  - icon: ':heavy_check_mark:'
    path: src/graph/forest.h
    title: Forest
  - icon: ':heavy_check_mark:'
    path: src/graph/graph.h
    title: Graph
  - icon: ':heavy_check_mark:'
    path: src/graph/scc.h
    title: Strongly Connected Component
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/GRL_1_A.test.cpp
    title: test/aizu-online-judge/GRL_1_A.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/GRL_2_A.test.cpp
    title: test/aizu-online-judge/GRL_2_A.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/GRL_3_C.test.cpp
    title: test/aizu-online-judge/GRL_3_C.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/GRL_4_A.test.cpp
    title: test/aizu-online-judge/GRL_4_A.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/GRL_5_A.test.cpp
    title: test/aizu-online-judge/GRL_5_A.test.cpp
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
    document_title: Edge
    links: []
  bundledCode: "#line 2 \"src/graph/edge.h\"\n\n/**\n * @file edge.h\n * @brief Edge\n\
    \ */\n\n#line 2 \"lib/cxx17\"\n\n#line 2 \"lib/cxx14\"\n\n#ifndef _CXX14_CONSTEXPR\n\
    #if __cplusplus >= 201402L\n#define _CXX14_CONSTEXPR constexpr\n#else\n#define\
    \ _CXX14_CONSTEXPR\n#endif\n#endif\n#line 4 \"lib/cxx17\"\n\n#ifndef _CXX17_CONSTEXPR\n\
    #if __cplusplus >= 201703L\n#define _CXX17_CONSTEXPR constexpr\n#else\n#define\
    \ _CXX17_CONSTEXPR\n#endif\n#endif\n\n#ifndef _CXX17_STATIC_ASSERT\n#if __cplusplus\
    \ >= 201703L\n#define _CXX17_STATIC_ASSERT static_assert\n#else\n#define _CXX17_STATIC_ASSERT\
    \ assert\n#endif\n#endif\n\n#include <iterator>\n\n#if __cplusplus < 201703L\n\
    \nnamespace std {\n\n/**\n *  @brief  Return the size of a container.\n *  @param\
    \  __cont  Container.\n */\ntemplate <typename _Container>\nconstexpr auto size(const\
    \ _Container& __cont) noexcept(noexcept(__cont.size()))\n    -> decltype(__cont.size())\
    \ {\n  return __cont.size();\n}\n\n/**\n *  @brief  Return the size of an array.\n\
    \ */\ntemplate <typename _Tp, size_t _Nm>\nconstexpr size_t size(const _Tp (&)[_Nm])\
    \ noexcept {\n  return _Nm;\n}\n\nstruct monostate {};\n\n}  // namespace std\n\
    \n#else\n\n#include <variant>\n\n#endif\n#line 9 \"src/graph/edge.h\"\n\nnamespace\
    \ workspace {\n\nnamespace _graph_impl {\n\n// Default edge attribute.\nstruct\
    \ null {};\n\n}  // namespace _graph_impl\n\ntemplate <class _Weight, class _Attr\
    \ = _graph_impl::null>\nstruct weighted_edge : _Attr {\n  using attribute = _Attr;\n\
    \  using value_type = _Weight;\n  using node_type = size_t;\n\n  node_type tail,\
    \ head;\n  value_type weight{};\n\n  constexpr weighted_edge() = default;\n\n\
    \  template <class... _Args>\n  constexpr weighted_edge(node_type __u, node_type\
    \ __v, value_type __c = 0,\n                          _Args &&...__args) noexcept\n\
    \      : _Attr{std::forward<_Args>(__args)...},\n        tail(__u),\n        head(__v),\n\
    \        weight(__c) {}\n\n  constexpr bool operator<(const weighted_edge &__e)\
    \ const noexcept {\n    return weight < __e.weight;\n  }\n  constexpr bool operator<=(const\
    \ weighted_edge &__e) const noexcept {\n    return weight <= __e.weight;\n  }\n\
    \  constexpr bool operator>(const weighted_edge &__e) const noexcept {\n    return\
    \ weight > __e.weight;\n  }\n  constexpr bool operator>=(const weighted_edge &__e)\
    \ const noexcept {\n    return weight >= __e.weight;\n  }\n};\n\ntemplate <class\
    \ _Attr = _graph_impl::null>\nstruct edge : weighted_edge<int, _Attr> {\n  using\
    \ base_type = weighted_edge<int, _Attr>;\n\n  using typename base_type::node_type;\n\
    \  using base_type::operator<;\n  using base_type::operator>;\n\n  constexpr edge()\
    \ = default;\n\n  template <class... _Args>\n  constexpr edge(node_type __u, node_type\
    \ __v, _Args &&...__args) noexcept\n      : base_type(__u, __v, __u != __v, std::forward<_Args>(__args)...)\
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
    }  // namespace std\n"
  code: "#pragma once\n\n/**\n * @file edge.h\n * @brief Edge\n */\n\n#include \"\
    lib/cxx17\"\n\nnamespace workspace {\n\nnamespace _graph_impl {\n\n// Default\
    \ edge attribute.\nstruct null {};\n\n}  // namespace _graph_impl\n\ntemplate\
    \ <class _Weight, class _Attr = _graph_impl::null>\nstruct weighted_edge : _Attr\
    \ {\n  using attribute = _Attr;\n  using value_type = _Weight;\n  using node_type\
    \ = size_t;\n\n  node_type tail, head;\n  value_type weight{};\n\n  constexpr\
    \ weighted_edge() = default;\n\n  template <class... _Args>\n  constexpr weighted_edge(node_type\
    \ __u, node_type __v, value_type __c = 0,\n                          _Args &&...__args)\
    \ noexcept\n      : _Attr{std::forward<_Args>(__args)...},\n        tail(__u),\n\
    \        head(__v),\n        weight(__c) {}\n\n  constexpr bool operator<(const\
    \ weighted_edge &__e) const noexcept {\n    return weight < __e.weight;\n  }\n\
    \  constexpr bool operator<=(const weighted_edge &__e) const noexcept {\n    return\
    \ weight <= __e.weight;\n  }\n  constexpr bool operator>(const weighted_edge &__e)\
    \ const noexcept {\n    return weight > __e.weight;\n  }\n  constexpr bool operator>=(const\
    \ weighted_edge &__e) const noexcept {\n    return weight >= __e.weight;\n  }\n\
    };\n\ntemplate <class _Attr = _graph_impl::null>\nstruct edge : weighted_edge<int,\
    \ _Attr> {\n  using base_type = weighted_edge<int, _Attr>;\n\n  using typename\
    \ base_type::node_type;\n  using base_type::operator<;\n  using base_type::operator>;\n\
    \n  constexpr edge() = default;\n\n  template <class... _Args>\n  constexpr edge(node_type\
    \ __u, node_type __v, _Args &&...__args) noexcept\n      : base_type(__u, __v,\
    \ __u != __v, std::forward<_Args>(__args)...) {}\n};\n\ntemplate <size_t _Nm,\
    \ class _Attr>\nconstexpr std::tuple_element_t<_Nm, edge<_Attr>> &get(\n    edge<_Attr>\
    \ &__e) noexcept {\n  if _CXX17_CONSTEXPR (_Nm > 1)\n    return __e;\n  else if\
    \ _CXX17_CONSTEXPR (_Nm)\n    return __e.head;\n  else\n    return __e.tail;\n\
    }\n\ntemplate <size_t _Nm, class _Attr>\nconstexpr const std::tuple_element_t<_Nm,\
    \ edge<_Attr>> &get(\n    const edge<_Attr> &__e) noexcept {\n  if _CXX17_CONSTEXPR\
    \ (_Nm > 1)\n    return __e;\n  else if _CXX17_CONSTEXPR (_Nm)\n    return __e.head;\n\
    \  else\n    return __e.tail;\n}\n\ntemplate <size_t _Nm, class _Attr>\nconstexpr\
    \ std::tuple_element_t<_Nm, edge<_Attr>> &&get(\n    edge<_Attr> &&__e) noexcept\
    \ {\n  return std::move(get<_Nm>(__e));\n}\n\ntemplate <size_t _Nm, class _Weight,\
    \ class _Attr>\nconstexpr const std::tuple_element_t<_Nm, weighted_edge<_Weight,\
    \ _Attr>> &get(\n    const weighted_edge<_Weight, _Attr> &__e) noexcept {\n  if\
    \ _CXX17_CONSTEXPR (_Nm > 2)\n    return __e;\n  else if _CXX17_CONSTEXPR (_Nm\
    \ > 1)\n    return __e.weight;\n  else if _CXX17_CONSTEXPR (_Nm)\n    return __e.head;\n\
    \  else\n    return __e.tail;\n}\n\ntemplate <size_t _Nm, class _Weight, class\
    \ _Attr>\nconstexpr std::tuple_element_t<_Nm, weighted_edge<_Weight, _Attr>> &get(\n\
    \    weighted_edge<_Weight, _Attr> &__e) noexcept {\n  if _CXX17_CONSTEXPR (_Nm\
    \ > 2)\n    return __e;\n  else if _CXX17_CONSTEXPR (_Nm > 1)\n    return __e.weight;\n\
    \  else if _CXX17_CONSTEXPR (_Nm)\n    return __e.head;\n  else\n    return __e.tail;\n\
    }\n\ntemplate <size_t _Nm, class _Weight, class _Attr>\nconstexpr std::tuple_element_t<_Nm,\
    \ weighted_edge<_Weight, _Attr>> &&get(\n    weighted_edge<_Weight, _Attr> &&__e)\
    \ noexcept {\n  return std::move(get<_Nm>(__e));\n}\n\n}  // namespace workspace\n\
    \nnamespace std {\n\ntemplate <class _Attr>\nstruct tuple_size<workspace::edge<_Attr>>\
    \ : integral_constant<size_t, 3> {};\n\ntemplate <>\nstruct tuple_size<workspace::edge<>>\
    \ : integral_constant<size_t, 2> {};\n\ntemplate <class _Weight, class _Attr>\n\
    struct tuple_size<workspace::weighted_edge<_Weight, _Attr>>\n    : integral_constant<size_t,\
    \ 4> {};\n\ntemplate <class _Weight>\nstruct tuple_size<workspace::weighted_edge<_Weight>>\n\
    \    : integral_constant<size_t, 3> {};\n\ntemplate <size_t _Nm, class _Attr>\n\
    struct tuple_element<_Nm, workspace::edge<_Attr>> {\n  using type = std::conditional_t<(_Nm\
    \ < 2), size_t, _Attr>;\n};\n\ntemplate <size_t _Nm, class _Weight, class _Attr>\n\
    struct tuple_element<_Nm, workspace::weighted_edge<_Weight, _Attr>> {\n  using\
    \ type = std::conditional_t<(_Nm < 2), size_t,\n                             \
    \     std::conditional_t<_Nm == 2, _Weight, _Attr>>;\n};\n\n}  // namespace std\n"
  dependsOn: []
  isVerificationFile: false
  path: src/graph/edge.h
  requiredBy:
  - src/graph/graph.h
  - src/graph/digraph.h
  - src/graph/base.h
  - src/graph/scc.h
  - src/graph/forest.h
  timestamp: '2021-10-09 10:54:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/shortest_path.test.cpp
  - test/library-checker/scc.test.cpp
  - test/aizu-online-judge/GRL_5_A.test.cpp
  - test/aizu-online-judge/GRL_4_A.test.cpp
  - test/aizu-online-judge/GRL_1_A.test.cpp
  - test/aizu-online-judge/GRL_2_A.test.cpp
  - test/aizu-online-judge/GRL_3_C.test.cpp
documentation_of: src/graph/edge.h
layout: document
redirect_from:
- /library/src/graph/edge.h
- /library/src/graph/edge.h.html
title: Edge
---
