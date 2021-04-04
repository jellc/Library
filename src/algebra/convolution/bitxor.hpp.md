---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/library-checker/bitwise_xor_convolution.test.cpp
    title: test/library-checker/bitwise_xor_convolution.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: Bitwise Xor Convolution
    links: []
  bundledCode: "#line 2 \"src/algebra/convolution/bitxor.hpp\"\n\n/**\n * @file bitxor.hpp\n\
    \ * @brief Bitwise Xor Convolution\n * @date 2021-01-08\n */\n\n#include <iterator>\n\
    \n#line 2 \"lib/bit\"\n\n#if __cplusplus > 201703L\n\n#include <bit>\n\n#else\n\
    \n#ifndef _GLIBCXX_BIT\n#define _GLIBCXX_BIT 1\n\n#include <limits>\n#include\
    \ <type_traits>\n\nnamespace std {\n\ntemplate <typename _Tp> constexpr _Tp __rotl(_Tp\
    \ __x, int __s) noexcept {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n\
    \  const int __r = __s % _Nd;\n  if (__r == 0)\n    return __x;\n  else if (__r\
    \ > 0)\n    return (__x << __r) | (__x >> ((_Nd - __r) % _Nd));\n  else\n    return\
    \ (__x >> -__r) | (__x << ((_Nd + __r) % _Nd));  // rotr(x, -r)\n}\n\ntemplate\
    \ <typename _Tp> constexpr _Tp __rotr(_Tp __x, int __s) noexcept {\n  constexpr\
    \ auto _Nd = numeric_limits<_Tp>::digits;\n  const int __r = __s % _Nd;\n  if\
    \ (__r == 0)\n    return __x;\n  else if (__r > 0)\n    return (__x >> __r) |\
    \ (__x << ((_Nd - __r) % _Nd));\n  else\n    return (__x << -__r) | (__x >> ((_Nd\
    \ + __r) % _Nd));  // rotl(x, -r)\n}\n\ntemplate <typename _Tp> constexpr int\
    \ __countl_zero(_Tp __x) noexcept {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n\
    \n  if (__x == 0) return _Nd;\n\n  constexpr auto _Nd_ull = numeric_limits<unsigned\
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
    }\n\ntemplate <typename _Tp> constexpr int __countl_one(_Tp __x) noexcept {\n\
    \  if (__x == numeric_limits<_Tp>::max()) return numeric_limits<_Tp>::digits;\n\
    \  return __countl_zero<_Tp>((_Tp)~__x);\n}\n\ntemplate <typename _Tp> constexpr\
    \ int __countr_zero(_Tp __x) noexcept {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n\
    \n  if (__x == 0) return _Nd;\n\n  constexpr auto _Nd_ull = numeric_limits<unsigned\
    \ long long>::digits;\n  constexpr auto _Nd_ul = numeric_limits<unsigned long>::digits;\n\
    \  constexpr auto _Nd_u = numeric_limits<unsigned>::digits;\n\n  if _GLIBCXX17_CONSTEXPR\
    \ (_Nd <= _Nd_u)\n    return __builtin_ctz(__x);\n  else if _GLIBCXX17_CONSTEXPR\
    \ (_Nd <= _Nd_ul)\n    return __builtin_ctzl(__x);\n  else if _GLIBCXX17_CONSTEXPR\
    \ (_Nd <= _Nd_ull)\n    return __builtin_ctzll(__x);\n  else  // (_Nd > _Nd_ull)\n\
    \  {\n    static_assert(_Nd <= (2 * _Nd_ull),\n                  \"Maximum supported\
    \ integer size is 128-bit\");\n\n    constexpr auto __max_ull = numeric_limits<unsigned\
    \ long long>::max();\n    unsigned long long __low = __x & __max_ull;\n    if\
    \ (__low != 0) return __builtin_ctzll(__low);\n    unsigned long long __high =\
    \ __x >> _Nd_ull;\n    return __builtin_ctzll(__high) + _Nd_ull;\n  }\n}\n\ntemplate\
    \ <typename _Tp> constexpr int __countr_one(_Tp __x) noexcept {\n  if (__x ==\
    \ numeric_limits<_Tp>::max()) return numeric_limits<_Tp>::digits;\n  return __countr_zero((_Tp)~__x);\n\
    }\n\ntemplate <typename _Tp> constexpr int __popcount(_Tp __x) noexcept {\n  constexpr\
    \ auto _Nd = numeric_limits<_Tp>::digits;\n\n  if (__x == 0) return 0;\n\n  constexpr\
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
    }\n\ntemplate <typename _Tp> constexpr bool __has_single_bit(_Tp __x) noexcept\
    \ {\n  return __popcount(__x) == 1;\n}\n\ntemplate <typename _Tp> constexpr _Tp\
    \ __bit_ceil(_Tp __x) noexcept {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n\
    \  if (__x == 0 || __x == 1) return 1;\n  auto __shift_exponent = _Nd - __countl_zero((_Tp)(__x\
    \ - 1u));\n#ifdef _GLIBCXX_HAVE_BUILTIN_IS_CONSTANT_EVALUATED\n  if (!__builtin_is_constant_evaluated())\
    \ {\n    __glibcxx_assert(__shift_exponent != numeric_limits<_Tp>::digits);\n\
    \  }\n#endif\n  using __promoted_type = decltype(__x << 1);\n  if _GLIBCXX17_CONSTEXPR\
    \ (!is_same<__promoted_type, _Tp>::value) {\n    const int __extra_exp = sizeof(__promoted_type)\
    \ / sizeof(_Tp) / 2;\n    __shift_exponent |= (__shift_exponent & _Nd) << __extra_exp;\n\
    \  }\n  return (_Tp)1u << __shift_exponent;\n}\n\ntemplate <typename _Tp> constexpr\
    \ _Tp __bit_floor(_Tp __x) noexcept {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n\
    \  if (__x == 0) return 0;\n  return (_Tp)1u << (_Nd - __countl_zero((_Tp)(__x\
    \ >> 1)));\n}\n\ntemplate <typename _Tp> constexpr _Tp __bit_width(_Tp __x) noexcept\
    \ {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n  return _Nd - __countl_zero(__x);\n\
    }\n\n}  // namespace std\n\n#endif\n\n#endif\n#line 12 \"src/algebra/convolution/bitxor.hpp\"\
    \n\nnamespace workspace {\n\ntemplate <class A> A bitwise_fft(A f) {\n  size_t\
    \ len = std::__bit_floor(std::size(f));\n  for (size_t p = 1; p < len; p <<= 1)\
    \ {\n    for (size_t i = 0; i < len; i += p << 1) {\n      for (size_t j = 0;\
    \ j < p; ++j) {\n        auto t = f[i + j + p];\n        f[i + j + p] = f[i +\
    \ j] - t;\n        f[i + j] += t;\n      }\n    }\n  }\n  return f;\n}\n\ntemplate\
    \ <class A> A bitwise_ifft(A f) {\n  size_t len = std::__bit_floor(std::size(f));\n\
    \  for (size_t p = len; p != 1; p >>= 1) {\n    for (size_t i = 0; i < len; i\
    \ += p) {\n      for (size_t j = 0; j << 1 < p; ++j) {\n        auto t = f[i +\
    \ j + (p >> 1)];\n        f[i + j + (p >> 1)] = (f[i + j] - t) / 2;\n        (f[i\
    \ + j] += t) /= 2;\n      }\n    }\n  }\n  return f;\n}\n\ntemplate <class A>\
    \ A bitxor_conv(A f, A g) {\n  f = bitwise_fft(f);\n  g = bitwise_fft(g);\n  for\
    \ (size_t i = 0; i != std::size(f); ++i) f[i] *= g[i];\n  f = bitwise_ifft(f);\n\
    \  return f;\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file bitxor.hpp\n * @brief Bitwise Xor Convolution\n\
    \ * @date 2021-01-08\n */\n\n#include <iterator>\n\n#include \"lib/bit\"\n\nnamespace\
    \ workspace {\n\ntemplate <class A> A bitwise_fft(A f) {\n  size_t len = std::__bit_floor(std::size(f));\n\
    \  for (size_t p = 1; p < len; p <<= 1) {\n    for (size_t i = 0; i < len; i +=\
    \ p << 1) {\n      for (size_t j = 0; j < p; ++j) {\n        auto t = f[i + j\
    \ + p];\n        f[i + j + p] = f[i + j] - t;\n        f[i + j] += t;\n      }\n\
    \    }\n  }\n  return f;\n}\n\ntemplate <class A> A bitwise_ifft(A f) {\n  size_t\
    \ len = std::__bit_floor(std::size(f));\n  for (size_t p = len; p != 1; p >>=\
    \ 1) {\n    for (size_t i = 0; i < len; i += p) {\n      for (size_t j = 0; j\
    \ << 1 < p; ++j) {\n        auto t = f[i + j + (p >> 1)];\n        f[i + j + (p\
    \ >> 1)] = (f[i + j] - t) / 2;\n        (f[i + j] += t) /= 2;\n      }\n    }\n\
    \  }\n  return f;\n}\n\ntemplate <class A> A bitxor_conv(A f, A g) {\n  f = bitwise_fft(f);\n\
    \  g = bitwise_fft(g);\n  for (size_t i = 0; i != std::size(f); ++i) f[i] *= g[i];\n\
    \  f = bitwise_ifft(f);\n  return f;\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/algebra/convolution/bitxor.hpp
  requiredBy: []
  timestamp: '2021-02-09 12:03:18+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/library-checker/bitwise_xor_convolution.test.cpp
documentation_of: src/algebra/convolution/bitxor.hpp
layout: document
redirect_from:
- /library/src/algebra/convolution/bitxor.hpp
- /library/src/algebra/convolution/bitxor.hpp.html
title: Bitwise Xor Convolution
---
