---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/data_structure/Mo.hpp
    title: Mo's Algorithm
  - icon: ':heavy_check_mark:'
    path: src/data_structure/coordinate_compression.hpp
    title: Coordinate Compression
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
    \ id;\n  }\n};\n\n}  // namespace workspace\n#line 2 \"src/data_structure/coordinate_compression.hpp\"\
    \n\n/*\n * @file coordinate_compression.hpp\n * @brief Coordinate Compression\n\
    \ */\n\n#include <algorithm>\n#line 10 \"src/data_structure/coordinate_compression.hpp\"\
    \n\nnamespace workspace {\n\ntemplate <class Type, class Result = size_t>\nstruct\
    \ coordinate_compression : std::vector<Type> {\n  using std::vector<Type>::vector;\n\
    \  using std::vector<Type>::begin;\n  using std::vector<Type>::end;\n\n  using\
    \ result_type = Result;\n\n  void make() {\n    std::sort(begin(), end());\n \
    \   std::vector<Type>::erase(std::unique(begin(), end()), end());\n  }\n\n  result_type\
    \ compress(const Type &value) const {\n    return std::lower_bound(begin(), end(),\
    \ value) - begin();\n  }\n\n  template <class Iter>\n  std::vector<result_type>\
    \ compress(Iter first, Iter last) const {\n    static_assert(std::is_convertible<\n\
    \                  typename std::decay<decltype(*std::declval<Iter>())>::type,\n\
    \                  Type>::value);\n    std::vector<result_type> res;\n    for\
    \ (Iter iter = first; iter != last; ++iter)\n      res.emplace_back(compress(*iter));\n\
    \    return res;\n  }\n};\n\n}  // namespace workspace\n#line 7 \"test/library-checker/range_kth_smallest.test.cpp\"\
    \n\nint main() {\n  int n, q;\n  scanf(\"%d%d\", &n, &q);\n  std::vector<size_t>\
    \ a(n);\n  for (auto &e : a) scanf(\"%d\", &e);\n  workspace::coordinate_compression<size_t>\
    \ ccmp(a.begin(), a.end());\n  ccmp.make();\n  a = ccmp.compress(a.begin(), a.end());\n\
    \  int bsize = std::sqrt(ccmp.size()) + 1;\n  std::vector<int> cnt(ccmp.size()),\
    \ bcnt(bsize);\n  auto add = [&](int i) {\n    int now = a[i];\n    cnt[now]++;\n\
    \    bcnt[now / bsize]++;\n  };\n  auto del = [&](int i) {\n    int now = a[i];\n\
    \    cnt[now]--;\n    bcnt[now / bsize]--;\n  };\n  workspace::Mo mo(add, del);\n\
    \  std::vector<int> k(q), ans(q);\n  for (int l, r, i = 0; i < q; i++) {\n   \
    \ scanf(\"%d%d%d\", &l, &r, &k[i]);\n    mo.add_query(l, r);\n  }\n  mo.make();\n\
    \  for (int t = 0; t < q; t++) {\n    int qid = mo.process();\n    for (int i\
    \ = 0, j = 0, nk = k[qid]; i < bsize; i++, j += bsize) {\n      if (bcnt[i] >\
    \ nk) {\n        int h;\n        for (h = j; nk >= cnt[h]; h++) {\n          nk\
    \ -= cnt[h];\n        }\n        ans[qid] = ccmp[h];\n        break;\n      }\
    \ else {\n        nk -= bcnt[i];\n      }\n    }\n  }\n  for (int e : ans) printf(\"\
    %d\\n\", e);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n\
    #include <cstdio>\n\n#include \"src/data_structure/Mo.hpp\"\n#include \"src/data_structure/coordinate_compression.hpp\"\
    \n\nint main() {\n  int n, q;\n  scanf(\"%d%d\", &n, &q);\n  std::vector<size_t>\
    \ a(n);\n  for (auto &e : a) scanf(\"%d\", &e);\n  workspace::coordinate_compression<size_t>\
    \ ccmp(a.begin(), a.end());\n  ccmp.make();\n  a = ccmp.compress(a.begin(), a.end());\n\
    \  int bsize = std::sqrt(ccmp.size()) + 1;\n  std::vector<int> cnt(ccmp.size()),\
    \ bcnt(bsize);\n  auto add = [&](int i) {\n    int now = a[i];\n    cnt[now]++;\n\
    \    bcnt[now / bsize]++;\n  };\n  auto del = [&](int i) {\n    int now = a[i];\n\
    \    cnt[now]--;\n    bcnt[now / bsize]--;\n  };\n  workspace::Mo mo(add, del);\n\
    \  std::vector<int> k(q), ans(q);\n  for (int l, r, i = 0; i < q; i++) {\n   \
    \ scanf(\"%d%d%d\", &l, &r, &k[i]);\n    mo.add_query(l, r);\n  }\n  mo.make();\n\
    \  for (int t = 0; t < q; t++) {\n    int qid = mo.process();\n    for (int i\
    \ = 0, j = 0, nk = k[qid]; i < bsize; i++, j += bsize) {\n      if (bcnt[i] >\
    \ nk) {\n        int h;\n        for (h = j; nk >= cnt[h]; h++) {\n          nk\
    \ -= cnt[h];\n        }\n        ans[qid] = ccmp[h];\n        break;\n      }\
    \ else {\n        nk -= bcnt[i];\n      }\n    }\n  }\n  for (int e : ans) printf(\"\
    %d\\n\", e);\n}\n"
  dependsOn:
  - src/data_structure/Mo.hpp
  - src/data_structure/coordinate_compression.hpp
  isVerificationFile: true
  path: test/library-checker/range_kth_smallest.test.cpp
  requiredBy: []
  timestamp: '2021-03-26 17:22:43+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/range_kth_smallest.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/range_kth_smallest.test.cpp
- /verify/test/library-checker/range_kth_smallest.test.cpp.html
title: test/library-checker/range_kth_smallest.test.cpp
---
