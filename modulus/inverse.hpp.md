---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: modulus/modint.hpp
    title: Modular arithmetic
  - icon: ':heavy_check_mark:'
    path: utils/sfinae.hpp
    title: utils/sfinae.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: combinatorics/binomial.hpp
    title: combinatorics/binomial.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/balls_and_boxes_4.test.cpp
    title: test/aizu-online-judge/balls_and_boxes_4.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 310, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ modulus/modint.hpp: line 6: #pragma once found in a non-first line\n"
  code: "#pragma once\n#include <vector>\n\n#include \"modint.hpp\"\ntemplate <class,\
    \ class = int> struct inverse;\n// mod must be prime.\ntemplate <class Modint>\n\
    struct inverse<Modint, decltype((void *)Modint::mod, 0)> {\n  using value_type\
    \ = Modint;\n  constexpr value_type operator()(int n) const {\n    constexpr int_fast64_t\
    \ mod = value_type::mod;\n    assert(n %= mod);\n    if (n < 0) n += mod;\n  \
    \  if (inv.empty()) inv = {1, mod != 1};\n    for (int m(inv.size()); m <= n;\
    \ ++m)\n      inv.emplace_back(mod / m * -inv[mod % m]);\n    return inv[n];\n\
    \  }\n\n private:\n  static std::vector<value_type> inv;\n};\ntemplate <class\
    \ Modint>\nstd::vector<Modint> inverse<Modint, decltype((void *)Modint::mod, 0)>::inv;\n"
  dependsOn:
  - modulus/modint.hpp
  - utils/sfinae.hpp
  isVerificationFile: false
  path: modulus/inverse.hpp
  requiredBy:
  - combinatorics/binomial.hpp
  timestamp: '2020-11-04 18:12:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aizu-online-judge/balls_and_boxes_4.test.cpp
documentation_of: modulus/inverse.hpp
layout: document
redirect_from:
- /library/modulus/inverse.hpp
- /library/modulus/inverse.hpp.html
title: modulus/inverse.hpp
---
