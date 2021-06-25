---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/data_structure/Mo.hpp
    title: Mo's Algorithm
  - icon: ':heavy_check_mark:'
    path: src/data_structure/compression.hpp
    title: Compression
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_kth_smallest
    links:
    - https://judge.yosupo.jp/problem/range_kth_smallest
  bundledCode: "#line 1 \"test/library-checker/range_kth_smallest.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n#include <cstdio>\n\
    \n#line 2 \"src/data_structure/Mo.hpp\"\n\n/**\n * @file Mo.hpp\n * @brief Mo's\
    \ Algorithm\n */\n\n#include <cassert>\n#include <cmath>\n#include <functional>\n\
    #include <vector>\n\nnamespace workspace {\n\n/**\n * @brief Mo's Alorithm. Process\
    \ queries about contiguous subarrays.\n *\n * @tparam _Push_back\n * @tparam _Pop_back\n\
    \ * @tparam _Push_front Use `_Push_back` as default\n * @tparam _Pop_front Use\
    \ `_Pop_back` as default\n */\ntemplate <class _Push_back, class _Pop_back, class\
    \ _Push_front = _Push_back,\n          class _Pop_front = _Pop_back>\nclass Mo\
    \ {\n public:\n  using size_type = std::size_t;\n\n  struct query {\n    size_type\
    \ index;\n    size_type left, right;\n  };\n\n  using value_type = query;\n  using\
    \ reference = query&;\n  using container_type = std::vector<query>;\n\n protected:\n\
    \  _Push_front push_front;\n  _Pop_front pop_front;\n  _Push_back push_back;\n\
    \  _Pop_back pop_back;\n\n  container_type queries;\n\n public:\n  /**\n   * @brief\
    \ Construct a new Mo object.\n   *\n   * @param push_back\n   * @param pop_back\n\
    \   */\n  Mo(_Push_back push_back, _Pop_back pop_back) noexcept\n      : Mo(push_back,\
    \ pop_back, push_back, pop_back) {}\n\n  /**\n   * @brief Construct a new Mo object.\n\
    \   *\n   * @param push_front\n   * @param pop_front\n   * @param push_back\n\
    \   * @param pop_back\n   */\n  Mo(_Push_front push_front, _Pop_front pop_front,\
    \ _Push_back push_back,\n     _Pop_back pop_back) noexcept\n      : push_front(push_front),\n\
    \        pop_front(pop_front),\n        push_back(push_back),\n        pop_back(pop_back)\
    \ {}\n\n  /**\n   * @return Number of queries.\n   */\n  size_type size() const\
    \ noexcept { return queries.size(); }\n\n  /**\n   * @brief Add a query for the\
    \ interval [l, r).\n   *\n   * @param __l Left end, inclusive\n   * @param __r\
    \ Right end, exclusive\n   * @return Index of the query.\n   */\n  reference insert(size_type\
    \ __l, size_type __r) noexcept {\n    assert(__l <= __r);\n    queries.push_back({queries.size(),\
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
    \ queries.end()}; }\n};\n\n}  // namespace workspace\n#line 2 \"src/data_structure/compression.hpp\"\
    \n\n/**\n * @file compression.hpp\n * @brief Compression\n */\n\n#include <algorithm>\n\
    #line 11 \"src/data_structure/compression.hpp\"\n\nnamespace workspace {\n\ntemplate\
    \ <class _Tp> class compression {\n  std::vector<_Tp> __vec;\n\n  decltype(auto)\
    \ begin() { return __vec.begin(); }\n\n  decltype(auto) end() { return __vec.end();\
    \ }\n\n public:\n  using size_type = typename std::vector<_Tp>::size_type;\n\n\
    \  /**\n   * @brief Construct a new compression object.\n   */\n  compression()\
    \ = default;\n\n  /**\n   * @brief Construct a new compression object.\n   *\n\
    \   * @param __first\n   * @param __last\n   */\n  template <class _IIter>\n \
    \ compression(_IIter __first, _IIter __last) noexcept : __vec(__first, __last)\
    \ {\n    make();\n  }\n\n  decltype(auto) begin() const noexcept { return __vec.begin();\
    \ }\n\n  decltype(auto) end() const noexcept { return __vec.end(); }\n\n  decltype(auto)\
    \ operator[](size_type __i) const noexcept {\n    assert(__i < size());\n    return\
    \ __vec[__i];\n  }\n\n  size_type size() const noexcept { return __vec.size();\
    \ }\n\n  template <class... _Args> decltype(auto) emplace(_Args&&... __args) noexcept\
    \ {\n    return __vec.emplace_back(std::forward<_Args>(__args)...);\n  }\n\n \
    \ template <class... _Args> void insert(_Args&&... __args) noexcept {\n    __vec.insert(end(),\
    \ std::forward<_Args>(__args)...);\n  }\n\n  /**\n   * @brief Sort and make unique.\n\
    \   * @return Number of different values.\n   */\n  size_type make() noexcept\
    \ {\n    std::sort(begin(), end());\n\n    __vec.erase(std::unique(begin(), end(),\n\
    \                            [](const _Tp& __l, const _Tp& __r) {\n          \
    \                    return !(__l < __r) && !(__r < __l);\n                  \
    \          }),\n                end());\n\n    return size();\n  }\n\n  size_type\
    \ lower_bound(const _Tp& __x) const noexcept {\n    return std::lower_bound(begin(),\
    \ end(), __x) - begin();\n  }\n\n  size_type upper_bound(const _Tp& __x) const\
    \ noexcept {\n    return std::upper_bound(begin(), end(), __x) - begin();\n  }\n\
    };\n\ntemplate <class _IIter>\ncompression(_IIter, _IIter)\n    -> compression<typename\
    \ std::iterator_traits<_IIter>::value_type>;\n\n}  // namespace workspace\n#line\
    \ 7 \"test/library-checker/range_kth_smallest.test.cpp\"\n\nint main() {\n  int\
    \ n, q;\n  scanf(\"%d%d\", &n, &q);\n  std::vector<size_t> a(n);\n  for (auto\
    \ &e : a) scanf(\"%d\", &e);\n  workspace::compression ccmp(a.begin(), a.end());\n\
    \  ccmp.make();\n  for (auto &&x : a) {\n    x = ccmp.lower_bound(x);\n  }\n \
    \ int bsize = std::sqrt(ccmp.size()) + 1;\n  std::vector<int> cnt(ccmp.size()),\
    \ bcnt(bsize);\n  auto add = [&](int i) {\n    int now = a[i];\n    cnt[now]++;\n\
    \    bcnt[now / bsize]++;\n  };\n  auto del = [&](int i) {\n    int now = a[i];\n\
    \    cnt[now]--;\n    bcnt[now / bsize]--;\n  };\n  workspace::Mo mo(add, del);\n\
    \  std::vector<int> k(q), ans(q);\n  for (int l, r, i = 0; i < q; i++) {\n   \
    \ scanf(\"%d%d%d\", &l, &r, &k[i]);\n    mo.insert(l, r);\n  }\n  mo.make();\n\
    \  for (auto &&q : mo) {\n    for (int i = 0, j = 0, nk = k[q.index]; i < bsize;\
    \ i++, j += bsize) {\n      if (bcnt[i] > nk) {\n        int h;\n        for (h\
    \ = j; nk >= cnt[h]; h++) {\n          nk -= cnt[h];\n        }\n        ans[q.index]\
    \ = ccmp[h];\n        break;\n      } else {\n        nk -= bcnt[i];\n      }\n\
    \    }\n  }\n  for (int e : ans) printf(\"%d\\n\", e);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n\
    #include <cstdio>\n\n#include \"src/data_structure/Mo.hpp\"\n#include \"src/data_structure/compression.hpp\"\
    \n\nint main() {\n  int n, q;\n  scanf(\"%d%d\", &n, &q);\n  std::vector<size_t>\
    \ a(n);\n  for (auto &e : a) scanf(\"%d\", &e);\n  workspace::compression ccmp(a.begin(),\
    \ a.end());\n  ccmp.make();\n  for (auto &&x : a) {\n    x = ccmp.lower_bound(x);\n\
    \  }\n  int bsize = std::sqrt(ccmp.size()) + 1;\n  std::vector<int> cnt(ccmp.size()),\
    \ bcnt(bsize);\n  auto add = [&](int i) {\n    int now = a[i];\n    cnt[now]++;\n\
    \    bcnt[now / bsize]++;\n  };\n  auto del = [&](int i) {\n    int now = a[i];\n\
    \    cnt[now]--;\n    bcnt[now / bsize]--;\n  };\n  workspace::Mo mo(add, del);\n\
    \  std::vector<int> k(q), ans(q);\n  for (int l, r, i = 0; i < q; i++) {\n   \
    \ scanf(\"%d%d%d\", &l, &r, &k[i]);\n    mo.insert(l, r);\n  }\n  mo.make();\n\
    \  for (auto &&q : mo) {\n    for (int i = 0, j = 0, nk = k[q.index]; i < bsize;\
    \ i++, j += bsize) {\n      if (bcnt[i] > nk) {\n        int h;\n        for (h\
    \ = j; nk >= cnt[h]; h++) {\n          nk -= cnt[h];\n        }\n        ans[q.index]\
    \ = ccmp[h];\n        break;\n      } else {\n        nk -= bcnt[i];\n      }\n\
    \    }\n  }\n  for (int e : ans) printf(\"%d\\n\", e);\n}\n"
  dependsOn:
  - src/data_structure/Mo.hpp
  - src/data_structure/compression.hpp
  isVerificationFile: true
  path: test/library-checker/range_kth_smallest.test.cpp
  requiredBy: []
  timestamp: '2021-06-25 19:18:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/range_kth_smallest.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/range_kth_smallest.test.cpp
- /verify/test/library-checker/range_kth_smallest.test.cpp.html
title: test/library-checker/range_kth_smallest.test.cpp
---
