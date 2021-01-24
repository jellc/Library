---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/data_structure/union_find/basic.hpp
    title: Basic Union-Find
  - icon: ':heavy_check_mark:'
    path: src/data_structure/union_find/unbalanced.hpp
    title: Unbalanced Union-Find
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/unionfind
    links:
    - https://judge.yosupo.jp/problem/unionfind
  bundledCode: "#line 1 \"test/library-checker/unionfind.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/unionfind\"\n\n#include <cstdio>\n\n#line\
    \ 2 \"src/data_structure/union_find/unbalanced.hpp\"\n\n/*\n * @file unbalanced.hpp\n\
    \ * @brief Unbalanced Union-Find\n */\n\n#line 2 \"src/data_structure/union_find/basic.hpp\"\
    \n\n/*\n * @file basic.hpp\n * @brief Basic Union-Find\n */\n\n#include <cassert>\n\
    #include <cstdint>\n#include <vector>\n\nnamespace workspace {\n\ntemplate <typename\
    \ Tp> struct union_find {\n protected:\n  using signed_t = typename std::make_signed<Tp>::type;\n\
    \  using unsigned_t = typename std::make_unsigned<Tp>::type;\n\n  std::vector<signed_t>\
    \ link;\n\n public:\n  /*\n   * @param n The number of nodes.\n   */\n  union_find(Tp\
    \ n = 0) : link(n, 1) {}\n\n  /*\n   * @fn find\n   * @param x A node.\n   * @return\
    \ The representative of the group.\n   */\n  virtual unsigned_t find(unsigned_t\
    \ x) {\n    assert(x < size());\n    return link[x] > 0 ? x : -(link[x] = -(signed_t)find(-link[x]));\n\
    \  }\n\n  /*\n   * @fn size\n   * @return The number of nodes.\n   */\n  unsigned_t\
    \ size() const { return link.size(); }\n\n  /*\n   * @fn size\n   * @param x A\
    \ node.\n   * @return The number of nodes in the group.\n   */\n  virtual unsigned_t\
    \ size(unsigned_t x) {\n    assert(x < size());\n    return link[find(x)];\n \
    \ }\n\n  /*\n   * @fn same\n   * @param x 1st node.\n   * @param y 2nd node.\n\
    \   * @return Whether or not the two nodes belong to the same group.\n   */\n\
    \  bool same(unsigned_t x, unsigned_t y) {\n    assert(x < size());\n    assert(y\
    \ < size());\n    return find(x) == find(y);\n  }\n\n  /*\n   * @fn unite\n  \
    \ * @param x 1st node.\n   * @param y 2nd node.\n   * @return Whether or not the\
    \ two groups were merged anew.\n   */\n  virtual bool unite(unsigned_t x, unsigned_t\
    \ y) {\n    assert(x < size()), x = find(x);\n    assert(y < size()), y = find(y);\n\
    \    if (x == y) return false;\n    if (link[x] < link[y]) std::swap(x, y);\n\
    \    link[x] += link[y];\n    link[y] = -(signed_t)x;\n    return true;\n  }\n\
    };\n\n}  // namespace workspace\n#line 9 \"src/data_structure/union_find/unbalanced.hpp\"\
    \n\nnamespace workspace {\n\nclass unbalanced_union_find : public union_find<uint_least32_t>\
    \ {\n  using base = union_find<uint_least32_t>;\n\n public:\n  using base::union_find;\n\
    \n  bool unite(unsigned_t x, unsigned_t y) override {\n    assert(x < size()),\
    \ x = find(x);\n    assert(y < size()), y = find(y);\n    if (x == y) return false;\n\
    \    link[x] += link[y];\n    link[y] = -(signed_t)x;\n    return true;\n  }\n\
    };\n\n}  // namespace workspace\n#line 6 \"test/library-checker/unionfind.test.cpp\"\
    \n\nint main() {\n  int n, q;\n  scanf(\"%d%d\", &n, &q);\n  workspace::union_find\
    \ uf(n);\n  workspace::unbalanced_union_find ufu(n);\n  while (q--) {\n    int\
    \ t, l, r;\n    scanf(\"%d%d%d\", &t, &l, &r);\n    if (t) {\n      printf(\"\
    %d\\n\", uf.same(l, r));\n      assert(uf.same(l, r) == ufu.same(l, r));\n   \
    \ } else {\n      uf.unite(l, r);\n      ufu.unite(l, r);\n    }\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\n\n#include\
    \ <cstdio>\n\n#include \"src/data_structure/union_find/unbalanced.hpp\"\n\nint\
    \ main() {\n  int n, q;\n  scanf(\"%d%d\", &n, &q);\n  workspace::union_find uf(n);\n\
    \  workspace::unbalanced_union_find ufu(n);\n  while (q--) {\n    int t, l, r;\n\
    \    scanf(\"%d%d%d\", &t, &l, &r);\n    if (t) {\n      printf(\"%d\\n\", uf.same(l,\
    \ r));\n      assert(uf.same(l, r) == ufu.same(l, r));\n    } else {\n      uf.unite(l,\
    \ r);\n      ufu.unite(l, r);\n    }\n  }\n}\n"
  dependsOn:
  - src/data_structure/union_find/unbalanced.hpp
  - src/data_structure/union_find/basic.hpp
  isVerificationFile: true
  path: test/library-checker/unionfind.test.cpp
  requiredBy: []
  timestamp: '2020-11-25 21:36:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/unionfind.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/unionfind.test.cpp
- /verify/test/library-checker/unionfind.test.cpp.html
title: test/library-checker/unionfind.test.cpp
---
