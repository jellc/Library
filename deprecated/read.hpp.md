---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"deprecated/read.hpp\"\n#include <iostream>\nnamespace workspace\
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
  path: deprecated/read.hpp
  requiredBy: []
  timestamp: '2020-11-20 23:47:37+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: deprecated/read.hpp
layout: document
redirect_from:
- /library/deprecated/read.hpp
- /library/deprecated/read.hpp.html
title: deprecated/read.hpp
---
