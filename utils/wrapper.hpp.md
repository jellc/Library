---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: template.cpp
    title: Template
  - icon: ':warning:'
    path: utils.hpp
    title: utils.hpp
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utils/wrapper.hpp\"\ntemplate <class Container> class reversed\
    \ {\n  Container &ref, copy;\n\n public:\n  constexpr reversed(Container &ref)\
    \ : ref(ref) {}\n  constexpr reversed(Container &&ref = Container()) : ref(copy),\
    \ copy(ref) {}\n  constexpr auto begin() const { return ref.rbegin(); }\n  constexpr\
    \ auto end() const { return ref.rend(); }\n  constexpr operator Container() const\
    \ { return ref; }\n};\n"
  code: "#pragma once\ntemplate <class Container> class reversed {\n  Container &ref,\
    \ copy;\n\n public:\n  constexpr reversed(Container &ref) : ref(ref) {}\n  constexpr\
    \ reversed(Container &&ref = Container()) : ref(copy), copy(ref) {}\n  constexpr\
    \ auto begin() const { return ref.rbegin(); }\n  constexpr auto end() const {\
    \ return ref.rend(); }\n  constexpr operator Container() const { return ref; }\n\
    };\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/wrapper.hpp
  requiredBy:
  - template.cpp
  - utils.hpp
  timestamp: '2020-10-07 23:27:03+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils/wrapper.hpp
layout: document
redirect_from:
- /library/utils/wrapper.hpp
- /library/utils/wrapper.hpp.html
title: utils/wrapper.hpp
---
