---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/aizu-online-judge/2292.test.cpp
    title: test/aizu-online-judge/2292.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: Manacher's Algorithm
    links: []
  bundledCode: "#line 2 \"src/string/Manacher.hpp\"\n\n/*\n * @file Manacher.hpp\n\
    \ * @brief Manacher's Algorithm\n */\n\n#include <iostream>\n#include <string>\n\
    #include <vector>\n\nnamespace workspace {\n\n/*\n * @class Manacher\n * @brief\
    \ Manacher's Algorithm.\n * @tparam str_type the type of string\n */\ntemplate\
    \ <class str_type = std::string> class Manacher {\n  const size_t len;\n  std::vector<size_t>\
    \ rad;\n\n public:\n  Manacher(const str_type &str) : len(str.size()), rad(str.size())\
    \ {\n    for (size_t i = 0, c = 0; i != len; ++i) {\n      int l = c * 2 - i;\n\
    \      if (l >= 0 && c + rad[c] > i + rad[l])\n        rad[i] = rad[l];\n    \
    \  else {\n        size_t j = c + rad[c] - i;\n        while (i >= j && i + j\
    \ != len && str[i - j] == str[i + j]) ++j;\n        rad[c = i] = j;\n      }\n\
    \    }\n  }\n\n  std::vector<size_t>::const_iterator begin() const { return rad.begin();\
    \ }\n\n  std::vector<size_t>::const_iterator end() const { return rad.end(); }\n\
    \n  /*\n   * @fn size\n   * @return length of the string\n   */\n  size_t size()\
    \ const { return rad.size(); }\n\n  /*\n   * @fn operator[]\n   * @param i index\n\
    \   * @return the maximum radius L s.t. the substring (i - L, i + L) is\n   *\
    \ palindrome\n   */\n  size_t operator[](size_t i) const { return rad[i]; }\n\n\
    \  /*\n   * @fn operator<<\n   * @brief print a Manacher object.\n   * @param\
    \ os ostream\n   * @param manacher a Manacher object\n   * @return os\n   */\n\
    \  friend std::ostream &operator<<(std::ostream &os, const Manacher &manacher)\
    \ {\n    bool is_front = true;\n    for (size_t r : manacher.rad) {\n      if\
    \ (is_front)\n        is_front = false;\n      else\n        os << \" \";\n  \
    \    os << r;\n    }\n    return os;\n  }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file Manacher.hpp\n * @brief Manacher's Algorithm\n\
    \ */\n\n#include <iostream>\n#include <string>\n#include <vector>\n\nnamespace\
    \ workspace {\n\n/*\n * @class Manacher\n * @brief Manacher's Algorithm.\n * @tparam\
    \ str_type the type of string\n */\ntemplate <class str_type = std::string> class\
    \ Manacher {\n  const size_t len;\n  std::vector<size_t> rad;\n\n public:\n  Manacher(const\
    \ str_type &str) : len(str.size()), rad(str.size()) {\n    for (size_t i = 0,\
    \ c = 0; i != len; ++i) {\n      int l = c * 2 - i;\n      if (l >= 0 && c + rad[c]\
    \ > i + rad[l])\n        rad[i] = rad[l];\n      else {\n        size_t j = c\
    \ + rad[c] - i;\n        while (i >= j && i + j != len && str[i - j] == str[i\
    \ + j]) ++j;\n        rad[c = i] = j;\n      }\n    }\n  }\n\n  std::vector<size_t>::const_iterator\
    \ begin() const { return rad.begin(); }\n\n  std::vector<size_t>::const_iterator\
    \ end() const { return rad.end(); }\n\n  /*\n   * @fn size\n   * @return length\
    \ of the string\n   */\n  size_t size() const { return rad.size(); }\n\n  /*\n\
    \   * @fn operator[]\n   * @param i index\n   * @return the maximum radius L s.t.\
    \ the substring (i - L, i + L) is\n   * palindrome\n   */\n  size_t operator[](size_t\
    \ i) const { return rad[i]; }\n\n  /*\n   * @fn operator<<\n   * @brief print\
    \ a Manacher object.\n   * @param os ostream\n   * @param manacher a Manacher\
    \ object\n   * @return os\n   */\n  friend std::ostream &operator<<(std::ostream\
    \ &os, const Manacher &manacher) {\n    bool is_front = true;\n    for (size_t\
    \ r : manacher.rad) {\n      if (is_front)\n        is_front = false;\n      else\n\
    \        os << \" \";\n      os << r;\n    }\n    return os;\n  }\n};\n\n}  //\
    \ namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/string/Manacher.hpp
  requiredBy: []
  timestamp: '2020-11-16 22:49:01+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/aizu-online-judge/2292.test.cpp
documentation_of: src/string/Manacher.hpp
layout: document
redirect_from:
- /library/src/string/Manacher.hpp
- /library/src/string/Manacher.hpp.html
title: Manacher's Algorithm
---
