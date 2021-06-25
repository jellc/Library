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
    document_title: Compression
    links: []
  bundledCode: "#line 2 \"src/data_structure/compression.hpp\"\n\n/**\n * @file compression.hpp\n\
    \ * @brief Compression\n */\n\n#include <algorithm>\n#include <cassert>\n#include\
    \ <vector>\n\nnamespace workspace {\n\ntemplate <class _Tp> class compression\
    \ {\n  std::vector<_Tp> __vec;\n\n  decltype(auto) begin() { return __vec.begin();\
    \ }\n\n  decltype(auto) end() { return __vec.end(); }\n\n public:\n  using size_type\
    \ = typename std::vector<_Tp>::size_type;\n\n  /**\n   * @brief Construct a new\
    \ compression object.\n   */\n  compression() = default;\n\n  /**\n   * @brief\
    \ Construct a new compression object.\n   *\n   * @param __first\n   * @param\
    \ __last\n   */\n  template <class _IIter>\n  compression(_IIter __first, _IIter\
    \ __last) noexcept : __vec(__first, __last) {\n    make();\n  }\n\n  decltype(auto)\
    \ begin() const noexcept { return __vec.begin(); }\n\n  decltype(auto) end() const\
    \ noexcept { return __vec.end(); }\n\n  decltype(auto) operator[](size_type __i)\
    \ const noexcept {\n    assert(__i < size());\n    return __vec[__i];\n  }\n\n\
    \  size_type size() const noexcept { return __vec.size(); }\n\n  template <class...\
    \ _Args> decltype(auto) emplace(_Args&&... __args) noexcept {\n    return __vec.emplace_back(std::forward<_Args>(__args)...);\n\
    \  }\n\n  template <class... _Args> void insert(_Args&&... __args) noexcept {\n\
    \    __vec.insert(end(), std::forward<_Args>(__args)...);\n  }\n\n  /**\n   *\
    \ @brief Sort and make unique.\n   * @return Number of different values.\n   */\n\
    \  size_type make() noexcept {\n    std::sort(begin(), end());\n\n    __vec.erase(std::unique(begin(),\
    \ end(),\n                            [](const _Tp& __l, const _Tp& __r) {\n \
    \                             return !(__l < __r) && !(__r < __l);\n         \
    \                   }),\n                end());\n\n    return size();\n  }\n\n\
    \  size_type lower_bound(const _Tp& __x) const noexcept {\n    return std::lower_bound(begin(),\
    \ end(), __x) - begin();\n  }\n\n  size_type upper_bound(const _Tp& __x) const\
    \ noexcept {\n    return std::upper_bound(begin(), end(), __x) - begin();\n  }\n\
    };\n\ntemplate <class _IIter>\ncompression(_IIter, _IIter)\n    -> compression<typename\
    \ std::iterator_traits<_IIter>::value_type>;\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file compression.hpp\n * @brief Compression\n */\n\
    \n#include <algorithm>\n#include <cassert>\n#include <vector>\n\nnamespace workspace\
    \ {\n\ntemplate <class _Tp> class compression {\n  std::vector<_Tp> __vec;\n\n\
    \  decltype(auto) begin() { return __vec.begin(); }\n\n  decltype(auto) end()\
    \ { return __vec.end(); }\n\n public:\n  using size_type = typename std::vector<_Tp>::size_type;\n\
    \n  /**\n   * @brief Construct a new compression object.\n   */\n  compression()\
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
    \ std::iterator_traits<_IIter>::value_type>;\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/data_structure/compression.hpp
  requiredBy: []
  timestamp: '2021-06-25 19:18:38+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/range_kth_smallest.test.cpp
  - test/library-checker/static_range_inversions_query.test.cpp
documentation_of: src/data_structure/compression.hpp
layout: document
redirect_from:
- /library/src/data_structure/compression.hpp
- /library/src/data_structure/compression.hpp.html
title: Compression
---
