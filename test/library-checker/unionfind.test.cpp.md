---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/union_find/basic.hpp
    title: Basic Union-Find
  - icon: ':heavy_check_mark:'
    path: data_structure/union_find/unbalanced.hpp
    title: data_structure/union_find/unbalanced.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/unionfind
    links:
    - https://judge.yosupo.jp/problem/unionfind
  bundledCode: "#line 1 \"test/library-checker/unionfind.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/unionfind\"\n#include <cstdio>\n\n#line 2\
    \ \"data_structure/union_find/basic.hpp\"\n\n/*\n * @file basic.hpp\n * @brief\
    \ Basic Union-Find\n */\n\n#include <cassert>\n#include <vector>\n\nstruct union_find\
    \ {\n  /*\n   * @param n The number of nodes.\n   */\n  union_find(size_t n =\
    \ 0) : link(n, -1) {}\n\n  /*\n   * @fn find\n   * @param x A node.\n   * @return\
    \ The representative of the group.\n   */\n  size_t find(size_t x) {\n    assert(x\
    \ < size());\n    return link[x] < 0 ? x : (link[x] = find(link[x]));\n  }\n\n\
    \  /*\n   * @fn size\n   * @return The number of nodes.\n   */\n  size_t size()\
    \ const { return link.size(); }\n\n  /*\n   * @fn size\n   * @param x A node.\n\
    \   * @return The number of nodes in the group.\n   */\n  size_t size(size_t x)\
    \ {\n    assert(x < size());\n    return -link[find(x)];\n  }\n\n  /*\n   * @fn\
    \ same\n   * @param x 1st node.\n   * @param y 2nd node.\n   * @return Whether\
    \ or not the two nodes belong to the same group.\n   */\n  bool same(size_t x,\
    \ size_t y) {\n    assert(x < size());\n    assert(y < size());\n    return find(x)\
    \ == find(y);\n  }\n\n  /*\n   * @fn unite\n   * @param x 1st node.\n   * @param\
    \ y 2nd node.\n   * @return Whether or not the two groups were merged anew.\n\
    \   */\n  virtual bool unite(size_t x, size_t y) {\n    assert(x < size()), x\
    \ = find(x);\n    assert(y < size()), y = find(y);\n    if (x == y) return false;\n\
    \    if (link[x] > link[y]) std::swap(x, y);\n    link[x] += link[y];\n    link[y]\
    \ = x;\n    return true;\n  }\n\n protected:\n  std::vector<int> link;\n};\n#line\
    \ 3 \"data_structure/union_find/unbalanced.hpp\"\nstruct union_find_unbalanced\
    \ : union_find\n{\n    using union_find::union_find;\n    \n    bool unite(size_t\
    \ x, size_t y) override\n    {\n        assert(x < size() && y < size());\n  \
    \      x = find(x), y = find(y);\n        if(x == y) return false;\n        link[x]\
    \ += link[y];\n        link[y] = x;\n        return true;\n    }\n}; // class\
    \ union_find_unbalanced\n#line 5 \"test/library-checker/unionfind.test.cpp\"\n\
    \nint main() {\n  int n, q;\n  scanf(\"%d%d\", &n, &q);\n  union_find uf(n);\n\
    \  union_find_unbalanced ufu(n);\n  while (q--) {\n    int t, l, r;\n    scanf(\"\
    %d%d%d\", &t, &l, &r);\n    if (t) {\n      printf(\"%d\\n\", uf.same(l, r));\n\
    \      assert(uf.same(l, r) == ufu.same(l, r));\n    } else {\n      uf.unite(l,\
    \ r);\n      ufu.unite(l, r);\n    }\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\n#include <cstdio>\n\
    \n#include \"data_structure/union_find/unbalanced.hpp\"\n\nint main() {\n  int\
    \ n, q;\n  scanf(\"%d%d\", &n, &q);\n  union_find uf(n);\n  union_find_unbalanced\
    \ ufu(n);\n  while (q--) {\n    int t, l, r;\n    scanf(\"%d%d%d\", &t, &l, &r);\n\
    \    if (t) {\n      printf(\"%d\\n\", uf.same(l, r));\n      assert(uf.same(l,\
    \ r) == ufu.same(l, r));\n    } else {\n      uf.unite(l, r);\n      ufu.unite(l,\
    \ r);\n    }\n  }\n}\n"
  dependsOn:
  - data_structure/union_find/unbalanced.hpp
  - data_structure/union_find/basic.hpp
  isVerificationFile: true
  path: test/library-checker/unionfind.test.cpp
  requiredBy: []
  timestamp: '2020-11-14 00:11:52+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/unionfind.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/unionfind.test.cpp
- /verify/test/library-checker/unionfind.test.cpp.html
title: test/library-checker/unionfind.test.cpp
---
