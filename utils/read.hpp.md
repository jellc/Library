---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: template.cpp
    title: template.cpp
  - icon: ':warning:'
    path: utils.hpp
    title: utils.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/aors_score.test.cpp
    title: test/aizu-online-judge/aors_score.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utils/read.hpp\"\n#include <iostream>\nnamespace workspace\
    \ {\n// read with std::cin.\ntemplate <class T = void>\nstruct read\n{\n    typename\
    \ std::remove_const<T>::type value;\n    template <class... types>\n    read(types...\
    \ args) : value(args...) { std::cin >> value; }\n    operator T() const { return\
    \ value; }\n};\ntemplate <>\nstruct read<void>\n{\n    template <class T>\n  \
    \  operator T() const { T value; std::cin >> value; return value; }\n};\n} //\
    \ namespace workspace\n"
  code: "#pragma once\n#include <iostream>\nnamespace workspace {\n// read with std::cin.\n\
    template <class T = void>\nstruct read\n{\n    typename std::remove_const<T>::type\
    \ value;\n    template <class... types>\n    read(types... args) : value(args...)\
    \ { std::cin >> value; }\n    operator T() const { return value; }\n};\ntemplate\
    \ <>\nstruct read<void>\n{\n    template <class T>\n    operator T() const { T\
    \ value; std::cin >> value; return value; }\n};\n} // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/read.hpp
  requiredBy:
  - utils.hpp
  - template.cpp
  timestamp: '2020-08-14 18:02:25+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aizu-online-judge/aors_score.test.cpp
documentation_of: utils/read.hpp
layout: document
redirect_from:
- /library/utils/read.hpp
- /library/utils/read.hpp.html
title: utils/read.hpp
---
