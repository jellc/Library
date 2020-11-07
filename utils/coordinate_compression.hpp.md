---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: template.cpp
    title: Code template
  - icon: ':warning:'
    path: utils.hpp
    title: all headers in utlis
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/range_kth_smallest.test.cpp
    title: test/library-checker/range_kth_smallest.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/static_range_inversions_query.test.cpp
    title: test/library-checker/static_range_inversions_query.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utils/coordinate_compression.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\ntemplate <class T> class coordinate_compression\
    \ {\n  std::vector<T> uniquely;\n  std::vector<size_t> compressed;\n\n public:\n\
    \  coordinate_compression(const std::vector<T> &raw)\n      : uniquely(raw), compressed(raw.size())\
    \ {\n    std::sort(uniquely.begin(), uniquely.end());\n    uniquely.erase(std::unique(uniquely.begin(),\
    \ uniquely.end()),\n                   uniquely.end());\n    for (size_t i = 0;\
    \ i != size(); ++i)\n      compressed[i] =\n          std::lower_bound(uniquely.begin(),\
    \ uniquely.end(), raw[i]) -\n          uniquely.begin();\n  }\n\n  size_t operator[](const\
    \ size_t idx) const {\n    assert(idx < size());\n    return compressed[idx];\n\
    \  }\n\n  size_t size() const { return compressed.size(); }\n\n  size_t count()\
    \ const { return uniquely.size(); }\n\n  T value(const size_t ord) const {\n \
    \   assert(ord < count());\n    return uniquely[ord];\n  }\n\n  size_t order(const\
    \ T &value) const {\n    return std::lower_bound(uniquely.begin(), uniquely.end(),\
    \ value) -\n           uniquely.begin();\n  }\n\n  auto begin() { return compressed.begin();\
    \ }\n  auto end() { return compressed.end(); }\n  auto rbegin() { return compressed.rbegin();\
    \ }\n  auto rend() { return compressed.rend(); }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\
    \ntemplate <class T> class coordinate_compression {\n  std::vector<T> uniquely;\n\
    \  std::vector<size_t> compressed;\n\n public:\n  coordinate_compression(const\
    \ std::vector<T> &raw)\n      : uniquely(raw), compressed(raw.size()) {\n    std::sort(uniquely.begin(),\
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
    \ }\n  auto rend() { return compressed.rend(); }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/coordinate_compression.hpp
  requiredBy:
  - template.cpp
  - utils.hpp
  timestamp: '2020-09-26 02:24:45+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/range_kth_smallest.test.cpp
  - test/library-checker/static_range_inversions_query.test.cpp
documentation_of: utils/coordinate_compression.hpp
layout: document
redirect_from:
- /library/utils/coordinate_compression.hpp
- /library/utils/coordinate_compression.hpp.html
title: utils/coordinate_compression.hpp
---
