---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Berlekamp-Massey Algorithm
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: src\\utils\\sfinae.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n\n/**\n * @file berlekamp_massey.hpp\n * @brief Berlekamp-Massey\
    \ Algorithm\n */\n\n#include <numeric>\n\n#include \"polynomial.hpp\"\n\nnamespace\
    \ workspace {\n\ntemplate <class _Iterator>\nauto Berlekamp_Massey(_Iterator __first,\
    \ _Iterator __last) noexcept {\n  using value_type = typename std::iterator_traits<_Iterator>::value_type;\n\
    \n  std::vector<value_type> __a(__first, __last);\n  polynomial<value_type> __c{1},\
    \ __b{1};\n\n  typename decltype(__c)::size_type __z = 1;\n\n  for (auto __s =\
    \ __a.begin(); __s != __a.end(); ++__s) {\n    ++__z;\n\n    auto __d = std::inner_product(__c.begin(),\
    \ __c.end(), __s + 1 - __c.size(),\n                                  value_type(0));\n\
    \    if (__d == value_type(0)) continue;\n\n    if (__c.size() < __z) {\n    \
    \  auto __tmp = __c;\n      __c <<= __z - __c.size();\n      __c -= __b *= __d;\n\
    \      __b = std::move(__tmp);\n      __b /= __d;\n      __z = __b.size();\n \
    \   } else {\n      for (auto __i = __c.end() - __z, __j = __b.begin(); __j !=\
    \ __b.end();\n           ++__i, ++__j)\n        *__i -= *__j * __d;\n    }\n \
    \ }\n\n  return __c;\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/algebra/berlekamp_massey.hpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/algebra/berlekamp_massey.hpp
layout: document
redirect_from:
- /library/src/algebra/berlekamp_massey.hpp
- /library/src/algebra/berlekamp_massey.hpp.html
title: Berlekamp-Massey Algorithm
---
