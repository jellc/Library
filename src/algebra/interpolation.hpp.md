---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Polynomial Interpolation
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
  code: "#pragma once\n\n/**\n * @file interpolation.hpp\n * @brief Polynomial Interpolation\n\
    \ */\n\n#include <vector>\n\n#include \"polynomial.hpp\"\n#include \"system\\\
    operation.hpp\"\n\nnamespace workspace {\n\n/**\n * @brief Lagrange interpolation\
    \ on the points 0, 1, 2, ...\n * @param __x Point to evaluate at.\n * @param __first\n\
    \ * @param __last\n */\ntemplate <class _Tp, class _InputIter,\n          typename\
    \ = std::_RequireInputIter<_InputIter>,\n          typename = require_arithmetic<\n\
    \              typename std::iterator_traits<_InputIter>::value_type>>\nauto interpolate(_Tp\
    \ __x, _InputIter __first, _InputIter __last) noexcept {\n  using value_type =\
    \ typename std::iterator_traits<_InputIter>::value_type;\n\n  std::vector<value_type>\
    \ __f(__first, __last);\n  decltype(__f.size()) __k = 0;\n\n  value_type __d =\
    \ 1;\n  while (__k != __f.size()) __k += 1, __d *= value_type{__k};\n\n  __d =\
    \ value_type{1} / __d;\n  value_type __c = __k & 1 ? -__d : __d;\n  auto __i =\
    \ __f.begin();\n\n  while (__i != __f.end()) {\n    __c *= -value_type{__k}, __k\
    \ -= 1;\n    *__i++ *= __c;\n    __c *= __x, __x -= 1;\n  }\n\n  __c = __d, __k\
    \ = __f.size();\n  value_type __y = 0;\n\n  while (__i != __f.begin()) {\n   \
    \ __c *= value_type{__k}, __k -= 1;\n    __y += *--__i * __c;\n    __x += 1, __c\
    \ *= __x;\n  }\n\n  return __y;\n}\n\n/**\n * @brief Polynomial interpolation\
    \ in O(n log(n)^2) time.\n * @param __first\n * @param __last\n */\ntemplate <class\
    \ _InputIter, typename = std::_RequireInputIter<_InputIter>>\nauto interpolate(_InputIter\
    \ __first, _InputIter __last) noexcept {\n  size_t __n = std::distance(__first,\
    \ __last);\n\n  auto [__1, __2] = typename std::iterator_traits<_InputIter>::value_type{};\n\
    \n  using poly = polynomial<decltype(__1)>;\n\n  if (!__n) return poly{};\n\n\
    \  struct node {\n    poly __all, __lack;\n  };\n\n  auto __tree = new node[__n\
    \ << 1];\n  auto __iter = __first;\n\n  for (size_t __i = 0; __i != __n; ++__i)\
    \ {\n    auto&& [__a, __b] = *__iter++;\n    __tree[__i + __n].__all = {-__a,\
    \ 1}, __tree[__i + __n].__lack = {1};\n  }\n\n  for (size_t __i = __n; --__i;)\n\
    \    __tree[__i].__all = __tree[__i << 1].__all * __tree[__i << 1 | 1].__all,\n\
    \    __tree[__i].__lack =\n        __tree[__i << 1].__all * std::move(__tree[__i\
    \ << 1 | 1].__lack) +\n        __tree[__i << 1 | 1].__all * std::move(__tree[__i\
    \ << 1].__lack);\n\n  for (size_t __i = 2; __i != __n << 1; __i += 2)\n    __tree[__i].__lack\
    \ = __tree[__i >> 1].__lack % __tree[__i].__all,\n    __tree[__i | 1].__lack =\n\
    \        std::move(__tree[__i >> 1].__lack %= __tree[__i | 1].__all);\n\n  for\
    \ (size_t __i = 0; __i != __n; ++__i) {\n    auto&& [__a, __b] = *__first++;\n\
    \    __tree[__i + __n].__lack[0] =\n        std::move(__b) / std::move(__tree[__i\
    \ + __n].__lack[0]);\n  }\n\n  for (size_t __i = __n; --__i;)\n    __tree[__i].__lack\
    \ = std::move(__tree[__i << 1].__all) *\n                             std::move(__tree[__i\
    \ << 1 | 1].__lack) +\n                         std::move(__tree[__i << 1 | 1].__all)\
    \ *\n                             std::move(__tree[__i << 1].__lack);\n\n  auto\
    \ __result = std::move(__tree[1].__lack);\n\n  delete[] __tree;\n\n  return __result;\n\
    }\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/algebra/interpolation.hpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/algebra/interpolation.hpp
layout: document
redirect_from:
- /library/src/algebra/interpolation.hpp
- /library/src/algebra/interpolation.hpp.html
title: Polynomial Interpolation
---
