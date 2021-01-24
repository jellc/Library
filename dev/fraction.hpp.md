---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 193, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: utils/sfinae.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include \"utils/sfinae.hpp\"\ntemplate <class T> struct fraction\
    \ {\n  static_assert(is_integral_ext_v<T>);\n  T num, den;\n  constexpr fraction(const\
    \ T &num = 0, const T &den = 1) : num(num), den(den) {}\n  constexpr fraction\
    \ operator-() const { return {-num, den}; }\n  constexpr fraction operator-(const\
    \ fraction &rhs) const {\n    return {num * rhs.den - rhs.num * den, den * rhs.den};\n\
    \  }\n  constexpr bool operator<(const fraction &rhs) const {\n    return operator-(rhs).num\
    \ < 0;\n  }\n\n private:\n  constexpr void normalize();\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: dev/fraction.hpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: dev/fraction.hpp
layout: document
redirect_from:
- /library/dev/fraction.hpp
- /library/dev/fraction.hpp.html
title: dev/fraction.hpp
---
