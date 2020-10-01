---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':question:'
    path: string/rolling_hash.hpp
    title: string/rolling_hash.hpp
  - icon: ':warning:'
    path: template.cpp
    title: template.cpp
  - icon: ':warning:'
    path: utils.hpp
    title: utils.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/pattern_search.test.cpp
    title: test/aizu-online-judge/pattern_search.test.cpp
  - icon: ':x:'
    path: test/library-checker/zalgorithm_2.test.cpp
    title: test/library-checker/zalgorithm_2.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utils/random_number_generator.hpp\"\n#include <random>\n\
    template <typename num_type> class random_number_generator {\n  typename std::conditional<std::is_integral<num_type>::value,\n\
    \                            std::uniform_int_distribution<num_type>,\n      \
    \                      std::uniform_real_distribution<num_type>>::type\n     \
    \ unif;\n\n  std::mt19937 engine;\n\n public:\n  random_number_generator(num_type\
    \ min = std::numeric_limits<num_type>::min(),\n                          num_type\
    \ max = std::numeric_limits<num_type>::max())\n      : unif(min, max), engine(std::random_device{}())\
    \ {}\n\n  num_type min() const { return unif.min(); }\n\n  num_type max() const\
    \ { return unif.max(); }\n\n  // generate a random number in [min(), max()].\n\
    \  num_type operator()() { return unif(engine); }\n};\n"
  code: "#pragma once\n#include <random>\ntemplate <typename num_type> class random_number_generator\
    \ {\n  typename std::conditional<std::is_integral<num_type>::value,\n        \
    \                    std::uniform_int_distribution<num_type>,\n              \
    \              std::uniform_real_distribution<num_type>>::type\n      unif;\n\n\
    \  std::mt19937 engine;\n\n public:\n  random_number_generator(num_type min =\
    \ std::numeric_limits<num_type>::min(),\n                          num_type max\
    \ = std::numeric_limits<num_type>::max())\n      : unif(min, max), engine(std::random_device{}())\
    \ {}\n\n  num_type min() const { return unif.min(); }\n\n  num_type max() const\
    \ { return unif.max(); }\n\n  // generate a random number in [min(), max()].\n\
    \  num_type operator()() { return unif(engine); }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/random_number_generator.hpp
  requiredBy:
  - template.cpp
  - utils.hpp
  - string/rolling_hash.hpp
  timestamp: '2020-09-22 15:16:13+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/library-checker/zalgorithm_2.test.cpp
  - test/aizu-online-judge/pattern_search.test.cpp
documentation_of: utils/random_number_generator.hpp
layout: document
redirect_from:
- /library/utils/random_number_generator.hpp
- /library/utils/random_number_generator.hpp.html
title: utils/random_number_generator.hpp
---
