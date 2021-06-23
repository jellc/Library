---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/3170.test.cpp
    title: test/aizu-online-judge/3170.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/range_chmin_chmax_add_range_sum.test.cpp
    title: test/library-checker/range_chmin_chmax_add_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/staticrmq.test.cpp
    title: test/library-checker/staticrmq.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Buckets
    links: []
  bundledCode: "#line 2 \"src/data_structure/buckets.hpp\"\n\n/**\n * @file buckets.hpp\n\
    \ * @brief Buckets\n */\n\n#include <cmath>\n#include <vector>\n\nnamespace workspace\
    \ {\n\n/**\n * @brief Buckets on a sequence.\n */\ntemplate <class _Iterator,\
    \ class _Pack, class _Unpack> struct buckets {\n  // Require random access.\n\
    \  static_assert(\n      std::is_same<typename std::iterator_traits<_Iterator>::iterator_category,\n\
    \                   std::random_access_iterator_tag>::value);\n\n  using difference_type\
    \ =\n      typename std::iterator_traits<_Iterator>::difference_type;\n\n  _Iterator\
    \ __begin, __end;\n\n  using value_type = decltype(std::declval<_Pack>()(std::declval<_Iterator>(),\n\
    \                                                    std::declval<_Iterator>()));\n\
    \n  struct bucket {\n    value_type __data;\n    _Iterator __begin;\n    _Iterator\
    \ __end;\n  };\n\n  _Pack __pack;\n  _Unpack __unpack;\n  difference_type __unit;\n\
    \  std::vector<bucket> __buckets;\n\n  void prepare() {\n    if (!__unit) __unit\
    \ = round(sqrt(std::distance(__begin, __end)));\n\n    for (auto __l = __begin,\
    \ __r = __l; __r != __end; __l = __r) {\n      for (auto __n = __unit; __r !=\
    \ __end && __n; --__n) ++__r;\n      __buckets.push_back({__pack(__l, __r), __l,\
    \ __r});\n    }\n  }\n\n public:\n  /**\n   * @brief Constuct a new buckets object.\n\
    \   */\n  buckets(_Iterator __first, _Iterator __last, _Pack __pack, _Unpack __unpack,\n\
    \          difference_type __unit = 0)\n      : __begin(__first),\n        __end(__last),\n\
    \        __pack(__pack),\n        __unpack(__unpack),\n        __unit(__unit)\
    \ {\n    prepare();\n  }\n\n  /**\n   * @brief Number of buckets.\n   */\n  auto\
    \ size() const { return __buckets.size(); }\n\n  bool empty() const { return __begin\
    \ == __end; }\n\n  /**\n   * @brief Operate on a subsegment.\n   *\n   * @param\
    \ __first\n   * @param __last\n   * @param __oper\n   */\n  template <class _Operator>\n\
    \  void operator()(_Iterator __first, _Iterator __last, _Operator __oper) {\n\
    \    if (__first == __last) return;\n\n    auto __index = std::distance(__begin,\
    \ __first);\n    auto __b = std::next(__buckets.begin(), __index / __unit);\n\n\
    \    if (__index % __unit) {\n      __unpack(__b->__data, __b->__begin, __b->__end);\n\
    \n      auto __mid = std::distance(__last, __b->__end) > 0 ? __last : __b->__end;\n\
    \n      auto __tmp = __pack(__first, __mid);\n      __oper(__tmp);\n      __unpack(__tmp,\
    \ __first, __mid);\n\n      __b->__data = __pack(__b->__begin, __b->__end);\n\
    \      ++__b;\n    }\n\n    while (true) {\n      if (__b == __buckets.end())\
    \ return;\n      if (std::distance(__b->__end, __last) < 0) break;\n\n      __oper(__b->__data);\n\
    \      ++__b;\n    }\n\n    if (std::distance(__b->__begin, __last) > 0) {\n \
    \     __unpack(__b->__data, __b->__begin, __b->__end);\n\n      auto __tmp = __pack(__b->__begin,\
    \ __last);\n      __oper(__tmp);\n      __unpack(__tmp, __b->__begin, __last);\n\
    \n      __b->__data = __pack(__b->__begin, __b->__end);\n    }\n  }\n\n  /**\n\
    \   * @brief Operate on a point.\n   *\n   * @param __pos\n   * @param __oper\n\
    \   */\n  template <class _Operator>\n  void operator()(_Iterator __pos, _Operator\
    \ __oper) {\n    auto __index = std::distance(__begin, __pos);\n    auto __b =\
    \ std::next(__buckets.begin(), __index / __unit);\n\n    __unpack(__b->__data,\
    \ __b->__begin, __b->__end);\n    __oper(*__pos);\n    __b->__data = __pack(__b->__begin,\
    \ __b->__end);\n  }\n\n  /**\n   * @brief Operate on a subsegment.\n   *\n   *\
    \ @param __i\n   * @param __j\n   * @param __oper\n   */\n  template <class _Operator>\n\
    \  void operator()(difference_type __i, difference_type __j, _Operator __oper)\
    \ {\n    operator()(std::next(__begin, __i), std::next(__begin, __j), __oper);\n\
    \  }\n\n  /**\n   * @brief Operate on a point.\n   *\n   * @param __pos\n   *\
    \ @param __oper\n   */\n  template <class _Operator>\n  void operator()(difference_type\
    \ __i, _Operator __oper) {\n    operator()(std::next(__begin, __i), __oper);\n\
    \  }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file buckets.hpp\n * @brief Buckets\n */\n\n#include\
    \ <cmath>\n#include <vector>\n\nnamespace workspace {\n\n/**\n * @brief Buckets\
    \ on a sequence.\n */\ntemplate <class _Iterator, class _Pack, class _Unpack>\
    \ struct buckets {\n  // Require random access.\n  static_assert(\n      std::is_same<typename\
    \ std::iterator_traits<_Iterator>::iterator_category,\n                   std::random_access_iterator_tag>::value);\n\
    \n  using difference_type =\n      typename std::iterator_traits<_Iterator>::difference_type;\n\
    \n  _Iterator __begin, __end;\n\n  using value_type = decltype(std::declval<_Pack>()(std::declval<_Iterator>(),\n\
    \                                                    std::declval<_Iterator>()));\n\
    \n  struct bucket {\n    value_type __data;\n    _Iterator __begin;\n    _Iterator\
    \ __end;\n  };\n\n  _Pack __pack;\n  _Unpack __unpack;\n  difference_type __unit;\n\
    \  std::vector<bucket> __buckets;\n\n  void prepare() {\n    if (!__unit) __unit\
    \ = round(sqrt(std::distance(__begin, __end)));\n\n    for (auto __l = __begin,\
    \ __r = __l; __r != __end; __l = __r) {\n      for (auto __n = __unit; __r !=\
    \ __end && __n; --__n) ++__r;\n      __buckets.push_back({__pack(__l, __r), __l,\
    \ __r});\n    }\n  }\n\n public:\n  /**\n   * @brief Constuct a new buckets object.\n\
    \   */\n  buckets(_Iterator __first, _Iterator __last, _Pack __pack, _Unpack __unpack,\n\
    \          difference_type __unit = 0)\n      : __begin(__first),\n        __end(__last),\n\
    \        __pack(__pack),\n        __unpack(__unpack),\n        __unit(__unit)\
    \ {\n    prepare();\n  }\n\n  /**\n   * @brief Number of buckets.\n   */\n  auto\
    \ size() const { return __buckets.size(); }\n\n  bool empty() const { return __begin\
    \ == __end; }\n\n  /**\n   * @brief Operate on a subsegment.\n   *\n   * @param\
    \ __first\n   * @param __last\n   * @param __oper\n   */\n  template <class _Operator>\n\
    \  void operator()(_Iterator __first, _Iterator __last, _Operator __oper) {\n\
    \    if (__first == __last) return;\n\n    auto __index = std::distance(__begin,\
    \ __first);\n    auto __b = std::next(__buckets.begin(), __index / __unit);\n\n\
    \    if (__index % __unit) {\n      __unpack(__b->__data, __b->__begin, __b->__end);\n\
    \n      auto __mid = std::distance(__last, __b->__end) > 0 ? __last : __b->__end;\n\
    \n      auto __tmp = __pack(__first, __mid);\n      __oper(__tmp);\n      __unpack(__tmp,\
    \ __first, __mid);\n\n      __b->__data = __pack(__b->__begin, __b->__end);\n\
    \      ++__b;\n    }\n\n    while (true) {\n      if (__b == __buckets.end())\
    \ return;\n      if (std::distance(__b->__end, __last) < 0) break;\n\n      __oper(__b->__data);\n\
    \      ++__b;\n    }\n\n    if (std::distance(__b->__begin, __last) > 0) {\n \
    \     __unpack(__b->__data, __b->__begin, __b->__end);\n\n      auto __tmp = __pack(__b->__begin,\
    \ __last);\n      __oper(__tmp);\n      __unpack(__tmp, __b->__begin, __last);\n\
    \n      __b->__data = __pack(__b->__begin, __b->__end);\n    }\n  }\n\n  /**\n\
    \   * @brief Operate on a point.\n   *\n   * @param __pos\n   * @param __oper\n\
    \   */\n  template <class _Operator>\n  void operator()(_Iterator __pos, _Operator\
    \ __oper) {\n    auto __index = std::distance(__begin, __pos);\n    auto __b =\
    \ std::next(__buckets.begin(), __index / __unit);\n\n    __unpack(__b->__data,\
    \ __b->__begin, __b->__end);\n    __oper(*__pos);\n    __b->__data = __pack(__b->__begin,\
    \ __b->__end);\n  }\n\n  /**\n   * @brief Operate on a subsegment.\n   *\n   *\
    \ @param __i\n   * @param __j\n   * @param __oper\n   */\n  template <class _Operator>\n\
    \  void operator()(difference_type __i, difference_type __j, _Operator __oper)\
    \ {\n    operator()(std::next(__begin, __i), std::next(__begin, __j), __oper);\n\
    \  }\n\n  /**\n   * @brief Operate on a point.\n   *\n   * @param __pos\n   *\
    \ @param __oper\n   */\n  template <class _Operator>\n  void operator()(difference_type\
    \ __i, _Operator __oper) {\n    operator()(std::next(__begin, __i), __oper);\n\
    \  }\n};\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/data_structure/buckets.hpp
  requiredBy: []
  timestamp: '2021-05-22 02:27:41+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aizu-online-judge/3170.test.cpp
  - test/library-checker/staticrmq.test.cpp
  - test/library-checker/range_chmin_chmax_add_range_sum.test.cpp
documentation_of: src/data_structure/buckets.hpp
layout: document
redirect_from:
- /library/src/data_structure/buckets.hpp
- /library/src/data_structure/buckets.hpp.html
title: Buckets
---
