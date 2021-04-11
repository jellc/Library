---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/number_theory/ext_gcd.hpp
    title: Extended Euclidean Algorithm
  - icon: ':heavy_check_mark:'
    path: src/utils/io/ostream.hpp
    title: Output Stream
  - icon: ':question:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_E
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_E
  bundledCode: "#line 1 \"test/aizu-online-judge/NTL_1_E.test.cpp\"\n#define PROBLEM\
    \ \"https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_E\"\n\n#include <iostream>\n\
    \n#line 2 \"src/number_theory/ext_gcd.hpp\"\n\n/**\n * @file ext_gcd.hpp\n * @brief\
    \ Extended Euclidean Algorithm\n */\n\n#include <tuple>\n\n#line 2 \"src/utils/sfinae.hpp\"\
    \n\n/**\n * @file sfinae.hpp\n * @brief SFINAE\n */\n\n#include <cstdint>\n#include\
    \ <iterator>\n#include <type_traits>\n\n#ifndef __INT128_DEFINED__\n\n#ifdef __SIZEOF_INT128__\n\
    #define __INT128_DEFINED__ 1\n#else\n#define __INT128_DEFINED__ 0\n#endif\n\n\
    #endif\n\nnamespace std {\n\n#if __INT128_DEFINED__\n\ntemplate <> struct make_signed<__uint128_t>\
    \ { using type = __int128_t; };\ntemplate <> struct make_signed<__int128_t> {\
    \ using type = __int128_t; };\n\ntemplate <> struct make_unsigned<__uint128_t>\
    \ { using type = __uint128_t; };\ntemplate <> struct make_unsigned<__int128_t>\
    \ { using type = __uint128_t; };\n\ntemplate <> struct is_signed<__uint128_t>\
    \ : std::false_type {};\ntemplate <> struct is_signed<__int128_t> : std::true_type\
    \ {};\n\ntemplate <> struct is_unsigned<__uint128_t> : std::true_type {};\ntemplate\
    \ <> struct is_unsigned<__int128_t> : std::false_type {};\n\n#endif\n\n}  // namespace\
    \ std\n\nnamespace workspace {\n\ntemplate <class Tp, class... Args> struct variadic_front\
    \ { using type = Tp; };\n\ntemplate <class... Args> struct variadic_back;\n\n\
    template <class Tp> struct variadic_back<Tp> { using type = Tp; };\n\ntemplate\
    \ <class Tp, class... Args> struct variadic_back<Tp, Args...> {\n  using type\
    \ = typename variadic_back<Args...>::type;\n};\n\ntemplate <class type, template\
    \ <class> class trait>\nusing enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
    \n/**\n * @brief Return type of subscripting ( @c [] ) access.\n */\ntemplate\
    \ <class _Tp>\nusing subscripted_type =\n    typename std::decay<decltype(std::declval<_Tp&>()[0])>::type;\n\
    \ntemplate <class Container>\nusing element_type = typename std::decay<decltype(\n\
    \    *std::begin(std::declval<Container&>()))>::type;\n\ntemplate <class _Tp,\
    \ class = std::nullptr_t>\nstruct has_begin : std::false_type {};\n\ntemplate\
    \ <class _Tp>\nstruct has_begin<_Tp, decltype(std::begin(std::declval<_Tp>()),\
    \ nullptr)>\n    : std::true_type {};\n\ntemplate <class _Tp, class = std::nullptr_t>\n\
    struct has_mod : std::false_type {};\n\ntemplate <class _Tp>\nstruct has_mod<_Tp,\
    \ decltype(_Tp::mod, nullptr)> : std::true_type {};\n\ntemplate <class _Tp, class\
    \ = void> struct is_integral_ext : std::false_type {};\ntemplate <class _Tp>\n\
    struct is_integral_ext<\n    _Tp, typename std::enable_if<std::is_integral<_Tp>::value>::type>\n\
    \    : std::true_type {};\n\n#if __INT128_DEFINED__\n\ntemplate <> struct is_integral_ext<__int128_t>\
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
    \ multiplicable_uint<_Tp>::type>,\n      _Tp>;\n};\n\n}  // namespace workspace\n\
    #line 11 \"src/number_theory/ext_gcd.hpp\"\n\nnamespace workspace {\n\n/**\n *\
    \ @param __a Integer\n * @param __b Integer\n * @return Pair of integers (x, y)\
    \ s.t. ax + by = g = gcd(a, b), 0 <= x <\n * |b/g|, -|a/g| < y <= 0. Return (0,\
    \ 0) if (a, b) = (0, 0).\n */\ntemplate <typename _T1, typename _T2> constexpr\
    \ auto ext_gcd(_T1 __a, _T2 __b) {\n  static_assert(is_integral_ext<_T1>::value);\n\
    \  static_assert(is_integral_ext<_T2>::value);\n\n  using result_type = typename\
    \ std::make_signed<\n      typename std::common_type<_T1, _T2>::type>::type;\n\
    \n  result_type a{__a}, b{__b}, p{1}, q{}, r{}, s{1};\n\n  // Euclidean algorithm\n\
    \  while (b) {\n    result_type t = a / b;\n    r ^= p ^= r ^= p -= t * r;\n \
    \   s ^= q ^= s ^= q -= t * s;\n    b ^= a ^= b ^= a -= t * b;\n  }\n\n  // Normalize\n\
    \  if (a < 0) p = -p, q = -q;\n  if (p < 0) p += __b / a, q -= __a / a;\n\n  return\
    \ std::make_pair(p, q);\n}\n\n}  // namespace workspace\n#line 2 \"src/utils/io/ostream.hpp\"\
    \n\n/**\n * @file ostream.hpp\n * @brief Output Stream\n */\n\n#line 9 \"src/utils/io/ostream.hpp\"\
    \n\nnamespace workspace {\n\ntemplate <class _Os> struct is_ostream {\n  template\
    \ <typename... _Args>\n  static std::true_type __test(std::basic_ostream<_Args...>\
    \ *);\n\n  static std::false_type __test(void *);\n\n  constexpr static bool value\
    \ = decltype(__test(std::declval<_Os *>()))::value;\n};\n\ntemplate <class _Os>\n\
    using ostream_ref =\n    typename std::enable_if<is_ostream<_Os>::value, _Os &>::type;\n\
    \n/**\n * @brief Stream insertion operator for C-style array.\n *\n * @param __os\
    \ Output stream\n * @param __a Array\n * @return Reference to __os.\n */\ntemplate\
    \ <class _Os, class _Tp, size_t _Nm>\ntypename std::enable_if<bool(sizeof(_Tp)\
    \ > 2), ostream_ref<_Os>>::type\noperator<<(_Os &__os, const _Tp (&__a)[_Nm])\
    \ {\n  if constexpr (_Nm) {\n    __os << *__a;\n    for (auto __i = __a + 1, __e\
    \ = __a + _Nm; __i != __e; ++__i)\n      __os << ' ' << *__i;\n  }\n  return __os;\n\
    }\n\n/**\n * @brief Stream insertion operator for std::array.\n *\n * @param __os\
    \ Output stream\n * @param __a Array\n * @return Reference to __os.\n */\ntemplate\
    \ <class _Os, class _Tp, size_t _Nm>\nostream_ref<_Os> operator<<(_Os &__os, const\
    \ std::array<_Tp, _Nm> &__a) {\n  if constexpr (_Nm) {\n    __os << __a[0];\n\
    \    for (size_t __i = 1; __i != _Nm; ++__i) __os << ' ' << __a[__i];\n  }\n \
    \ return __os;\n}\n\n/**\n * @brief Stream insertion operator for std::pair.\n\
    \ *\n * @param __os Output stream\n * @param __p Pair\n * @return Reference to\
    \ __os.\n */\ntemplate <class _Os, class _T1, class _T2>\nostream_ref<_Os> operator<<(_Os\
    \ &__os, const std::pair<_T1, _T2> &__p) {\n  return __os << __p.first << ' '\
    \ << __p.second;\n}\n\n/**\n * @brief Stream insertion operator for std::tuple.\n\
    \ *\n * @param __os Output stream\n * @param __t Tuple\n * @return Reference to\
    \ __os.\n */\ntemplate <class _Os, class _Tp, size_t _Nm = 0>\ntypename std::enable_if<bool(std::tuple_size<_Tp>::value\
    \ + 1),\n                        ostream_ref<_Os>>::type\noperator<<(_Os &__os,\
    \ const _Tp &__t) {\n  if constexpr (_Nm != std::tuple_size<_Tp>::value) {\n \
    \   if constexpr (_Nm) __os << ' ';\n    __os << std::get<_Nm>(__t);\n    operator<<<_Os,\
    \ _Tp, _Nm + 1>(__os, __t);\n  }\n  return __os;\n}\n\ntemplate <class _Os, class\
    \ _Container,\n          typename = decltype(std::begin(std::declval<_Container>()))>\n\
    typename std::enable_if<\n    !std::is_same<std::decay_t<_Container>, std::string>::value\
    \ &&\n        !std::is_same<std::decay_t<_Container>, char *>::value,\n    ostream_ref<_Os>>::type\n\
    operator<<(_Os &__os, const _Container &__cont) {\n  bool __h = true;\n  for (auto\
    \ &&__e : __cont) __h ? __h = 0 : (__os << ' ', 0), __os << __e;\n  return __os;\n\
    }\n\n#ifdef __SIZEOF_INT128__\n\n/**\n * @brief Stream insertion operator for\
    \ __int128_t.\n *\n * @param __os Output Stream\n * @param __x 128-bit integer\n\
    \ * @return Reference to __os.\n */\ntemplate <class _Os> ostream_ref<_Os> operator<<(_Os\
    \ &__os, __int128_t __x) {\n  if (!__x) return __os << '0';\n  if (__x < 0) __os\
    \ << '-';\n  char __s[40], *__p = __s;\n  while (__x) {\n    auto __d = __x %\
    \ 10;\n    *__p++ = '0' + (__x < 0 ? -__d : __d);\n    __x /= 10;\n  }\n  *__p\
    \ = 0;\n  for (char *__t = __s; __t < --__p; ++__t) *__t ^= *__p ^= *__t ^= *__p;\n\
    \  return __os << __s;\n}\n\n/**\n * @brief Stream insertion operator for __uint128_t.\n\
    \ *\n * @param __os Output Stream\n * @param __x 128-bit unsigned integer\n *\
    \ @return Reference to __os.\n */\ntemplate <class _Os> ostream_ref<_Os> operator<<(_Os\
    \ &__os, __uint128_t __x) {\n  if (!__x) return __os << '0';\n  char __s[40],\
    \ *__p = __s;\n  while (__x) *__p++ = '0' + __x % 10, __x /= 10;\n  *__p = 0;\n\
    \  for (char *__t = __s; __t < --__p; ++__t) *__t ^= *__p ^= *__t ^= *__p;\n \
    \ return __os << __s;\n}\n\n#endif\n\n}  // namespace workspace\n#line 7 \"test/aizu-online-judge/NTL_1_E.test.cpp\"\
    \n\nint main() {\n  using namespace workspace;\n  int a, b;\n  std::cin >> a >>\
    \ b;\n  __int128_t _a = a;\n  auto [x, y] = ext_gcd(_a, b);\n  if (x > 0) x -=\
    \ b, y += a;\n  if ((y - x) * 2 > a + b) x += b, y -= a;\n  a = x, b = y;\n  std::cout\
    \ << std::tie(a, b) << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_E\"\n\n\
    #include <iostream>\n\n#include \"src/number_theory/ext_gcd.hpp\"\n#include \"\
    src/utils/io/ostream.hpp\"\n\nint main() {\n  using namespace workspace;\n  int\
    \ a, b;\n  std::cin >> a >> b;\n  __int128_t _a = a;\n  auto [x, y] = ext_gcd(_a,\
    \ b);\n  if (x > 0) x -= b, y += a;\n  if ((y - x) * 2 > a + b) x += b, y -= a;\n\
    \  a = x, b = y;\n  std::cout << std::tie(a, b) << \"\\n\";\n}\n"
  dependsOn:
  - src/number_theory/ext_gcd.hpp
  - src/utils/sfinae.hpp
  - src/utils/io/ostream.hpp
  isVerificationFile: true
  path: test/aizu-online-judge/NTL_1_E.test.cpp
  requiredBy: []
  timestamp: '2021-04-11 21:05:14+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aizu-online-judge/NTL_1_E.test.cpp
layout: document
redirect_from:
- /verify/test/aizu-online-judge/NTL_1_E.test.cpp
- /verify/test/aizu-online-judge/NTL_1_E.test.cpp.html
title: test/aizu-online-judge/NTL_1_E.test.cpp
---
