---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: src/utils/io/print.hpp
    title: Print
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/ITP1_6_D.test.cpp
    title: test/aizu-online-judge/ITP1_6_D.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/ITP1_7_D.test.cpp
    title: test/aizu-online-judge/ITP1_7_D.test.cpp
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
    path: test/library-checker/cartesian_tree.test.cpp
    title: test/library-checker/cartesian_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/convolution_mod.test.cpp
    title: test/library-checker/convolution_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/division_of_polynomials.test.cpp
    title: test/library-checker/division_of_polynomials.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/find_linear_recurrence.test.cpp
    title: test/library-checker/find_linear_recurrence.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/min_cost_b_flow.test.cpp
    title: test/library-checker/min_cost_b_flow.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/multipoint_evaluation.test.cpp
    title: test/library-checker/multipoint_evaluation.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/polynomial_taylor_shift.test.cpp
    title: test/library-checker/polynomial_taylor_shift.test.cpp
  - icon: ':x:'
    path: test/library-checker/suffix_array.test.cpp
    title: test/library-checker/suffix_array.test.cpp
  - icon: ':x:'
    path: test/library-checker/system_of_linear_equations.test.cpp
    title: test/library-checker/system_of_linear_equations.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/zalgorithm.test.cpp
    title: test/library-checker/zalgorithm.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    document_title: Output Stream
    links: []
  bundledCode: "#line 2 \"src/utils/io/ostream.hpp\"\n\n/**\n * @file ostream.hpp\n\
    \ * @brief Output Stream\n */\n\n#include <tuple>\n\n#line 2 \"lib/cxx17\"\n\n\
    #line 2 \"lib/cxx14\"\n\n#ifndef _CXX14_CONSTEXPR\n#if __cplusplus >= 201402L\n\
    #define _CXX14_CONSTEXPR constexpr\n#else\n#define _CXX14_CONSTEXPR\n#endif\n\
    #endif\n#line 4 \"lib/cxx17\"\n\n#ifndef _CXX17_CONSTEXPR\n#if __cplusplus >=\
    \ 201703L\n#define _CXX17_CONSTEXPR constexpr\n#else\n#define _CXX17_CONSTEXPR\n\
    #endif\n#endif\n\n#ifndef _CXX17_STATIC_ASSERT\n#if __cplusplus >= 201703L\n#define\
    \ _CXX17_STATIC_ASSERT static_assert\n#else\n#define _CXX17_STATIC_ASSERT assert\n\
    #endif\n#endif\n\n#include <iterator>\n\n#if __cplusplus < 201703L\n\nnamespace\
    \ std {\n\n/**\n *  @brief  Return the size of a container.\n *  @param  __cont\
    \  Container.\n */\ntemplate <typename _Container>\nconstexpr auto size(const\
    \ _Container& __cont) noexcept(noexcept(__cont.size()))\n    -> decltype(__cont.size())\
    \ {\n  return __cont.size();\n}\n\n/**\n *  @brief  Return the size of an array.\n\
    \ */\ntemplate <typename _Tp, size_t _Nm>\nconstexpr size_t size(const _Tp (&)[_Nm])\
    \ noexcept {\n  return _Nm;\n}\n\n/**\n *  @brief  Return whether a container\
    \ is empty.\n *  @param  __cont  Container.\n */\ntemplate <typename _Container>\n\
    [[nodiscard]] constexpr auto empty(const _Container& __cont) noexcept(\n    noexcept(__cont.empty()))\
    \ -> decltype(__cont.empty()) {\n  return __cont.empty();\n}\n\n/**\n *  @brief\
    \  Return whether an array is empty (always false).\n */\ntemplate <typename _Tp,\
    \ size_t _Nm>\n[[nodiscard]] constexpr bool empty(const _Tp (&)[_Nm]) noexcept\
    \ {\n  return false;\n}\n\n/**\n *  @brief  Return whether an initializer_list\
    \ is empty.\n *  @param  __il  Initializer list.\n */\ntemplate <typename _Tp>\n\
    [[nodiscard]] constexpr bool empty(initializer_list<_Tp> __il) noexcept {\n  return\
    \ __il.size() == 0;\n}\n\nstruct monostate {};\n\n}  // namespace std\n\n#else\n\
    \n#include <variant>\n\n#endif\n#line 11 \"src/utils/io/ostream.hpp\"\n\nnamespace\
    \ workspace {\n\ntemplate <class _Os> struct is_ostream {\n  template <typename...\
    \ _Args>\n  static std::true_type __test(std::basic_ostream<_Args...> *);\n  static\
    \ std::false_type __test(void *);\n  constexpr static bool value = decltype(__test(std::declval<_Os\
    \ *>()))::value;\n};\n\ntemplate <class _Os>\nusing ostream_ref =\n    typename\
    \ std::enable_if<is_ostream<_Os>::value, _Os &>::type;\n\n/**\n * @brief Stream\
    \ insertion operator for C-style array.\n *\n * @param __os Output stream\n *\
    \ @param __a Array\n * @return Reference to __os.\n */\ntemplate <class _Os, class\
    \ _Tp, size_t _Nm>\ntypename std::enable_if<bool(sizeof(_Tp) > 2), ostream_ref<_Os>>::type\n\
    operator<<(_Os &__os, const _Tp (&__a)[_Nm]) {\n  if _CXX17_CONSTEXPR (_Nm) {\n\
    \    __os << *__a;\n    for (auto __i = __a + 1, __e = __a + _Nm; __i != __e;\
    \ ++__i)\n      __os << ' ' << *__i;\n  }\n  return __os;\n}\n\n/**\n * @brief\
    \ Stream insertion operator for std::array.\n *\n * @param __os Output stream\n\
    \ * @param __a Array\n * @return Reference to __os.\n */\ntemplate <class _Os,\
    \ class _Tp, size_t _Nm>\nostream_ref<_Os> operator<<(_Os &__os, const std::array<_Tp,\
    \ _Nm> &__a) {\n  if _CXX17_CONSTEXPR (_Nm) {\n    __os << __a[0];\n    for (size_t\
    \ __i = 1; __i != _Nm; ++__i) __os << ' ' << __a[__i];\n  }\n  return __os;\n\
    }\n\n/**\n * @brief Stream insertion operator for std::pair.\n *\n * @param __os\
    \ Output stream\n * @param __p Pair\n * @return Reference to __os.\n */\ntemplate\
    \ <class _Os, class _T1, class _T2>\nostream_ref<_Os> operator<<(_Os &__os, const\
    \ std::pair<_T1, _T2> &__p) {\n  return __os << __p.first << ' ' << __p.second;\n\
    }\n\n/**\n * @brief Stream insertion operator for std::tuple.\n *\n * @param __os\
    \ Output stream\n * @param __t Tuple\n * @return Reference to __os.\n */\ntemplate\
    \ <class _Os, class _Tp, size_t _Nm = 0>\ntypename std::enable_if<bool(std::tuple_size<_Tp>::value\
    \ + 1),\n                        ostream_ref<_Os>>::type\noperator<<(_Os &__os,\
    \ const _Tp &__t) {\n  if _CXX17_CONSTEXPR (_Nm != std::tuple_size<_Tp>::value)\
    \ {\n    if _CXX17_CONSTEXPR (_Nm) __os << ' ';\n    __os << std::get<_Nm>(__t);\n\
    \    operator<<<_Os, _Tp, _Nm + 1>(__os, __t);\n  }\n  return __os;\n}\n\ntemplate\
    \ <class _Os, class _Container,\n          typename = decltype(std::begin(std::declval<_Container>()))>\n\
    typename std::enable_if<\n    !std::is_convertible<std::decay_t<_Container>, std::string>::value\
    \ &&\n        !std::is_convertible<std::decay_t<_Container>, char *>::value,\n\
    \    ostream_ref<_Os>>::type\noperator<<(_Os &__os, const _Container &__cont)\
    \ {\n  bool __h = true;\n  for (auto &&__e : __cont) __h ? __h = 0 : (__os <<\
    \ ' ', 0), __os << __e;\n  return __os;\n}\n\n#ifdef __SIZEOF_INT128__\n\n/**\n\
    \ * @brief Stream insertion operator for __int128_t.\n *\n * @param __os Output\
    \ Stream\n * @param __x 128-bit integer\n * @return Reference to __os.\n */\n\
    template <class _Os> ostream_ref<_Os> operator<<(_Os &__os, __int128_t __x) {\n\
    \  if (!__x) return __os << '0';\n  if (__x < 0) __os << '-';\n  char __s[40],\
    \ *__p = __s;\n  while (__x) {\n    auto __d = __x % 10;\n    *__p++ = '0' + (__x\
    \ < 0 ? -__d : __d);\n    __x /= 10;\n  }\n  *__p = 0;\n  for (char *__t = __s;\
    \ __t < --__p; ++__t) *__t ^= *__p ^= *__t ^= *__p;\n  return __os << __s;\n}\n\
    \n/**\n * @brief Stream insertion operator for __uint128_t.\n *\n * @param __os\
    \ Output Stream\n * @param __x 128-bit unsigned integer\n * @return Reference\
    \ to __os.\n */\ntemplate <class _Os> ostream_ref<_Os> operator<<(_Os &__os, __uint128_t\
    \ __x) {\n  if (!__x) return __os << '0';\n  char __s[40], *__p = __s;\n  while\
    \ (__x) *__p++ = '0' + __x % 10, __x /= 10;\n  *__p = 0;\n  for (char *__t = __s;\
    \ __t < --__p; ++__t) *__t ^= *__p ^= *__t ^= *__p;\n  return __os << __s;\n}\n\
    \n#endif\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file ostream.hpp\n * @brief Output Stream\n */\n\
    \n#include <tuple>\n\n#include \"lib/cxx17\"\n\nnamespace workspace {\n\ntemplate\
    \ <class _Os> struct is_ostream {\n  template <typename... _Args>\n  static std::true_type\
    \ __test(std::basic_ostream<_Args...> *);\n  static std::false_type __test(void\
    \ *);\n  constexpr static bool value = decltype(__test(std::declval<_Os *>()))::value;\n\
    };\n\ntemplate <class _Os>\nusing ostream_ref =\n    typename std::enable_if<is_ostream<_Os>::value,\
    \ _Os &>::type;\n\n/**\n * @brief Stream insertion operator for C-style array.\n\
    \ *\n * @param __os Output stream\n * @param __a Array\n * @return Reference to\
    \ __os.\n */\ntemplate <class _Os, class _Tp, size_t _Nm>\ntypename std::enable_if<bool(sizeof(_Tp)\
    \ > 2), ostream_ref<_Os>>::type\noperator<<(_Os &__os, const _Tp (&__a)[_Nm])\
    \ {\n  if _CXX17_CONSTEXPR (_Nm) {\n    __os << *__a;\n    for (auto __i = __a\
    \ + 1, __e = __a + _Nm; __i != __e; ++__i)\n      __os << ' ' << *__i;\n  }\n\
    \  return __os;\n}\n\n/**\n * @brief Stream insertion operator for std::array.\n\
    \ *\n * @param __os Output stream\n * @param __a Array\n * @return Reference to\
    \ __os.\n */\ntemplate <class _Os, class _Tp, size_t _Nm>\nostream_ref<_Os> operator<<(_Os\
    \ &__os, const std::array<_Tp, _Nm> &__a) {\n  if _CXX17_CONSTEXPR (_Nm) {\n \
    \   __os << __a[0];\n    for (size_t __i = 1; __i != _Nm; ++__i) __os << ' ' <<\
    \ __a[__i];\n  }\n  return __os;\n}\n\n/**\n * @brief Stream insertion operator\
    \ for std::pair.\n *\n * @param __os Output stream\n * @param __p Pair\n * @return\
    \ Reference to __os.\n */\ntemplate <class _Os, class _T1, class _T2>\nostream_ref<_Os>\
    \ operator<<(_Os &__os, const std::pair<_T1, _T2> &__p) {\n  return __os << __p.first\
    \ << ' ' << __p.second;\n}\n\n/**\n * @brief Stream insertion operator for std::tuple.\n\
    \ *\n * @param __os Output stream\n * @param __t Tuple\n * @return Reference to\
    \ __os.\n */\ntemplate <class _Os, class _Tp, size_t _Nm = 0>\ntypename std::enable_if<bool(std::tuple_size<_Tp>::value\
    \ + 1),\n                        ostream_ref<_Os>>::type\noperator<<(_Os &__os,\
    \ const _Tp &__t) {\n  if _CXX17_CONSTEXPR (_Nm != std::tuple_size<_Tp>::value)\
    \ {\n    if _CXX17_CONSTEXPR (_Nm) __os << ' ';\n    __os << std::get<_Nm>(__t);\n\
    \    operator<<<_Os, _Tp, _Nm + 1>(__os, __t);\n  }\n  return __os;\n}\n\ntemplate\
    \ <class _Os, class _Container,\n          typename = decltype(std::begin(std::declval<_Container>()))>\n\
    typename std::enable_if<\n    !std::is_convertible<std::decay_t<_Container>, std::string>::value\
    \ &&\n        !std::is_convertible<std::decay_t<_Container>, char *>::value,\n\
    \    ostream_ref<_Os>>::type\noperator<<(_Os &__os, const _Container &__cont)\
    \ {\n  bool __h = true;\n  for (auto &&__e : __cont) __h ? __h = 0 : (__os <<\
    \ ' ', 0), __os << __e;\n  return __os;\n}\n\n#ifdef __SIZEOF_INT128__\n\n/**\n\
    \ * @brief Stream insertion operator for __int128_t.\n *\n * @param __os Output\
    \ Stream\n * @param __x 128-bit integer\n * @return Reference to __os.\n */\n\
    template <class _Os> ostream_ref<_Os> operator<<(_Os &__os, __int128_t __x) {\n\
    \  if (!__x) return __os << '0';\n  if (__x < 0) __os << '-';\n  char __s[40],\
    \ *__p = __s;\n  while (__x) {\n    auto __d = __x % 10;\n    *__p++ = '0' + (__x\
    \ < 0 ? -__d : __d);\n    __x /= 10;\n  }\n  *__p = 0;\n  for (char *__t = __s;\
    \ __t < --__p; ++__t) *__t ^= *__p ^= *__t ^= *__p;\n  return __os << __s;\n}\n\
    \n/**\n * @brief Stream insertion operator for __uint128_t.\n *\n * @param __os\
    \ Output Stream\n * @param __x 128-bit unsigned integer\n * @return Reference\
    \ to __os.\n */\ntemplate <class _Os> ostream_ref<_Os> operator<<(_Os &__os, __uint128_t\
    \ __x) {\n  if (!__x) return __os << '0';\n  char __s[40], *__p = __s;\n  while\
    \ (__x) *__p++ = '0' + __x % 10, __x /= 10;\n  *__p = 0;\n  for (char *__t = __s;\
    \ __t < --__p; ++__t) *__t ^= *__p ^= *__t ^= *__p;\n  return __os << __s;\n}\n\
    \n#endif\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/io/ostream.hpp
  requiredBy:
  - src/utils/io/print.hpp
  timestamp: '2021-11-30 17:55:32+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/library-checker/division_of_polynomials.test.cpp
  - test/library-checker/suffix_array.test.cpp
  - test/library-checker/find_linear_recurrence.test.cpp
  - test/library-checker/convolution_mod.test.cpp
  - test/library-checker/polynomial_taylor_shift.test.cpp
  - test/library-checker/multipoint_evaluation.test.cpp
  - test/library-checker/cartesian_tree.test.cpp
  - test/library-checker/system_of_linear_equations.test.cpp
  - test/library-checker/bitwise_and_convolution.test.cpp
  - test/library-checker/bitwise_xor_convolution.test.cpp
  - test/library-checker/zalgorithm.test.cpp
  - test/library-checker/min_cost_b_flow.test.cpp
  - test/aizu-online-judge/ITP1_6_D.test.cpp
  - test/aizu-online-judge/NTL_1_E.test.cpp
  - test/aizu-online-judge/ITP1_7_D.test.cpp
documentation_of: src/utils/io/ostream.hpp
layout: document
redirect_from:
- /library/src/utils/io/ostream.hpp
- /library/src/utils/io/ostream.hpp.html
title: Output Stream
---
