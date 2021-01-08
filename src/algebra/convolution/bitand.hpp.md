---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Bitwise And Convolution
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 193, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: bitor.hh: line\
    \ -1: no such header\n"
  code: "#pragma once\n\n/**\n * @file bitand.hh\n * @brief Bitwise And Convolution\n\
    \ * @date 2021-01-08\n */\n\n#include <algorithm>\n\n#include \"bitor.hh\"\n\n\
    namespace workspace {\n\ntemplate <class A> A bitand_conv(A f, A g) {\n  std::reverse(std::begin(f),\
    \ std::end(f));\n  std::reverse(std::begin(g), std::end(g));\n  f = bitor_conv(f,\
    \ g);\n  std::reverse(std::begin(f), std::end(f));\n  return f;\n}\n\n}  // namespace\
    \ workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/algebra/convolution/bitand.hpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/algebra/convolution/bitand.hpp
layout: document
redirect_from:
- /library/src/algebra/convolution/bitand.hpp
- /library/src/algebra/convolution/bitand.hpp.html
title: Bitwise And Convolution
---
