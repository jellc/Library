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
    \ntemplate <typename _Arithmetic>\nusing uniform_distribution = typename std::conditional<\n\
    \    std::is_integral<_Arithmetic>::value,\n    std::uniform_int_distribution<_Arithmetic>,\n\
    \    std::uniform_real_distribution<_Arithmetic>>::type;\n\ntemplate <typename\
    \ _Arithmetic, class _Engine = std::mt19937>\nclass random_number_generator :\
    \ uniform_distribution<_Arithmetic> {\n  using base = uniform_distribution<_Arithmetic>;\n\
    \n  _Engine __engine;\n\n public:\n  random_number_generator(_Arithmetic __min,\
    \ _Arithmetic __max)\n      : base(__min, __max), __engine(std::random_device{}())\
    \ {}\n\n  random_number_generator(_Arithmetic __max = 1)\n      : random_number_generator(0,\
    \ __max) {}\n\n  random_number_generator(typename base::param_type const& __param)\n\
    \      : base(__param), __engine(std::random_device{}()) {}\n\n  decltype(auto)\
    \ operator()() noexcept { return base::operator()(__engine); }\n};\n\n}  // namespace\
    \ workspace\n"
  code: "#pragma once\n\n/**\n * @file rng.hpp\n * @brief Random Number Generator\n\
    \ */\n\n#include <random>\n\nnamespace workspace {\n\ntemplate <typename _Arithmetic>\n\
    using uniform_distribution = typename std::conditional<\n    std::is_integral<_Arithmetic>::value,\n\
    \    std::uniform_int_distribution<_Arithmetic>,\n    std::uniform_real_distribution<_Arithmetic>>::type;\n\
    \ntemplate <typename _Arithmetic, class _Engine = std::mt19937>\nclass random_number_generator\
    \ : uniform_distribution<_Arithmetic> {\n  using base = uniform_distribution<_Arithmetic>;\n\
    \n  _Engine __engine;\n\n public:\n  random_number_generator(_Arithmetic __min,\
    \ _Arithmetic __max)\n      : base(__min, __max), __engine(std::random_device{}())\
    \ {}\n\n  random_number_generator(_Arithmetic __max = 1)\n      : random_number_generator(0,\
    \ __max) {}\n\n  random_number_generator(typename base::param_type const& __param)\n\
    \      : base(__param), __engine(std::random_device{}()) {}\n\n  decltype(auto)\
    \ operator()() noexcept { return base::operator()(__engine); }\n};\n\n}  // namespace\
    \ workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/rand/rng.hpp
  requiredBy:
  - src/string/rolling_hash.hpp
  timestamp: '2021-02-24 23:48:13+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/zalgorithm_2.test.cpp
  - test/aizu-online-judge/ALDS1_14_C.test.cpp
documentation_of: src/utils/rand/rng.hpp
layout: document
redirect_from:
- /library/src/utils/rand/rng.hpp
- /library/src/utils/rand/rng.hpp.html
title: Random Number Generator
---
