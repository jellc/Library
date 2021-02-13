---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: src/string/rolling_hash.hpp
    title: Rolling Hash
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/ALDS1_14_C.test.cpp
    title: test/aizu-online-judge/ALDS1_14_C.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/zalgorithm_2.test.cpp
    title: test/library-checker/zalgorithm_2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Random Number Generator
    links: []
  bundledCode: "#line 2 \"src/utils/rand/rng.hpp\"\n\n/**\n * @file rng.hpp\n * @brief\
    \ Random Number Generator\n */\n\n#include <random>\n\nnamespace workspace {\n\
    \ntemplate <typename Arithmetic>\nusing uniform_distribution =\n    typename std::conditional<std::is_integral<Arithmetic>::value,\n\
    \                              std::uniform_int_distribution<Arithmetic>,\n  \
    \                            std::uniform_real_distribution<Arithmetic>>::type;\n\
    \ntemplate <typename Arithmetic>\nclass random_number_generator : uniform_distribution<Arithmetic>\
    \ {\n  using base = uniform_distribution<Arithmetic>;\n\n  std::mt19937 engine;\n\
    \n public:\n  template <class... Args>\n  random_number_generator(Args&&... args)\n\
    \      : base(args...), engine(std::random_device{}()) {}\n\n  auto operator()()\
    \ { return base::operator()(engine); }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file rng.hpp\n * @brief Random Number Generator\n\
    \ */\n\n#include <random>\n\nnamespace workspace {\n\ntemplate <typename Arithmetic>\n\
    using uniform_distribution =\n    typename std::conditional<std::is_integral<Arithmetic>::value,\n\
    \                              std::uniform_int_distribution<Arithmetic>,\n  \
    \                            std::uniform_real_distribution<Arithmetic>>::type;\n\
    \ntemplate <typename Arithmetic>\nclass random_number_generator : uniform_distribution<Arithmetic>\
    \ {\n  using base = uniform_distribution<Arithmetic>;\n\n  std::mt19937 engine;\n\
    \n public:\n  template <class... Args>\n  random_number_generator(Args&&... args)\n\
    \      : base(args...), engine(std::random_device{}()) {}\n\n  auto operator()()\
    \ { return base::operator()(engine); }\n};\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/rand/rng.hpp
  requiredBy:
  - src/string/rolling_hash.hpp
  timestamp: '2020-12-12 22:39:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aizu-online-judge/ALDS1_14_C.test.cpp
  - test/library-checker/zalgorithm_2.test.cpp
documentation_of: src/utils/rand/rng.hpp
layout: document
redirect_from:
- /library/src/utils/rand/rng.hpp
- /library/src/utils/rand/rng.hpp.html
title: Random Number Generator
---
