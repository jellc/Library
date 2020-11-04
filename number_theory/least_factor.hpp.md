---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utils/sfinae.hpp
    title: utils/sfinae.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: calculate the least prime factor for positive integers.
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 310, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ number_theory/least_factor.hpp: line 6: #pragma once found in a non-first line\n"
  code: "/*\n * @file least_factor.hpp\n * @breif Least prime factor\n */\n\n#pragma\
    \ once\n#include <cassert>\n#include <vector>\n\n#include \"utils/sfinae.hpp\"\
    \n\nnamespace workspace {\n\n/*\n * @class least_factor\n * @brief calculate the\
    \ least prime factor for positive integers.\n * @tparam N range of calculation,\
    \ exclusive\n */\ntemplate <unsigned N> class least_factor {\n  unsigned least[N],\
    \ prime[N >> 3], n;\n\n public:\n  constexpr least_factor() : least{1}, prime{},\
    \ n{} {\n    for (auto i = 2u; i < N; ++i) {\n      if (!least[i]) prime[n++]\
    \ = least[i] = i;\n      for (auto *p = prime; *p && *p <= least[i] && *p * i\
    \ < N; ++p) {\n        least[*p * i] = *p;\n      }\n    }\n  }\n\n  /*\n   *\
    \ @param x an integer with 0 < |x| < N\n   * @return least prime factor of x\n\
    \   */\n  template <typename int_type>\n  constexpr\n      typename std::enable_if<is_integral_ext<int_type>::value,\
    \ int_type>::type\n      operator()(int_type x) const {\n    assert(x);\n    if\
    \ (x < 0) x = -x;\n    assert(x < N);\n    return least[x];\n  }\n\n  /*\n   *\
    \ @fn primes\n   * @return sorted list of prime numbers less than N\n   */\n \
    \ const std::vector<unsigned> &primes() const {\n    static const std::vector<unsigned>\
    \ prime_vector(prime, prime + n);\n    return prime_vector;\n  }\n};\n\n}  //\
    \ namespace workspace\n"
  dependsOn:
  - utils/sfinae.hpp
  isVerificationFile: false
  path: number_theory/least_factor.hpp
  requiredBy: []
  timestamp: '2020-11-04 17:56:57+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: number_theory/least_factor.hpp
layout: document
redirect_from:
- /library/number_theory/least_factor.hpp
- /library/number_theory/least_factor.hpp.html
title: calculate the least prime factor for positive integers.
---
