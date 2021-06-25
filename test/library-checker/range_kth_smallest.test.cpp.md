---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: src/data_structure/Mo.hpp
    title: Mo's Algorithm
  - icon: ':x:'
    path: src/data_structure/compression.hpp
    title: Compression
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_kth_smallest
    links:
    - https://judge.yosupo.jp/problem/range_kth_smallest
  bundledCode: "#line 1 \"test/library-checker/range_kth_smallest.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n#include <cstdio>\n\
    \n#line 2 \"src/data_structure/Mo.hpp\"\n\n/**\n * @file Mo.hpp\n * @brief Mo's\
    \ Algorithm\n */\n\n#include <cassert>\n#include <cmath>\n#include <functional>\n\
    #include <numeric>\n#include <vector>\n\nnamespace workspace {\n\n/**\n * @brief\
    \ Mo's Alorithm. Process queries about contiguous subarrays.\n *\n * @tparam Push_back\n\
    \ * @tparam Pop_back\n * @tparam Push_front Use `Push_back` as default\n * @tparam\
    \ Pop_front Use `Pop_back` as default\n */\ntemplate <class Push_back, class Pop_back,\
    \ class Push_front = Push_back,\n          class Pop_front = Pop_back>\nclass\
    \ Mo {\n  Push_front push_front;\n  Pop_front pop_front;\n  Push_back push_back;\n\
    \  Pop_back pop_back;\n  std::vector<size_t> lft, rgt, ord;\n  std::vector<size_t>::iterator\
    \ iter;\n  size_t lpos, rpos;\n\n public:\n  /**\n   * @brief Construct a new\
    \ Mo object.\n   *\n   * @param push_back\n   * @param pop_back\n   */\n  Mo(Push_back\
    \ push_back, Pop_back pop_back)\n      : Mo(push_back, pop_back, push_back, pop_back)\
    \ {}\n\n  /**\n   * @brief Construct a new Mo object.\n   *\n   * @param push_front\n\
    \   * @param pop_front\n   * @param push_back\n   * @param pop_back\n   */\n \
    \ Mo(Push_front push_front, Pop_front pop_front, Push_back push_back,\n     Pop_back\
    \ pop_back)\n      : push_front(push_front),\n        pop_front(pop_front),\n\
    \        push_back(push_back),\n        pop_back(pop_back),\n        lpos(),\n\
    \        rpos() {}\n\n  /**\n   * @return Number of queries.\n   */\n  size_t\
    \ size() const { return lft.size(); }\n\n  /**\n   * @brief Add a query for the\
    \ interval [l, r).\n   *\n   * @param __l Left end, inclusive\n   * @param __r\
    \ Right end, exclusive\n   * @return Index of the query.\n   */\n  size_t add_query(size_t\
    \ __l, size_t __r) {\n    assert(__l <= __r);\n    lft.emplace_back(__l), rgt.emplace_back(__r);\n\
    \    return lft.size() - 1;\n  }\n\n  /**\n   * @brief Sort all queries.\n   */\n\
    \  void make() {\n    assert(size());\n    ord.resize(size());\n    std::iota(ord.begin(),\
    \ ord.end(), 0);\n    const size_t width =\n        ceil(*max_element(rgt.begin(),\
    \ rgt.end()) / sqrt(size()));\n    std::sort(ord.begin(), ord.end(), [&](size_t\
    \ x, size_t y) {\n      if (lft[x] / width != lft[y] / width) return lft[x] <\
    \ lft[y];\n      return rgt[x] < rgt[y];\n    });\n    iter = ord.begin();\n \
    \ }\n\n  /**\n   * @brief Process the next query.\n   * @return Index of the query.\n\
    \   */\n  size_t process() {\n    if (iter == ord.end()) return ord.size();\n\
    \    const size_t id = *iter++, l = lft[id], r = rgt[id];\n    while (lpos > l)\
    \ push_front(--lpos);\n    while (rpos < r) push_back(rpos++);\n    while (lpos\
    \ < l) pop_front(lpos++);\n    while (rpos > r) pop_back(--rpos);\n    return\
    \ id;\n  }\n};\n\n}  // namespace workspace\n#line 2 \"src/data_structure/compression.hpp\"\
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
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/library-checker/range_kth_smallest.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/range_kth_smallest.test.cpp
- /verify/test/library-checker/range_kth_smallest.test.cpp.html
title: test/library-checker/range_kth_smallest.test.cpp
---
