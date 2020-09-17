---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/zalgorithm.test.cpp
    title: test/library-checker/zalgorithm.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 2 \"string/z_algorithm.hpp\"\n#include <string>\n#include <vector>\n\
    \ntemplate <class str_type = std::string> class z_algorithm {\n  str_type key;\n\
    \  std::vector<size_t> z;\n\n  void make() {\n    if (z.empty()) return;\n   \
    \ for (size_t i{1}, j{0}; i != size(); ++i) {\n      if (z[i - j] + i < z[j] +\
    \ j) {\n        z[i] = z[i - j];\n      } else {\n        size_t k{z[j] + j >\
    \ i ? z[j] + j - i : 0};\n        while (k + i < size() && key[k] == key[k + i])\
    \ ++k;\n        z[i] = k;\n        j = i;\n      }\n    }\n    z.front() = size();\n\
    \  }\n\n public:\n  z_algorithm(const str_type &key) : key(key), z(size()) { make();\
    \ }\n\n  std::vector<size_t>::const_iterator begin() const { return z.begin();\
    \ }\n  std::vector<size_t>::const_iterator end() const { return z.end(); }\n\n\
    \  size_t size() const { return key.size(); }\n\n  size_t operator[](size_t i)\
    \ const {\n    assert(i < size());\n    return z[i];\n  }\n\n  std::vector<size_t>\
    \ pattern_search(const str_type &str) const {\n    str_type ccat(key);\n    ccat.insert(end(ccat),\
    \ begin(str), end(str));\n    z_algorithm z(ccat);\n    std::vector<size_t> res(z.begin()\
    \ + size(), z.end());\n    for (size_t &x : res)\n      if (x > size()) x = size();\n\
    \    return res;\n  }\n};\n"
  code: "#pragma once\n#include <string>\n#include <vector>\n\ntemplate <class str_type\
    \ = std::string> class z_algorithm {\n  str_type key;\n  std::vector<size_t> z;\n\
    \n  void make() {\n    if (z.empty()) return;\n    for (size_t i{1}, j{0}; i !=\
    \ size(); ++i) {\n      if (z[i - j] + i < z[j] + j) {\n        z[i] = z[i - j];\n\
    \      } else {\n        size_t k{z[j] + j > i ? z[j] + j - i : 0};\n        while\
    \ (k + i < size() && key[k] == key[k + i]) ++k;\n        z[i] = k;\n        j\
    \ = i;\n      }\n    }\n    z.front() = size();\n  }\n\n public:\n  z_algorithm(const\
    \ str_type &key) : key(key), z(size()) { make(); }\n\n  std::vector<size_t>::const_iterator\
    \ begin() const { return z.begin(); }\n  std::vector<size_t>::const_iterator end()\
    \ const { return z.end(); }\n\n  size_t size() const { return key.size(); }\n\n\
    \  size_t operator[](size_t i) const {\n    assert(i < size());\n    return z[i];\n\
    \  }\n\n  std::vector<size_t> pattern_search(const str_type &str) const {\n  \
    \  str_type ccat(key);\n    ccat.insert(end(ccat), begin(str), end(str));\n  \
    \  z_algorithm z(ccat);\n    std::vector<size_t> res(z.begin() + size(), z.end());\n\
    \    for (size_t &x : res)\n      if (x > size()) x = size();\n    return res;\n\
    \  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: string/z_algorithm.hpp
  requiredBy: []
  timestamp: '2020-09-07 03:07:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/zalgorithm.test.cpp
documentation_of: string/z_algorithm.hpp
layout: document
redirect_from:
- /library/string/z_algorithm.hpp
- /library/string/z_algorithm.hpp.html
title: string/z_algorithm.hpp
---