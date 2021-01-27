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
  bundledCode: "#line 2 \"src/data_structure/Mo.hpp\"\n\n/*\n * @file Mo.hpp\n * @brief\
    \ Mo's Algorithm\n */\n\n#include <cassert>\n#include <cmath>\n#include <functional>\n\
    #include <numeric>\n#include <vector>\n\nnamespace workspace {\n\n/*\n * @class\
    \ Mo\n * @brief process queries about contiguous subarray\n * @tparam Push_back\n\
    \ * @tparam Pop_back\n * @tparam Push_front Push_back as default\n * @tparam Pop_front\
    \ Pop_back as default\n */\ntemplate <class Push_back, class Pop_back, class Push_front\
    \ = Push_back,\n          class Pop_front = Pop_back>\nclass Mo {\n  Push_front\
    \ push_front;\n  Pop_front pop_front;\n  Push_back push_back;\n  Pop_back pop_back;\n\
    \  std::vector<size_t> lft, rgt, ord;\n  std::vector<size_t>::iterator itr;\n\
    \  size_t lpos, rpos;\n\n public:\n  /*\n   * @param push_back\n   * @param pop_back\n\
    \   */\n  Mo(Push_back push_back, Pop_back pop_back)\n      : Mo(push_back, pop_back,\
    \ push_back, pop_back) {}\n\n  /*\n   * @param push_front\n   * @param pop_front\n\
    \   * @param push_back\n   * @param pop_back\n   */\n  Mo(Push_front push_front,\
    \ Pop_front pop_front, Push_back push_back,\n     Pop_back pop_back)\n      :\
    \ push_front(push_front),\n        pop_front(pop_front),\n        push_back(push_back),\n\
    \        pop_back(pop_back),\n        lpos(),\n        rpos() {}\n\n  /*\n   *\
    \ @return number of queries\n   */\n  size_t size() const { return lft.size();\
    \ }\n\n  /*\n   * @brief add query\n   * @param l left end, inclusive\n   * @param\
    \ r right end, exclusive\n   */\n  void set(size_t l, size_t r) {\n    assert(!(r\
    \ < l));\n    lft.emplace_back(l), rgt.emplace_back(r);\n  }\n\n  /*\n   * @brief\
    \ sort queries\n   */\n  void make() {\n    assert(size());\n    ord.resize(size());\n\
    \    iota(ord.begin(), ord.end(), 0);\n    const size_t width = sqrt(*max_element(rgt.begin(),\
    \ rgt.end()));\n    std::sort(ord.begin(), ord.end(), [&](size_t x, size_t y)\
    \ {\n      if (lft[x] / width != lft[y] / width) return lft[x] < lft[y];\n   \
    \   return rgt[x] < rgt[y];\n    });\n    itr = ord.begin();\n  }\n\n  /*\n  \
    \ * @brief process one query\n   * @return index of query\n   */\n  size_t process()\
    \ {\n    if (itr == ord.end()) return ord.size();\n    const size_t id = *itr++,\
    \ l = lft[id], r = rgt[id];\n    while (lpos > l) push_front(--lpos);\n    while\
    \ (rpos < r) push_back(rpos++);\n    while (lpos < l) pop_front(lpos++);\n   \
    \ while (rpos > r) pop_back(--rpos);\n    return id;\n  }\n};\n\n}  // namespace\
    \ workspace\n"
  code: "#pragma once\n\n/*\n * @file Mo.hpp\n * @brief Mo's Algorithm\n */\n\n#include\
    \ <cassert>\n#include <cmath>\n#include <functional>\n#include <numeric>\n#include\
    \ <vector>\n\nnamespace workspace {\n\n/*\n * @class Mo\n * @brief process queries\
    \ about contiguous subarray\n * @tparam Push_back\n * @tparam Pop_back\n * @tparam\
    \ Push_front Push_back as default\n * @tparam Pop_front Pop_back as default\n\
    \ */\ntemplate <class Push_back, class Pop_back, class Push_front = Push_back,\n\
    \          class Pop_front = Pop_back>\nclass Mo {\n  Push_front push_front;\n\
    \  Pop_front pop_front;\n  Push_back push_back;\n  Pop_back pop_back;\n  std::vector<size_t>\
    \ lft, rgt, ord;\n  std::vector<size_t>::iterator itr;\n  size_t lpos, rpos;\n\
    \n public:\n  /*\n   * @param push_back\n   * @param pop_back\n   */\n  Mo(Push_back\
    \ push_back, Pop_back pop_back)\n      : Mo(push_back, pop_back, push_back, pop_back)\
    \ {}\n\n  /*\n   * @param push_front\n   * @param pop_front\n   * @param push_back\n\
    \   * @param pop_back\n   */\n  Mo(Push_front push_front, Pop_front pop_front,\
    \ Push_back push_back,\n     Pop_back pop_back)\n      : push_front(push_front),\n\
    \        pop_front(pop_front),\n        push_back(push_back),\n        pop_back(pop_back),\n\
    \        lpos(),\n        rpos() {}\n\n  /*\n   * @return number of queries\n\
    \   */\n  size_t size() const { return lft.size(); }\n\n  /*\n   * @brief add\
    \ query\n   * @param l left end, inclusive\n   * @param r right end, exclusive\n\
    \   */\n  void set(size_t l, size_t r) {\n    assert(!(r < l));\n    lft.emplace_back(l),\
    \ rgt.emplace_back(r);\n  }\n\n  /*\n   * @brief sort queries\n   */\n  void make()\
    \ {\n    assert(size());\n    ord.resize(size());\n    iota(ord.begin(), ord.end(),\
    \ 0);\n    const size_t width = sqrt(*max_element(rgt.begin(), rgt.end()));\n\
    \    std::sort(ord.begin(), ord.end(), [&](size_t x, size_t y) {\n      if (lft[x]\
    \ / width != lft[y] / width) return lft[x] < lft[y];\n      return rgt[x] < rgt[y];\n\
    \    });\n    itr = ord.begin();\n  }\n\n  /*\n   * @brief process one query\n\
    \   * @return index of query\n   */\n  size_t process() {\n    if (itr == ord.end())\
    \ return ord.size();\n    const size_t id = *itr++, l = lft[id], r = rgt[id];\n\
    \    while (lpos > l) push_front(--lpos);\n    while (rpos < r) push_back(rpos++);\n\
    \    while (lpos < l) pop_front(lpos++);\n    while (rpos > r) pop_back(--rpos);\n\
    \    return id;\n  }\n};\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/data_structure/Mo.hpp
  requiredBy: []
  timestamp: '2020-11-21 15:39:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/static_range_inversions_query.test.cpp
  - test/library-checker/range_kth_smallest.test.cpp
documentation_of: src/data_structure/Mo.hpp
layout: document
redirect_from:
- /library/src/data_structure/Mo.hpp
- /library/src/data_structure/Mo.hpp.html
title: Mo's Algorithm
---
