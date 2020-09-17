---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/lowest_common_ancestor.test.cpp
    title: test/library-checker/lowest_common_ancestor.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"graph/undirected/tree/lowest_common_ancestor.hpp\"\n#include\
    \ <cassert>\n#include <vector>\n\n// query: O(1)\n// build: O(nlog(n))\nclass\
    \ lowest_common_ancestor\n{\n    std::vector<std::vector<size_t>> tree, tab;\n\
    \    std::vector<size_t> idx;\n\n    void tour(size_t node, size_t pre)\n    {\n\
    \        idx[node] = tab[0].size();\n        tab[0].emplace_back(node);\n    \
    \    for(size_t to : tree[node])\n        {\n            if(to != pre)\n     \
    \       {\n                tour(to, node);\n                tab[0].emplace_back(node);\n\
    \            }\n        }\n    }\n\n    void make_table()\n    {\n        const\
    \ size_t len = tab[0].size();\n        for(size_t w = 2; w < len; w <<= 1)\n \
    \       {\n            std::vector<size_t> &crt(tab.back()), nxt(crt);\n     \
    \       for(size_t i = 0, j = w >> 1; j != len; ++i, ++j) if(idx[crt[i]] > idx[crt[j]])\
    \ nxt[i] = crt[j];\n            tab.emplace_back(nxt);\n        }\n    }\n\npublic:\n\
    \    lowest_common_ancestor(size_t n) : tree(n), tab(1), idx(n) {}\n\n    size_t\
    \ size() const { return tree.size(); }\n\n    void add_edge(size_t u, size_t v)\n\
    \    {\n        assert(u < size()); assert(v < size());\n        tree[u].emplace_back(v);\n\
    \        tree[v].emplace_back(u);\n    }\n\n    void make(size_t root)\n    {\n\
    \        assert(root < size());\n        tour(root, root);\n        make_table();\n\
    \    }\n\n    size_t query(size_t u, size_t v) const\n    {\n        assert(u\
    \ < size()); assert(v < size());\n        if(u == v) return u;\n        if(idx[u]\
    \ > idx[v]) std::swap(u, v);\n        u = idx[u], v = idx[v];\n        size_t\
    \ h = std::__lg(v - u);\n        return std::min(tab[h][u], tab[h][v - (1 << h)]);\n\
    \    }\n}; // class lowest_common_ancestor\n"
  code: "#include <cassert>\n#include <vector>\n\n// query: O(1)\n// build: O(nlog(n))\n\
    class lowest_common_ancestor\n{\n    std::vector<std::vector<size_t>> tree, tab;\n\
    \    std::vector<size_t> idx;\n\n    void tour(size_t node, size_t pre)\n    {\n\
    \        idx[node] = tab[0].size();\n        tab[0].emplace_back(node);\n    \
    \    for(size_t to : tree[node])\n        {\n            if(to != pre)\n     \
    \       {\n                tour(to, node);\n                tab[0].emplace_back(node);\n\
    \            }\n        }\n    }\n\n    void make_table()\n    {\n        const\
    \ size_t len = tab[0].size();\n        for(size_t w = 2; w < len; w <<= 1)\n \
    \       {\n            std::vector<size_t> &crt(tab.back()), nxt(crt);\n     \
    \       for(size_t i = 0, j = w >> 1; j != len; ++i, ++j) if(idx[crt[i]] > idx[crt[j]])\
    \ nxt[i] = crt[j];\n            tab.emplace_back(nxt);\n        }\n    }\n\npublic:\n\
    \    lowest_common_ancestor(size_t n) : tree(n), tab(1), idx(n) {}\n\n    size_t\
    \ size() const { return tree.size(); }\n\n    void add_edge(size_t u, size_t v)\n\
    \    {\n        assert(u < size()); assert(v < size());\n        tree[u].emplace_back(v);\n\
    \        tree[v].emplace_back(u);\n    }\n\n    void make(size_t root)\n    {\n\
    \        assert(root < size());\n        tour(root, root);\n        make_table();\n\
    \    }\n\n    size_t query(size_t u, size_t v) const\n    {\n        assert(u\
    \ < size()); assert(v < size());\n        if(u == v) return u;\n        if(idx[u]\
    \ > idx[v]) std::swap(u, v);\n        u = idx[u], v = idx[v];\n        size_t\
    \ h = std::__lg(v - u);\n        return std::min(tab[h][u], tab[h][v - (1 << h)]);\n\
    \    }\n}; // class lowest_common_ancestor"
  dependsOn: []
  isVerificationFile: false
  path: graph/undirected/tree/lowest_common_ancestor.hpp
  requiredBy: []
  timestamp: '2020-08-02 22:26:27+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/lowest_common_ancestor.test.cpp
documentation_of: graph/undirected/tree/lowest_common_ancestor.hpp
layout: document
redirect_from:
- /library/graph/undirected/tree/lowest_common_ancestor.hpp
- /library/graph/undirected/tree/lowest_common_ancestor.hpp.html
title: graph/undirected/tree/lowest_common_ancestor.hpp
---
