---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/library-checker/zalgorithm.test.cpp
    title: test/library-checker/zalgorithm.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: Z-Algorithm
    links: []
  bundledCode: "#line 2 \"src/string/z_algorithm.hpp\"\n\n/*\n * @file z_algorith.hpp\n\
    \ * @brief Z-Algorithm\n */\n\n#include <string>\n#include <vector>\n\nnamespace\
    \ workspace {\n\n/*\n * @class z_algorithm\n * @brief construct Z-array in linear\
    \ time.\n * @tparam str_type the type of string\n */\ntemplate <class str_type\
    \ = std::string> class z_algorithm {\n  str_type key;\n  std::vector<size_t> z;\n\
    \n  void make() {\n    if (z.empty()) return;\n    for (size_t i{1}, j{0}; i !=\
    \ size(); ++i) {\n      if (z[i - j] + i < z[j] + j) {\n        z[i] = z[i - j];\n\
    \      } else {\n        size_t k{z[j] + j > i ? z[j] + j - i : 0};\n        while\
    \ (k + i < size() && key[k] == key[k + i]) ++k;\n        z[i] = k;\n        j\
    \ = i;\n      }\n    }\n    z.front() = size();\n  }\n\n public:\n  z_algorithm(const\
    \ str_type &key) : key(key), z(size()) { make(); }\n\n  std::vector<size_t>::const_iterator\
    \ begin() const { return z.begin(); }\n\n  std::vector<size_t>::const_iterator\
    \ end() const { return z.end(); }\n\n  /*\n   * @fn size\n   * @return length\
    \ of the string\n   */\n  size_t size() const { return key.size(); }\n\n  /*\n\
    \   * @fn operator[]\n   * @param i index\n   * @return LCP of (i)-th suffix and\
    \ the whole string\n   */\n  size_t operator[](size_t i) const {\n    assert(i\
    \ < size());\n    return z[i];\n  }\n\n  /*\n   * @fn pattern_search\n   * @param\
    \ str\n   * @return length of the string\n   */\n  std::vector<size_t> pattern_search(const\
    \ str_type &str) const {\n    str_type ccat(key);\n    ccat.insert(end(ccat),\
    \ begin(str), end(str));\n    z_algorithm z(ccat);\n    std::vector<size_t> res(z.begin()\
    \ + size(), z.end());\n    for (size_t &x : res)\n      if (x > size()) x = size();\n\
    \    return res;\n  }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file z_algorith.hpp\n * @brief Z-Algorithm\n */\n\
    \n#include <string>\n#include <vector>\n\nnamespace workspace {\n\n/*\n * @class\
    \ z_algorithm\n * @brief construct Z-array in linear time.\n * @tparam str_type\
    \ the type of string\n */\ntemplate <class str_type = std::string> class z_algorithm\
    \ {\n  str_type key;\n  std::vector<size_t> z;\n\n  void make() {\n    if (z.empty())\
    \ return;\n    for (size_t i{1}, j{0}; i != size(); ++i) {\n      if (z[i - j]\
    \ + i < z[j] + j) {\n        z[i] = z[i - j];\n      } else {\n        size_t\
    \ k{z[j] + j > i ? z[j] + j - i : 0};\n        while (k + i < size() && key[k]\
    \ == key[k + i]) ++k;\n        z[i] = k;\n        j = i;\n      }\n    }\n   \
    \ z.front() = size();\n  }\n\n public:\n  z_algorithm(const str_type &key) : key(key),\
    \ z(size()) { make(); }\n\n  std::vector<size_t>::const_iterator begin() const\
    \ { return z.begin(); }\n\n  std::vector<size_t>::const_iterator end() const {\
    \ return z.end(); }\n\n  /*\n   * @fn size\n   * @return length of the string\n\
    \   */\n  size_t size() const { return key.size(); }\n\n  /*\n   * @fn operator[]\n\
    \   * @param i index\n   * @return LCP of (i)-th suffix and the whole string\n\
    \   */\n  size_t operator[](size_t i) const {\n    assert(i < size());\n    return\
    \ z[i];\n  }\n\n  /*\n   * @fn pattern_search\n   * @param str\n   * @return length\
    \ of the string\n   */\n  std::vector<size_t> pattern_search(const str_type &str)\
    \ const {\n    str_type ccat(key);\n    ccat.insert(end(ccat), begin(str), end(str));\n\
    \    z_algorithm z(ccat);\n    std::vector<size_t> res(z.begin() + size(), z.end());\n\
    \    for (size_t &x : res)\n      if (x > size()) x = size();\n    return res;\n\
    \  }\n};\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/string/z_algorithm.hpp
  requiredBy: []
  timestamp: '2020-11-16 17:31:16+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/library-checker/zalgorithm.test.cpp
documentation_of: src/string/z_algorithm.hpp
layout: document
redirect_from:
- /library/src/string/z_algorithm.hpp
- /library/src/string/z_algorithm.hpp.html
title: Z-Algorithm
---
