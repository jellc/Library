---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Least Prime Factor
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
  code: "#pragma once\n\n/*\n * @file least_factor.hpp\n * @brief Least Prime Factor\n\
    \ */\n\n#include <cassert>\n#include <vector>\n\n#include \"utils/sfinae.hpp\"\
    \n\nnamespace workspace {\n\n/*\n * @class least_factor\n * @brief Calculate the\
    \ least prime factor for positive integers.\n * @tparam N Range of calculation,\
    \ exclusive\n */\ntemplate <unsigned N> class least_factor {\n  unsigned least[N],\
    \ prime[N >> 3], n;\n\n public:\n  constexpr least_factor() : least{1}, prime{},\
    \ n{} {\n    for (auto i = 2u; i < N; ++i) {\n      if (!least[i]) prime[n++]\
    \ = least[i] = i;\n      for (auto *p = prime; *p && *p <= least[i] && *p * i\
    \ < N; ++p) {\n        least[*p * i] = *p;\n      }\n    }\n  }\n\n  /*\n   *\
    \ @param x an integer with 0 < |x| < N\n   * @return Least prime factor of x\n\
    \   */\n  template <typename int_type>\n  constexpr\n      typename std::enable_if<is_integral_ext<int_type>::value,\
    \ int_type>::type\n      operator()(int_type x) const {\n    assert(x);\n    if\
    \ (x < 0) x = -x;\n    assert(x < N);\n    return least[x];\n  }\n\n  /*\n   *\
    \ @fn primes\n   * @return Sorted list of prime numbers less than N\n   */\n \
    \ const std::vector<unsigned> &primes() const {\n    static const std::vector<unsigned>\
    \ prime_vector(prime, prime + n);\n    return prime_vector;\n  }\n};\n\n}  //\
    \ namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/number_theory/least_factor.hpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/number_theory/least_factor.hpp
layout: document
redirect_from:
- /library/src/number_theory/least_factor.hpp
- /library/src/number_theory/least_factor.hpp.html
title: Least Prime Factor
---
