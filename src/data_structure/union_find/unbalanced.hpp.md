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
    document_title: Unbalanced Union-Find
    links: []
  bundledCode: "#line 2 \"src/data_structure/union_find/unbalanced.hpp\"\n\n/*\n *\
    \ @file unbalanced.hpp\n * @brief Unbalanced Union-Find\n */\n\n#line 2 \"src/data_structure/union_find/basic.hpp\"\
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
    };\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file unbalanced.hpp\n * @brief Unbalanced Union-Find\n\
    \ */\n\n#include \"basic.hpp\"\n\nnamespace workspace {\n\nclass unbalanced_union_find\
    \ : public union_find<uint_least32_t> {\n  using base = union_find<uint_least32_t>;\n\
    \n public:\n  using base::union_find;\n\n  bool unite(unsigned_t x, unsigned_t\
    \ y) override {\n    assert(x < size()), x = find(x);\n    assert(y < size()),\
    \ y = find(y);\n    if (x == y) return false;\n    link[x] += link[y];\n    link[y]\
    \ = -(signed_t)x;\n    return true;\n  }\n};\n\n}  // namespace workspace\n"
  dependsOn:
  - src/data_structure/union_find/basic.hpp
  isVerificationFile: false
  path: src/data_structure/union_find/unbalanced.hpp
  requiredBy: []
  timestamp: '2020-11-25 21:36:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/unionfind.test.cpp
documentation_of: src/data_structure/union_find/unbalanced.hpp
layout: document
redirect_from:
- /library/src/data_structure/union_find/unbalanced.hpp
- /library/src/data_structure/union_find/unbalanced.hpp.html
title: Unbalanced Union-Find
---
