---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/range_kth_smallest.test.cpp
    title: test/library-checker/range_kth_smallest.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/static_range_inversions_query.test.cpp
    title: test/library-checker/static_range_inversions_query.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Mo's Algorithm
    links: []
  bundledCode: "#line 2 \"src/data_structure/Mo.hpp\"\n\n/**\n * @file Mo.hpp\n *\
    \ @brief Mo's Algorithm\n */\n\n#include <cassert>\n#include <cmath>\n#include\
    \ <functional>\n#include <vector>\n\nnamespace workspace {\n\n/**\n * @brief Mo's\
    \ Alorithm. Process queries about contiguous subarrays.\n *\n * @tparam _Push_back\n\
    \ * @tparam _Pop_back\n * @tparam _Push_front Use `_Push_back` as default\n *\
    \ @tparam _Pop_front Use `_Pop_back` as default\n */\ntemplate <class _Push_back,\
    \ class _Pop_back, class _Push_front = _Push_back,\n          class _Pop_front\
    \ = _Pop_back>\nclass Mo {\n public:\n  using size_type = std::size_t;\n\n  struct\
    \ query {\n    size_type index;\n    size_type left, right;\n  };\n\n  using value_type\
    \ = query;\n  using reference = query&;\n  using container_type = std::vector<query>;\n\
    \n protected:\n  _Push_front push_front;\n  _Pop_front pop_front;\n  _Push_back\
    \ push_back;\n  _Pop_back pop_back;\n\n  container_type queries;\n\n public:\n\
    \  /**\n   * @brief Construct a new Mo object.\n   *\n   * @param push_back\n\
    \   * @param pop_back\n   */\n  Mo(_Push_back push_back, _Pop_back pop_back) noexcept\n\
    \      : Mo(push_back, pop_back, push_back, pop_back) {}\n\n  /**\n   * @brief\
    \ Construct a new Mo object.\n   *\n   * @param push_front\n   * @param pop_front\n\
    \   * @param push_back\n   * @param pop_back\n   */\n  Mo(_Push_front push_front,\
    \ _Pop_front pop_front, _Push_back push_back,\n     _Pop_back pop_back) noexcept\n\
    \      : push_front(push_front),\n        pop_front(pop_front),\n        push_back(push_back),\n\
    \        pop_back(pop_back) {}\n\n  /**\n   * @return Number of queries.\n   */\n\
    \  size_type size() const noexcept { return queries.size(); }\n\n  /**\n   * @brief\
    \ Add a query for the interval [l, r).\n   *\n   * @param __l Left end, inclusive\n\
    \   * @param __r Right end, exclusive\n   * @return Index of the query.\n   */\n\
    \  reference insert(size_type __l, size_type __r) noexcept {\n    assert(__l <=\
    \ __r);\n    queries.push_back({queries.size(), __l, __r});\n    return queries.back();\n\
    \  }\n\n  /**\n   * @brief Sort all queries.\n   */\n  void make() noexcept {\n\
    \    assert(size());\n    size_type __n = 0;\n    for (const auto& __q : queries)\
    \ __n = std::max(__n, __q.right);\n    size_type __width = ceil(__n / sqrt(size()));\n\
    \    std::sort(queries.begin(), queries.end(), [&](auto __x, auto __y) {\n   \
    \   if (__x.left / __width != __y.left / __width) return __x.left < __y.left;\n\
    \      return __x.right < __y.right;\n    });\n  }\n\n  class iterator : public\
    \ container_type::iterator {\n    using base = typename container_type::iterator;\n\
    \    Mo* __mo;\n\n    void fit(size_type __l1, size_type __r1, size_type __l2,\n\
    \             size_type __r2) const noexcept {\n      while (__l1 > __l2) __mo->push_front(--__l1);\n\
    \      while (__r1 < __r2) __mo->push_back(__r1++);\n      while (__l1 < __l2)\
    \ __mo->pop_front(__l1++);\n      while (__r1 > __r2) __mo->pop_back(--__r1);\n\
    \    }\n\n    void fit_from_empty(size_type __l, size_type __r) const noexcept\
    \ {\n      while (__l < __r) __mo->push_back(__l++);\n    }\n\n    void fit_to_empty(size_type\
    \ __l, size_type __r) const noexcept {\n      while (__l < __r) __mo->push_back(--__r);\n\
    \    }\n\n    bool at_end() const noexcept { return __mo->queries.end() == *this;\
    \ }\n\n   public:\n    iterator() = default;\n\n    iterator(Mo* __mo, base __i)\
    \ noexcept : base(__i), __mo(__mo) {\n      if (__i != __mo->queries.end()) fit_from_empty(__i->left,\
    \ __i->right);\n    }\n\n    iterator& operator++() noexcept {\n      auto __l\
    \ = (*this)->left, __r = (*this)->right;\n      base::operator++();\n      if\
    \ (at_end())\n        fit_to_empty(__l, __r);\n      else\n        fit(__l, __r,\
    \ (*this)->left, (*this)->right);\n      return *this;\n    }\n\n    iterator&\
    \ operator--() noexcept {\n      if (at_end()) {\n        base::operator--();\n\
    \        fit_from_empty((*this)->left, (*this)->right);\n      } else {\n    \
    \    size_type __l = (*this)->left, __r = (*this)->right;\n        base::operator--();\n\
    \        fit(__l, __r, (*this)->left, (*this)->right);\n      }\n      return\
    \ *this;\n    }\n\n    iterator operator++(int) noexcept {\n      auto __tmp =\
    \ *this;\n      operator++();\n      return __tmp;\n    }\n\n    iterator operator--(int)\
    \ noexcept {\n      auto __tmp = *this;\n      operator--();\n      return __tmp;\n\
    \    }\n  };\n\n  iterator begin() noexcept { return {this, queries.begin()};\
    \ }\n\n  iterator end() noexcept { return {this, queries.end()}; }\n};\n\n}  //\
    \ namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file Mo.hpp\n * @brief Mo's Algorithm\n */\n\n#include\
    \ <cassert>\n#include <cmath>\n#include <functional>\n#include <vector>\n\nnamespace\
    \ workspace {\n\n/**\n * @brief Mo's Alorithm. Process queries about contiguous\
    \ subarrays.\n *\n * @tparam _Push_back\n * @tparam _Pop_back\n * @tparam _Push_front\
    \ Use `_Push_back` as default\n * @tparam _Pop_front Use `_Pop_back` as default\n\
    \ */\ntemplate <class _Push_back, class _Pop_back, class _Push_front = _Push_back,\n\
    \          class _Pop_front = _Pop_back>\nclass Mo {\n public:\n  using size_type\
    \ = std::size_t;\n\n  struct query {\n    size_type index;\n    size_type left,\
    \ right;\n  };\n\n  using value_type = query;\n  using reference = query&;\n \
    \ using container_type = std::vector<query>;\n\n protected:\n  _Push_front push_front;\n\
    \  _Pop_front pop_front;\n  _Push_back push_back;\n  _Pop_back pop_back;\n\n \
    \ container_type queries;\n\n public:\n  /**\n   * @brief Construct a new Mo object.\n\
    \   *\n   * @param push_back\n   * @param pop_back\n   */\n  Mo(_Push_back push_back,\
    \ _Pop_back pop_back) noexcept\n      : Mo(push_back, pop_back, push_back, pop_back)\
    \ {}\n\n  /**\n   * @brief Construct a new Mo object.\n   *\n   * @param push_front\n\
    \   * @param pop_front\n   * @param push_back\n   * @param pop_back\n   */\n \
    \ Mo(_Push_front push_front, _Pop_front pop_front, _Push_back push_back,\n   \
    \  _Pop_back pop_back) noexcept\n      : push_front(push_front),\n        pop_front(pop_front),\n\
    \        push_back(push_back),\n        pop_back(pop_back) {}\n\n  /**\n   * @return\
    \ Number of queries.\n   */\n  size_type size() const noexcept { return queries.size();\
    \ }\n\n  /**\n   * @brief Add a query for the interval [l, r).\n   *\n   * @param\
    \ __l Left end, inclusive\n   * @param __r Right end, exclusive\n   * @return\
    \ Index of the query.\n   */\n  reference insert(size_type __l, size_type __r)\
    \ noexcept {\n    assert(__l <= __r);\n    queries.push_back({queries.size(),\
    \ __l, __r});\n    return queries.back();\n  }\n\n  /**\n   * @brief Sort all\
    \ queries.\n   */\n  void make() noexcept {\n    assert(size());\n    size_type\
    \ __n = 0;\n    for (const auto& __q : queries) __n = std::max(__n, __q.right);\n\
    \    size_type __width = ceil(__n / sqrt(size()));\n    std::sort(queries.begin(),\
    \ queries.end(), [&](auto __x, auto __y) {\n      if (__x.left / __width != __y.left\
    \ / __width) return __x.left < __y.left;\n      return __x.right < __y.right;\n\
    \    });\n  }\n\n  class iterator : public container_type::iterator {\n    using\
    \ base = typename container_type::iterator;\n    Mo* __mo;\n\n    void fit(size_type\
    \ __l1, size_type __r1, size_type __l2,\n             size_type __r2) const noexcept\
    \ {\n      while (__l1 > __l2) __mo->push_front(--__l1);\n      while (__r1 <\
    \ __r2) __mo->push_back(__r1++);\n      while (__l1 < __l2) __mo->pop_front(__l1++);\n\
    \      while (__r1 > __r2) __mo->pop_back(--__r1);\n    }\n\n    void fit_from_empty(size_type\
    \ __l, size_type __r) const noexcept {\n      while (__l < __r) __mo->push_back(__l++);\n\
    \    }\n\n    void fit_to_empty(size_type __l, size_type __r) const noexcept {\n\
    \      while (__l < __r) __mo->push_back(--__r);\n    }\n\n    bool at_end() const\
    \ noexcept { return __mo->queries.end() == *this; }\n\n   public:\n    iterator()\
    \ = default;\n\n    iterator(Mo* __mo, base __i) noexcept : base(__i), __mo(__mo)\
    \ {\n      if (__i != __mo->queries.end()) fit_from_empty(__i->left, __i->right);\n\
    \    }\n\n    iterator& operator++() noexcept {\n      auto __l = (*this)->left,\
    \ __r = (*this)->right;\n      base::operator++();\n      if (at_end())\n    \
    \    fit_to_empty(__l, __r);\n      else\n        fit(__l, __r, (*this)->left,\
    \ (*this)->right);\n      return *this;\n    }\n\n    iterator& operator--() noexcept\
    \ {\n      if (at_end()) {\n        base::operator--();\n        fit_from_empty((*this)->left,\
    \ (*this)->right);\n      } else {\n        size_type __l = (*this)->left, __r\
    \ = (*this)->right;\n        base::operator--();\n        fit(__l, __r, (*this)->left,\
    \ (*this)->right);\n      }\n      return *this;\n    }\n\n    iterator operator++(int)\
    \ noexcept {\n      auto __tmp = *this;\n      operator++();\n      return __tmp;\n\
    \    }\n\n    iterator operator--(int) noexcept {\n      auto __tmp = *this;\n\
    \      operator--();\n      return __tmp;\n    }\n  };\n\n  iterator begin() noexcept\
    \ { return {this, queries.begin()}; }\n\n  iterator end() noexcept { return {this,\
    \ queries.end()}; }\n};\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/data_structure/Mo.hpp
  requiredBy: []
  timestamp: '2021-06-26 00:26:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/range_kth_smallest.test.cpp
  - test/library-checker/static_range_inversions_query.test.cpp
documentation_of: src/data_structure/Mo.hpp
layout: document
redirect_from:
- /library/src/data_structure/Mo.hpp
- /library/src/data_structure/Mo.hpp.html
title: Mo's Algorithm
---
