---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: src/algebra/sum.hpp
    title: src/algebra/sum.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/algebra/prod.hpp\"\n\n#line 2 \"src/algebra/sum.hpp\"\
    \n\n#include <iterator>\n#include <vector>\n\nnamespace workspace {\n\n// Sum\
    \ of all elements in given range.\ntemplate <class _Iterator,\n          class\
    \ _Operator =\n              std::plus<typename std::iterator_traits<_Iterator>::value_type>>\n\
    typename std::iterator_traits<_Iterator>::value_type sum(\n    _Iterator __first,\
    \ _Iterator __last,\n    _Operator __op = _Operator{}) noexcept {\n  using value_type\
    \ = typename std::iterator_traits<_Iterator>::value_type;\n\n  if (__first ==\
    \ __last) return value_type{};\n\n  std::vector<value_type> __v(__first, __last);\n\
    \n  for (auto __b = __v.begin(), __e = __v.end(); __e - __b != 1;)\n    for (std::move_iterator<typename\
    \ decltype(__v)::iterator> __t(__e),\n         __s(__e = __v.begin());\n     \
    \    __s != __t; ++__s, ++__e)\n      if (__t - __s == 1)\n        *__e = *__s;\n\
    \      else\n        *__e = __op(*__s, *(__s + 1)), ++__s;\n\n  return __v.front();\n\
    }\n\n}  // namespace workspace\n#line 4 \"src/algebra/prod.hpp\"\n\nnamespace\
    \ workspace {\n\n// Product of all elements in given range.\ntemplate <class _Iterator,\n\
    \          class _Operator = std::multiplies<\n              typename std::iterator_traits<_Iterator>::value_type>>\n\
    typename std::iterator_traits<_Iterator>::value_type prod(\n    _Iterator __first,\
    \ _Iterator __last,\n    _Operator __op = _Operator{}) noexcept {\n  return sum(__first,\
    \ __last, __op);\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n#include \"sum.hpp\"\n\nnamespace workspace {\n\n// Product\
    \ of all elements in given range.\ntemplate <class _Iterator,\n          class\
    \ _Operator = std::multiplies<\n              typename std::iterator_traits<_Iterator>::value_type>>\n\
    typename std::iterator_traits<_Iterator>::value_type prod(\n    _Iterator __first,\
    \ _Iterator __last,\n    _Operator __op = _Operator{}) noexcept {\n  return sum(__first,\
    \ __last, __op);\n}\n\n}  // namespace workspace\n"
  dependsOn:
  - src/algebra/sum.hpp
  isVerificationFile: false
  path: src/algebra/prod.hpp
  requiredBy: []
  timestamp: '2021-08-12 13:27:32+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/algebra/prod.hpp
layout: document
redirect_from:
- /library/src/algebra/prod.hpp
- /library/src/algebra/prod.hpp.html
title: src/algebra/prod.hpp
---
