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
    links: []
  bundledCode: "#line 2 \"graph/directed/strongly_connected_components.hpp\"\n#include\
    \ <algorithm>\n#include <cassert>\n#include <vector>\nstruct strongly_connected_components\
    \ {\n  strongly_connected_components(size_t n) : graph(n), low(n), made() {}\n\
    \n  // add an edge from the vertex s to the vertex t.\n  void add_edge(size_t\
    \ src, size_t dst) {\n    assert(src < size());\n    assert(dst < size());\n \
    \   graph[src].emplace_back(dst);\n    made = false;\n  }\n\n  // the number of\
    \ the components.\n  size_t count() {\n    make();\n    return comp_cnt;\n  }\n\
    \n  size_t size() const { return graph.size(); }\n\n  // the component which the\
    \ vertex v belongs to.\n  size_t operator[](size_t v) {\n    make();\n    return\
    \ low[v];\n  }\n\n  // the directed acyclic graph consisting of the components.\n\
    \  const std::vector<std::vector<size_t>> &shrinked_dag() {\n    make();\n   \
    \ return dag;\n  }\n\n protected:\n  std::vector<std::vector<size_t>> graph, dag;\n\
    \  std::vector<size_t> low;\n  size_t comp_cnt;\n  bool made;\n\n  void make()\
    \ {\n    if (made) return;\n    made = true, comp_cnt = 0;\n    low.assign(size(),\
    \ 0);\n    size_t *itr = new size_t[size()];\n    bool *const used = new bool[size()];\n\
    \    for (size_t v{}, c{}; v != size(); ++v) affix(v, c, itr, used + size());\n\
    \    delete[] itr;\n    delete[] used;\n    for (auto &e : low) e += comp_cnt;\n\
    \    reverse(begin(dag), end(dag));\n    for (auto &arcs : dag)\n      for (auto\
    \ &to : arcs) to += comp_cnt;\n  }\n\n  size_t affix(size_t src, size_t &c, size_t\
    \ *&itr, bool *used) {\n    if (low[src]) return low[src];\n    size_t idx = ++c;\n\
    \    low[src] = idx;\n    *itr++ = src;\n    for (size_t dst : graph[src])\n \
    \     low[src] = std::min(low[src], affix(dst, c, itr, used));\n    if (low[src]\
    \ == idx) {\n      ++comp_cnt;\n      used[-comp_cnt] = true;\n      dag.emplace_back(0);\n\
    \      auto srcp = itr;\n      do {\n        low[*--srcp] = -comp_cnt;\n     \
    \ } while (*srcp != src);\n      while (itr != srcp) {\n        auto now = *--itr;\n\
    \        for (auto to : graph[now]) {\n          if (!used[(int)low[to]]) {\n\
    \            dag.back().emplace_back(low[to]);\n            used[(int)low[to]]\
    \ = true;\n          }\n        }\n      }\n      for (int c : dag.back()) used[c]\
    \ = false;\n      used[-comp_cnt] = false;\n      return idx;\n    }\n    return\
    \ low[src];\n  }\n};  // class strongly_connected_components\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\
    struct strongly_connected_components {\n  strongly_connected_components(size_t\
    \ n) : graph(n), low(n), made() {}\n\n  // add an edge from the vertex s to the\
    \ vertex t.\n  void add_edge(size_t src, size_t dst) {\n    assert(src < size());\n\
    \    assert(dst < size());\n    graph[src].emplace_back(dst);\n    made = false;\n\
    \  }\n\n  // the number of the components.\n  size_t count() {\n    make();\n\
    \    return comp_cnt;\n  }\n\n  size_t size() const { return graph.size(); }\n\
    \n  // the component which the vertex v belongs to.\n  size_t operator[](size_t\
    \ v) {\n    make();\n    return low[v];\n  }\n\n  // the directed acyclic graph\
    \ consisting of the components.\n  const std::vector<std::vector<size_t>> &shrinked_dag()\
    \ {\n    make();\n    return dag;\n  }\n\n protected:\n  std::vector<std::vector<size_t>>\
    \ graph, dag;\n  std::vector<size_t> low;\n  size_t comp_cnt;\n  bool made;\n\n\
    \  void make() {\n    if (made) return;\n    made = true, comp_cnt = 0;\n    low.assign(size(),\
    \ 0);\n    size_t *itr = new size_t[size()];\n    bool *const used = new bool[size()];\n\
    \    for (size_t v{}, c{}; v != size(); ++v) affix(v, c, itr, used + size());\n\
    \    delete[] itr;\n    delete[] used;\n    for (auto &e : low) e += comp_cnt;\n\
    \    reverse(begin(dag), end(dag));\n    for (auto &arcs : dag)\n      for (auto\
    \ &to : arcs) to += comp_cnt;\n  }\n\n  size_t affix(size_t src, size_t &c, size_t\
    \ *&itr, bool *used) {\n    if (low[src]) return low[src];\n    size_t idx = ++c;\n\
    \    low[src] = idx;\n    *itr++ = src;\n    for (size_t dst : graph[src])\n \
    \     low[src] = std::min(low[src], affix(dst, c, itr, used));\n    if (low[src]\
    \ == idx) {\n      ++comp_cnt;\n      used[-comp_cnt] = true;\n      dag.emplace_back(0);\n\
    \      auto srcp = itr;\n      do {\n        low[*--srcp] = -comp_cnt;\n     \
    \ } while (*srcp != src);\n      while (itr != srcp) {\n        auto now = *--itr;\n\
    \        for (auto to : graph[now]) {\n          if (!used[(int)low[to]]) {\n\
    \            dag.back().emplace_back(low[to]);\n            used[(int)low[to]]\
    \ = true;\n          }\n        }\n      }\n      for (int c : dag.back()) used[c]\
    \ = false;\n      used[-comp_cnt] = false;\n      return idx;\n    }\n    return\
    \ low[src];\n  }\n};  // class strongly_connected_components\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/directed/strongly_connected_components.hpp
  requiredBy: []
  timestamp: '2020-09-05 02:51:04+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/scc.test.cpp
documentation_of: graph/directed/strongly_connected_components.hpp
layout: document
redirect_from:
- /library/graph/directed/strongly_connected_components.hpp
- /library/graph/directed/strongly_connected_components.hpp.html
title: graph/directed/strongly_connected_components.hpp
---
