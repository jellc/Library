---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/utils/random_number_generator.hpp\"\n#include <random>\n\
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
  path: src/utils/random_number_generator.hpp
  requiredBy: []
  timestamp: '2020-11-16 14:21:51+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/random_number_generator.hpp
layout: document
redirect_from:
- /library/src/utils/random_number_generator.hpp
- /library/src/utils/random_number_generator.hpp.html
title: src/utils/random_number_generator.hpp
---
