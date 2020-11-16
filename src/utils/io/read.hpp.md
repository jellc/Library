---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: src/utils/io.hpp
    title: src/utils/io.hpp
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/utils/io/read.hpp\"\n#include <iostream>\nnamespace\
    \ workspace {\n// read with std::cin.\ntemplate <class T = void>\nstruct read\n\
    {\n    typename std::remove_const<T>::type value;\n    template <class... types>\n\
    \    read(types... args) : value(args...) { std::cin >> value; }\n    operator\
    \ T() const { return value; }\n};\ntemplate <>\nstruct read<void>\n{\n    template\
    \ <class T>\n    operator T() const { T value; std::cin >> value; return value;\
    \ }\n};\n} // namespace workspace\n"
  code: "#pragma once\n#include <iostream>\nnamespace workspace {\n// read with std::cin.\n\
    template <class T = void>\nstruct read\n{\n    typename std::remove_const<T>::type\
    \ value;\n    template <class... types>\n    read(types... args) : value(args...)\
    \ { std::cin >> value; }\n    operator T() const { return value; }\n};\ntemplate\
    \ <>\nstruct read<void>\n{\n    template <class T>\n    operator T() const { T\
    \ value; std::cin >> value; return value; }\n};\n} // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/io/read.hpp
  requiredBy:
  - src/utils/io.hpp
  timestamp: '2020-11-16 14:21:51+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/io/read.hpp
layout: document
redirect_from:
- /library/src/utils/io/read.hpp
- /library/src/utils/io/read.hpp.html
title: src/utils/io/read.hpp
---
