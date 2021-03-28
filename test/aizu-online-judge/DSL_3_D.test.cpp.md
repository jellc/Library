---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/data_structure/disjoint_sparse_table.hpp
    title: Disjoint Sparse Table
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/DSL_3_D
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/DSL_3_D
  bundledCode: "#line 1 \"test/aizu-online-judge/DSL_3_D.test.cpp\"\n#define PROBLEM\
    \ \"https://onlinejudge.u-aizu.ac.jp/problems/DSL_3_D\"\n\n#include <cstdio>\n\
    \n#line 1 \"src/data_structure/disjoint_sparse_table.hpp\"\n/**\n * @file disjoint_sparse_table.hpp\n\
    \ * @brief Disjoint Sparse Table\n */\n\n#include <cassert>\n#include <vector>\n\
    \nnamespace workspace {\n\n/**\n * @brief Disjoint Sparse Table.\n *\n * @tparam\
    \ _Semigroup `operator+`\n */\ntemplate <class _Semigroup> class disjoint_sparse_table\
    \ {\n public:\n  using value_type = _Semigroup;\n  using container_type = std::vector<std::vector<_Semigroup>>;\n\
    \  using size_type = typename container_type::size_type;\n  using const_reference\
    \ = typename container_type::const_reference;\n\n protected:\n  container_type\
    \ __table;\n\n  void make() {\n    for (size_type __w = 2; __w < size(); __w <<=\
    \ 1) {\n      auto &__t = __table.emplace_back();\n      __t.reserve(size());\n\
    \n      const auto &__a = __table.front();\n\n      for (size_type __i = __w;\
    \ __i < size(); __i += __w << 1) {\n        __t.emplace_back(__a[__i - 1]);\n\n\
    \        for (size_type __k = 2; __k <= __w; ++__k)\n          __t.emplace_back(__a[__i\
    \ - __k] + __t.back());\n\n        __t.emplace_back(__a[__i]);\n\n        for\
    \ (size_type __k = 1; __k < __w && __i + __k < size(); ++__k)\n          __t.emplace_back(__t.back()\
    \ + __a[__i + __k]);\n      }\n    }\n  }\n\n public:\n  /**\n   * @brief Default\
    \ construct.\n   */\n  disjoint_sparse_table() = default;\n\n  /**\n   * @brief\
    \ Construct in O(n log(n)) time.\n   *\n   * @param __x Vector\n   */\n  disjoint_sparse_table(const\
    \ std::vector<_Semigroup> &__x) {\n    __table.emplace_back(__x);\n    make();\n\
    \  }\n\n  /**\n   * @brief Construct in O(n log(n)) time.\n   *\n   * @param __x\
    \ Vector\n   */\n  disjoint_sparse_table(std::vector<_Semigroup> &&__x) {\n  \
    \  __table.emplace_back(std::move(__x));\n    make();\n  }\n\n  /**\n   * @brief\
    \ Construct in O(n log(n)) time.\n   *\n   * @param __first\n   * @param __last\n\
    \   */\n  template <class _IIter> disjoint_sparse_table(_IIter __first, _IIter\
    \ __last) {\n    __table.emplace_back(__first, __last);\n    make();\n  }\n\n\
    \  /**\n   * @return Number of elements.\n   */\n  size_type size() const {\n\
    \    return __table.empty() ? 0 : __table.front().size();\n  }\n\n  bool empty()\
    \ const { return !size(); }\n\n  /**\n   * @param __first Left end, inclusive.\n\
    \   * @param __last Right end, exclusive.\n   * @return Sum of given range.\n\
    \   */\n  value_type fold(size_type __first, size_type __last) {\n    assert(__first\
    \ < __last);\n    --__last;\n    if (__first == __last) return __table.front()[__first];\n\
    \n    size_type __b = 31 - __builtin_clz(__first ^ __last);\n    return __table[__b][__first\
    \ ^ ((1 << __b) - 1)] + __table[__b][__last];\n  }\n\n  const_reference operator[](size_type\
    \ __i) const {\n    return __table.front()[__i];\n  }\n};\n\ntemplate <class _IIter>\n\
    disjoint_sparse_table(_IIter, _IIter)\n    -> disjoint_sparse_table<typename std::iterator_traits<_IIter>::value_type>;\n\
    \n}  // namespace workspace\n#line 6 \"test/aizu-online-judge/DSL_3_D.test.cpp\"\
    \n\nint main() {\n  using namespace workspace;\n\n  struct min {\n    int _v;\n\
    \    min(int _v) : _v(_v) {}\n    min operator+(min r) const { return {_v < r._v\
    \ ? _v : r._v}; }\n  };\n\n  int n, k, a[1 << 20];\n  scanf(\"%d%d\", &n, &k);\n\
    \  for (int i = 0; i < n; ++i) scanf(\"%d\", a + i);\n  disjoint_sparse_table<min>\
    \ dst(a, a + n);\n  for (int i = k; i < n; ++i) printf(\"%d \", dst.fold(i - k,\
    \ i)._v);\n  printf(\"%d\\n\", dst.fold(n - k, n)._v);\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/DSL_3_D\"\n\n\
    #include <cstdio>\n\n#include \"src/data_structure/disjoint_sparse_table.hpp\"\
    \n\nint main() {\n  using namespace workspace;\n\n  struct min {\n    int _v;\n\
    \    min(int _v) : _v(_v) {}\n    min operator+(min r) const { return {_v < r._v\
    \ ? _v : r._v}; }\n  };\n\n  int n, k, a[1 << 20];\n  scanf(\"%d%d\", &n, &k);\n\
    \  for (int i = 0; i < n; ++i) scanf(\"%d\", a + i);\n  disjoint_sparse_table<min>\
    \ dst(a, a + n);\n  for (int i = k; i < n; ++i) printf(\"%d \", dst.fold(i - k,\
    \ i)._v);\n  printf(\"%d\\n\", dst.fold(n - k, n)._v);\n}\n"
  dependsOn:
  - src/data_structure/disjoint_sparse_table.hpp
  isVerificationFile: true
  path: test/aizu-online-judge/DSL_3_D.test.cpp
  requiredBy: []
  timestamp: '2021-03-28 15:03:13+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aizu-online-judge/DSL_3_D.test.cpp
layout: document
redirect_from:
- /verify/test/aizu-online-judge/DSL_3_D.test.cpp
- /verify/test/aizu-online-judge/DSL_3_D.test.cpp.html
title: test/aizu-online-judge/DSL_3_D.test.cpp
---
