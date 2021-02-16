---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/NTL_1_E.test.cpp
    title: test/aizu-online-judge/NTL_1_E.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/bitwise_and_convolution.test.cpp
    title: test/library-checker/bitwise_and_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/bitwise_xor_convolution.test.cpp
    title: test/library-checker/bitwise_xor_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/min_cost_b_flow.test.cpp
    title: test/library-checker/min_cost_b_flow.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/suffix_array.test.cpp
    title: test/library-checker/suffix_array.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/zalgorithm.test.cpp
    title: test/library-checker/zalgorithm.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Output Stream
    links: []
  bundledCode: "#line 2 \"src/utils/io/ostream.hpp\"\n\n/**\n * @file ostream.hpp\n\
    \ * @brief Output Stream\n */\n\n#include <tuple>\n\nnamespace workspace {\n\n\
    /**\n * @brief Stream insertion operator for C-style array.\n *\n * @param __os\
    \ Output stream\n * @param __a Array\n * @return Reference to __os.\n */\ntemplate\
    \ <class _Os, class _Tp, size_t _Nm>\ntypename std::enable_if<bool(sizeof(_Tp)\
    \ > 2), _Os &>::type operator<<(\n    _Os &__os, const _Tp (&__a)[_Nm]) {\n  if\
    \ constexpr (_Nm) {\n    __os << *__a;\n    for (auto __i = __a + 1, __e = __a\
    \ + _Nm; __i != __e; ++__i)\n      __os << ' ' << *__i;\n  }\n  return __os;\n\
    }\n\n/**\n * @brief Stream insertion operator for std::pair.\n *\n * @param __os\
    \ Output stream\n * @param __p Pair\n * @return Reference to __os.\n */\ntemplate\
    \ <class _Os, class _T1, class _T2>\n_Os &operator<<(_Os &__os, const std::pair<_T1,\
    \ _T2> &__p) {\n  return __os << __p.first << ' ' << __p.second;\n}\n\n/**\n *\
    \ @brief Stream insertion operator for std::tuple.\n *\n * @param __os Output\
    \ stream\n * @param __t Tuple\n * @return Reference to __os.\n */\ntemplate <class\
    \ _Os, class _Tp, size_t _Nm = 0>\ntypename std::enable_if<bool(std::tuple_size<_Tp>::value\
    \ + 1), _Os &>::type\noperator<<(_Os &__os, const _Tp &__t) {\n  if constexpr\
    \ (_Nm != std::tuple_size<_Tp>::value) {\n    if constexpr (_Nm) __os << ' ';\n\
    \    __os << std::get<_Nm>(__t);\n    operator<<<_Os, _Tp, _Nm + 1>(__os, __t);\n\
    \  }\n  return __os;\n}\n\ntemplate <class _Os, class _Container,\n          typename\
    \ = decltype(std::begin(std::declval<_Container>()))>\ntypename std::enable_if<\n\
    \    !std::is_same<typename std::decay<_Container>::type, std::string>::value\
    \ &&\n        !std::is_same<typename std::decay<_Container>::type, char *>::value,\n\
    \    _Os &>::type\noperator<<(_Os &__os, const _Container &__cont) {\n  bool __h\
    \ = true;\n  for (auto &&__e : __cont) __h ? __h = 0 : (__os << ' ', 0), __os\
    \ << __e;\n  return __os;\n}\n\n#ifdef __SIZEOF_INT128__\n\n/**\n * @brief Stream\
    \ insertion operator for __int128_t.\n *\n * @param __os Output Stream\n * @param\
    \ __x 128-bit integer\n * @return Reference to __os.\n */\ntemplate <class _Os>\
    \ _Os &operator<<(_Os &__os, __int128_t __x) {\n  if (!__x) return __os << '0';\n\
    \  if (__x < 0) __os << '-';\n  char __s[40], *__p = __s;\n  while (__x) {\n \
    \   auto __d = __x % 10;\n    *__p++ = '0' + (__x < 0 ? -__d : __d);\n    __x\
    \ /= 10;\n  }\n  *__p = 0;\n  for (char *__t = __s; __t < --__p; ++__t) *__t ^=\
    \ *__p ^= *__t ^= *__p;\n  return __os << __s;\n}\n\n/**\n * @brief Stream insertion\
    \ operator for __uint128_t.\n *\n * @param __os Output Stream\n * @param __x 128-bit\
    \ unsigned integer\n * @return Reference to __os.\n */\ntemplate <class _Os> _Os\
    \ &operator<<(_Os &__os, __uint128_t __x) {\n  if (!__x) return __os << '0';\n\
    \  char __s[40], *__p = __s;\n  while (__x) *__p++ = '0' + __x % 10, __x /= 10;\n\
    \  *__p = 0;\n  for (char *__t = __s; __t < --__p; ++__t) *__t ^= *__p ^= *__t\
    \ ^= *__p;\n  return __os << __s;\n}\n\n#endif\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file ostream.hpp\n * @brief Output Stream\n */\n\
    \n#include <tuple>\n\nnamespace workspace {\n\n/**\n * @brief Stream insertion\
    \ operator for C-style array.\n *\n * @param __os Output stream\n * @param __a\
    \ Array\n * @return Reference to __os.\n */\ntemplate <class _Os, class _Tp, size_t\
    \ _Nm>\ntypename std::enable_if<bool(sizeof(_Tp) > 2), _Os &>::type operator<<(\n\
    \    _Os &__os, const _Tp (&__a)[_Nm]) {\n  if constexpr (_Nm) {\n    __os <<\
    \ *__a;\n    for (auto __i = __a + 1, __e = __a + _Nm; __i != __e; ++__i)\n  \
    \    __os << ' ' << *__i;\n  }\n  return __os;\n}\n\n/**\n * @brief Stream insertion\
    \ operator for std::pair.\n *\n * @param __os Output stream\n * @param __p Pair\n\
    \ * @return Reference to __os.\n */\ntemplate <class _Os, class _T1, class _T2>\n\
    _Os &operator<<(_Os &__os, const std::pair<_T1, _T2> &__p) {\n  return __os <<\
    \ __p.first << ' ' << __p.second;\n}\n\n/**\n * @brief Stream insertion operator\
    \ for std::tuple.\n *\n * @param __os Output stream\n * @param __t Tuple\n * @return\
    \ Reference to __os.\n */\ntemplate <class _Os, class _Tp, size_t _Nm = 0>\ntypename\
    \ std::enable_if<bool(std::tuple_size<_Tp>::value + 1), _Os &>::type\noperator<<(_Os\
    \ &__os, const _Tp &__t) {\n  if constexpr (_Nm != std::tuple_size<_Tp>::value)\
    \ {\n    if constexpr (_Nm) __os << ' ';\n    __os << std::get<_Nm>(__t);\n  \
    \  operator<<<_Os, _Tp, _Nm + 1>(__os, __t);\n  }\n  return __os;\n}\n\ntemplate\
    \ <class _Os, class _Container,\n          typename = decltype(std::begin(std::declval<_Container>()))>\n\
    typename std::enable_if<\n    !std::is_same<typename std::decay<_Container>::type,\
    \ std::string>::value &&\n        !std::is_same<typename std::decay<_Container>::type,\
    \ char *>::value,\n    _Os &>::type\noperator<<(_Os &__os, const _Container &__cont)\
    \ {\n  bool __h = true;\n  for (auto &&__e : __cont) __h ? __h = 0 : (__os <<\
    \ ' ', 0), __os << __e;\n  return __os;\n}\n\n#ifdef __SIZEOF_INT128__\n\n/**\n\
    \ * @brief Stream insertion operator for __int128_t.\n *\n * @param __os Output\
    \ Stream\n * @param __x 128-bit integer\n * @return Reference to __os.\n */\n\
    template <class _Os> _Os &operator<<(_Os &__os, __int128_t __x) {\n  if (!__x)\
    \ return __os << '0';\n  if (__x < 0) __os << '-';\n  char __s[40], *__p = __s;\n\
    \  while (__x) {\n    auto __d = __x % 10;\n    *__p++ = '0' + (__x < 0 ? -__d\
    \ : __d);\n    __x /= 10;\n  }\n  *__p = 0;\n  for (char *__t = __s; __t < --__p;\
    \ ++__t) *__t ^= *__p ^= *__t ^= *__p;\n  return __os << __s;\n}\n\n/**\n * @brief\
    \ Stream insertion operator for __uint128_t.\n *\n * @param __os Output Stream\n\
    \ * @param __x 128-bit unsigned integer\n * @return Reference to __os.\n */\n\
    template <class _Os> _Os &operator<<(_Os &__os, __uint128_t __x) {\n  if (!__x)\
    \ return __os << '0';\n  char __s[40], *__p = __s;\n  while (__x) *__p++ = '0'\
    \ + __x % 10, __x /= 10;\n  *__p = 0;\n  for (char *__t = __s; __t < --__p; ++__t)\
    \ *__t ^= *__p ^= *__t ^= *__p;\n  return __os << __s;\n}\n\n#endif\n\n}  // namespace\
    \ workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/io/ostream.hpp
  requiredBy: []
  timestamp: '2021-02-16 14:54:56+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aizu-online-judge/NTL_1_E.test.cpp
  - test/library-checker/min_cost_b_flow.test.cpp
  - test/library-checker/zalgorithm.test.cpp
  - test/library-checker/bitwise_xor_convolution.test.cpp
  - test/library-checker/suffix_array.test.cpp
  - test/library-checker/bitwise_and_convolution.test.cpp
documentation_of: src/utils/io/ostream.hpp
layout: document
redirect_from:
- /library/src/utils/io/ostream.hpp
- /library/src/utils/io/ostream.hpp.html
title: Output Stream
---
