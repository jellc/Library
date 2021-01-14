---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/DSL_3_D.test.cpp
    title: test/aizu-online-judge/DSL_3_D.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Disjoint Sparse Table
    links: []
  bundledCode: "#line 1 \"src/data_structure/disjoint_sparse_table.hpp\"\n/**\n *\
    \ @file disjoint_sparse_table.hpp\n * @brief Disjoint Sparse Table\n * @date 2021-01-14\n\
    \ *\n *\n */\n\n#include <cassert>\n#include <vector>\n\nnamespace workspace {\n\
    \n/**\n * @brief Disjoint Sparse Table.\n *\n * @tparam Semigroup `operator+`\n\
    \ */\ntemplate <class Semigroup> class disjoint_sparse_table {\n  using container_type\
    \ = std::vector<std::vector<Semigroup>>;\n  container_type __dst;\n\n public:\n\
    \  using value_type = Semigroup;\n  using size_type = typename container_type::size_type;\n\
    \  using const_reference = typename container_type::const_reference;\n\n public:\n\
    \  disjoint_sparse_table() = default;\n\n  /**\n   * @brief Construct in O(n log(n))\
    \ time.\n   *\n   * @param __args Create a vector from.\n   */\n  template <class...\
    \ Args> disjoint_sparse_table(Args... __args) {\n    __dst.emplace_back(__args...);\n\
    \    const size_type size = __dst.front().size();\n    for (size_type __w = 2;\
    \ __w < size; __w <<= 1) {\n      typename container_type::value_type __t;\n \
    \     __t.reserve(size);\n      for (size_type __i = __w; __i < size; __i += __w\
    \ << 1) {\n        __t.emplace_back(__dst.front()[__i - 1]);\n        for (size_type\
    \ __k = 2; __k <= __w; ++__k)\n          __t.emplace_back(__dst.front()[__i -\
    \ __k] + __t.back());\n        __t.emplace_back(__dst.front()[__i]);\n       \
    \ for (size_type __k = 1; __k < __w && __i + __k < size; ++__k)\n          __t.emplace_back(__t.back()\
    \ + __dst.front()[__i + __k]);\n      }\n      __dst.emplace_back(::std::move(__t));\n\
    \    }\n  }\n\n  /**\n   * @return The number of elements.\n   */\n  size_type\
    \ size() const { return __dst.empty() ? 0 : __dst.front().size(); }\n\n  bool\
    \ empty() const { return !size(); }\n\n  /**\n   * @param __first Left end, inclusive.\n\
    \   * @param __last Right end, exclusive.\n   * @return The sum of given range.\n\
    \   */\n  value_type fold(size_type __first, size_type __last) {\n    assert(__first\
    \ < __last);\n    --__last;\n    if (__first == __last) return __dst.front()[__first];\n\
    \    size_type __b = 31 - __builtin_clz(__first ^ __last);\n    return __dst[__b][__first\
    \ ^ ((1 << __b) - 1)] + __dst[__b][__last];\n  }\n\n  const_reference operator[](size_type\
    \ __i) const { return __dst.front()[__i]; }\n};\n\n}  // namespace workspace\n"
  code: "/**\n * @file disjoint_sparse_table.hpp\n * @brief Disjoint Sparse Table\n\
    \ * @date 2021-01-14\n *\n *\n */\n\n#include <cassert>\n#include <vector>\n\n\
    namespace workspace {\n\n/**\n * @brief Disjoint Sparse Table.\n *\n * @tparam\
    \ Semigroup `operator+`\n */\ntemplate <class Semigroup> class disjoint_sparse_table\
    \ {\n  using container_type = std::vector<std::vector<Semigroup>>;\n  container_type\
    \ __dst;\n\n public:\n  using value_type = Semigroup;\n  using size_type = typename\
    \ container_type::size_type;\n  using const_reference = typename container_type::const_reference;\n\
    \n public:\n  disjoint_sparse_table() = default;\n\n  /**\n   * @brief Construct\
    \ in O(n log(n)) time.\n   *\n   * @param __args Create a vector from.\n   */\n\
    \  template <class... Args> disjoint_sparse_table(Args... __args) {\n    __dst.emplace_back(__args...);\n\
    \    const size_type size = __dst.front().size();\n    for (size_type __w = 2;\
    \ __w < size; __w <<= 1) {\n      typename container_type::value_type __t;\n \
    \     __t.reserve(size);\n      for (size_type __i = __w; __i < size; __i += __w\
    \ << 1) {\n        __t.emplace_back(__dst.front()[__i - 1]);\n        for (size_type\
    \ __k = 2; __k <= __w; ++__k)\n          __t.emplace_back(__dst.front()[__i -\
    \ __k] + __t.back());\n        __t.emplace_back(__dst.front()[__i]);\n       \
    \ for (size_type __k = 1; __k < __w && __i + __k < size; ++__k)\n          __t.emplace_back(__t.back()\
    \ + __dst.front()[__i + __k]);\n      }\n      __dst.emplace_back(::std::move(__t));\n\
    \    }\n  }\n\n  /**\n   * @return The number of elements.\n   */\n  size_type\
    \ size() const { return __dst.empty() ? 0 : __dst.front().size(); }\n\n  bool\
    \ empty() const { return !size(); }\n\n  /**\n   * @param __first Left end, inclusive.\n\
    \   * @param __last Right end, exclusive.\n   * @return The sum of given range.\n\
    \   */\n  value_type fold(size_type __first, size_type __last) {\n    assert(__first\
    \ < __last);\n    --__last;\n    if (__first == __last) return __dst.front()[__first];\n\
    \    size_type __b = 31 - __builtin_clz(__first ^ __last);\n    return __dst[__b][__first\
    \ ^ ((1 << __b) - 1)] + __dst[__b][__last];\n  }\n\n  const_reference operator[](size_type\
    \ __i) const { return __dst.front()[__i]; }\n};\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/data_structure/disjoint_sparse_table.hpp
  requiredBy: []
  timestamp: '2021-01-14 21:12:41+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aizu-online-judge/DSL_3_D.test.cpp
documentation_of: src/data_structure/disjoint_sparse_table.hpp
layout: document
redirect_from:
- /library/src/data_structure/disjoint_sparse_table.hpp
- /library/src/data_structure/disjoint_sparse_table.hpp.html
title: Disjoint Sparse Table
---
