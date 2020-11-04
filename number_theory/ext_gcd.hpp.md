---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utils/sfinae.hpp
    title: utils/sfinae.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/extended_euclid_algorithm.test.cpp
    title: test/aizu-online-judge/extended_euclid_algorithm.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Extended Euclidean algorithm
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 310, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ number_theory/ext_gcd.hpp: line 6: #pragma once found in a non-first line\n"
  code: "/*\n * @file ext_gcd\n * @brief Extended Euclidean algorithm\n */\n\n#pragma\
    \ once\n#include <tuple>\n\n#include \"utils/sfinae.hpp\"\n\nnamespace workspace\
    \ {\n\n/*\n * @fn ext_gcd\n * @param a an integer\n * @param b an integer\n *\
    \ @return a pair of integers (x, y) s.t. ax + by = gcd(a, b)\n * @note return\
    \ (0, 0) if (a, b) = (0, 0)\n */\ntemplate <typename T1, typename T2>\nconstexpr\
    \ typename std::enable_if<\n    (is_integral_ext<T1>::value && is_integral_ext<T2>::value),\n\
    \    std::pair<typename std::common_type<T1, T2>::type,\n              typename\
    \ std::common_type<T1, T2>::type>>::type\next_gcd(T1 a, T2 b) {\n  typename std::common_type<T1,\
    \ T2>::type p{1}, q{}, r{}, s{1}, t{};\n  if (a < 0) {\n    std::tie(p, q) = ext_gcd(-a,\
    \ b);\n    p = -p;\n  } else if (b < 0) {\n    std::tie(p, q) = ext_gcd(a, -b);\n\
    \    q = -q;\n  } else {\n    while (b) {\n      r ^= p ^= r ^= p -= (t = a /\
    \ b) * r;\n      s ^= q ^= s ^= q -= t * s;\n      b ^= a ^= b ^= a %= b;\n  \
    \  }\n  }\n  return {p, q};\n}\n\n}  // namespace workspace\n"
  dependsOn:
  - utils/sfinae.hpp
  isVerificationFile: false
  path: number_theory/ext_gcd.hpp
  requiredBy: []
  timestamp: '2020-11-04 17:56:57+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aizu-online-judge/extended_euclid_algorithm.test.cpp
documentation_of: number_theory/ext_gcd.hpp
layout: document
redirect_from:
- /library/number_theory/ext_gcd.hpp
- /library/number_theory/ext_gcd.hpp.html
title: Extended Euclidean algorithm
---
