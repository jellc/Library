---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/union_find/basic.hpp
    title: data_structure/union_find/basic.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/unionfind.test.cpp
    title: test/library-checker/unionfind.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 2 \"data_structure/union_find/basic.hpp\"\n#include <cassert>\n\
    #include <vector>\nstruct union_find\n{\n    union_find(const size_t &n = 0) :\
    \ link(n, -1) {}\n\n    size_t find(const size_t &x)\n    {\n        assert(x\
    \ < size());\n        return link[x] < 0 ? x : (link[x] = find(link[x]));\n  \
    \  }\n\n    size_t size() const { return link.size(); }\n\n    size_t size(const\
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
    \ true;\n    }\n}; // class union_find_unbalanced\n"
  code: "#pragma once\n#include \"basic.hpp\"\nstruct union_find_unbalanced : union_find\n\
    {\n    using union_find::union_find;\n    \n    bool unite(size_t x, size_t y)\
    \ override\n    {\n        assert(x < size() && y < size());\n        x = find(x),\
    \ y = find(y);\n        if(x == y) return false;\n        link[x] += link[y];\n\
    \        link[y] = x;\n        return true;\n    }\n}; // class union_find_unbalanced\n"
  dependsOn:
  - data_structure/union_find/basic.hpp
  isVerificationFile: false
  path: data_structure/union_find/unbalanced.hpp
  requiredBy: []
  timestamp: '2020-08-30 00:35:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/unionfind.test.cpp
documentation_of: data_structure/union_find/unbalanced.hpp
layout: document
redirect_from:
- /library/data_structure/union_find/unbalanced.hpp
- /library/data_structure/union_find/unbalanced.hpp.html
title: data_structure/union_find/unbalanced.hpp
---
