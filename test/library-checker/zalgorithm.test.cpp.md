---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/string/z_algorithm.hpp
    title: Z-Algorithm
  - icon: ':heavy_check_mark:'
    path: src/utils/io/ostream.hpp
    title: Output Stream
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/zalgorithm
    links:
    - https://judge.yosupo.jp/problem/zalgorithm
  bundledCode: "#line 1 \"test/library-checker/zalgorithm.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/zalgorithm\"\n\n#include <iostream>\n\n#line\
    \ 2 \"src/string/z_algorithm.hpp\"\n\n/**\n * @file z_algorithm.hpp\n * @brief\
    \ Z-Algorithm\n * @date 2021-01-08\n */\n\n#include <string>\n#include <vector>\n\
    \nnamespace workspace {\n\n/**\n * @brief Construct Z-array in linear time.\n\
    \ * @param __s A string\n * @return The i-th element (0-indexed) is the length\
    \ of the Longest Common\n * Prefix between __s and __s[i:].\n */\ntemplate <class\
    \ _Str> std::vector<size_t> z_algorithm(_Str const &__s) {\n  std::vector<size_t>\
    \ __z(__s.size());\n  if (!__z.empty()) {\n    for (size_t __i{1}, __j{0}; __i\
    \ != __s.size(); ++__i) {\n      if (__z[__i - __j] + __i < __z[__j] + __j) {\n\
    \        __z[__i] = __z[__i - __j];\n      } else {\n        size_t __k{__z[__j]\
    \ + __j > __i ? __z[__j] + __j - __i : 0};\n        while (__k + __i < __s.size()\
    \ && __s[__k] == __s[__k + __i]) ++__k;\n        __z[__i] = __k;\n        __j\
    \ = __i;\n      }\n    }\n    __z.front() = __s.size();\n  }\n  return __z;\n\
    }\n\n}  // namespace workspace\n#line 2 \"src/utils/io/ostream.hpp\"\n\n/**\n\
    \ * @file ostream.hpp\n * @brief Output Stream\n */\n\n#include <tuple>\n\nnamespace\
    \ workspace {\n\ntemplate <class _Os> struct is_ostream {\n  template <typename...\
    \ _Args>\n  static std::true_type __test(std::basic_ostream<_Args...> *);\n\n\
    \  static std::false_type __test(void *);\n\n  constexpr static bool value = decltype(__test(std::declval<_Os\
    \ *>()))::value;\n};\n\ntemplate <class _Os>\nusing ostream_ref =\n    typename\
    \ std::enable_if<is_ostream<_Os>::value, _Os &>::type;\n\n/**\n * @brief Stream\
    \ insertion operator for C-style array.\n *\n * @param __os Output stream\n *\
    \ @param __a Array\n * @return Reference to __os.\n */\ntemplate <class _Os, class\
    \ _Tp, size_t _Nm>\ntypename std::enable_if<bool(sizeof(_Tp) > 2), ostream_ref<_Os>>::type\n\
    operator<<(_Os &__os, const _Tp (&__a)[_Nm]) {\n  if constexpr (_Nm) {\n    __os\
    \ << *__a;\n    for (auto __i = __a + 1, __e = __a + _Nm; __i != __e; ++__i)\n\
    \      __os << ' ' << *__i;\n  }\n  return __os;\n}\n\n/**\n * @brief Stream insertion\
    \ operator for std::array.\n *\n * @param __os Output stream\n * @param __a Array\n\
    \ * @return Reference to __os.\n */\ntemplate <class _Os, class _Tp, size_t _Nm>\n\
    ostream_ref<_Os> operator<<(_Os &__os, const std::array<_Tp, _Nm> &__a) {\n  if\
    \ constexpr (_Nm) {\n    __os << __a[0];\n    for (size_t __i = 1; __i != _Nm;\
    \ ++__i) __os << ' ' << __a[__i];\n  }\n  return __os;\n}\n\n/**\n * @brief Stream\
    \ insertion operator for std::pair.\n *\n * @param __os Output stream\n * @param\
    \ __p Pair\n * @return Reference to __os.\n */\ntemplate <class _Os, class _T1,\
    \ class _T2>\nostream_ref<_Os> operator<<(_Os &__os, const std::pair<_T1, _T2>\
    \ &__p) {\n  return __os << __p.first << ' ' << __p.second;\n}\n\n/**\n * @brief\
    \ Stream insertion operator for std::tuple.\n *\n * @param __os Output stream\n\
    \ * @param __t Tuple\n * @return Reference to __os.\n */\ntemplate <class _Os,\
    \ class _Tp, size_t _Nm = 0>\ntypename std::enable_if<bool(std::tuple_size<_Tp>::value\
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
    \ return __os << __s;\n}\n\n#endif\n\n}  // namespace workspace\n#line 7 \"test/library-checker/zalgorithm.test.cpp\"\
    \n\nint main() {\n  using namespace workspace;\n  std::string s;\n  std::cin >>\
    \ s;\n  std::cout << z_algorithm(s) << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/zalgorithm\"\n\n#include\
    \ <iostream>\n\n#include \"src/string/z_algorithm.hpp\"\n#include \"src/utils/io/ostream.hpp\"\
    \n\nint main() {\n  using namespace workspace;\n  std::string s;\n  std::cin >>\
    \ s;\n  std::cout << z_algorithm(s) << \"\\n\";\n}\n"
  dependsOn:
  - src/string/z_algorithm.hpp
  - src/utils/io/ostream.hpp
  isVerificationFile: true
  path: test/library-checker/zalgorithm.test.cpp
  requiredBy: []
  timestamp: '2021-04-04 23:33:06+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/zalgorithm.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/zalgorithm.test.cpp
- /verify/test/library-checker/zalgorithm.test.cpp.html
title: test/library-checker/zalgorithm.test.cpp
---
