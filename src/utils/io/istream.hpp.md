---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/aizu-online-judge/2450.test.cpp
    title: test/aizu-online-judge/2450.test.cpp
  - icon: ':x:'
    path: test/aizu-online-judge/ITP1_6_D.test.cpp
    title: test/aizu-online-judge/ITP1_6_D.test.cpp
  - icon: ':x:'
    path: test/aizu-online-judge/ITP1_7_D.test.cpp
    title: test/aizu-online-judge/ITP1_7_D.test.cpp
  - icon: ':x:'
    path: test/library-checker/bitwise_and_convolution.test.cpp
    title: test/library-checker/bitwise_and_convolution.test.cpp
  - icon: ':x:'
    path: test/library-checker/bitwise_xor_convolution.test.cpp
    title: test/library-checker/bitwise_xor_convolution.test.cpp
  - icon: ':x:'
    path: test/library-checker/matrix_det.test.cpp
    title: test/library-checker/matrix_det.test.cpp
  - icon: ':x:'
    path: test/library-checker/system_of_linear_equations.test.cpp
    title: test/library-checker/system_of_linear_equations.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: Input Stream
    links: []
  bundledCode: "#line 2 \"src/utils/io/istream.hpp\"\n\n/**\n * @file istream.hpp\n\
    \ * @brief Input Stream\n */\n\n#include <cxxabi.h>\n\n#include <cassert>\n#include\
    \ <iostream>\n#include <tuple>\n\n#line 2 \"src/utils/sfinae.hpp\"\n\n/**\n *\
    \ @file sfinae.hpp\n * @brief SFINAE\n */\n\n#include <cstdint>\n#include <iterator>\n\
    #include <type_traits>\n\n#ifndef __INT128_DEFINED__\n\n#ifdef __SIZEOF_INT128__\n\
    #define __INT128_DEFINED__ 1\n#else\n#define __INT128_DEFINED__ 0\n#endif\n\n\
    #endif\n\nnamespace std {\n\n#if __INT128_DEFINED__\n\ntemplate <> struct make_signed<__uint128_t>\
    \ { using type = __int128_t; };\ntemplate <> struct make_signed<__int128_t> {\
    \ using type = __int128_t; };\n\ntemplate <> struct make_unsigned<__uint128_t>\
    \ { using type = __uint128_t; };\ntemplate <> struct make_unsigned<__int128_t>\
    \ { using type = __uint128_t; };\n\n#endif\n\n}  // namespace std\n\nnamespace\
    \ workspace {\n\ntemplate <class Tp, class... Args> struct variadic_front { using\
    \ type = Tp; };\n\ntemplate <class... Args> struct variadic_back;\n\ntemplate\
    \ <class Tp> struct variadic_back<Tp> { using type = Tp; };\n\ntemplate <class\
    \ Tp, class... Args> struct variadic_back<Tp, Args...> {\n  using type = typename\
    \ variadic_back<Args...>::type;\n};\n\ntemplate <class type, template <class>\
    \ class trait>\nusing enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
    \ntemplate <class Container>\nusing element_type = typename std::decay<decltype(\n\
    \    *std::begin(std::declval<Container&>()))>::type;\n\ntemplate <class T, class\
    \ = std::nullptr_t>\nstruct has_begin : std::false_type {};\n\ntemplate <class\
    \ T>\nstruct has_begin<T, decltype(std::begin(std::declval<T>()), nullptr)>\n\
    \    : std::true_type {};\n\ntemplate <class T, class = int> struct mapped_of\
    \ {\n  using type = element_type<T>;\n};\ntemplate <class T>\nstruct mapped_of<T,\n\
    \                 typename std::pair<int, typename T::mapped_type>::first_type>\
    \ {\n  using type = typename T::mapped_type;\n};\ntemplate <class T> using mapped_type\
    \ = typename mapped_of<T>::type;\n\ntemplate <class T, class = void> struct is_integral_ext\
    \ : std::false_type {};\ntemplate <class T>\nstruct is_integral_ext<\n    T, typename\
    \ std::enable_if<std::is_integral<T>::value>::type>\n    : std::true_type {};\n\
    \n#if __INT128_DEFINED__\n\ntemplate <> struct is_integral_ext<__int128_t> : std::true_type\
    \ {};\ntemplate <> struct is_integral_ext<__uint128_t> : std::true_type {};\n\n\
    #endif\n\n#if __cplusplus >= 201402\n\ntemplate <class T>\nconstexpr static bool\
    \ is_integral_ext_v = is_integral_ext<T>::value;\n\n#endif\n\ntemplate <typename\
    \ T, typename = void> struct multiplicable_uint {\n  using type = uint_least32_t;\n\
    };\ntemplate <typename T>\nstruct multiplicable_uint<\n    T, typename std::enable_if<(2\
    \ < sizeof(T)) &&\n                               (!__INT128_DEFINED__ || sizeof(T)\
    \ <= 4)>::type> {\n  using type = uint_least64_t;\n};\n\n#if __INT128_DEFINED__\n\
    \ntemplate <typename T>\nstruct multiplicable_uint<T, typename std::enable_if<(4\
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n\n#endif\n\ntemplate\
    \ <typename T> struct multiplicable_int {\n  using type =\n      typename std::make_signed<typename\
    \ multiplicable_uint<T>::type>::type;\n};\n\n}  // namespace workspace\n#line\
    \ 15 \"src/utils/io/istream.hpp\"\n\nnamespace workspace {\n\nnamespace _istream_impl\
    \ {\n\ntemplate <class _Tp, typename = std::nullptr_t> struct istream_helper {\n\
    \  istream_helper(std::istream &__is, _Tp &__x) {\n    if constexpr (has_begin<_Tp>::value)\n\
    \      for (auto &&__e : __x)\n        istream_helper<std::__decay_t<decltype(__e)>>(__is,\
    \ __e);\n    else\n      static_assert(has_begin<_Tp>::value, \"istream unsupported\
    \ type.\");\n  }\n};\n\ntemplate <class _Tp>\nstruct istream_helper<\n    _Tp,\n\
    \    decltype(std::declval<std::__decay_t<decltype(\n                 std::declval<std::istream\
    \ &>() >> std::declval<_Tp &>())>>(),\n             nullptr)> {\n  istream_helper(std::istream\
    \ &__is, _Tp &__x) { __is >> __x; }\n};\n\n#ifdef __SIZEOF_INT128__\n\ntemplate\
    \ <> struct istream_helper<__uint128_t, std::nullptr_t> {\n  istream_helper(std::istream\
    \ &__is, __uint128_t &__x) {\n    std::string __s;\n    __is >> __s;\n    bool\
    \ __neg = false;\n    if (__s.front() == '-') __neg = true, __s.erase(__s.begin());\n\
    \    __x = 0;\n    for (char __d : __s) {\n      __x *= 10;\n      __d -= '0';\n\
    \      if (__neg)\n        __x -= __d;\n      else\n        __x += __d;\n    }\n\
    \  }\n};\n\ntemplate <> struct istream_helper<__int128_t, std::nullptr_t> {\n\
    \  istream_helper(std::istream &__is, __int128_t &__x) {\n    std::string __s;\n\
    \    __is >> __s;\n    bool __neg = false;\n    if (__s.front() == '-') __neg\
    \ = true, __s.erase(__s.begin());\n    __x = 0;\n    for (char __d : __s) {\n\
    \      __x *= 10;\n      __d -= '0';\n      if (__neg)\n        __x -= __d;\n\
    \      else\n        __x += __d;\n    }\n  }\n};\n\n#endif  // INT128\n\ntemplate\
    \ <class T1, class T2> struct istream_helper<std::pair<T1, T2>> {\n  istream_helper(std::istream\
    \ &__is, std::pair<T1, T2> &__x) {\n    istream_helper<T1>(__is, __x.first), istream_helper<T2>(__is,\
    \ __x.second);\n  }\n};\n\ntemplate <class... Tps> struct istream_helper<std::tuple<Tps...>>\
    \ {\n  istream_helper(std::istream &__is, std::tuple<Tps...> &__x) {\n    iterate(__is,\
    \ __x);\n  }\n\n private:\n  template <class _Tp, size_t N = 0>\n  void iterate(std::istream\
    \ &__is, _Tp &__x) {\n    if constexpr (N == std::tuple_size<_Tp>::value)\n  \
    \    return;\n    else\n      istream_helper<typename std::tuple_element<N, _Tp>::type>(\n\
    \          __is, std::get<N>(__x)),\n          iterate<_Tp, N + 1>(__is, __x);\n\
    \  }\n};\n\n}  // namespace _istream_impl\n\n/**\n * @brief A wrapper class for\
    \ std::istream.\n */\nclass istream : public std::istream {\n public:\n  /**\n\
    \   * @brief Wrapped operator.\n   */\n  template <typename _Tp> istream &operator>>(_Tp\
    \ &__x) {\n    _istream_impl::istream_helper<_Tp>(*this, __x);\n    if (std::istream::fail())\
    \ {\n      static auto once = atexit([] {\n        std::cerr << \"\\n\\033[43m\\\
    033[30mwarning: failed to read \\'\"\n                  << abi::__cxa_demangle(typeid(_Tp).name(),\
    \ 0, 0, 0)\n                  << \"\\'.\\033[0m\\n\\n\";\n      });\n      assert(!once);\n\
    \    }\n    return *this;\n  }\n};\n\ndecltype(auto) cin = static_cast<istream\
    \ &>(std::cin);\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file istream.hpp\n * @brief Input Stream\n */\n\n\
    #include <cxxabi.h>\n\n#include <cassert>\n#include <iostream>\n#include <tuple>\n\
    \n#include \"src/utils/sfinae.hpp\"\n\nnamespace workspace {\n\nnamespace _istream_impl\
    \ {\n\ntemplate <class _Tp, typename = std::nullptr_t> struct istream_helper {\n\
    \  istream_helper(std::istream &__is, _Tp &__x) {\n    if constexpr (has_begin<_Tp>::value)\n\
    \      for (auto &&__e : __x)\n        istream_helper<std::__decay_t<decltype(__e)>>(__is,\
    \ __e);\n    else\n      static_assert(has_begin<_Tp>::value, \"istream unsupported\
    \ type.\");\n  }\n};\n\ntemplate <class _Tp>\nstruct istream_helper<\n    _Tp,\n\
    \    decltype(std::declval<std::__decay_t<decltype(\n                 std::declval<std::istream\
    \ &>() >> std::declval<_Tp &>())>>(),\n             nullptr)> {\n  istream_helper(std::istream\
    \ &__is, _Tp &__x) { __is >> __x; }\n};\n\n#ifdef __SIZEOF_INT128__\n\ntemplate\
    \ <> struct istream_helper<__uint128_t, std::nullptr_t> {\n  istream_helper(std::istream\
    \ &__is, __uint128_t &__x) {\n    std::string __s;\n    __is >> __s;\n    bool\
    \ __neg = false;\n    if (__s.front() == '-') __neg = true, __s.erase(__s.begin());\n\
    \    __x = 0;\n    for (char __d : __s) {\n      __x *= 10;\n      __d -= '0';\n\
    \      if (__neg)\n        __x -= __d;\n      else\n        __x += __d;\n    }\n\
    \  }\n};\n\ntemplate <> struct istream_helper<__int128_t, std::nullptr_t> {\n\
    \  istream_helper(std::istream &__is, __int128_t &__x) {\n    std::string __s;\n\
    \    __is >> __s;\n    bool __neg = false;\n    if (__s.front() == '-') __neg\
    \ = true, __s.erase(__s.begin());\n    __x = 0;\n    for (char __d : __s) {\n\
    \      __x *= 10;\n      __d -= '0';\n      if (__neg)\n        __x -= __d;\n\
    \      else\n        __x += __d;\n    }\n  }\n};\n\n#endif  // INT128\n\ntemplate\
    \ <class T1, class T2> struct istream_helper<std::pair<T1, T2>> {\n  istream_helper(std::istream\
    \ &__is, std::pair<T1, T2> &__x) {\n    istream_helper<T1>(__is, __x.first), istream_helper<T2>(__is,\
    \ __x.second);\n  }\n};\n\ntemplate <class... Tps> struct istream_helper<std::tuple<Tps...>>\
    \ {\n  istream_helper(std::istream &__is, std::tuple<Tps...> &__x) {\n    iterate(__is,\
    \ __x);\n  }\n\n private:\n  template <class _Tp, size_t N = 0>\n  void iterate(std::istream\
    \ &__is, _Tp &__x) {\n    if constexpr (N == std::tuple_size<_Tp>::value)\n  \
    \    return;\n    else\n      istream_helper<typename std::tuple_element<N, _Tp>::type>(\n\
    \          __is, std::get<N>(__x)),\n          iterate<_Tp, N + 1>(__is, __x);\n\
    \  }\n};\n\n}  // namespace _istream_impl\n\n/**\n * @brief A wrapper class for\
    \ std::istream.\n */\nclass istream : public std::istream {\n public:\n  /**\n\
    \   * @brief Wrapped operator.\n   */\n  template <typename _Tp> istream &operator>>(_Tp\
    \ &__x) {\n    _istream_impl::istream_helper<_Tp>(*this, __x);\n    if (std::istream::fail())\
    \ {\n      static auto once = atexit([] {\n        std::cerr << \"\\n\\033[43m\\\
    033[30mwarning: failed to read \\'\"\n                  << abi::__cxa_demangle(typeid(_Tp).name(),\
    \ 0, 0, 0)\n                  << \"\\'.\\033[0m\\n\\n\";\n      });\n      assert(!once);\n\
    \    }\n    return *this;\n  }\n};\n\ndecltype(auto) cin = static_cast<istream\
    \ &>(std::cin);\n\n}  // namespace workspace\n"
  dependsOn:
  - src/utils/sfinae.hpp
  isVerificationFile: false
  path: src/utils/io/istream.hpp
  requiredBy: []
  timestamp: '2021-04-04 23:17:34+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/aizu-online-judge/ITP1_6_D.test.cpp
  - test/aizu-online-judge/ITP1_7_D.test.cpp
  - test/aizu-online-judge/2450.test.cpp
  - test/library-checker/matrix_det.test.cpp
  - test/library-checker/system_of_linear_equations.test.cpp
  - test/library-checker/bitwise_and_convolution.test.cpp
  - test/library-checker/bitwise_xor_convolution.test.cpp
documentation_of: src/utils/io/istream.hpp
layout: document
redirect_from:
- /library/src/utils/io/istream.hpp
- /library/src/utils/io/istream.hpp.html
title: Input Stream
---
