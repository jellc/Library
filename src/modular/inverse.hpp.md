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
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: utils/sfinae.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include <vector>\n\n#include \"modint.hpp\"\ntemplate <class,\
    \ class = int> struct inverse;\n// mod must be prime.\ntemplate <class Modint>\n\
    struct inverse<Modint, decltype((void *)Modint::mod, 0)> {\n  using value_type\
    \ = Modint;\n  constexpr value_type operator()(int n) const {\n    constexpr int_fast64_t\
    \ mod = value_type::mod;\n    assert(n %= mod);\n    if (n < 0) n += mod;\n  \
    \  if (inv.empty()) inv = {1, mod != 1};\n    for (int m(inv.size()); m <= n;\
    \ ++m)\n      inv.emplace_back(mod / m * -inv[mod % m]);\n    return inv[n];\n\
    \  }\n\n private:\n  static std::vector<value_type> inv;\n};\ntemplate <class\
    \ Modint>\nstd::vector<Modint> inverse<Modint, decltype((void *)Modint::mod, 0)>::inv;\n"
  dependsOn: []
  isVerificationFile: false
  path: src/modular/inverse.hpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/modular/inverse.hpp
layout: document
redirect_from:
- /library/src/modular/inverse.hpp
- /library/src/modular/inverse.hpp.html
title: src/modular/inverse.hpp
---
