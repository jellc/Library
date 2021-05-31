---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/subset_convolution.test.cpp
    title: test/library-checker/subset_convolution.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Subset Convolution
    links: []
  bundledCode: "#line 2 \"src/algebra/convolution/subset.hpp\"\n\n/*\n * @brief Subset\
    \ Convolution\n */\n\n#include <cassert>\n#include <vector>\n\n#line 2 \"lib/bit\"\
    \n\n#if __cplusplus > 201703L\n\n#include <bit>\n\n#elif __cplusplus > 201402L\n\
    \n#ifndef _GLIBCXX_BIT\n#define _GLIBCXX_BIT 1\n\n#include <limits>\n#include\
    \ <type_traits>\n\nnamespace std {\n\ntemplate <typename _Tp> constexpr int __countl_zero(_Tp\
    \ __x) noexcept {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n\n  if\
    \ (__x == 0) return _Nd;\n\n  constexpr auto _Nd_ull = numeric_limits<unsigned\
    \ long long>::digits;\n  constexpr auto _Nd_ul = numeric_limits<unsigned long>::digits;\n\
    \  constexpr auto _Nd_u = numeric_limits<unsigned>::digits;\n\n  if _GLIBCXX17_CONSTEXPR\
    \ (_Nd <= _Nd_u) {\n    constexpr int __diff = _Nd_u - _Nd;\n    return __builtin_clz(__x)\
    \ - __diff;\n  } else if _GLIBCXX17_CONSTEXPR (_Nd <= _Nd_ul) {\n    constexpr\
    \ int __diff = _Nd_ul - _Nd;\n    return __builtin_clzl(__x) - __diff;\n  } else\
    \ if _GLIBCXX17_CONSTEXPR (_Nd <= _Nd_ull) {\n    constexpr int __diff = _Nd_ull\
    \ - _Nd;\n    return __builtin_clzll(__x) - __diff;\n  } else  // (_Nd > _Nd_ull)\n\
    \  {\n    static_assert(_Nd <= (2 * _Nd_ull),\n                  \"Maximum supported\
    \ integer size is 128-bit\");\n\n    unsigned long long __high = __x >> _Nd_ull;\n\
    \    if (__high != 0) {\n      constexpr int __diff = (2 * _Nd_ull) - _Nd;\n \
    \     return __builtin_clzll(__high) - __diff;\n    }\n    constexpr auto __max_ull\
    \ = numeric_limits<unsigned long long>::max();\n    unsigned long long __low =\
    \ __x & __max_ull;\n    return (_Nd - _Nd_ull) + __builtin_clzll(__low);\n  }\n\
    }\n\ntemplate <typename _Tp> constexpr int __countr_zero(_Tp __x) noexcept {\n\
    \  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n\n  if (__x == 0) return\
    \ _Nd;\n\n  constexpr auto _Nd_ull = numeric_limits<unsigned long long>::digits;\n\
    \  constexpr auto _Nd_ul = numeric_limits<unsigned long>::digits;\n  constexpr\
    \ auto _Nd_u = numeric_limits<unsigned>::digits;\n\n  if _GLIBCXX17_CONSTEXPR\
    \ (_Nd <= _Nd_u)\n    return __builtin_ctz(__x);\n  else if _GLIBCXX17_CONSTEXPR\
    \ (_Nd <= _Nd_ul)\n    return __builtin_ctzl(__x);\n  else if _GLIBCXX17_CONSTEXPR\
    \ (_Nd <= _Nd_ull)\n    return __builtin_ctzll(__x);\n  else  // (_Nd > _Nd_ull)\n\
    \  {\n    static_assert(_Nd <= (2 * _Nd_ull),\n                  \"Maximum supported\
    \ integer size is 128-bit\");\n\n    constexpr auto __max_ull = numeric_limits<unsigned\
    \ long long>::max();\n    unsigned long long __low = __x & __max_ull;\n    if\
    \ (__low != 0) return __builtin_ctzll(__low);\n    unsigned long long __high =\
    \ __x >> _Nd_ull;\n    return __builtin_ctzll(__high) + _Nd_ull;\n  }\n}\n\ntemplate\
    \ <typename _Tp> constexpr int __popcount(_Tp __x) noexcept {\n  constexpr auto\
    \ _Nd = numeric_limits<_Tp>::digits;\n\n  if (__x == 0) return 0;\n\n  constexpr\
    \ auto _Nd_ull = numeric_limits<unsigned long long>::digits;\n  constexpr auto\
    \ _Nd_ul = numeric_limits<unsigned long>::digits;\n  constexpr auto _Nd_u = numeric_limits<unsigned>::digits;\n\
    \n  if _GLIBCXX17_CONSTEXPR (_Nd <= _Nd_u)\n    return __builtin_popcount(__x);\n\
    \  else if _GLIBCXX17_CONSTEXPR (_Nd <= _Nd_ul)\n    return __builtin_popcountl(__x);\n\
    \  else if _GLIBCXX17_CONSTEXPR (_Nd <= _Nd_ull)\n    return __builtin_popcountll(__x);\n\
    \  else  // (_Nd > _Nd_ull)\n  {\n    static_assert(_Nd <= (2 * _Nd_ull),\n  \
    \                \"Maximum supported integer size is 128-bit\");\n\n    constexpr\
    \ auto __max_ull = numeric_limits<unsigned long long>::max();\n    unsigned long\
    \ long __low = __x & __max_ull;\n    unsigned long long __high = __x >> _Nd_ull;\n\
    \    return __builtin_popcountll(__low) + __builtin_popcountll(__high);\n  }\n\
    }\n\ntemplate <typename _Tp> constexpr _Tp __bit_ceil(_Tp __x) noexcept {\n  constexpr\
    \ auto _Nd = numeric_limits<_Tp>::digits;\n  if (__x == 0 || __x == 1) return\
    \ 1;\n  auto __shift_exponent = _Nd - __countl_zero((_Tp)(__x - 1u));\n#ifdef\
    \ _GLIBCXX_HAVE_BUILTIN_IS_CONSTANT_EVALUATED\n  if (!__builtin_is_constant_evaluated())\
    \ {\n    __glibcxx_assert(__shift_exponent != numeric_limits<_Tp>::digits);\n\
    \  }\n#endif\n  using __promoted_type = decltype(__x << 1);\n  if _GLIBCXX17_CONSTEXPR\
    \ (!is_same<__promoted_type, _Tp>::value) {\n    const int __extra_exp = sizeof(__promoted_type)\
    \ / sizeof(_Tp) / 2;\n    __shift_exponent |= (__shift_exponent & _Nd) << __extra_exp;\n\
    \  }\n  return (_Tp)1u << __shift_exponent;\n}\n\ntemplate <typename _Tp> constexpr\
    \ _Tp __bit_floor(_Tp __x) noexcept {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n\
    \  if (__x == 0) return 0;\n  return (_Tp)1u << (_Nd - __countl_zero((_Tp)(__x\
    \ >> 1)));\n}\n\ntemplate <typename _Tp> constexpr _Tp __bit_width(_Tp __x) noexcept\
    \ {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n  return _Nd - __countl_zero(__x);\n\
    }\n\n}  // namespace std\n\n#endif\n\n#endif\n#line 11 \"src/algebra/convolution/subset.hpp\"\
    \n\nnamespace workspace {\n\ntemplate <class A> A subset_conv(const A &f, const\
    \ A &g) {\n  const size_t len = std::__bit_floor(std::size(f));\n  const size_t\
    \ n = std::__countr_zero(len);\n\n  std::vector<A> ff(n + 1, A(len)), gg(ff);\n\
    \  ff[0] = f, gg[0] = g;\n\n  for (size_t k = 0; k != n; ++k)\n    for (size_t\
    \ i = k + 1; ~i; --i)\n      for (size_t s = 0; s != len; ++s)\n        if (s\
    \ >> k & 1) {\n          if (i)\n            ff[i][s] = ff[i - 1][s], gg[i][s]\
    \ = gg[i - 1][s];\n          else\n            ff[i][s] = gg[i][s] = {};\n   \
    \       ff[i][s] += ff[i][s ^ 1 << k];\n          gg[i][s] += gg[i][s ^ 1 << k];\n\
    \        }\n\n  for (size_t i = n; ~i; --i)\n    for (size_t s = 0; s != len;\
    \ ++s) {\n      ff[i][s] *= gg[0][s];\n      for (size_t j = i; j; --j) ff[i][s]\
    \ += ff[i - j][s] * gg[j][s];\n    }\n\n  for (size_t k = n - 1; ~k; --k)\n  \
    \  for (size_t s = 0; s != len; ++s)\n      if (~s >> k & 1)\n        for (size_t\
    \ i = n; ~i; --i) {\n          ff[i][s ^ 1 << k] -= ff[i][s];\n          if (i)\
    \ ff[i][s] = ff[i - 1][s];\n        }\n\n  return ff[n];\n}\n\n}  // namespace\
    \ workspace\n"
  code: "#pragma once\n\n/*\n * @brief Subset Convolution\n */\n\n#include <cassert>\n\
    #include <vector>\n\n#include \"lib/bit\"\n\nnamespace workspace {\n\ntemplate\
    \ <class A> A subset_conv(const A &f, const A &g) {\n  const size_t len = std::__bit_floor(std::size(f));\n\
    \  const size_t n = std::__countr_zero(len);\n\n  std::vector<A> ff(n + 1, A(len)),\
    \ gg(ff);\n  ff[0] = f, gg[0] = g;\n\n  for (size_t k = 0; k != n; ++k)\n    for\
    \ (size_t i = k + 1; ~i; --i)\n      for (size_t s = 0; s != len; ++s)\n     \
    \   if (s >> k & 1) {\n          if (i)\n            ff[i][s] = ff[i - 1][s],\
    \ gg[i][s] = gg[i - 1][s];\n          else\n            ff[i][s] = gg[i][s] =\
    \ {};\n          ff[i][s] += ff[i][s ^ 1 << k];\n          gg[i][s] += gg[i][s\
    \ ^ 1 << k];\n        }\n\n  for (size_t i = n; ~i; --i)\n    for (size_t s =\
    \ 0; s != len; ++s) {\n      ff[i][s] *= gg[0][s];\n      for (size_t j = i; j;\
    \ --j) ff[i][s] += ff[i - j][s] * gg[j][s];\n    }\n\n  for (size_t k = n - 1;\
    \ ~k; --k)\n    for (size_t s = 0; s != len; ++s)\n      if (~s >> k & 1)\n  \
    \      for (size_t i = n; ~i; --i) {\n          ff[i][s ^ 1 << k] -= ff[i][s];\n\
    \          if (i) ff[i][s] = ff[i - 1][s];\n        }\n\n  return ff[n];\n}\n\n\
    }  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/algebra/convolution/subset.hpp
  requiredBy: []
  timestamp: '2021-05-31 22:43:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/subset_convolution.test.cpp
documentation_of: src/algebra/convolution/subset.hpp
layout: document
redirect_from:
- /library/src/algebra/convolution/subset.hpp
- /library/src/algebra/convolution/subset.hpp.html
title: Subset Convolution
---
