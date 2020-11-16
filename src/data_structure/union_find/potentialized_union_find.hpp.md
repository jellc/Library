---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://atcoder.jp/contests/abc087/submissions/9511701
  bundledCode: "#line 1 \"src/data_structure/union_find/potentialized_union_find.hpp\"\
    \n// #line 2 \"potentialized_union_find.hpp\"\n// verified at https://atcoder.jp/contests/abc087/submissions/9511701\n\
    #ifndef Potentialized_union_find_hpp\n#define Potentialized_union_find_hpp\n#include\
    \ <cassert>\n#include <cstddef>\n#include <vector>\n\ntemplate <class Abelian>\n\
    class potentialized_union_find\n{\n    size_t n;\n    std::vector<int> link;\n\
    \    std::vector<Abelian> diff_weight;\n\npublic:\n    explicit potentialized_union_find(size_t\
    \ _n) : n(_n), link(n, -1), diff_weight(n) {}\n\n    size_t find(const size_t\
    \ x)\n    {\n        assert(x < n);\n        if(link[x] < 0) return x;\n     \
    \   const size_t root = find(link[x]);\n        diff_weight[x] += diff_weight[link[x]];\n\
    \        return link[x] = root;\n    }\n\n    size_t size() const { return n;\
    \ }\n    size_t size(const size_t x) { return -link[find(x)]; }\n\n    Abelian\
    \ weight(size_t x) { return find(x), diff_weight[x]; }\n\n    Abelian diff(size_t\
    \ x, size_t y) { return weight(y) - weight(x); }\n\n    bool same(const size_t\
    \ x, const size_t y) { return find(x) == find(y); }\n\n    bool unite(size_t x,\
    \ size_t y, Abelian w)\n    {\n        w += weight(x) - weight(y);\n        x\
    \ = find(x), y = find(y);\n        if(x == y) return false;\n        if(link[x]\
    \ > link[y]) std::swap(x, y), w = -w;\n        link[x] += link[y], link[y] = x;\n\
    \        diff_weight[y] = w;\n        return true;\n    }\n}; // class potentialized_union_find\n\
    \n#endif\n"
  code: "// #line 2 \"potentialized_union_find.hpp\"\n// verified at https://atcoder.jp/contests/abc087/submissions/9511701\n\
    #ifndef Potentialized_union_find_hpp\n#define Potentialized_union_find_hpp\n#include\
    \ <cassert>\n#include <cstddef>\n#include <vector>\n\ntemplate <class Abelian>\n\
    class potentialized_union_find\n{\n    size_t n;\n    std::vector<int> link;\n\
    \    std::vector<Abelian> diff_weight;\n\npublic:\n    explicit potentialized_union_find(size_t\
    \ _n) : n(_n), link(n, -1), diff_weight(n) {}\n\n    size_t find(const size_t\
    \ x)\n    {\n        assert(x < n);\n        if(link[x] < 0) return x;\n     \
    \   const size_t root = find(link[x]);\n        diff_weight[x] += diff_weight[link[x]];\n\
    \        return link[x] = root;\n    }\n\n    size_t size() const { return n;\
    \ }\n    size_t size(const size_t x) { return -link[find(x)]; }\n\n    Abelian\
    \ weight(size_t x) { return find(x), diff_weight[x]; }\n\n    Abelian diff(size_t\
    \ x, size_t y) { return weight(y) - weight(x); }\n\n    bool same(const size_t\
    \ x, const size_t y) { return find(x) == find(y); }\n\n    bool unite(size_t x,\
    \ size_t y, Abelian w)\n    {\n        w += weight(x) - weight(y);\n        x\
    \ = find(x), y = find(y);\n        if(x == y) return false;\n        if(link[x]\
    \ > link[y]) std::swap(x, y), w = -w;\n        link[x] += link[y], link[y] = x;\n\
    \        diff_weight[y] = w;\n        return true;\n    }\n}; // class potentialized_union_find\n\
    \n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: src/data_structure/union_find/potentialized_union_find.hpp
  requiredBy: []
  timestamp: '2020-11-16 21:34:32+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/data_structure/union_find/potentialized_union_find.hpp
layout: document
redirect_from:
- /library/src/data_structure/union_find/potentialized_union_find.hpp
- /library/src/data_structure/union_find/potentialized_union_find.hpp.html
title: src/data_structure/union_find/potentialized_union_find.hpp
---
