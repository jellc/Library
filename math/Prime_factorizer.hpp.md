---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"math/Prime_factorizer.hpp\"\n\n\n\n// calculate the least\
    \ prime factor for positive integers less than N in compile time.\ntemplate <int\
    \ N>\nclass prime_factorizer\n{\n    constexpr static int loop_limit = 1 << 17;\n\
    \    int least[N], primes[N >> 3];\n    int n = 0;\n\n  public:\n    constexpr\
    \ prime_factorizer() : least{1}, primes{}, n{}\n    {\n        for(int i = 2;\
    \ i < N; )\n        {\n            for(int j = 0; j < loop_limit && i < N; ++j,\
    \ ++i)\n            {\n                if(!least[i]) primes[n++] = least[i] =\
    \ i;\n                int *p = primes;\n\n                while(*p && *p <= least[i]\
    \ && *p * i < N)\n                {\n                    for(int k = 0; k < loop_limit\
    \ && *p && *p <= least[i] && *p * i < N; ++k, ++p)\n                    {\n  \
    \                      least[*p * i] = *p;\n                    }\n          \
    \      }\n            }\n        }\n    }\n\n    constexpr bool prime(int x) const\
    \ { assert(0 <= x && x < N); return least[x] == x; }\n\n    constexpr int least_prime_factor(int\
    \ x) const { assert(0 < x && x < N); return least[x]; }\n}; // class prime_factorizer\n\
    \n\n"
  code: "#ifndef Prime_factorizer_hpp\n#define Prime_factorizer_hpp\n\n// calculate\
    \ the least prime factor for positive integers less than N in compile time.\n\
    template <int N>\nclass prime_factorizer\n{\n    constexpr static int loop_limit\
    \ = 1 << 17;\n    int least[N], primes[N >> 3];\n    int n = 0;\n\n  public:\n\
    \    constexpr prime_factorizer() : least{1}, primes{}, n{}\n    {\n        for(int\
    \ i = 2; i < N; )\n        {\n            for(int j = 0; j < loop_limit && i <\
    \ N; ++j, ++i)\n            {\n                if(!least[i]) primes[n++] = least[i]\
    \ = i;\n                int *p = primes;\n\n                while(*p && *p <=\
    \ least[i] && *p * i < N)\n                {\n                    for(int k =\
    \ 0; k < loop_limit && *p && *p <= least[i] && *p * i < N; ++k, ++p)\n       \
    \             {\n                        least[*p * i] = *p;\n               \
    \     }\n                }\n            }\n        }\n    }\n\n    constexpr bool\
    \ prime(int x) const { assert(0 <= x && x < N); return least[x] == x; }\n\n  \
    \  constexpr int least_prime_factor(int x) const { assert(0 < x && x < N); return\
    \ least[x]; }\n}; // class prime_factorizer\n\n#endif // Prime_factorizer_hpp"
  dependsOn: []
  isVerificationFile: false
  path: math/Prime_factorizer.hpp
  requiredBy: []
  timestamp: '2020-08-12 16:20:54+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/Prime_factorizer.hpp
layout: document
redirect_from:
- /library/math/Prime_factorizer.hpp
- /library/math/Prime_factorizer.hpp.html
title: math/Prime_factorizer.hpp
---
