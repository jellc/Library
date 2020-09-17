---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/static_range_inversions_query.test.cpp
    title: test/library-checker/static_range_inversions_query.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/range_kth_smallest.test.cpp
    title: test/library-checker/range_kth_smallest.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"utils/coordinate_compression.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\ntemplate <class T>\nclass coordinate_compression\n\
    {\n    std::vector<T> uniquely;\n    std::vector<size_t> compressed;\n\npublic:\n\
    \    coordinate_compression(const std::vector<T> &raw) : uniquely(raw), compressed(raw.size())\n\
    \    {\n        std::sort(uniquely.begin(), uniquely.end());\n        uniquely.erase(std::unique(uniquely.begin(),\
    \ uniquely.end()), uniquely.end());\n        for(size_t i = 0; i != size(); ++i)\n\
    \            compressed[i] = std::lower_bound(uniquely.begin(), uniquely.end(),\
    \ raw[i]) - uniquely.begin();\n    }\n\n    size_t operator[](const size_t idx)\
    \ const\n    {\n        assert(idx < size());\n        return compressed[idx];\n\
    \    }\n\n    size_t size() const { return compressed.size(); }\n\n    size_t\
    \ count() const { return uniquely.size(); }\n\n    T value_of(const size_t ord)\
    \ const\n    {\n        assert(ord < count());\n        return uniquely[ord];\n\
    \    }\n\n    size_t order_of(const T &val) const { return std::lower_bound(uniquely.begin(),\
    \ uniquely.end(), val) - uniquely.begin(); }\n\n    std::vector<size_t>::iterator\
    \ begin() { return compressed.begin(); }\n    std::vector<size_t>::iterator end()\
    \ { return compressed.end(); }\n    std::vector<size_t>::reverse_iterator rbegin()\
    \ { return compressed.rbegin(); }\n    std::vector<size_t>::reverse_iterator rend()\
    \ { return compressed.rend(); }\n};\n"
  code: "#include <algorithm>\n#include <cassert>\n#include <vector>\n\ntemplate <class\
    \ T>\nclass coordinate_compression\n{\n    std::vector<T> uniquely;\n    std::vector<size_t>\
    \ compressed;\n\npublic:\n    coordinate_compression(const std::vector<T> &raw)\
    \ : uniquely(raw), compressed(raw.size())\n    {\n        std::sort(uniquely.begin(),\
    \ uniquely.end());\n        uniquely.erase(std::unique(uniquely.begin(), uniquely.end()),\
    \ uniquely.end());\n        for(size_t i = 0; i != size(); ++i)\n            compressed[i]\
    \ = std::lower_bound(uniquely.begin(), uniquely.end(), raw[i]) - uniquely.begin();\n\
    \    }\n\n    size_t operator[](const size_t idx) const\n    {\n        assert(idx\
    \ < size());\n        return compressed[idx];\n    }\n\n    size_t size() const\
    \ { return compressed.size(); }\n\n    size_t count() const { return uniquely.size();\
    \ }\n\n    T value_of(const size_t ord) const\n    {\n        assert(ord < count());\n\
    \        return uniquely[ord];\n    }\n\n    size_t order_of(const T &val) const\
    \ { return std::lower_bound(uniquely.begin(), uniquely.end(), val) - uniquely.begin();\
    \ }\n\n    std::vector<size_t>::iterator begin() { return compressed.begin();\
    \ }\n    std::vector<size_t>::iterator end() { return compressed.end(); }\n  \
    \  std::vector<size_t>::reverse_iterator rbegin() { return compressed.rbegin();\
    \ }\n    std::vector<size_t>::reverse_iterator rend() { return compressed.rend();\
    \ }\n};"
  dependsOn: []
  isVerificationFile: false
  path: utils/coordinate_compression.hpp
  requiredBy: []
  timestamp: '2020-08-03 02:03:38+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/static_range_inversions_query.test.cpp
  - test/library-checker/range_kth_smallest.test.cpp
documentation_of: utils/coordinate_compression.hpp
layout: document
redirect_from:
- /library/utils/coordinate_compression.hpp
- /library/utils/coordinate_compression.hpp.html
title: utils/coordinate_compression.hpp
---
