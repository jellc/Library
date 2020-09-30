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
  bundledCode: "#line 1 \"graph/undirected/two_edge_connected_components.hpp\"\n#include\
    \ <cassert>\n#include <vector>\n\n// instance: an undirected and not necessarily\
    \ simple graph\nclass two_edge_connected_component\n{\n    static constexpr size_t\
    \ nil = -1;\n    bool made;\n    std::vector<size_t> stack, low, comp;\n    std::vector<std::vector<size_t>>\
    \ graph, tree, memb;\n\n    void make(size_t now, size_t pre)\n    {\n       \
    \ size_t ord = low[now] = stack.size();\n        stack.emplace_back(now);\n  \
    \      std::vector<size_t> brid;\n        for(size_t to : graph[now])\n      \
    \  {\n            if(to == pre) { pre = nil; continue; }\n            if(low[to]\
    \ == nil) make(to, now);\n            if(low[to] > ord)\n            {\n     \
    \           brid.emplace_back(to);\n                graph[to].emplace_back(now);\n\
    \            }\n            else if(low[now] > low[to]) low[now] = low[to];\n\
    \        }\n        brid.swap(graph[now]);\n        if(ord == low[now])\n    \
    \    {\n            auto pos = stack.end();\n            tree.resize(tree.size()\
    \ + 1);\n            auto &adjc = tree.back();\n            do\n            {\n\
    \                --pos;\n                comp[*pos] = memb.size();\n         \
    \       for(size_t u : graph[*pos]) adjc.emplace_back(comp[u]);\n            }\
    \ while(*pos != now);\n            memb.emplace_back(pos, stack.end());\n    \
    \        stack.erase(pos, stack.end());\n        }\n    }\n\npublic:\n    two_edge_connected_component(size_t\
    \ n) : made(false), comp(n), graph(n)\n    {\n        stack.reserve(n), tree.reserve(n),\
    \ memb.reserve(n);\n    }\n\n    void add_edge(size_t u, size_t v)\n    {\n  \
    \      assert(u < size()), assert(v < size());\n        graph[u].emplace_back(v),\
    \ graph[v].emplace_back(u);\n        made = false;\n    }\n\n    void make()\n\
    \    {\n        if(made) return;\n        made = true;\n        low.assign(size(),\
    \ nil);\n        for(size_t v = 0; v != size(); ++v) if(low[v] == nil) make(v,\
    \ nil);\n    }\n\n    size_t size() const { return graph.size(); }\n\n    size_t\
    \ size(size_t i) { make(); assert(i < count()); return memb[i].size(); }\n\n \
    \   size_t count() { make(); return memb.size(); }\n\n    size_t operator[](size_t\
    \ v) { make(); assert(v < size()); return comp[v]; }\n\n    const std::vector<size_t>\
    \ &bridge(size_t v) { make(); assert(v < size()); return graph[v]; }\n\n    const\
    \ std::vector<size_t> &component(size_t i) { make(); assert(i < count()); return\
    \ memb[i]; }\n\n    const std::vector<std::vector<size_t>> &bridge_tree() { make();\
    \ return tree; }\n}; // class two_edge_connected_component\n"
  code: "#include <cassert>\n#include <vector>\n\n// instance: an undirected and not\
    \ necessarily simple graph\nclass two_edge_connected_component\n{\n    static\
    \ constexpr size_t nil = -1;\n    bool made;\n    std::vector<size_t> stack, low,\
    \ comp;\n    std::vector<std::vector<size_t>> graph, tree, memb;\n\n    void make(size_t\
    \ now, size_t pre)\n    {\n        size_t ord = low[now] = stack.size();\n   \
    \     stack.emplace_back(now);\n        std::vector<size_t> brid;\n        for(size_t\
    \ to : graph[now])\n        {\n            if(to == pre) { pre = nil; continue;\
    \ }\n            if(low[to] == nil) make(to, now);\n            if(low[to] > ord)\n\
    \            {\n                brid.emplace_back(to);\n                graph[to].emplace_back(now);\n\
    \            }\n            else if(low[now] > low[to]) low[now] = low[to];\n\
    \        }\n        brid.swap(graph[now]);\n        if(ord == low[now])\n    \
    \    {\n            auto pos = stack.end();\n            tree.resize(tree.size()\
    \ + 1);\n            auto &adjc = tree.back();\n            do\n            {\n\
    \                --pos;\n                comp[*pos] = memb.size();\n         \
    \       for(size_t u : graph[*pos]) adjc.emplace_back(comp[u]);\n            }\
    \ while(*pos != now);\n            memb.emplace_back(pos, stack.end());\n    \
    \        stack.erase(pos, stack.end());\n        }\n    }\n\npublic:\n    two_edge_connected_component(size_t\
    \ n) : made(false), comp(n), graph(n)\n    {\n        stack.reserve(n), tree.reserve(n),\
    \ memb.reserve(n);\n    }\n\n    void add_edge(size_t u, size_t v)\n    {\n  \
    \      assert(u < size()), assert(v < size());\n        graph[u].emplace_back(v),\
    \ graph[v].emplace_back(u);\n        made = false;\n    }\n\n    void make()\n\
    \    {\n        if(made) return;\n        made = true;\n        low.assign(size(),\
    \ nil);\n        for(size_t v = 0; v != size(); ++v) if(low[v] == nil) make(v,\
    \ nil);\n    }\n\n    size_t size() const { return graph.size(); }\n\n    size_t\
    \ size(size_t i) { make(); assert(i < count()); return memb[i].size(); }\n\n \
    \   size_t count() { make(); return memb.size(); }\n\n    size_t operator[](size_t\
    \ v) { make(); assert(v < size()); return comp[v]; }\n\n    const std::vector<size_t>\
    \ &bridge(size_t v) { make(); assert(v < size()); return graph[v]; }\n\n    const\
    \ std::vector<size_t> &component(size_t i) { make(); assert(i < count()); return\
    \ memb[i]; }\n\n    const std::vector<std::vector<size_t>> &bridge_tree() { make();\
    \ return tree; }\n}; // class two_edge_connected_component\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/undirected/two_edge_connected_components.hpp
  requiredBy: []
  timestamp: '2020-08-21 01:25:04+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/two_edge_connected_components.test.cpp
documentation_of: graph/undirected/two_edge_connected_components.hpp
layout: document
redirect_from:
- /library/graph/undirected/two_edge_connected_components.hpp
- /library/graph/undirected/two_edge_connected_components.hpp.html
title: graph/undirected/two_edge_connected_components.hpp
---
