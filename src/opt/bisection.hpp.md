---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Bisection
    links: []
  bundledCode: "#line 2 \"src/opt/bisection.hpp\"\n\n/**\n * @file bisection.hpp\n\
    \ * @brief Bisection\n */\n\nnamespace workspace {\n\n/**\n * @brief Bisection\
    \ method.\n * @param __first\n * @param __last\n * @param __pred\n */\ntemplate\
    \ <class _Iterator, class _Predicate>\n_Iterator bisection(_Iterator __first,\
    \ _Iterator __last, _Predicate &&__pred) {\n  _Iterator __mid;\n  for (decltype(__last\
    \ - __first) __w = 0; __w < __last - __first;\n       __w = __w << 1 | 1) {\n\
    \    __mid = __first + __w;\n    if (!__pred(__mid)) {\n      __last = __mid;\n\
    \      break;\n    }\n    __first = __mid;\n  }\n  while (1 < __last - __first)\
    \ {\n    __mid = __first + (__last - __first) / 2;\n    (__pred(__mid) ? __first\
    \ : __last) = __mid;\n  }\n  return __last;\n}\n\n/**\n * @brief Bisection method.\n\
    \ * @param __first\n * @param __last\n * @param __pred\n * @param __eps\n */\n\
    template <class _Iterator, class _Predicate, class _Difference>\n_Iterator bisection(_Iterator\
    \ __first, _Iterator __last, _Predicate &&__pred,\n                    _Difference\
    \ __eps) {\n  while (__eps < _Difference(__last - __first)) {\n    _Iterator __mid\
    \ = __first + (__last - __first) / 2;\n    (__pred(__mid) ? __first : __last)\
    \ = __mid;\n  }\n  return __last;\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file bisection.hpp\n * @brief Bisection\n */\n\n\
    namespace workspace {\n\n/**\n * @brief Bisection method.\n * @param __first\n\
    \ * @param __last\n * @param __pred\n */\ntemplate <class _Iterator, class _Predicate>\n\
    _Iterator bisection(_Iterator __first, _Iterator __last, _Predicate &&__pred)\
    \ {\n  _Iterator __mid;\n  for (decltype(__last - __first) __w = 0; __w < __last\
    \ - __first;\n       __w = __w << 1 | 1) {\n    __mid = __first + __w;\n    if\
    \ (!__pred(__mid)) {\n      __last = __mid;\n      break;\n    }\n    __first\
    \ = __mid;\n  }\n  while (1 < __last - __first) {\n    __mid = __first + (__last\
    \ - __first) / 2;\n    (__pred(__mid) ? __first : __last) = __mid;\n  }\n  return\
    \ __last;\n}\n\n/**\n * @brief Bisection method.\n * @param __first\n * @param\
    \ __last\n * @param __pred\n * @param __eps\n */\ntemplate <class _Iterator, class\
    \ _Predicate, class _Difference>\n_Iterator bisection(_Iterator __first, _Iterator\
    \ __last, _Predicate &&__pred,\n                    _Difference __eps) {\n  while\
    \ (__eps < _Difference(__last - __first)) {\n    _Iterator __mid = __first + (__last\
    \ - __first) / 2;\n    (__pred(__mid) ? __first : __last) = __mid;\n  }\n  return\
    \ __last;\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/opt/bisection.hpp
  requiredBy: []
  timestamp: '2021-07-17 02:19:08+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/opt/bisection.hpp
layout: document
redirect_from:
- /library/src/opt/bisection.hpp
- /library/src/opt/bisection.hpp.html
title: Bisection
---
