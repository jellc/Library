---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 193, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: modulus/inverse.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include \"factorial.hpp\"\n#include \"modulus/inverse.hpp\"\
    \n#include \"modulus/modint.hpp\"\ntemplate <class, class = int> struct binomial;\n\
    template <class Modint>\nstruct binomial<Modint, decltype((void *)Modint::mod,\
    \ 0)> {\n  using value_type = Modint;\n  struct mulinv_Op {\n    value_type operator()(const\
    \ value_type &f, const size_t &n) const {\n      return f * inv(n);\n    }\n \
    \ };\n  static inverse<value_type> inv;\n  static factorial<value_type, mulinv_Op>\
    \ fact_inv;\n  static factorial<value_type> fact;\n  value_type operator()(const\
    \ int &n, const int &k) {\n    return fact_inv(k) * fact_inv(n - k) * fact(n);\n\
    \  }\n};\ntemplate <class Modint>\ninverse<Modint> binomial<Modint, decltype((void\
    \ *)Modint::mod, 0)>::inv;\ntemplate <class Modint>\nfactorial<Modint,\n     \
    \     class binomial<Modint, decltype((void *)Modint::mod, 0)>::mulinv_Op>\n \
    \   binomial<Modint, decltype((void *)Modint::mod, 0)>::fact_inv;\ntemplate <class\
    \ Modint>\nfactorial<Modint> binomial<Modint, decltype((void *)Modint::mod, 0)>::fact;\n"
  dependsOn: []
  isVerificationFile: false
  path: combinatorics/binomial.hpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: combinatorics/binomial.hpp
layout: document
redirect_from:
- /library/combinatorics/binomial.hpp
- /library/combinatorics/binomial.hpp.html
title: combinatorics/binomial.hpp
---
