---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy:
  - icon: ':warning:'
    path: src/utils/io/input.hpp
    title: Input
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/2450.test.cpp
    title: test/aizu-online-judge/2450.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/ITP1_6_D.test.cpp
    title: test/aizu-online-judge/ITP1_6_D.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/ITP1_7_D.test.cpp
    title: test/aizu-online-judge/ITP1_7_D.test.cpp
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
    path: test/library-checker/matrix_det.test.cpp
    title: test/library-checker/matrix_det.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/system_of_linear_equations.test.cpp
    title: test/library-checker/system_of_linear_equations.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Input Stream
    links: []
  bundledCode: "#line 2 \"src/utils/io/istream.hpp\"\n\n/**\n * @file istream.hpp\n\
    \ * @brief Input Stream\n */\n\n#include <cxxabi.h>\n\n#include <cassert>\n#include\
    \ <iostream>\n#include <tuple>\n\n#line 2 \"lib/cxx17\"\n\n#ifndef _CXX17_CONSTEXPR\n\
    #if __cplusplus >= 201703L\n#define _CXX17_CONSTEXPR constexpr\n#else\n#define\
    \ _CXX17_CONSTEXPR\n#endif\n#endif\n\n#ifndef _CXX17_STATIC_ASSERT\n#if __cplusplus\
    \ >= 201703L\n#define _CXX17_STATIC_ASSERT static_assert\n#else\n#define _CXX17_STATIC_ASSERT\
    \ assert\n#endif\n#endif\n\n#include <iterator>\n\n#if __cplusplus < 201703L\n\
    \nnamespace std {\n\n/**\n *  @brief  Return the size of a container.\n *  @param\
    \  __cont  Container.\n */\ntemplate <typename _Container>\nconstexpr auto size(const\
    \ _Container& __cont) noexcept(noexcept(__cont.size()))\n    -> decltype(__cont.size())\
    \ {\n  return __cont.size();\n}\n\n/**\n *  @brief  Return the size of an array.\n\
    \ */\ntemplate <typename _Tp, size_t _Nm>\nconstexpr size_t size(const _Tp (&)[_Nm])\
    \ noexcept {\n  return _Nm;\n}\n\nstruct monostate {};\n\n}  // namespace std\n\
    \n#else\n\n#include <variant>\n\n#endif\n#line 2 \"src/utils/sfinae.hpp\"\n\n\
    /**\n * @file sfinae.hpp\n * @brief SFINAE\n */\n\n#include <cstdint>\n#line 10\
    \ \"src/utils/sfinae.hpp\"\n#include <type_traits>\n\n#ifndef __INT128_DEFINED__\n\
    \n#ifdef __SIZEOF_INT128__\n#define __INT128_DEFINED__ 1\n#else\n#define __INT128_DEFINED__\
    \ 0\n#endif\n\n#endif\n\nnamespace std {\n\n#if __INT128_DEFINED__\n\ntemplate\
    \ <> struct make_signed<__uint128_t> { using type = __int128_t; };\ntemplate <>\
    \ struct make_signed<__int128_t> { using type = __int128_t; };\n\ntemplate <>\
    \ struct make_unsigned<__uint128_t> { using type = __uint128_t; };\ntemplate <>\
    \ struct make_unsigned<__int128_t> { using type = __uint128_t; };\n\ntemplate\
    \ <> struct is_signed<__uint128_t> : std::false_type {};\ntemplate <> struct is_signed<__int128_t>\
    \ : std::true_type {};\n\ntemplate <> struct is_unsigned<__uint128_t> : std::true_type\
    \ {};\ntemplate <> struct is_unsigned<__int128_t> : std::false_type {};\n\n#endif\n\
    \n}  // namespace std\n\nnamespace workspace {\n\ntemplate <class Tp, class...\
    \ Args> struct variadic_front { using type = Tp; };\n\ntemplate <class... Args>\
    \ struct variadic_back;\n\ntemplate <class Tp> struct variadic_back<Tp> { using\
    \ type = Tp; };\n\ntemplate <class Tp, class... Args> struct variadic_back<Tp,\
    \ Args...> {\n  using type = typename variadic_back<Args...>::type;\n};\n\ntemplate\
    \ <class type, template <class> class trait>\nusing enable_if_trait_type = typename\
    \ std::enable_if<trait<type>::value>::type;\n\n/**\n * @brief Return type of subscripting\
    \ ( @c [] ) access.\n */\ntemplate <class _Tp>\nusing subscripted_type =\n   \
    \ typename std::decay<decltype(std::declval<_Tp&>()[0])>::type;\n\ntemplate <class\
    \ Container>\nusing element_type = typename std::decay<decltype(\n    *std::begin(std::declval<Container&>()))>::type;\n\
    \ntemplate <class _Tp, class = std::nullptr_t>\nstruct has_begin : std::false_type\
    \ {};\n\ntemplate <class _Tp>\nstruct has_begin<_Tp, decltype(std::begin(std::declval<_Tp>()),\
    \ nullptr)>\n    : std::true_type {};\n\ntemplate <class _Tp, class = void> struct\
    \ has_mod : std::false_type {};\n\ntemplate <class _Tp>\nstruct has_mod<_Tp, std::__void_t<decltype(_Tp::mod)>>\
    \ : std::true_type {};\n\ntemplate <class _Tp, class = void> struct is_integral_ext\
    \ : std::false_type {};\ntemplate <class _Tp>\nstruct is_integral_ext<\n    _Tp,\
    \ typename std::enable_if<std::is_integral<_Tp>::value>::type>\n    : std::true_type\
    \ {};\n\n#if __INT128_DEFINED__\n\ntemplate <> struct is_integral_ext<__int128_t>\
    \ : std::true_type {};\ntemplate <> struct is_integral_ext<__uint128_t> : std::true_type\
    \ {};\n\n#endif\n\n#if __cplusplus >= 201402\n\ntemplate <class _Tp>\nconstexpr\
    \ static bool is_integral_ext_v = is_integral_ext<_Tp>::value;\n\n#endif\n\ntemplate\
    \ <typename _Tp, typename = void> struct multiplicable_uint {\n  using type =\
    \ uint_least32_t;\n};\ntemplate <typename _Tp>\nstruct multiplicable_uint<\n \
    \   _Tp,\n    typename std::enable_if<(2 < sizeof(_Tp)) &&\n                 \
    \           (!__INT128_DEFINED__ || sizeof(_Tp) <= 4)>::type> {\n  using type\
    \ = uint_least64_t;\n};\n\n#if __INT128_DEFINED__\n\ntemplate <typename _Tp>\n\
    struct multiplicable_uint<_Tp,\n                          typename std::enable_if<(4\
    \ < sizeof(_Tp))>::type> {\n  using type = __uint128_t;\n};\n\n#endif\n\ntemplate\
    \ <typename _Tp> struct multiplicable_int {\n  using type =\n      typename std::make_signed<typename\
    \ multiplicable_uint<_Tp>::type>::type;\n};\n\ntemplate <typename _Tp> struct\
    \ multiplicable {\n  using type = std::conditional_t<\n      is_integral_ext<_Tp>::value,\n\
    \      std::conditional_t<std::is_signed<_Tp>::value,\n                      \
    \   typename multiplicable_int<_Tp>::type,\n                         typename\
    \ multiplicable_uint<_Tp>::type>,\n      _Tp>;\n};\n\ntemplate <class> struct\
    \ first_arg { using type = void; };\n\ntemplate <class _R, class _Tp, class...\
    \ _Args>\nstruct first_arg<_R(_Tp, _Args...)> {\n  using type = _Tp;\n};\n\ntemplate\
    \ <class _R, class _Tp, class... _Args>\nstruct first_arg<_R (*)(_Tp, _Args...)>\
    \ {\n  using type = _Tp;\n};\n\ntemplate <class _G, class _R, class _Tp, class...\
    \ _Args>\nstruct first_arg<_R (_G::*)(_Tp, _Args...)> {\n  using type = _Tp;\n\
    };\n\ntemplate <class _G, class _R, class _Tp, class... _Args>\nstruct first_arg<_R\
    \ (_G::*)(_Tp, _Args...) const> {\n  using type = _Tp;\n};\n\ntemplate <class\
    \ _Tp, class = void> struct parse_compare : first_arg<_Tp> {};\n\ntemplate <class\
    \ _Tp>\nstruct parse_compare<_Tp, std::__void_t<decltype(&_Tp::operator())>>\n\
    \    : first_arg<decltype(&_Tp::operator())> {};\n\n}  // namespace workspace\n\
    #line 16 \"src/utils/io/istream.hpp\"\n\nnamespace workspace {\n\nnamespace _istream_impl\
    \ {\n\ntemplate <class _Tp, typename = void> struct helper {\n  helper(std::istream\
    \ &__is, _Tp &__x) {\n    if _CXX17_CONSTEXPR (has_begin<_Tp &>::value)\n    \
    \  for (auto &&__e : __x) helper<std::decay_t<decltype(__e)>>(__is, __e);\n  \
    \  else\n      static_assert(has_begin<_Tp>::value, \"istream unsupported type.\"\
    );\n  }\n};\n\ntemplate <class _Tp>\nstruct helper<_Tp, std::__void_t<decltype(std::declval<std::istream\
    \ &>() >>\n                                          std::declval<_Tp &>())>>\
    \ {\n  helper(std::istream &__is, _Tp &__x) { __is >> __x; }\n};\n\n#ifdef __SIZEOF_INT128__\n\
    \ntemplate <> struct helper<__uint128_t, void> {\n  helper(std::istream &__is,\
    \ __uint128_t &__x) {\n    std::string __s;\n    __is >> __s;\n    bool __neg\
    \ = false;\n    if (__s.front() == '-') __neg = true, __s.erase(__s.begin());\n\
    \    __x = 0;\n    for (char __d : __s) {\n      __x *= 10;\n      __d -= '0';\n\
    \      if (__neg)\n        __x -= __d;\n      else\n        __x += __d;\n    }\n\
    \  }\n};\n\ntemplate <> struct helper<__int128_t, void> {\n  helper(std::istream\
    \ &__is, __int128_t &__x) {\n    std::string __s;\n    __is >> __s;\n    bool\
    \ __neg = false;\n    if (__s.front() == '-') __neg = true, __s.erase(__s.begin());\n\
    \    __x = 0;\n    for (char __d : __s) {\n      __x *= 10;\n      __d -= '0';\n\
    \      if (__neg)\n        __x -= __d;\n      else\n        __x += __d;\n    }\n\
    \  }\n};\n\n#endif  // INT128\n\ntemplate <class _T1, class _T2> struct helper<std::pair<_T1,\
    \ _T2>> {\n  helper(std::istream &__is, std::pair<_T1, _T2> &__x) {\n    helper<_T1>(__is,\
    \ __x.first), helper<_T2>(__is, __x.second);\n  }\n};\n\ntemplate <class... _Tp>\
    \ struct helper<std::tuple<_Tp...>> {\n  helper(std::istream &__is, std::tuple<_Tp...>\
    \ &__x) { iterate(__is, __x); }\n\n private:\n  template <class _Tuple, size_t\
    \ _Nm = 0>\n  void iterate(std::istream &__is, _Tuple &__x) {\n    if _CXX17_CONSTEXPR\
    \ (_Nm != std::tuple_size<_Tuple>::value) {\n      helper<typename std::tuple_element<_Nm,\
    \ _Tuple>::type>(\n          __is, std::get<_Nm>(__x)),\n          iterate<_Tuple,\
    \ _Nm + 1>(__is, __x);\n    }\n  }\n};\n\n}  // namespace _istream_impl\n\n/**\n\
    \ * @brief A wrapper class for std::istream.\n */\nclass istream : public std::istream\
    \ {\n public:\n  /**\n   * @brief Wrapped operator.\n   */\n  template <typename\
    \ _Tp> istream &operator>>(_Tp &__x) {\n    _istream_impl::helper<_Tp>(*this,\
    \ __x);\n    if (std::istream::fail()) {\n      static auto once = atexit([] {\n\
    \        std::cerr << \"\\n\\033[43m\\033[30mwarning: failed to read \\'\"\n \
    \                 << abi::__cxa_demangle(typeid(_Tp).name(), 0, 0, 0)\n      \
    \            << \"\\'.\\033[0m\\n\\n\";\n      });\n      assert(!once);\n   \
    \ }\n    return *this;\n  }\n};\n\ndecltype(auto) cin = static_cast<istream &>(std::cin);\n\
    \n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file istream.hpp\n * @brief Input Stream\n */\n\n\
    #include <cxxabi.h>\n\n#include <cassert>\n#include <iostream>\n#include <tuple>\n\
    \n#include \"lib/cxx17\"\n#include \"src/utils/sfinae.hpp\"\n\nnamespace workspace\
    \ {\n\nnamespace _istream_impl {\n\ntemplate <class _Tp, typename = void> struct\
    \ helper {\n  helper(std::istream &__is, _Tp &__x) {\n    if _CXX17_CONSTEXPR\
    \ (has_begin<_Tp &>::value)\n      for (auto &&__e : __x) helper<std::decay_t<decltype(__e)>>(__is,\
    \ __e);\n    else\n      static_assert(has_begin<_Tp>::value, \"istream unsupported\
    \ type.\");\n  }\n};\n\ntemplate <class _Tp>\nstruct helper<_Tp, std::__void_t<decltype(std::declval<std::istream\
    \ &>() >>\n                                          std::declval<_Tp &>())>>\
    \ {\n  helper(std::istream &__is, _Tp &__x) { __is >> __x; }\n};\n\n#ifdef __SIZEOF_INT128__\n\
    \ntemplate <> struct helper<__uint128_t, void> {\n  helper(std::istream &__is,\
    \ __uint128_t &__x) {\n    std::string __s;\n    __is >> __s;\n    bool __neg\
    \ = false;\n    if (__s.front() == '-') __neg = true, __s.erase(__s.begin());\n\
    \    __x = 0;\n    for (char __d : __s) {\n      __x *= 10;\n      __d -= '0';\n\
    \      if (__neg)\n        __x -= __d;\n      else\n        __x += __d;\n    }\n\
    \  }\n};\n\ntemplate <> struct helper<__int128_t, void> {\n  helper(std::istream\
    \ &__is, __int128_t &__x) {\n    std::string __s;\n    __is >> __s;\n    bool\
    \ __neg = false;\n    if (__s.front() == '-') __neg = true, __s.erase(__s.begin());\n\
    \    __x = 0;\n    for (char __d : __s) {\n      __x *= 10;\n      __d -= '0';\n\
    \      if (__neg)\n        __x -= __d;\n      else\n        __x += __d;\n    }\n\
    \  }\n};\n\n#endif  // INT128\n\ntemplate <class _T1, class _T2> struct helper<std::pair<_T1,\
    \ _T2>> {\n  helper(std::istream &__is, std::pair<_T1, _T2> &__x) {\n    helper<_T1>(__is,\
    \ __x.first), helper<_T2>(__is, __x.second);\n  }\n};\n\ntemplate <class... _Tp>\
    \ struct helper<std::tuple<_Tp...>> {\n  helper(std::istream &__is, std::tuple<_Tp...>\
    \ &__x) { iterate(__is, __x); }\n\n private:\n  template <class _Tuple, size_t\
    \ _Nm = 0>\n  void iterate(std::istream &__is, _Tuple &__x) {\n    if _CXX17_CONSTEXPR\
    \ (_Nm != std::tuple_size<_Tuple>::value) {\n      helper<typename std::tuple_element<_Nm,\
    \ _Tuple>::type>(\n          __is, std::get<_Nm>(__x)),\n          iterate<_Tuple,\
    \ _Nm + 1>(__is, __x);\n    }\n  }\n};\n\n}  // namespace _istream_impl\n\n/**\n\
    \ * @brief A wrapper class for std::istream.\n */\nclass istream : public std::istream\
    \ {\n public:\n  /**\n   * @brief Wrapped operator.\n   */\n  template <typename\
    \ _Tp> istream &operator>>(_Tp &__x) {\n    _istream_impl::helper<_Tp>(*this,\
    \ __x);\n    if (std::istream::fail()) {\n      static auto once = atexit([] {\n\
    \        std::cerr << \"\\n\\033[43m\\033[30mwarning: failed to read \\'\"\n \
    \                 << abi::__cxa_demangle(typeid(_Tp).name(), 0, 0, 0)\n      \
    \            << \"\\'.\\033[0m\\n\\n\";\n      });\n      assert(!once);\n   \
    \ }\n    return *this;\n  }\n};\n\ndecltype(auto) cin = static_cast<istream &>(std::cin);\n\
    \n}  // namespace workspace\n"
  dependsOn:
  - src/utils/sfinae.hpp
  isVerificationFile: false
  path: src/utils/io/istream.hpp
  requiredBy:
  - src/utils/io/input.hpp
  timestamp: '2021-08-17 17:53:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/matrix_det.test.cpp
  - test/library-checker/bitwise_xor_convolution.test.cpp
  - test/library-checker/bitwise_and_convolution.test.cpp
  - test/library-checker/division_of_polynomials.test.cpp
  - test/library-checker/find_linear_recurrence.test.cpp
  - test/library-checker/cartesian_tree.test.cpp
  - test/library-checker/convolution_mod.test.cpp
  - test/library-checker/system_of_linear_equations.test.cpp
  - test/aizu-online-judge/ITP1_7_D.test.cpp
  - test/aizu-online-judge/ITP1_6_D.test.cpp
  - test/aizu-online-judge/2450.test.cpp
documentation_of: src/utils/io/istream.hpp
layout: document
redirect_from:
- /library/src/utils/io/istream.hpp
- /library/src/utils/io/istream.hpp.html
title: Input Stream
---
