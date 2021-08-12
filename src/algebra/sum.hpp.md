---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: src/algebra/prod.hpp
    title: src/algebra/prod.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/algebra/sum.hpp\"\n\n#include <iterator>\n#include <vector>\n\
    \nnamespace workspace {\n\n// Sum of all elements in given range.\ntemplate <class\
    \ _Iterator,\n          class _Operator =\n              std::plus<typename std::iterator_traits<_Iterator>::value_type>>\n\
    typename std::iterator_traits<_Iterator>::value_type sum(\n    _Iterator __first,\
    \ _Iterator __last,\n    _Operator __op = _Operator{}) noexcept {\n  using value_type\
    \ = typename std::iterator_traits<_Iterator>::value_type;\n\n  if (__first ==\
    \ __last) return value_type{};\n\n  auto __b = new value_type[std::distance(__first,\
    \ __last)],\n       __e = std::copy(__first, __last, __b);\n\n  while (__b + 1\
    \ != __e)\n    for (auto __t = __e, __s = __e = __b; __s != __t; ++__s, ++__e)\n\
    \      if (__t - __s == 1)\n        *__e = std::move(*__s);\n      else\n    \
    \    *__e = __op(*__s, *(__s + 1)), ++__s;\n\n  value_type __tmp = std::move(*__b);\n\
    \  delete[] __b;\n  return __tmp;\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n#include <iterator>\n#include <vector>\n\nnamespace workspace\
    \ {\n\n// Sum of all elements in given range.\ntemplate <class _Iterator,\n  \
    \        class _Operator =\n              std::plus<typename std::iterator_traits<_Iterator>::value_type>>\n\
    typename std::iterator_traits<_Iterator>::value_type sum(\n    _Iterator __first,\
    \ _Iterator __last,\n    _Operator __op = _Operator{}) noexcept {\n  using value_type\
    \ = typename std::iterator_traits<_Iterator>::value_type;\n\n  if (__first ==\
    \ __last) return value_type{};\n\n  auto __b = new value_type[std::distance(__first,\
    \ __last)],\n       __e = std::copy(__first, __last, __b);\n\n  while (__b + 1\
    \ != __e)\n    for (auto __t = __e, __s = __e = __b; __s != __t; ++__s, ++__e)\n\
    \      if (__t - __s == 1)\n        *__e = std::move(*__s);\n      else\n    \
    \    *__e = __op(*__s, *(__s + 1)), ++__s;\n\n  value_type __tmp = std::move(*__b);\n\
    \  delete[] __b;\n  return __tmp;\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/algebra/sum.hpp
  requiredBy:
  - src/algebra/prod.hpp
  timestamp: '2021-08-12 13:53:26+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/algebra/sum.hpp
layout: document
redirect_from:
- /library/src/algebra/sum.hpp
- /library/src/algebra/sum.hpp.html
title: src/algebra/sum.hpp
---
