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
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 2 \"utils/make_vector.hpp\"\n#include <vector>\nnamespace workspace\
    \ {\ntemplate <typename T, size_t N>\nconstexpr auto make_vector(size_t* sizes,\
    \ T const& init = T()) {\n  if constexpr (N)\n    return std::vector(*sizes, make_vector<T,\
    \ N - 1>(std::next(sizes), init));\n  else\n    return init;\n}\ntemplate <typename\
    \ T, size_t N>\nconstexpr auto make_vector(const size_t (&sizes)[N], T const&\
    \ init = T()) {\n  return make_vector<T, N>((size_t*)sizes, init);\n}\n}  // namespace\
    \ workspace\n"
  code: "#pragma once\n#include <vector>\nnamespace workspace {\ntemplate <typename\
    \ T, size_t N>\nconstexpr auto make_vector(size_t* sizes, T const& init = T())\
    \ {\n  if constexpr (N)\n    return std::vector(*sizes, make_vector<T, N - 1>(std::next(sizes),\
    \ init));\n  else\n    return init;\n}\ntemplate <typename T, size_t N>\nconstexpr\
    \ auto make_vector(const size_t (&sizes)[N], T const& init = T()) {\n  return\
    \ make_vector<T, N>((size_t*)sizes, init);\n}\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/make_vector.hpp
  requiredBy:
  - template.cpp
  - utils.hpp
  timestamp: '2020-09-11 03:33:31+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils/make_vector.hpp
layout: document
redirect_from:
- /library/utils/make_vector.hpp
- /library/utils/make_vector.hpp.html
title: utils/make_vector.hpp
---
