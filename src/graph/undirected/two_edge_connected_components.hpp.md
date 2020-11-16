---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/two_edge_connected_components.test.cpp
    title: test/library-checker/two_edge_connected_components.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/graph/undirected/two_edge_connected_components.hpp\"\
    \n#include <cassert>\n#include <vector>\n\n// instance: an undirected and not\
    \ necessarily simple graph\nclass two_edge_connected_component {\n  static constexpr\
    \ size_t nil = -1;\n  std::vector<size_t> stack, low, comp;\n  std::vector<std::vector<size_t>>\
    \ graph, tree, memb;\n\n  void make(size_t now, size_t pre) {\n    size_t ord\
    \ = low[now] = stack.size();\n    stack.emplace_back(now);\n    std::vector<size_t>\
    \ brid;\n    for (size_t to : graph[now]) {\n      if (to == pre) {\n        pre\
    \ = nil;\n        continue;\n      }\n      if (low[to] == nil) make(to, now);\n\
    \      if (low[to] > ord) {\n        brid.emplace_back(to);\n        graph[to].emplace_back(now);\n\
    \      } else if (low[now] > low[to])\n        low[now] = low[to];\n    }\n  \
    \  brid.swap(graph[now]);\n    if (ord == low[now]) {\n      auto pos = stack.end();\n\
    \      tree.resize(tree.size() + 1);\n      auto &adjc = tree.back();\n      do\
    \ {\n        --pos;\n        comp[*pos] = memb.size();\n        for (size_t u\
    \ : graph[*pos]) adjc.emplace_back(comp[u]);\n      } while (*pos != now);\n \
    \     memb.emplace_back(pos, stack.end());\n      stack.erase(pos, stack.end());\n\
    \    }\n  }\n\n public:\n  two_edge_connected_component(size_t n) : comp(n), graph(n)\
    \ {\n    stack.reserve(n), tree.reserve(n), memb.reserve(n);\n  }\n\n  void add_edge(size_t\
    \ u, size_t v) {\n    assert(u < size()), assert(v < size());\n    graph[u].emplace_back(v),\
    \ graph[v].emplace_back(u);\n  }\n\n  void make() {\n    low.assign(size(), nil);\n\
    \    for (size_t v = 0; v != size(); ++v)\n      if (low[v] == nil) make(v, nil);\n\
    \  }\n\n  size_t size() const { return graph.size(); }\n\n  size_t size(size_t\
    \ i) const {\n    assert(i < count());\n    return memb[i].size();\n  }\n\n  size_t\
    \ count() const { return memb.size(); }\n\n  size_t operator[](size_t v) const\
    \ {\n    assert(v < size());\n    return comp[v];\n  }\n\n  const std::vector<size_t>\
    \ &bridge(size_t v) const {\n    assert(v < size());\n    return graph[v];\n \
    \ }\n\n  const std::vector<size_t> &component(size_t i) const {\n    assert(i\
    \ < count());\n    return memb[i];\n  }\n\n  const std::vector<std::vector<size_t>>\
    \ &bridge_tree() const { return tree; }\n};  // class two_edge_connected_component\n"
  code: "#pragma once\n#include <cassert>\n#include <vector>\n\n// instance: an undirected\
    \ and not necessarily simple graph\nclass two_edge_connected_component {\n  static\
    \ constexpr size_t nil = -1;\n  std::vector<size_t> stack, low, comp;\n  std::vector<std::vector<size_t>>\
    \ graph, tree, memb;\n\n  void make(size_t now, size_t pre) {\n    size_t ord\
    \ = low[now] = stack.size();\n    stack.emplace_back(now);\n    std::vector<size_t>\
    \ brid;\n    for (size_t to : graph[now]) {\n      if (to == pre) {\n        pre\
    \ = nil;\n        continue;\n      }\n      if (low[to] == nil) make(to, now);\n\
    \      if (low[to] > ord) {\n        brid.emplace_back(to);\n        graph[to].emplace_back(now);\n\
    \      } else if (low[now] > low[to])\n        low[now] = low[to];\n    }\n  \
    \  brid.swap(graph[now]);\n    if (ord == low[now]) {\n      auto pos = stack.end();\n\
    \      tree.resize(tree.size() + 1);\n      auto &adjc = tree.back();\n      do\
    \ {\n        --pos;\n        comp[*pos] = memb.size();\n        for (size_t u\
    \ : graph[*pos]) adjc.emplace_back(comp[u]);\n      } while (*pos != now);\n \
    \     memb.emplace_back(pos, stack.end());\n      stack.erase(pos, stack.end());\n\
    \    }\n  }\n\n public:\n  two_edge_connected_component(size_t n) : comp(n), graph(n)\
    \ {\n    stack.reserve(n), tree.reserve(n), memb.reserve(n);\n  }\n\n  void add_edge(size_t\
    \ u, size_t v) {\n    assert(u < size()), assert(v < size());\n    graph[u].emplace_back(v),\
    \ graph[v].emplace_back(u);\n  }\n\n  void make() {\n    low.assign(size(), nil);\n\
    \    for (size_t v = 0; v != size(); ++v)\n      if (low[v] == nil) make(v, nil);\n\
    \  }\n\n  size_t size() const { return graph.size(); }\n\n  size_t size(size_t\
    \ i) const {\n    assert(i < count());\n    return memb[i].size();\n  }\n\n  size_t\
    \ count() const { return memb.size(); }\n\n  size_t operator[](size_t v) const\
    \ {\n    assert(v < size());\n    return comp[v];\n  }\n\n  const std::vector<size_t>\
    \ &bridge(size_t v) const {\n    assert(v < size());\n    return graph[v];\n \
    \ }\n\n  const std::vector<size_t> &component(size_t i) const {\n    assert(i\
    \ < count());\n    return memb[i];\n  }\n\n  const std::vector<std::vector<size_t>>\
    \ &bridge_tree() const { return tree; }\n};  // class two_edge_connected_component\n"
  dependsOn: []
  isVerificationFile: false
  path: src/graph/undirected/two_edge_connected_components.hpp
  requiredBy: []
  timestamp: '2020-11-16 14:21:51+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/two_edge_connected_components.test.cpp
documentation_of: src/graph/undirected/two_edge_connected_components.hpp
layout: document
redirect_from:
- /library/src/graph/undirected/two_edge_connected_components.hpp
- /library/src/graph/undirected/two_edge_connected_components.hpp.html
title: src/graph/undirected/two_edge_connected_components.hpp
---
