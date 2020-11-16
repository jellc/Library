---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/library-checker/subset_convolution.test.cpp
    title: test/library-checker/subset_convolution.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"algebra/convolution/subset.hpp\"\n#include <cassert>\n#include\
    \ <vector>\n\ntemplate <class Ring>\nstd::vector<Ring> subset_convolute(const\
    \ std::vector<Ring> &f, const std::vector<Ring> &g)\n{\n    assert(!f.empty());\
    \ assert(!g.empty());\n    const size_t n = __builtin_ctz(std::min(f.size(), g.size()));\n\
    \    std::vector ff(n + 1, std::vector<Ring>(1 << n)), gg(ff);\n    ff[0] = f,\
    \ gg[0] = g;\n    for(size_t k = 0; k != n; ++k)\n    {\n        for(size_t i\
    \ = k + 1; ~i; --i)\n        {\n            for(size_t s = 0; s != 1u << n; ++s)\n\
    \            {\n                if(s >> k & 1)\n                {\n          \
    \          if(i)\n                    {\n                        ff[i][s] = ff[i\
    \ - 1][s];\n                        gg[i][s] = gg[i - 1][s];\n               \
    \     }\n                    else\n                    {\n                   \
    \     ff[i][s] = gg[i][s] = Ring{};\n                    }\n                 \
    \   ff[i][s] += ff[i][s ^ 1 << k];\n                    gg[i][s] += gg[i][s ^\
    \ 1 << k];\n                }\n            }\n        }\n    }\n    for(size_t\
    \ i = n; ~i; --i)\n    {\n        for(size_t s = 0; s != 1u << n; ++s)\n     \
    \   {\n            ff[i][s] *= gg[0][s];\n            for(size_t j = i; j; --j)\n\
    \            {\n                ff[i][s] += ff[i - j][s] * gg[j][s];\n       \
    \     }\n        }\n    }\n    for(size_t k = n - 1; ~k; --k)\n    {\n       \
    \ for(size_t s = 0; s != 1u << n; ++s)\n        {\n            if(~s >> k & 1)\n\
    \            {\n                for(size_t i = n; ~i; --i)\n                {\n\
    \                    ff[i][s ^ 1 << k] -= ff[i][s];\n                    if(i)\
    \ ff[i][s] = ff[i - 1][s];\n                }\n            }\n        }\n    }\n\
    \    return ff[n];\n}\n"
  code: "#include <cassert>\n#include <vector>\n\ntemplate <class Ring>\nstd::vector<Ring>\
    \ subset_convolute(const std::vector<Ring> &f, const std::vector<Ring> &g)\n{\n\
    \    assert(!f.empty()); assert(!g.empty());\n    const size_t n = __builtin_ctz(std::min(f.size(),\
    \ g.size()));\n    std::vector ff(n + 1, std::vector<Ring>(1 << n)), gg(ff);\n\
    \    ff[0] = f, gg[0] = g;\n    for(size_t k = 0; k != n; ++k)\n    {\n      \
    \  for(size_t i = k + 1; ~i; --i)\n        {\n            for(size_t s = 0; s\
    \ != 1u << n; ++s)\n            {\n                if(s >> k & 1)\n          \
    \      {\n                    if(i)\n                    {\n                 \
    \       ff[i][s] = ff[i - 1][s];\n                        gg[i][s] = gg[i - 1][s];\n\
    \                    }\n                    else\n                    {\n    \
    \                    ff[i][s] = gg[i][s] = Ring{};\n                    }\n  \
    \                  ff[i][s] += ff[i][s ^ 1 << k];\n                    gg[i][s]\
    \ += gg[i][s ^ 1 << k];\n                }\n            }\n        }\n    }\n\
    \    for(size_t i = n; ~i; --i)\n    {\n        for(size_t s = 0; s != 1u << n;\
    \ ++s)\n        {\n            ff[i][s] *= gg[0][s];\n            for(size_t j\
    \ = i; j; --j)\n            {\n                ff[i][s] += ff[i - j][s] * gg[j][s];\n\
    \            }\n        }\n    }\n    for(size_t k = n - 1; ~k; --k)\n    {\n\
    \        for(size_t s = 0; s != 1u << n; ++s)\n        {\n            if(~s >>\
    \ k & 1)\n            {\n                for(size_t i = n; ~i; --i)\n        \
    \        {\n                    ff[i][s ^ 1 << k] -= ff[i][s];\n             \
    \       if(i) ff[i][s] = ff[i - 1][s];\n                }\n            }\n   \
    \     }\n    }\n    return ff[n];\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: algebra/convolution/subset.hpp
  requiredBy: []
  timestamp: '2020-08-06 06:09:12+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/library-checker/subset_convolution.test.cpp
documentation_of: algebra/convolution/subset.hpp
layout: document
redirect_from:
- /library/algebra/convolution/subset.hpp
- /library/algebra/convolution/subset.hpp.html
title: algebra/convolution/subset.hpp
---
