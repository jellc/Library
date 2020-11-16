---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/utils/coordinate_compression.hpp\"\n#include <algorithm>\n\
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
  path: src/utils/coordinate_compression.hpp
  requiredBy: []
  timestamp: '2020-11-16 14:21:51+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/coordinate_compression.hpp
layout: document
redirect_from:
- /library/src/utils/coordinate_compression.hpp
- /library/src/utils/coordinate_compression.hpp.html
title: src/utils/coordinate_compression.hpp
---
