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
    document_title: Coordinate Compression
    links: []
  bundledCode: "#line 2 \"src/data_structure/coordinate_compression.hpp\"\n\n/*\n\
    \ * @file coordinate_compression.hpp\n * @brief Coordinate Compression\n */\n\n\
    #include <algorithm>\n#include <vector>\n\nnamespace workspace {\n\ntemplate <class\
    \ Type, class Result = size_t>\nstruct coordinate_compression : std::vector<Type>\
    \ {\n  using std::vector<Type>::vector;\n  using std::vector<Type>::begin;\n \
    \ using std::vector<Type>::end;\n\n  using result_type = Result;\n\n  void make()\
    \ {\n    std::sort(begin(), end());\n    std::vector<Type>::erase(std::unique(begin(),\
    \ end()), end());\n  }\n\n  result_type compress(const Type &value) const {\n\
    \    return std::lower_bound(begin(), end(), value) - begin();\n  }\n\n  template\
    \ <class Iter>\n  std::vector<result_type> compress(Iter first, Iter last) const\
    \ {\n    static_assert(std::is_convertible<\n                  typename std::decay<decltype(*std::declval<Iter>())>::type,\n\
    \                  Type>::value);\n    std::vector<result_type> res;\n    for\
    \ (Iter iter = first; iter != last; ++iter)\n      res.emplace_back(compress(*iter));\n\
    \    return res;\n  }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file coordinate_compression.hpp\n * @brief Coordinate\
    \ Compression\n */\n\n#include <algorithm>\n#include <vector>\n\nnamespace workspace\
    \ {\n\ntemplate <class Type, class Result = size_t>\nstruct coordinate_compression\
    \ : std::vector<Type> {\n  using std::vector<Type>::vector;\n  using std::vector<Type>::begin;\n\
    \  using std::vector<Type>::end;\n\n  using result_type = Result;\n\n  void make()\
    \ {\n    std::sort(begin(), end());\n    std::vector<Type>::erase(std::unique(begin(),\
    \ end()), end());\n  }\n\n  result_type compress(const Type &value) const {\n\
    \    return std::lower_bound(begin(), end(), value) - begin();\n  }\n\n  template\
    \ <class Iter>\n  std::vector<result_type> compress(Iter first, Iter last) const\
    \ {\n    static_assert(std::is_convertible<\n                  typename std::decay<decltype(*std::declval<Iter>())>::type,\n\
    \                  Type>::value);\n    std::vector<result_type> res;\n    for\
    \ (Iter iter = first; iter != last; ++iter)\n      res.emplace_back(compress(*iter));\n\
    \    return res;\n  }\n};\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/data_structure/coordinate_compression.hpp
  requiredBy: []
  timestamp: '2020-11-28 14:32:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/range_kth_smallest.test.cpp
  - test/library-checker/static_range_inversions_query.test.cpp
documentation_of: src/data_structure/coordinate_compression.hpp
layout: document
redirect_from:
- /library/src/data_structure/coordinate_compression.hpp
- /library/src/data_structure/coordinate_compression.hpp.html
title: Coordinate Compression
---
