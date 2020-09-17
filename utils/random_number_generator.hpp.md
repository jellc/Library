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
  bundledCode: "#line 2 \"utils/random_number_generator.hpp\"\n#include <random>\n\
    template <typename num_t>\nclass random_number_generator\n{\n    template <bool\
    \ is_int, class = void>\n    struct unif_t\n    {\n        std::uniform_int_distribution<num_t>\
    \ unif;\n        unif_t(num_t lower, num_t upper) : unif(lower, upper) {}\n  \
    \      num_t operator()(std::mt19937 &engine) { return unif(engine); }\n    };\n\
    \    template <class void_t>\n    struct unif_t<false, void_t>\n    {\n      \
    \  std::uniform_real_distribution<num_t> unif;\n        unif_t(num_t lower, num_t\
    \ upper) : unif(lower, upper) {}\n        num_t operator()(std::mt19937 &engine)\
    \ { return unif(engine); }\n    };\n    unif_t<std::is_integral<num_t>::value>\
    \ unif;\n    std::mt19937 engine;\n  public:\n    // generate random number in\
    \ [lower, upper].\n    random_number_generator(num_t lower = std::numeric_limits<num_t>::min(),\
    \ num_t upper = std::numeric_limits<num_t>::max()) : unif(lower, upper), engine(std::random_device{}())\
    \ {}\n    num_t operator()() { return unif(engine); }\n}; // class random_number_generator\n"
  code: "#pragma once\n#include <random>\ntemplate <typename num_t>\nclass random_number_generator\n\
    {\n    template <bool is_int, class = void>\n    struct unif_t\n    {\n      \
    \  std::uniform_int_distribution<num_t> unif;\n        unif_t(num_t lower, num_t\
    \ upper) : unif(lower, upper) {}\n        num_t operator()(std::mt19937 &engine)\
    \ { return unif(engine); }\n    };\n    template <class void_t>\n    struct unif_t<false,\
    \ void_t>\n    {\n        std::uniform_real_distribution<num_t> unif;\n      \
    \  unif_t(num_t lower, num_t upper) : unif(lower, upper) {}\n        num_t operator()(std::mt19937\
    \ &engine) { return unif(engine); }\n    };\n    unif_t<std::is_integral<num_t>::value>\
    \ unif;\n    std::mt19937 engine;\n  public:\n    // generate random number in\
    \ [lower, upper].\n    random_number_generator(num_t lower = std::numeric_limits<num_t>::min(),\
    \ num_t upper = std::numeric_limits<num_t>::max()) : unif(lower, upper), engine(std::random_device{}())\
    \ {}\n    num_t operator()() { return unif(engine); }\n}; // class random_number_generator\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/random_number_generator.hpp
  requiredBy:
  - template.cpp
  - utils.hpp
  timestamp: '2020-08-14 02:27:35+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils/random_number_generator.hpp
layout: document
redirect_from:
- /library/utils/random_number_generator.hpp
- /library/utils/random_number_generator.hpp.html
title: utils/random_number_generator.hpp
---
