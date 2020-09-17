---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/union_find/unbalanced.hpp
    title: data_structure/union_find/unbalanced.hpp
  - icon: ':heavy_check_mark:'
    path: data_structure/union_find/basic.hpp
    title: data_structure/union_find/basic.hpp
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
    \ \"https://judge.yosupo.jp/problem/unionfind\"\n#line 2 \"data_structure/union_find/basic.hpp\"\
    \n#include <cassert>\n#include <vector>\nstruct union_find\n{\n    union_find(const\
    \ size_t &n = 0) : link(n, -1) {}\n\n    size_t find(const size_t &x)\n    {\n\
    \        assert(x < size());\n        return link[x] < 0 ? x : (link[x] = find(link[x]));\n\
    \    }\n\n    size_t size() const { return link.size(); }\n\n    size_t size(const\
    \ size_t &x)\n    {\n        assert(x < size());\n        return -link[find(x)];\n\
    \    }\n\n    bool same(const size_t &x, const size_t &y)\n    {\n        assert(x\
    \ < size() && y < size());\n        return find(x) == find(y);\n    }\n\n    virtual\
    \ bool unite(size_t x, size_t y)\n    {\n        assert(x < size() && y < size());\n\
    \        x = find(x), y = find(y);\n        if(x == y) return false;\n       \
    \ if(link[x] > link[y]) std::swap(x, y);\n        link[x] += link[y];\n      \
    \  link[y] = x;\n        return true;\n    }\n\nprotected:\n    std::vector<int>\
    \ link;\n}; // class union_find\n#line 3 \"data_structure/union_find/unbalanced.hpp\"\
    \nstruct union_find_unbalanced : union_find\n{\n    using union_find::union_find;\n\
    \    \n    bool unite(size_t x, size_t y) override\n    {\n        assert(x <\
    \ size() && y < size());\n        x = find(x), y = find(y);\n        if(x == y)\
    \ return false;\n        link[x] += link[y];\n        link[y] = x;\n        return\
    \ true;\n    }\n}; // class union_find_unbalanced\n#line 3 \"test/library-checker/unionfind.test.cpp\"\
    \n#include <cstdio>\n\nint main()\n{\n    int n,q; scanf(\"%d%d\",&n,&q);\n  \
    \  union_find uf(n);\n    union_find_unbalanced ufu(n);\n    while(q--)\n    {\n\
    \        int t,l,r; scanf(\"%d%d%d\",&t,&l,&r);\n        if(t)\n        {\n  \
    \          printf(\"%d\\n\",uf.same(l,r));\n            assert(uf.same(l,r)==ufu.same(l,r));\n\
    \        }\n        else\n        {\n            uf.unite(l,r);\n            ufu.unite(l,r);\n\
    \        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\n#include \"\
    data_structure/union_find/unbalanced.hpp\"\n#include <cstdio>\n\nint main()\n\
    {\n    int n,q; scanf(\"%d%d\",&n,&q);\n    union_find uf(n);\n    union_find_unbalanced\
    \ ufu(n);\n    while(q--)\n    {\n        int t,l,r; scanf(\"%d%d%d\",&t,&l,&r);\n\
    \        if(t)\n        {\n            printf(\"%d\\n\",uf.same(l,r));\n     \
    \       assert(uf.same(l,r)==ufu.same(l,r));\n        }\n        else\n      \
    \  {\n            uf.unite(l,r);\n            ufu.unite(l,r);\n        }\n   \
    \ }\n}\n"
  dependsOn:
  - data_structure/union_find/unbalanced.hpp
  - data_structure/union_find/basic.hpp
  isVerificationFile: true
  path: test/library-checker/unionfind.test.cpp
  requiredBy: []
  timestamp: '2020-08-30 00:35:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/unionfind.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/unionfind.test.cpp
- /verify/test/library-checker/unionfind.test.cpp.html
title: test/library-checker/unionfind.test.cpp
---
