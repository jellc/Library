---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/undirected/tree/lowest_common_ancestor.hpp
    title: graph/undirected/tree/lowest_common_ancestor.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/lca
    links:
    - https://judge.yosupo.jp/problem/lca
  bundledCode: "#line 1 \"test/library-checker/lowest_common_ancestor.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\n#include <cstdio>\n#include\
    \ <ext/rope>\n\n#line 2 \"graph/undirected/tree/lowest_common_ancestor.hpp\"\n\
    #include <cassert>\n#include <vector>\n\nclass lowest_common_ancestor {\n  std::vector<std::vector<size_t>>\
    \ tree, table;\n  std::vector<size_t> &sorted, index;\n\n  void tour(const size_t\
    \ node, const size_t prev) {\n    index[node] = sorted.size();\n    sorted.emplace_back(node);\n\
    \    for (const size_t to : tree[node]) {\n      if (to != prev) {\n        tour(to,\
    \ node);\n        sorted.emplace_back(node);\n      }\n    }\n  }\n\n  void make_table()\
    \ {\n    const size_t len = sorted.size();\n    for (size_t w = 2; w < len; w\
    \ <<= 1) {\n      auto &curr(table.back()), next(curr);\n      for (size_t i =\
    \ 0, j = w >> 1; j != len; ++i, ++j)\n        if (index[curr[j]] < index[curr[i]])\
    \ next[i] = curr[j];\n      table.emplace_back(next);\n    }\n  }\n\n public:\n\
    \  lowest_common_ancestor(const size_t n = 0)\n      : tree(n), table(1), sorted(table.front()),\
    \ index(n) {}\n\n  size_t size() const { return tree.size(); }\n\n  void add_edge(const\
    \ size_t u, const size_t v) {\n    assert(u < size());\n    assert(v < size());\n\
    \    tree[u].emplace_back(v);\n    tree[v].emplace_back(u);\n  }\n\n  // O(n log(n))\n\
    \  void make(const size_t root) {\n    assert(root < size());\n    tour(root,\
    \ root);\n    make_table();\n  }\n\n  // O(1)\n  size_t query(size_t u, size_t\
    \ v) const {\n    assert(u < size());\n    assert(v < size());\n    if (u == v)\
    \ return u;\n    if ((v = index[v]) < (u = index[u])) std::swap(u, v);\n    size_t\
    \ h = std::__lg(v - u);\n    return std::min(table[h][u], table[h][v - (1 << h)]);\n\
    \  }\n};  // class lowest_common_ancestor\n#line 6 \"test/library-checker/lowest_common_ancestor.test.cpp\"\
    \n\nint main() {\n  int n, q;\n  scanf(\"%d%d\", &n, &q);\n  lowest_common_ancestor\
    \ lca(n);\n  for (int i = 1, p; i < n; i++) {\n    scanf(\"%d\", &p);\n    lca.add_edge(i,\
    \ p);\n  }\n  lca.make(0);\n  for (int u, v; q--;) {\n    scanf(\"%d%d\", &u,\
    \ &v);\n    printf(\"%d\\n\", (int)lca.query(u, v));\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\n#include <cstdio>\n\
    #include <ext/rope>\n\n#include \"graph/undirected/tree/lowest_common_ancestor.hpp\"\
    \n\nint main() {\n  int n, q;\n  scanf(\"%d%d\", &n, &q);\n  lowest_common_ancestor\
    \ lca(n);\n  for (int i = 1, p; i < n; i++) {\n    scanf(\"%d\", &p);\n    lca.add_edge(i,\
    \ p);\n  }\n  lca.make(0);\n  for (int u, v; q--;) {\n    scanf(\"%d%d\", &u,\
    \ &v);\n    printf(\"%d\\n\", (int)lca.query(u, v));\n  }\n}\n"
  dependsOn:
  - graph/undirected/tree/lowest_common_ancestor.hpp
  isVerificationFile: true
  path: test/library-checker/lowest_common_ancestor.test.cpp
  requiredBy: []
  timestamp: '2020-09-25 17:28:18+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/lowest_common_ancestor.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/lowest_common_ancestor.test.cpp
- /verify/test/library-checker/lowest_common_ancestor.test.cpp.html
title: test/library-checker/lowest_common_ancestor.test.cpp
---
