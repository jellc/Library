---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Strongly Connected Component Algorithm
    links: []
  bundledCode: "#line 2 \"deprecated/scc.hpp\"\n\n/**\n * @file strongly_connected_component.hpp\n\
    \ * @brief Strongly Connected Component Algorithm\n */\n\n#include <algorithm>\n\
    #include <cassert>\n#include <numeric>\n#include <vector>\n\nnamespace workspace\
    \ {\n\nclass strongly_connected_component {\n public:\n  using size_type = std::size_t;\n\
    \n protected:\n  std::vector<std::vector<size_type>> __graph, __dag;\n  std::vector<size_type>\
    \ __low;\n\n  bool made() const { return !__low.empty(); }\n\n  /**\n   * @param\
    \ src Vertex\n   * @param c Counter\n   * @param ptr Pointer to a stack\n   *\
    \ @param used Negative indexed\n   * @return Low-link number of the vertex.\n\
    \   */\n  size_type affix(size_type src, size_type &c, size_type *&ptr,\n    \
    \              bool *const used) {\n    if (__low[src]) return __low[src];\n \
    \   const size_type idx = ++c;\n    __low[src] = idx;\n    *ptr++ = src;\n   \
    \ for (const size_type dst : __graph[src])\n      __low[src] = std::min(__low[src],\
    \ affix(dst, c, ptr, used));\n    if (__low[src] == idx) {\n      __dag.push_back({});\n\
    \      const size_type ccnt = __dag.size();\n      used[-ccnt] = true;\n     \
    \ size_type *srcp = ptr;\n      do __low[*--srcp] = -ccnt;\n      while (*srcp\
    \ != src);\n      while (ptr != srcp) {\n        const size_type now = *--ptr;\n\
    \        for (const size_type dst : __graph[now]) {\n          if (!used[(int)__low[dst]])\
    \ {\n            __dag.back().emplace_back(__low[dst]);\n            used[(int)__low[dst]]\
    \ = true;\n          }\n        }\n      }\n      for (const size_type dst : __dag.back())\
    \ used[dst] = false;\n      used[-ccnt] = false;\n      return idx;\n    }\n \
    \   return __low[src];\n  }\n\n public:\n  strongly_connected_component() = default;\n\
    \n  strongly_connected_component(size_type __n) : __graph(__n) {}\n\n  size_type\
    \ add_node() {\n    __graph.emplace_back();\n    return __graph.size() - 1;\n\
    \  }\n\n  std::vector<size_type> add_nodes(size_type __n) {\n    std::vector<size_type>\
    \ __nds(__n);\n    std::iota(__nds.begin(), __nds.end(), size());\n    __graph.resize(size()\
    \ + __n);\n    return __nds;\n  }\n\n  /**\n   * @brief Add an edge.\n   * @param\
    \ src Source\n   * @param dst Destination\n   */\n  void add_edge(size_type src,\
    \ size_type dst) {\n    assert(src < size());\n    assert(dst < size());\n   \
    \ __graph[src].emplace_back(dst);\n  }\n\n  /**\n   * @return Number of components.\n\
    \   */\n  size_type count() {\n    assert(made());\n    return __dag.size();\n\
    \  }\n\n  /**\n   * @return Number of vertices.\n   */\n  size_type size() const\
    \ { return __graph.size(); }\n\n  /**\n   * @param v Vertex\n   * @return Component\
    \ including given vertex.\n   */\n  size_type operator[](size_type v) {\n    assert(made());\n\
    \    return __low[v];\n  }\n\n  const auto &graph() const { return __graph; }\n\
    \n  /**\n   * @return Directed Acyclic Graph consisting of components.\n   */\n\
    \  const auto &shrinked_dag() {\n    assert(made());\n    return __dag;\n  }\n\
    \n  /**\n   * @brief Run SCC decomposition in linear time.\n   */\n  void make()\
    \ {\n    __low.assign(size(), 0);\n    __dag.clear();\n    size_type *ptr = new\
    \ size_type[size()];\n    bool *const used = new bool[size()];\n    for (size_type\
    \ v{}, c{}; v != size(); ++v) affix(v, c, ptr, used + size());\n    delete[] ptr;\n\
    \    delete[] used;\n    for (auto &e : __low) e += __dag.size();\n    reverse(begin(__dag),\
    \ end(__dag));\n    for (auto &arcs : __dag)\n      for (auto &dst : arcs) dst\
    \ += __dag.size();\n  }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file strongly_connected_component.hpp\n * @brief\
    \ Strongly Connected Component Algorithm\n */\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <numeric>\n#include <vector>\n\nnamespace workspace {\n\n\
    class strongly_connected_component {\n public:\n  using size_type = std::size_t;\n\
    \n protected:\n  std::vector<std::vector<size_type>> __graph, __dag;\n  std::vector<size_type>\
    \ __low;\n\n  bool made() const { return !__low.empty(); }\n\n  /**\n   * @param\
    \ src Vertex\n   * @param c Counter\n   * @param ptr Pointer to a stack\n   *\
    \ @param used Negative indexed\n   * @return Low-link number of the vertex.\n\
    \   */\n  size_type affix(size_type src, size_type &c, size_type *&ptr,\n    \
    \              bool *const used) {\n    if (__low[src]) return __low[src];\n \
    \   const size_type idx = ++c;\n    __low[src] = idx;\n    *ptr++ = src;\n   \
    \ for (const size_type dst : __graph[src])\n      __low[src] = std::min(__low[src],\
    \ affix(dst, c, ptr, used));\n    if (__low[src] == idx) {\n      __dag.push_back({});\n\
    \      const size_type ccnt = __dag.size();\n      used[-ccnt] = true;\n     \
    \ size_type *srcp = ptr;\n      do __low[*--srcp] = -ccnt;\n      while (*srcp\
    \ != src);\n      while (ptr != srcp) {\n        const size_type now = *--ptr;\n\
    \        for (const size_type dst : __graph[now]) {\n          if (!used[(int)__low[dst]])\
    \ {\n            __dag.back().emplace_back(__low[dst]);\n            used[(int)__low[dst]]\
    \ = true;\n          }\n        }\n      }\n      for (const size_type dst : __dag.back())\
    \ used[dst] = false;\n      used[-ccnt] = false;\n      return idx;\n    }\n \
    \   return __low[src];\n  }\n\n public:\n  strongly_connected_component() = default;\n\
    \n  strongly_connected_component(size_type __n) : __graph(__n) {}\n\n  size_type\
    \ add_node() {\n    __graph.emplace_back();\n    return __graph.size() - 1;\n\
    \  }\n\n  std::vector<size_type> add_nodes(size_type __n) {\n    std::vector<size_type>\
    \ __nds(__n);\n    std::iota(__nds.begin(), __nds.end(), size());\n    __graph.resize(size()\
    \ + __n);\n    return __nds;\n  }\n\n  /**\n   * @brief Add an edge.\n   * @param\
    \ src Source\n   * @param dst Destination\n   */\n  void add_edge(size_type src,\
    \ size_type dst) {\n    assert(src < size());\n    assert(dst < size());\n   \
    \ __graph[src].emplace_back(dst);\n  }\n\n  /**\n   * @return Number of components.\n\
    \   */\n  size_type count() {\n    assert(made());\n    return __dag.size();\n\
    \  }\n\n  /**\n   * @return Number of vertices.\n   */\n  size_type size() const\
    \ { return __graph.size(); }\n\n  /**\n   * @param v Vertex\n   * @return Component\
    \ including given vertex.\n   */\n  size_type operator[](size_type v) {\n    assert(made());\n\
    \    return __low[v];\n  }\n\n  const auto &graph() const { return __graph; }\n\
    \n  /**\n   * @return Directed Acyclic Graph consisting of components.\n   */\n\
    \  const auto &shrinked_dag() {\n    assert(made());\n    return __dag;\n  }\n\
    \n  /**\n   * @brief Run SCC decomposition in linear time.\n   */\n  void make()\
    \ {\n    __low.assign(size(), 0);\n    __dag.clear();\n    size_type *ptr = new\
    \ size_type[size()];\n    bool *const used = new bool[size()];\n    for (size_type\
    \ v{}, c{}; v != size(); ++v) affix(v, c, ptr, used + size());\n    delete[] ptr;\n\
    \    delete[] used;\n    for (auto &e : __low) e += __dag.size();\n    reverse(begin(__dag),\
    \ end(__dag));\n    for (auto &arcs : __dag)\n      for (auto &dst : arcs) dst\
    \ += __dag.size();\n  }\n};\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: deprecated/scc.hpp
  requiredBy: []
  timestamp: '2021-10-09 10:54:50+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: deprecated/scc.hpp
layout: document
redirect_from:
- /library/deprecated/scc.hpp
- /library/deprecated/scc.hpp.html
title: Strongly Connected Component Algorithm
---
