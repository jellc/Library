---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/data_structure/union_find/basic.hpp
    title: Basic Union-Find
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/unionfind.test.cpp
    title: test/library-checker/unionfind.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/data_structure/union_find/basic.hpp\"\n\n/*\n * @file\
    \ basic.hpp\n * @brief Basic Union-Find\n */\n\n#include <cassert>\n#include <vector>\n\
    \nstruct union_find {\n  /*\n   * @param n The number of nodes.\n   */\n  union_find(size_t\
    \ n = 0) : link(n, -1) {}\n\n  /*\n   * @fn find\n   * @param x A node.\n   *\
    \ @return The representative of the group.\n   */\n  size_t find(size_t x) {\n\
    \    assert(x < size());\n    return link[x] < 0 ? x : (link[x] = find(link[x]));\n\
    \  }\n\n  /*\n   * @fn size\n   * @return The number of nodes.\n   */\n  size_t\
    \ size() const { return link.size(); }\n\n  /*\n   * @fn size\n   * @param x A\
    \ node.\n   * @return The number of nodes in the group.\n   */\n  size_t size(size_t\
    \ x) {\n    assert(x < size());\n    return -link[find(x)];\n  }\n\n  /*\n   *\
    \ @fn same\n   * @param x 1st node.\n   * @param y 2nd node.\n   * @return Whether\
    \ or not the two nodes belong to the same group.\n   */\n  bool same(size_t x,\
    \ size_t y) {\n    assert(x < size());\n    assert(y < size());\n    return find(x)\
    \ == find(y);\n  }\n\n  /*\n   * @fn unite\n   * @param x 1st node.\n   * @param\
    \ y 2nd node.\n   * @return Whether or not the two groups were merged anew.\n\
    \   */\n  virtual bool unite(size_t x, size_t y) {\n    assert(x < size()), x\
    \ = find(x);\n    assert(y < size()), y = find(y);\n    if (x == y) return false;\n\
    \    if (link[x] > link[y]) std::swap(x, y);\n    link[x] += link[y];\n    link[y]\
    \ = x;\n    return true;\n  }\n\n protected:\n  std::vector<int> link;\n};\n#line\
    \ 3 \"src/data_structure/union_find/unbalanced.hpp\"\nstruct union_find_unbalanced\
    \ : union_find\n{\n    using union_find::union_find;\n    \n    bool unite(size_t\
    \ x, size_t y) override\n    {\n        assert(x < size() && y < size());\n  \
    \      x = find(x), y = find(y);\n        if(x == y) return false;\n        link[x]\
    \ += link[y];\n        link[y] = x;\n        return true;\n    }\n}; // class\
    \ union_find_unbalanced\n"
  code: "#pragma once\n#include \"basic.hpp\"\nstruct union_find_unbalanced : union_find\n\
    {\n    using union_find::union_find;\n    \n    bool unite(size_t x, size_t y)\
    \ override\n    {\n        assert(x < size() && y < size());\n        x = find(x),\
    \ y = find(y);\n        if(x == y) return false;\n        link[x] += link[y];\n\
    \        link[y] = x;\n        return true;\n    }\n}; // class union_find_unbalanced\n"
  dependsOn:
  - src/data_structure/union_find/basic.hpp
  isVerificationFile: false
  path: src/data_structure/union_find/unbalanced.hpp
  requiredBy: []
  timestamp: '2020-11-16 21:34:32+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/unionfind.test.cpp
documentation_of: src/data_structure/union_find/unbalanced.hpp
layout: document
redirect_from:
- /library/src/data_structure/union_find/unbalanced.hpp
- /library/src/data_structure/union_find/unbalanced.hpp.html
title: src/data_structure/union_find/unbalanced.hpp
---
