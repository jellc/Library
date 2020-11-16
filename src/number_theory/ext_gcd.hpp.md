---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Extended Euclidean Algorithm
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 193, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: utils/sfinae.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n\n/*\n * @file ext_gcd\n * @brief Extended Euclidean Algorithm\n\
    \ */\n\n#include <tuple>\n\n#include \"utils/sfinae.hpp\"\n\nnamespace workspace\
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
  dependsOn: []
  isVerificationFile: false
  path: src/number_theory/ext_gcd.hpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/number_theory/ext_gcd.hpp
layout: document
redirect_from:
- /library/src/number_theory/ext_gcd.hpp
- /library/src/number_theory/ext_gcd.hpp.html
title: Extended Euclidean Algorithm
---
