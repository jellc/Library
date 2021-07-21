---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/combinatorics/factorial.hpp
    title: Factorial
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/DPL_5_D.test.cpp
    title: test/aizu-online-judge/DPL_5_D.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Binomial Coefficient
    links: []
  bundledCode: "#line 2 \"src/combinatorics/binomial.hpp\"\n\n/**\n * @file binomial.hpp\n\
    \ * @brief Binomial Coefficient\n */\n\n#include <cassert>\n\n#line 2 \"src/combinatorics/factorial.hpp\"\
    \n\n/**\n * @file factorial.hpp\n * @brief Factorial\n */\n\n#include <vector>\n\
    \nnamespace workspace {\n\n// Factorial\ntemplate <class _Tp, class _X> _Tp factorial(_X\
    \ __x) noexcept {\n  if (__x < 0) return 0;\n  static std::vector<_Tp> __t{1};\n\
    \  static size_t __i = (__t.reserve(0x1000000), 0);\n  while (__i < size_t(__x))\
    \ __t.emplace_back(__t.back() * _Tp(++__i));\n  return __t[__x];\n}\n\n// Inverse\
    \ of factorial\ntemplate <class _Tp, class _X> _Tp inverse_factorial(_X __x) noexcept\
    \ {\n  if (__x < 0) return 0;\n  static std::vector<_Tp> __t{1};\n  static size_t\
    \ __i = (__t.reserve(0x1000000), 0);\n  while (__i < size_t(__x)) __t.emplace_back(__t.back()\
    \ / _Tp(++__i));\n  return __t[__x];\n}\n\n}  // namespace workspace\n#line 11\
    \ \"src/combinatorics/binomial.hpp\"\n\nnamespace workspace {\n\nnamespace _binom_impl\
    \ {\n\nstruct _binom_table {\n  constexpr static int size = 132;\n  __uint128_t\
    \ __b[size][size]{1};\n\n  constexpr _binom_table() noexcept {\n    for (int __i\
    \ = 1; __i != size; ++__i)\n      for (int __j = 0; __j != __i; ++__j)\n     \
    \   __b[__i][__j] += __b[__i - 1][__j],\n            __b[__i][__j + 1] += __b[__i\
    \ - 1][__j];\n  }\n\n  constexpr auto operator()(int __x, int __y) const noexcept\
    \ {\n    return __x < 0 || __x < __y ? 0 : (assert(__x < size), __b[__x][__y]);\n\
    \  }\n};\n\nconstexpr _binom_table table;\n\n}  // namespace _binom_impl\n\n/**\n\
    \ * @brief Binomial coefficient for integer args. Be careful with overflow.\n\
    \ */\ntemplate <class _Tp, class _X, class _Y>\nconstexpr _Tp binomial(_X __x,\
    \ _Y __y) {\n  if constexpr (is_integral_ext<_Tp>::value)\n    return _binom_impl::table(__x,\
    \ __y);\n\n  if (__y < 0 || __x < __y) return 0;\n\n  return factorial<_Tp>(__x)\
    \ * inverse_factorial<_Tp>(__y) *\n         inverse_factorial<_Tp>(__x - __y);\n\
    }\n\n/**\n * @brief Catalan number.\n */\ntemplate <class _Tp, class _X> constexpr\
    \ _Tp catalan(_X __x) {\n  return __x < 0\n             ? _Tp(0)\n           \
    \  : binomial<_Tp>(__x << 1, __x) - binomial<_Tp>(__x << 1, __x + 1);\n}\n\n}\
    \  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file binomial.hpp\n * @brief Binomial Coefficient\n\
    \ */\n\n#include <cassert>\n\n#include \"factorial.hpp\"\n\nnamespace workspace\
    \ {\n\nnamespace _binom_impl {\n\nstruct _binom_table {\n  constexpr static int\
    \ size = 132;\n  __uint128_t __b[size][size]{1};\n\n  constexpr _binom_table()\
    \ noexcept {\n    for (int __i = 1; __i != size; ++__i)\n      for (int __j =\
    \ 0; __j != __i; ++__j)\n        __b[__i][__j] += __b[__i - 1][__j],\n       \
    \     __b[__i][__j + 1] += __b[__i - 1][__j];\n  }\n\n  constexpr auto operator()(int\
    \ __x, int __y) const noexcept {\n    return __x < 0 || __x < __y ? 0 : (assert(__x\
    \ < size), __b[__x][__y]);\n  }\n};\n\nconstexpr _binom_table table;\n\n}  //\
    \ namespace _binom_impl\n\n/**\n * @brief Binomial coefficient for integer args.\
    \ Be careful with overflow.\n */\ntemplate <class _Tp, class _X, class _Y>\nconstexpr\
    \ _Tp binomial(_X __x, _Y __y) {\n  if constexpr (is_integral_ext<_Tp>::value)\n\
    \    return _binom_impl::table(__x, __y);\n\n  if (__y < 0 || __x < __y) return\
    \ 0;\n\n  return factorial<_Tp>(__x) * inverse_factorial<_Tp>(__y) *\n       \
    \  inverse_factorial<_Tp>(__x - __y);\n}\n\n/**\n * @brief Catalan number.\n */\n\
    template <class _Tp, class _X> constexpr _Tp catalan(_X __x) {\n  return __x <\
    \ 0\n             ? _Tp(0)\n             : binomial<_Tp>(__x << 1, __x) - binomial<_Tp>(__x\
    \ << 1, __x + 1);\n}\n\n}  // namespace workspace\n"
  dependsOn:
  - src/combinatorics/factorial.hpp
  isVerificationFile: false
  path: src/combinatorics/binomial.hpp
  requiredBy: []
  timestamp: '2021-07-22 00:37:02+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aizu-online-judge/DPL_5_D.test.cpp
documentation_of: src/combinatorics/binomial.hpp
layout: document
redirect_from:
- /library/src/combinatorics/binomial.hpp
- /library/src/combinatorics/binomial.hpp.html
title: Binomial Coefficient
---
