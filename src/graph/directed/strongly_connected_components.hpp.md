---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/scc.test.cpp
    title: test/library-checker/scc.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Strongly Connected Components
    links: []
  bundledCode: "#line 2 \"src/graph/directed/strongly_connected_components.hpp\"\n\
    \n/*\n * @file strongly_connected_components.hpp\n * @brief Strongly Connected\
    \ Components\n */\n\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\
    \nnamespace workspace {\n\nstruct strongly_connected_components {\n  strongly_connected_components(size_t\
    \ n) : graph(n) {}\n\n  /*\n   * @fn add_edge\n   * @brief Add an edge.\n   *\
    \ @param src Source\n   * @param dst Destination\n   */\n  void add_edge(size_t\
    \ src, size_t dst) {\n    assert(src < size());\n    assert(dst < size());\n \
    \   graph[src].emplace_back(dst);\n  }\n\n  /*\n   * @fn count\n   * @return The\
    \ number of components.\n   */\n  size_t count() {\n    assert(made());\n    return\
    \ dag.size();\n  }\n\n  /*\n   * @fn size\n   * @return The number of vertices.\n\
    \   */\n  size_t size() const { return graph.size(); }\n\n  /*\n   * @fn operator[]\n\
    \   * @param v Vertex\n   * @return The component including given vertex.\n  \
    \ */\n  size_t operator[](size_t v) {\n    assert(made());\n    return low[v];\n\
    \  }\n\n  /*\n   * @fn shrinked_dag\n   * @return Directed Acyclic Graph consisting\
    \ of components.\n   */\n  const std::vector<std::vector<size_t>> &shrinked_dag()\
    \ {\n    assert(made());\n    return dag;\n  }\n\n  /*\n   * @fn make\n   * @brief\
    \ Run SCC decomposition in linear time.\n   */\n  void make() {\n    low.assign(size(),\
    \ 0);\n    dag.clear();\n    size_t *ptr = new size_t[size()];\n    bool *const\
    \ used = new bool[size()];\n    for (size_t v{}, c{}; v != size(); ++v) affix(v,\
    \ c, ptr, used + size());\n    delete[] ptr;\n    delete[] used;\n    for (auto\
    \ &e : low) e += dag.size();\n    reverse(begin(dag), end(dag));\n    for (auto\
    \ &arcs : dag)\n      for (auto &dst : arcs) dst += dag.size();\n  }\n\n protected:\n\
    \  std::vector<std::vector<size_t>> graph, dag;\n  std::vector<size_t> low;\n\n\
    \  bool made() const { return !low.empty(); }\n\n  /*\n   * @fn affix\n   * @param\
    \ src Vertex\n   * @param c Counter\n   * @param ptr Pointer to a stack\n   *\
    \ @param used Negative indexed\n   * @return Low-link number of the vertex.\n\
    \   */\n  size_t affix(size_t src, size_t &c, size_t *&ptr, bool *const used)\
    \ {\n    if (low[src]) return low[src];\n    const size_t idx = ++c;\n    low[src]\
    \ = idx;\n    *ptr++ = src;\n    for (const size_t dst : graph[src])\n      low[src]\
    \ = std::min(low[src], affix(dst, c, ptr, used));\n    if (low[src] == idx) {\n\
    \      dag.push_back({});\n      const size_t ccnt = dag.size();\n      used[-ccnt]\
    \ = true;\n      size_t *srcp = ptr;\n      do\n        low[*--srcp] = -ccnt;\n\
    \      while (*srcp != src);\n      while (ptr != srcp) {\n        const size_t\
    \ now = *--ptr;\n        for (const size_t dst : graph[now]) {\n          if (!used[(int)low[dst]])\
    \ {\n            dag.back().emplace_back(low[dst]);\n            used[(int)low[dst]]\
    \ = true;\n          }\n        }\n      }\n      for (const size_t dst : dag.back())\
    \ used[dst] = false;\n      used[-ccnt] = false;\n      return idx;\n    }\n \
    \   return low[src];\n  }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file strongly_connected_components.hpp\n * @brief\
    \ Strongly Connected Components\n */\n\n#include <algorithm>\n#include <cassert>\n\
    #include <vector>\n\nnamespace workspace {\n\nstruct strongly_connected_components\
    \ {\n  strongly_connected_components(size_t n) : graph(n) {}\n\n  /*\n   * @fn\
    \ add_edge\n   * @brief Add an edge.\n   * @param src Source\n   * @param dst\
    \ Destination\n   */\n  void add_edge(size_t src, size_t dst) {\n    assert(src\
    \ < size());\n    assert(dst < size());\n    graph[src].emplace_back(dst);\n \
    \ }\n\n  /*\n   * @fn count\n   * @return The number of components.\n   */\n \
    \ size_t count() {\n    assert(made());\n    return dag.size();\n  }\n\n  /*\n\
    \   * @fn size\n   * @return The number of vertices.\n   */\n  size_t size() const\
    \ { return graph.size(); }\n\n  /*\n   * @fn operator[]\n   * @param v Vertex\n\
    \   * @return The component including given vertex.\n   */\n  size_t operator[](size_t\
    \ v) {\n    assert(made());\n    return low[v];\n  }\n\n  /*\n   * @fn shrinked_dag\n\
    \   * @return Directed Acyclic Graph consisting of components.\n   */\n  const\
    \ std::vector<std::vector<size_t>> &shrinked_dag() {\n    assert(made());\n  \
    \  return dag;\n  }\n\n  /*\n   * @fn make\n   * @brief Run SCC decomposition\
    \ in linear time.\n   */\n  void make() {\n    low.assign(size(), 0);\n    dag.clear();\n\
    \    size_t *ptr = new size_t[size()];\n    bool *const used = new bool[size()];\n\
    \    for (size_t v{}, c{}; v != size(); ++v) affix(v, c, ptr, used + size());\n\
    \    delete[] ptr;\n    delete[] used;\n    for (auto &e : low) e += dag.size();\n\
    \    reverse(begin(dag), end(dag));\n    for (auto &arcs : dag)\n      for (auto\
    \ &dst : arcs) dst += dag.size();\n  }\n\n protected:\n  std::vector<std::vector<size_t>>\
    \ graph, dag;\n  std::vector<size_t> low;\n\n  bool made() const { return !low.empty();\
    \ }\n\n  /*\n   * @fn affix\n   * @param src Vertex\n   * @param c Counter\n \
    \  * @param ptr Pointer to a stack\n   * @param used Negative indexed\n   * @return\
    \ Low-link number of the vertex.\n   */\n  size_t affix(size_t src, size_t &c,\
    \ size_t *&ptr, bool *const used) {\n    if (low[src]) return low[src];\n    const\
    \ size_t idx = ++c;\n    low[src] = idx;\n    *ptr++ = src;\n    for (const size_t\
    \ dst : graph[src])\n      low[src] = std::min(low[src], affix(dst, c, ptr, used));\n\
    \    if (low[src] == idx) {\n      dag.push_back({});\n      const size_t ccnt\
    \ = dag.size();\n      used[-ccnt] = true;\n      size_t *srcp = ptr;\n      do\n\
    \        low[*--srcp] = -ccnt;\n      while (*srcp != src);\n      while (ptr\
    \ != srcp) {\n        const size_t now = *--ptr;\n        for (const size_t dst\
    \ : graph[now]) {\n          if (!used[(int)low[dst]]) {\n            dag.back().emplace_back(low[dst]);\n\
    \            used[(int)low[dst]] = true;\n          }\n        }\n      }\n  \
    \    for (const size_t dst : dag.back()) used[dst] = false;\n      used[-ccnt]\
    \ = false;\n      return idx;\n    }\n    return low[src];\n  }\n};\n\n}  // namespace\
    \ workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/graph/directed/strongly_connected_components.hpp
  requiredBy: []
  timestamp: '2020-11-25 12:11:14+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/scc.test.cpp
documentation_of: src/graph/directed/strongly_connected_components.hpp
layout: document
redirect_from:
- /library/src/graph/directed/strongly_connected_components.hpp
- /library/src/graph/directed/strongly_connected_components.hpp.html
title: Strongly Connected Components
---