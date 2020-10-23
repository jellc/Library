---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/Mo.hpp
    title: data_structure/Mo.hpp
  - icon: ':heavy_check_mark:'
    path: utils/coordinate_compression.hpp
    title: utils/coordinate_compression.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_kth_smallest
    links:
    - https://judge.yosupo.jp/problem/range_kth_smallest
  bundledCode: "#line 1 \"test/library-checker/range_kth_smallest.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n#include <cstdio>\n\
    \n#line 2 \"data_structure/Mo.hpp\"\n#include <cassert>\n#include <cmath>\n#include\
    \ <functional>\n#include <numeric>\n#include <vector>\n\ntemplate <class Push_back,\
    \ class Pop_back, class Push_front = Push_back,\n          class Pop_front = Pop_back>\n\
    class Mo {\n  Push_front push_front;\n  Pop_front pop_front;\n  Push_back push_back;\n\
    \  Pop_back pop_back;\n  std::vector<size_t> lft, rgt, ord;\n  std::vector<size_t>::iterator\
    \ itr;\n  size_t lpos, rpos;\n\n public:\n  Mo(Push_back push_back, Pop_back pop_back)\n\
    \      : Mo(push_back, pop_back, push_back, pop_back) {}\n\n  Mo(Push_front push_front,\
    \ Pop_front pop_front, Push_back push_back,\n     Pop_back pop_back)\n      :\
    \ push_front(push_front),\n        pop_front(pop_front),\n        push_back(push_back),\n\
    \        pop_back(pop_back),\n        lpos(),\n        rpos() {}\n\n  size_t size()\
    \ const { return lft.size(); }\n\n  // query for [l, r)\n  void set(size_t l,\
    \ size_t r) {\n    assert(!(r < l));\n    lft.emplace_back(l), rgt.emplace_back(r);\n\
    \  }\n\n  void make() {\n    assert(size());\n    ord.resize(size());\n    iota(ord.begin(),\
    \ ord.end(), 0);\n    const size_t width = sqrt(*max_element(rgt.begin(), rgt.end()));\n\
    \    std::sort(ord.begin(), ord.end(), [&](size_t x, size_t y) {\n      if (lft[x]\
    \ / width != lft[y] / width) return lft[x] < lft[y];\n      return rgt[x] < rgt[y];\n\
    \    });\n    itr = ord.begin();\n  }\n\n  size_t process() {\n    if (itr ==\
    \ ord.end()) return ord.size();\n    const size_t id = *itr++, l = lft[id], r\
    \ = rgt[id];\n    while (lpos > l) push_front(--lpos);\n    while (rpos < r) push_back(rpos++);\n\
    \    while (lpos < l) pop_front(lpos++);\n    while (rpos > r) pop_back(--rpos);\n\
    \    return id;\n  }\n};\n#line 2 \"utils/coordinate_compression.hpp\"\n#include\
    \ <algorithm>\n#line 5 \"utils/coordinate_compression.hpp\"\n\ntemplate <class\
    \ T> class coordinate_compression {\n  std::vector<T> uniquely;\n  std::vector<size_t>\
    \ compressed;\n\n public:\n  coordinate_compression(const std::vector<T> &raw)\n\
    \      : uniquely(raw), compressed(raw.size()) {\n    std::sort(uniquely.begin(),\
    \ uniquely.end());\n    uniquely.erase(std::unique(uniquely.begin(), uniquely.end()),\n\
    \                   uniquely.end());\n    for (size_t i = 0; i != size(); ++i)\n\
    \      compressed[i] =\n          std::lower_bound(uniquely.begin(), uniquely.end(),\
    \ raw[i]) -\n          uniquely.begin();\n  }\n\n  size_t operator[](const size_t\
    \ idx) const {\n    assert(idx < size());\n    return compressed[idx];\n  }\n\n\
    \  size_t size() const { return compressed.size(); }\n\n  size_t count() const\
    \ { return uniquely.size(); }\n\n  T value(const size_t ord) const {\n    assert(ord\
    \ < count());\n    return uniquely[ord];\n  }\n\n  size_t order(const T &value)\
    \ const {\n    return std::lower_bound(uniquely.begin(), uniquely.end(), value)\
    \ -\n           uniquely.begin();\n  }\n\n  auto begin() { return compressed.begin();\
    \ }\n  auto end() { return compressed.end(); }\n  auto rbegin() { return compressed.rbegin();\
    \ }\n  auto rend() { return compressed.rend(); }\n};\n#line 6 \"test/library-checker/range_kth_smallest.test.cpp\"\
    \n\nint main() {\n  int n, q;\n  scanf(\"%d%d\", &n, &q);\n  std::vector<int>\
    \ a(n);\n  for (int &e : a) scanf(\"%d\", &e);\n  coordinate_compression ccmp(a);\n\
    \  int bsize = std::sqrt(ccmp.count()) + 1;\n  std::vector<int> cnt(ccmp.count()),\
    \ bcnt(bsize);\n  auto add = [&](int i) {\n    int now = ccmp[i];\n    cnt[now]++;\n\
    \    bcnt[now / bsize]++;\n  };\n  auto del = [&](int i) {\n    int now = ccmp[i];\n\
    \    cnt[now]--;\n    bcnt[now / bsize]--;\n  };\n  Mo mo(add, del);\n  std::vector<int>\
    \ k(q), ans(q);\n  for (int l, r, i = 0; i < q; i++) {\n    scanf(\"%d%d%d\",\
    \ &l, &r, &k[i]);\n    mo.set(l, r);\n  }\n  mo.make();\n  for (int t = 0; t <\
    \ q; t++) {\n    int qid = mo.process();\n    for (int i = 0, j = 0, nk = k[qid];\
    \ i < bsize; i++, j += bsize) {\n      if (bcnt[i] > nk) {\n        int h;\n \
    \       for (h = j; nk >= cnt[h]; h++) {\n          nk -= cnt[h];\n        }\n\
    \        ans[qid] = ccmp.value(h);\n        break;\n      } else {\n        nk\
    \ -= bcnt[i];\n      }\n    }\n  }\n  for (int e : ans) printf(\"%d\\n\", e);\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\
    #include <cstdio>\n\n#include \"data_structure/Mo.hpp\"\n#include \"utils/coordinate_compression.hpp\"\
    \n\nint main() {\n  int n, q;\n  scanf(\"%d%d\", &n, &q);\n  std::vector<int>\
    \ a(n);\n  for (int &e : a) scanf(\"%d\", &e);\n  coordinate_compression ccmp(a);\n\
    \  int bsize = std::sqrt(ccmp.count()) + 1;\n  std::vector<int> cnt(ccmp.count()),\
    \ bcnt(bsize);\n  auto add = [&](int i) {\n    int now = ccmp[i];\n    cnt[now]++;\n\
    \    bcnt[now / bsize]++;\n  };\n  auto del = [&](int i) {\n    int now = ccmp[i];\n\
    \    cnt[now]--;\n    bcnt[now / bsize]--;\n  };\n  Mo mo(add, del);\n  std::vector<int>\
    \ k(q), ans(q);\n  for (int l, r, i = 0; i < q; i++) {\n    scanf(\"%d%d%d\",\
    \ &l, &r, &k[i]);\n    mo.set(l, r);\n  }\n  mo.make();\n  for (int t = 0; t <\
    \ q; t++) {\n    int qid = mo.process();\n    for (int i = 0, j = 0, nk = k[qid];\
    \ i < bsize; i++, j += bsize) {\n      if (bcnt[i] > nk) {\n        int h;\n \
    \       for (h = j; nk >= cnt[h]; h++) {\n          nk -= cnt[h];\n        }\n\
    \        ans[qid] = ccmp.value(h);\n        break;\n      } else {\n        nk\
    \ -= bcnt[i];\n      }\n    }\n  }\n  for (int e : ans) printf(\"%d\\n\", e);\n\
    }\n"
  dependsOn:
  - data_structure/Mo.hpp
  - utils/coordinate_compression.hpp
  isVerificationFile: true
  path: test/library-checker/range_kth_smallest.test.cpp
  requiredBy: []
  timestamp: '2020-10-24 01:09:25+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/range_kth_smallest.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/range_kth_smallest.test.cpp
- /verify/test/library-checker/range_kth_smallest.test.cpp.html
title: test/library-checker/range_kth_smallest.test.cpp
---
