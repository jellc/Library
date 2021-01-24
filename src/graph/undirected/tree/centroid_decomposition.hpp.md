---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/graph/undirected/tree/centroid_decomposition.hpp\"\n\
    #include <cassert>\n#include <vector>\n\nclass centroid_decomposition\n{\n   \
    \ std::vector<std::vector<size_t>> tree, sub;\n    std::vector<size_t> siz;\n\
    \    std::vector<bool> chkd;\n\n    bool dfs(size_t nod, size_t pre, size_t all,\
    \ size_t rot)\n    {\n        siz[nod] = 1;\n        bool cent = true;\n     \
    \   for(size_t to : tree[nod])\n        {\n            if(to == pre || chkd[to])\
    \ continue;\n            if(dfs(to, nod, all, rot)) return true;\n           \
    \ siz[nod] += siz[to];\n            if(siz[to] > all / 2) cent = false;\n    \
    \    }\n        if(all - siz[nod] > all / 2) cent = false;\n        if(!cent)\
    \ return false;\n        chkd[nod] = true;\n        if(~rot) sub[rot].emplace_back(nod);\n\
    \        else root = nod;\n        for(size_t to : tree[nod])\n        {\n   \
    \         if(chkd[to]) continue;\n            if(to == pre) assert(dfs(to, nod,\
    \ all - siz[nod], nod));\n            else assert(dfs(to, nod, siz[to], nod));\n\
    \        }\n        return true;\n    }\n\npublic:\n    size_t root;\n\n    centroid_decomposition(size_t\
    \ _n = 0) : tree(_n), sub(_n), siz(_n), chkd(_n) {}\n\n    size_t size() const\
    \ { return tree.size(); }\n\n    void add_edge(size_t u, size_t v)\n    {\n  \
    \      assert(u < size()); assert(v < size());\n        tree[u].emplace_back(v);\n\
    \        tree[v].emplace_back(u);\n    }\n\n    size_t make() { assert(dfs(0,\
    \ 0, size(), -1)); return root; }\n\n    decltype(sub)::const_reference operator[](size_t\
    \ nod) const { return sub[nod]; }\n}; // class centroid_decomposition\n"
  code: "#include <cassert>\n#include <vector>\n\nclass centroid_decomposition\n{\n\
    \    std::vector<std::vector<size_t>> tree, sub;\n    std::vector<size_t> siz;\n\
    \    std::vector<bool> chkd;\n\n    bool dfs(size_t nod, size_t pre, size_t all,\
    \ size_t rot)\n    {\n        siz[nod] = 1;\n        bool cent = true;\n     \
    \   for(size_t to : tree[nod])\n        {\n            if(to == pre || chkd[to])\
    \ continue;\n            if(dfs(to, nod, all, rot)) return true;\n           \
    \ siz[nod] += siz[to];\n            if(siz[to] > all / 2) cent = false;\n    \
    \    }\n        if(all - siz[nod] > all / 2) cent = false;\n        if(!cent)\
    \ return false;\n        chkd[nod] = true;\n        if(~rot) sub[rot].emplace_back(nod);\n\
    \        else root = nod;\n        for(size_t to : tree[nod])\n        {\n   \
    \         if(chkd[to]) continue;\n            if(to == pre) assert(dfs(to, nod,\
    \ all - siz[nod], nod));\n            else assert(dfs(to, nod, siz[to], nod));\n\
    \        }\n        return true;\n    }\n\npublic:\n    size_t root;\n\n    centroid_decomposition(size_t\
    \ _n = 0) : tree(_n), sub(_n), siz(_n), chkd(_n) {}\n\n    size_t size() const\
    \ { return tree.size(); }\n\n    void add_edge(size_t u, size_t v)\n    {\n  \
    \      assert(u < size()); assert(v < size());\n        tree[u].emplace_back(v);\n\
    \        tree[v].emplace_back(u);\n    }\n\n    size_t make() { assert(dfs(0,\
    \ 0, size(), -1)); return root; }\n\n    decltype(sub)::const_reference operator[](size_t\
    \ nod) const { return sub[nod]; }\n}; // class centroid_decomposition\n"
  dependsOn: []
  isVerificationFile: false
  path: src/graph/undirected/tree/centroid_decomposition.hpp
  requiredBy: []
  timestamp: '2020-11-16 14:21:51+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/graph/undirected/tree/centroid_decomposition.hpp
layout: document
redirect_from:
- /library/src/graph/undirected/tree/centroid_decomposition.hpp
- /library/src/graph/undirected/tree/centroid_decomposition.hpp.html
title: src/graph/undirected/tree/centroid_decomposition.hpp
---
