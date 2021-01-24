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
    /**\n * @brief Stream insertion operator for std::pair.\n *\n * @param __os Output\
    \ stream\n * @param __p Pair\n * @return Reference to __os.\n */\ntemplate <class\
    \ Os, class T1, class T2>\nOs &operator<<(Os &__os, const std::pair<T1, T2> &__p)\
    \ {\n  return __os << __p.first << ' ' << __p.second;\n}\n\n/**\n * @brief Stream\
    \ insertion operator for std::tuple.\n *\n * @param __os Output stream\n * @param\
    \ __t Tuple\n * @return Reference to __os.\n */\ntemplate <class Os, class Tp,\
    \ size_t N = 0>\ntypename std::enable_if<bool(std::tuple_size<Tp>::value + 1),\
    \ Os &>::type\noperator<<(Os &__os, const Tp &__t) {\n  if constexpr (N != std::tuple_size<Tp>::value)\
    \ {\n    if constexpr (N) __os << ' ';\n    __os << std::get<N>(__t);\n    operator<<<Os,\
    \ Tp, N + 1>(__os, __t);\n  }\n  return __os;\n}\n\ntemplate <class Os, class\
    \ Container,\n          typename = decltype(std::begin(std::declval<Container>()))>\n\
    typename std::enable_if<\n    !std::is_same<typename std::decay<Container>::type,\
    \ std::string>::value &&\n        !std::is_same<typename std::decay<Container>::type,\
    \ char *>::value,\n    Os &>::type\noperator<<(Os &__os, const Container &__cont)\
    \ {\n  bool __h = true;\n  for (auto &&__e : __cont) __h ? __h = 0 : (__os <<\
    \ ' ', 0), __os << __e;\n  return __os;\n}\n\n#ifdef __SIZEOF_INT128__\n\n/**\n\
    \ * @brief Stream insertion operator for __int128_t.\n *\n * @param __os Output\
    \ Stream\n * @param __x 128-bit integer\n * @return Reference to __os.\n */\n\
    template <class Os> Os &operator<<(Os &__os, __int128_t __x) {\n  if (!__x) return\
    \ __os << '0';\n  if (__x < 0) __os << '-';\n  char __s[40], *__p = __s;\n  while\
    \ (__x) {\n    auto __d = __x % 10;\n    *__p++ = '0' + (__x < 0 ? -__d : __d);\n\
    \    __x /= 10;\n  }\n  *__p = 0;\n  for (char *__t = __s; __t < --__p; ++__t)\
    \ *__t ^= *__p ^= *__t ^= *__p;\n  return __os << __s;\n}\n\n/**\n * @brief Stream\
    \ insertion operator for __uint128_t.\n *\n * @param __os Output Stream\n * @param\
    \ __x 128-bit unsigned integer\n * @return Reference to __os.\n */\ntemplate <class\
    \ Os> Os &operator<<(Os &__os, __uint128_t __x) {\n  if (!__x) return __os <<\
    \ '0';\n  char __s[40], *__p = __s;\n  while (__x) *__p++ = '0' + __x % 10, __x\
    \ /= 10;\n  *__p = 0;\n  for (char *__t = __s; __t < --__p; ++__t) *__t ^= *__p\
    \ ^= *__t ^= *__p;\n  return __os << __s;\n}\n\n#endif\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file ostream.hpp\n * @brief Output Stream\n */\n\
    \n#include <tuple>\n\nnamespace workspace {\n\n/**\n * @brief Stream insertion\
    \ operator for std::pair.\n *\n * @param __os Output stream\n * @param __p Pair\n\
    \ * @return Reference to __os.\n */\ntemplate <class Os, class T1, class T2>\n\
    Os &operator<<(Os &__os, const std::pair<T1, T2> &__p) {\n  return __os << __p.first\
    \ << ' ' << __p.second;\n}\n\n/**\n * @brief Stream insertion operator for std::tuple.\n\
    \ *\n * @param __os Output stream\n * @param __t Tuple\n * @return Reference to\
    \ __os.\n */\ntemplate <class Os, class Tp, size_t N = 0>\ntypename std::enable_if<bool(std::tuple_size<Tp>::value\
    \ + 1), Os &>::type\noperator<<(Os &__os, const Tp &__t) {\n  if constexpr (N\
    \ != std::tuple_size<Tp>::value) {\n    if constexpr (N) __os << ' ';\n    __os\
    \ << std::get<N>(__t);\n    operator<<<Os, Tp, N + 1>(__os, __t);\n  }\n  return\
    \ __os;\n}\n\ntemplate <class Os, class Container,\n          typename = decltype(std::begin(std::declval<Container>()))>\n\
    typename std::enable_if<\n    !std::is_same<typename std::decay<Container>::type,\
    \ std::string>::value &&\n        !std::is_same<typename std::decay<Container>::type,\
    \ char *>::value,\n    Os &>::type\noperator<<(Os &__os, const Container &__cont)\
    \ {\n  bool __h = true;\n  for (auto &&__e : __cont) __h ? __h = 0 : (__os <<\
    \ ' ', 0), __os << __e;\n  return __os;\n}\n\n#ifdef __SIZEOF_INT128__\n\n/**\n\
    \ * @brief Stream insertion operator for __int128_t.\n *\n * @param __os Output\
    \ Stream\n * @param __x 128-bit integer\n * @return Reference to __os.\n */\n\
    template <class Os> Os &operator<<(Os &__os, __int128_t __x) {\n  if (!__x) return\
    \ __os << '0';\n  if (__x < 0) __os << '-';\n  char __s[40], *__p = __s;\n  while\
    \ (__x) {\n    auto __d = __x % 10;\n    *__p++ = '0' + (__x < 0 ? -__d : __d);\n\
    \    __x /= 10;\n  }\n  *__p = 0;\n  for (char *__t = __s; __t < --__p; ++__t)\
    \ *__t ^= *__p ^= *__t ^= *__p;\n  return __os << __s;\n}\n\n/**\n * @brief Stream\
    \ insertion operator for __uint128_t.\n *\n * @param __os Output Stream\n * @param\
    \ __x 128-bit unsigned integer\n * @return Reference to __os.\n */\ntemplate <class\
    \ Os> Os &operator<<(Os &__os, __uint128_t __x) {\n  if (!__x) return __os <<\
    \ '0';\n  char __s[40], *__p = __s;\n  while (__x) *__p++ = '0' + __x % 10, __x\
    \ /= 10;\n  *__p = 0;\n  for (char *__t = __s; __t < --__p; ++__t) *__t ^= *__p\
    \ ^= *__t ^= *__p;\n  return __os << __s;\n}\n\n#endif\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/io/ostream.hpp
  requiredBy: []
  timestamp: '2021-01-24 20:27:26+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/suffix_array.test.cpp
  - test/library-checker/zalgorithm.test.cpp
  - test/library-checker/bitwise_xor_convolution.test.cpp
  - test/library-checker/bitwise_and_convolution.test.cpp
  - test/aizu-online-judge/NTL_1_E.test.cpp
documentation_of: src/utils/io/ostream.hpp
layout: document
redirect_from:
- /library/src/utils/io/ostream.hpp
- /library/src/utils/io/ostream.hpp.html
title: Output Stream
---
