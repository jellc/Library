---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/utils/wrapper.hpp\"\ntemplate <class Container> class\
    \ reversed {\n  Container &ref, copy;\n\n public:\n  constexpr reversed(Container\
    \ &ref) : ref(ref) {}\n  constexpr reversed(Container &&ref = Container()) : ref(copy),\
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
  path: src/utils/wrapper.hpp
  requiredBy: []
  timestamp: '2020-11-16 14:21:51+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/wrapper.hpp
layout: document
redirect_from:
- /library/src/utils/wrapper.hpp
- /library/src/utils/wrapper.hpp.html
title: src/utils/wrapper.hpp
---
