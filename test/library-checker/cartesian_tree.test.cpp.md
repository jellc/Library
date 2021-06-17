---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/data_structure/cartesian_tree.hpp
    title: Cartesian Tree
  - icon: ':heavy_check_mark:'
    path: src/utils/io/istream.hpp
    title: Input Stream
  - icon: ':heavy_check_mark:'
    path: src/utils/io/ostream.hpp
    title: Output Stream
  - icon: ':heavy_check_mark:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/cartesian_tree
    links:
    - https://judge.yosupo.jp/problem/cartesian_tree
  bundledCode: "#line 1 \"test/library-checker/cartesian_tree.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/cartesian_tree\"\n\n#include <algorithm>\n\
    \n#line 2 \"src/data_structure/cartesian_tree.hpp\"\n\n/**\n * @file cartesian_tree.hpp\n\
    \ * @brief Cartesian Tree\n */\n\n#include <vector>\n\nnamespace workspace {\n\
    \n/**\n * @brief Cartesian Tree.\n */\ntemplate <class _Iterator>\nauto Cartesian_tree(_Iterator\
    \ __first, _Iterator __last) noexcept {\n  std::vector<std::size_t> __p;\n  std::vector<_Iterator>\
    \ __it;\n\n  for (std::size_t __i = 0, __j = -1; __first != __last;\n       __p.emplace_back(__j),\
    \ __j = __i++, __it.emplace_back(__first++)) {\n    std::size_t __k = -1;\n  \
    \  while (~__j && *__first < *__it[__j]) __k = __j, __j = __p[__j];\n    if (~__k)\
    \ __p[__k] = __i;\n  }\n\n  return __p;\n}\n\n/**\n * @brief Cartesian Tree.\n\
    \ */\ntemplate <class _Iterator, class _Compare>\nauto Cartesian_tree(_Iterator\
    \ __first, _Iterator __last,\n                    _Compare __comp) noexcept {\n\
    \  std::vector<std::size_t> __p;\n  std::vector<_Iterator> __it;\n\n  for (std::size_t\
    \ __i = 0, __j = -1; __first != __last;\n       __p.emplace_back(__j), __j = __i++,\
    \ __it.emplace_back(__first++)) {\n    std::size_t __k = -1;\n    while (~__j\
    \ && __comp(*__first, *__it[__j])) __k = __j, __j = __p[__j];\n    if (~__k) __p[__k]\
    \ = __i;\n  }\n\n  return __p;\n}\n\n}  // namespace workspace\n#line 2 \"src/utils/io/istream.hpp\"\
    \n\n/**\n * @file istream.hpp\n * @brief Input Stream\n */\n\n#include <cxxabi.h>\n\
    \n#include <cassert>\n#include <iostream>\n#include <tuple>\n\n#line 2 \"lib/cxx17\"\
    \n\n#ifndef _CXX17_CONSTEXPR\n#if __cplusplus >= 201703L\n#define _CXX17_CONSTEXPR\
    \ constexpr\n#else\n#define _CXX17_CONSTEXPR\n#endif\n#endif\n#line 2 \"src/utils/sfinae.hpp\"\
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
    \n}  // namespace workspace\n#line 2 \"src/utils/io/ostream.hpp\"\n\n/**\n * @file\
    \ ostream.hpp\n * @brief Output Stream\n */\n\n#line 9 \"src/utils/io/ostream.hpp\"\
    \n\n#line 11 \"src/utils/io/ostream.hpp\"\n\nnamespace workspace {\n\ntemplate\
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
    \ return __os << __s;\n}\n\n#endif\n\n}  // namespace workspace\n#line 8 \"test/library-checker/cartesian_tree.test.cpp\"\
    \n\nint main() {\n  using namespace workspace;\n\n  int n;\n  cin >> n;\n  std::vector<int>\
    \ a(n);\n  cin >> a;\n  auto ans = Cartesian_tree(a.begin(), a.end());\n  auto\
    \ r = std::find(ans.begin(), ans.end(), -1);\n  *r = r - ans.begin();\n  std::cout\
    \ << ans << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/cartesian_tree\"\n\n#include\
    \ <algorithm>\n\n#include \"src/data_structure/cartesian_tree.hpp\"\n#include\
    \ \"src/utils/io/istream.hpp\"\n#include \"src/utils/io/ostream.hpp\"\n\nint main()\
    \ {\n  using namespace workspace;\n\n  int n;\n  cin >> n;\n  std::vector<int>\
    \ a(n);\n  cin >> a;\n  auto ans = Cartesian_tree(a.begin(), a.end());\n  auto\
    \ r = std::find(ans.begin(), ans.end(), -1);\n  *r = r - ans.begin();\n  std::cout\
    \ << ans << \"\\n\";\n}\n"
  dependsOn:
  - src/data_structure/cartesian_tree.hpp
  - src/utils/io/istream.hpp
  - src/utils/sfinae.hpp
  - src/utils/io/ostream.hpp
  isVerificationFile: true
  path: test/library-checker/cartesian_tree.test.cpp
  requiredBy: []
  timestamp: '2021-06-17 15:39:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/cartesian_tree.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/cartesian_tree.test.cpp
- /verify/test/library-checker/cartesian_tree.test.cpp.html
title: test/library-checker/cartesian_tree.test.cpp
---
