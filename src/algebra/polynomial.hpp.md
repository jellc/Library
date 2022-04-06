---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Polynomial
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: src\\utils\\sfinae.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n\n/**\n * @file polynomial.hpp\n * @brief Polynomial\n */\n\
    \n#include <algorithm>\n#include <cassert>\n#include <vector>\n\n#include \"fft.hpp\"\
    \n#include \"lib/cxx17\"\n#include \"src/utils/sfinae.hpp\"\n\nnamespace workspace\
    \ {\n\n/**\n * @brief Polynomial.\n *\n * @tparam _Tp Ring structure\n * @tparam\
    \ _Conv_threshold Threshold for convolution method\n */\ntemplate <class _Tp,\
    \ std::size_t _Conv_threshold = 64>\nclass polynomial : public std::vector<_Tp>\
    \ {\n  using vec = std::vector<_Tp>;\n  using poly = polynomial;\n\n  template\
    \ <class _Os> friend _Os& operator<<(_Os& __os, const poly& __x) {\n    bool __head\
    \ = true;\n    for (const auto& __a : __x) {\n      if (!__head) __os << ' ';\n\
    \      __head = false;\n      __os << __a;\n    }\n    return __os;\n  }\n\n public:\n\
    \  using typename vec::size_type;\n  using typename vec::value_type;\n  using\
    \ vec::size;\n  using vec::vec;\n\n  using field = typename _fft_impl::field<_Tp>::type;\n\
    \n protected:\n  constexpr static _fft_impl::coef<field> __coef{};\n  static std::vector<field>\
    \ __work1, __work2;\n\n  void _erase_leading_zeros() noexcept {\n    auto __i\
    \ = vec::_M_impl._M_finish;\n    while (__i != vec::_M_impl._M_start && *(__i\
    \ - 1) == _Tp(0)) --__i;\n    vec::_M_erase_at_end(__i);\n  }\n\n  template <class\
    \ _Iter> void _dft(_Iter __first, _Iter __last) const noexcept {\n    fft<false>(__first,\
    \ __last);\n  }\n\n  template <class _Iter>\n  void _idft(_Iter __first, _Iter\
    \ __last) const noexcept {\n    fft<true>(__first, __last);\n  }\n\n  void _conv_naive(const\
    \ poly& __x) noexcept {\n    if (vec::_M_impl._M_start == vec::_M_impl._M_finish)\
    \ return;\n\n    if (__x._M_impl._M_start == __x._M_impl._M_finish) {\n      vec::_M_erase_at_end(vec::_M_impl._M_start);\n\
    \      return;\n    }\n\n    vec::_M_default_append(__x._M_impl._M_finish - __x._M_impl._M_start\
    \ - 1);\n\n    for (auto __i = vec::_M_impl._M_finish; __i-- != vec::_M_impl._M_start;)\
    \ {\n      auto __j = __i, __k = __x._M_impl._M_start;\n      *__i *= *__k++;\n\
    \n      while (__j != vec::_M_impl._M_start && __k != __x._M_impl._M_finish)\n\
    \        *__i += *--__j * *__k++;\n    }\n  }\n\n  template <class _Poly> void\
    \ _conv_dft(_Poly&& __x) noexcept {\n    size_type __n = vec::_M_impl._M_finish\
    \ - vec::_M_impl._M_start,\n              __m = __x._M_impl._M_finish - __x._M_impl._M_start,\n\
    \              __len = 1 << (32 - __builtin_clz(__n + __m - 1));\n\n    if (__work1.size()\
    \ < __len) __work1.resize(__len);\n    if (__work2.size() < __len) __work2.resize(__len);\n\
    \n    vec::_M_default_append(__m - 1);\n\n    if _CXX17_CONSTEXPR (std::is_same<_Tp,\
    \ field>::value) {\n      std::fill(std::move(vec::_M_impl._M_start, vec::_M_impl._M_finish,\n\
    \                          __work1.data()),\n                __work1.data() +\
    \ __len, _Tp(0));\n\n      std::fill(std::move(__x._M_impl._M_start, __x._M_impl._M_finish,\n\
    \                          __work2.data()),\n                __work2.data() +\
    \ __len, _Tp(0));\n\n      fft(__work1.data(), __len);\n      fft(__work2.data(),\
    \ __len);\n\n      for (size_type __i = 0; __i < __len; ++__i)\n        __work1[__i]\
    \ *= std::move(__work2[__i]);\n\n      ifft(__work1.data(), __len);\n\n      std::move(__work1.data(),\
    \ __work1.data() + __n + __m - 1,\n                vec::_M_impl._M_start);\n \
    \   }\n\n    else {\n      std::fill_n(__work1.data(), __len, _Tp(0));\n     \
    \ std::fill_n(__work2.data(), __len, _Tp(0));\n\n      for (size_type __i = 0;\
    \ __i < __n; ++__i)\n        __work1[__i].real(vec::_M_impl._M_start[__i]);\n\n\
    \      for (size_type __i = 0; __i < __m; ++__i)\n        __work1[__i].imag(__x._M_impl._M_start[__i]);\n\
    \n      fft(__work1.data(), __len);\n\n      __work2[0].imag(__work1[0].real()\
    \ * __work1[0].imag());\n\n      for (size_type __b = 1; __b != __len; __b <<=\
    \ 1)\n        for (size_type __i = __b, __j = __b << 1; __j-- != __b; ++__i)\n\
    \          __work2[__i] = (__work1[__i] + conj(__work1[__j])) *\n            \
    \             (__work1[__i] - conj(__work1[__j])) / 4;\n\n      ifft(__work2.data(),\
    \ __len);\n\n      for (size_type __i = 0; __i < __n + __m - 1; ++__i)\n     \
    \   if _CXX17_CONSTEXPR (std::is_floating_point<_Tp>::value)\n          vec::_M_impl._M_start[__i]\
    \ = __work2[__i].imag();\n        else\n          vec::_M_impl._M_start[__i] =\
    \ roundl(__work2[__i].imag());\n    }\n  }\n\n  size_type _divmod_naive(const\
    \ poly& __x) {\n    auto __xfin = __x._M_impl._M_finish;\n    auto __xlen = __x.size();\n\
    \    while (__xfin != __x._M_impl._M_start && *(__xfin - 1) == _Tp(0))\n     \
    \ --__xfin, --__xlen;\n\n    assert(__xlen != 0);\n    _erase_leading_zeros();\n\
    \n    auto __p = vec::_M_impl._M_finish;\n\n    while (size_type(__p - vec::_M_impl._M_start)\
    \ >= __xlen) {\n      --__p;\n\n      auto __src = __xfin;\n      auto __dst =\
    \ __p;\n\n      *__dst /= *--__src;\n      while (__src != __x._M_impl._M_start)\
    \ *--__dst -= *--__src * *__p;\n    }\n\n    return std::min<size_type>(__xlen\
    \ - 1, __p - vec::_M_impl._M_start);\n  }\n\n  void _div_naive(const poly& __x)\
    \ { operator>>=(_divmod_naive(__x)); }\n\n  void _div_doubling(poly&& __x) noexcept\
    \ {\n    _erase_leading_zeros();\n    __x._erase_leading_zeros();\n\n    auto\
    \ __n = vec::_M_impl._M_finish - vec::_M_impl._M_start;\n    auto __m = __x._M_impl._M_finish\
    \ - __x._M_impl._M_start;\n\n    if (__n < __m)\n      vec::clear();\n    else\
    \ {\n      assert(__m != 0);\n\n      std::reverse(__x._M_impl._M_start, __x._M_impl._M_finish);\n\
    \      __x = __x.inv(__n - __m + 1);\n\n      std::reverse(vec::_M_impl._M_start,\
    \ vec::_M_impl._M_finish);\n      vec::_M_erase_at_end(vec::_M_impl._M_finish\
    \ - (__m - 1));\n\n      operator*=(__x).resize(__n - __m + 1);\n      std::reverse(vec::_M_impl._M_start,\
    \ vec::_M_impl._M_finish);\n    }\n  }\n\n public:\n  /**\n   * @return Degree\
    \ of %polynomial. Return -1 if it equals zero.\n   */\n  size_type deg() const\
    \ noexcept { return size() - 1; }\n\n  /**\n   * @param __i Not exceeding the\
    \ degree.\n   * @return Coefficient of x^i.\n   */\n  typename vec::reference\
    \ operator[](size_type __i) noexcept {\n    assert(__i < size());\n    return\
    \ *(vec::_M_impl._M_start + __i);\n  }\n\n  /**\n   * @param __i Not exceeding\
    \ the degree.\n   * @return Coefficient of x^i.\n   */\n  typename vec::const_reference\
    \ operator[](size_type __i) const noexcept {\n    assert(__i < size());\n    return\
    \ *(vec::_M_impl._M_start + __i);\n  }\n\n  /**\n   * @brief Evaluate at given\
    \ point.\n   */\n  _Tp eval(const _Tp& __a) const noexcept {\n    _Tp __v(0),\
    \ __p(1);\n\n    for (auto __i = vec::_M_impl._M_start; __i != vec::_M_impl._M_finish;\n\
    \         ++__i, __p *= __a)\n      __v += *__i * __p;\n\n    return __v;\n  }\n\
    \n  /**\n   * @brief In-place multipoint evaluation.\n   */\n  template <class\
    \ _Iter, typename = std::_RequireInputIter<_Iter>>\n  _Iter eval(_Iter __first,\
    \ _Iter __last) const noexcept {\n    return eval(__first, __last, __first);\n\
    \  }\n\n  /**\n   * @brief Multipoint evaluation.\n   */\n  template <class _InputIter,\
    \ class _OutputIter,\n            typename = std::_RequireInputIter<_InputIter>>\n\
    \  _OutputIter eval(_InputIter __first, _InputIter __last,\n                 \
    \  _OutputIter __result) const noexcept {\n    size_type __n = std::distance(__first,\
    \ __last);\n    if (!__n) return __result;\n\n    auto __tree = new poly[__n <<\
    \ 1];\n\n    for (auto __p = __tree + __n; __first != __last; ++__p, ++__first)\n\
    \      *__p = {-*__first, 1};\n\n    for (size_type __i = __n; --__i;)\n     \
    \ __tree[__i] = __tree[__i << 1] * __tree[__i << 1 | 1];\n\n    __tree[1] = operator%(std::move(__tree[1]));\n\
    \n    for (size_type __i = 2; __i != __n << 1; __i += 2)\n      __tree[__i] =\
    \ __tree[__i >> 1] % std::move(__tree[__i]),\n      __tree[__i | 1] =\n      \
    \    std::move(__tree[__i >> 1] %= std::move(__tree[__i | 1]));\n\n    for (size_type\
    \ __i = 0; __i != __n; ++__i)\n      *__result++ = std::move(*__tree[__n + __i]._M_impl._M_start);\n\
    \n    delete[] __tree;\n\n    return __result;\n  }\n\n  /**\n   * @brief Multiply\
    \ by x^i.\n   */\n  poly& operator<<=(size_type __i) noexcept {\n    vec::insert(vec::begin(),\
    \ __i, _Tp(0));\n    return *this;\n  }\n\n  /**\n   * @brief Divide by x^i.\n\
    \   */\n  poly& operator>>=(size_type __i) noexcept {\n    vec::_M_erase_at_end(\n\
    \        std::move(vec::_M_impl._M_start + std::min(__i, size()),\n          \
    \        vec::_M_impl._M_finish, vec::_M_impl._M_start));\n\n    return *this;\n\
    \  }\n\n  /**\n   * @brief Multiply by x^i.\n   */\n  poly operator<<(size_type\
    \ __i) const noexcept {\n    return poly(*this).operator<<=(__i);\n  }\n\n  /**\n\
    \   * @brief Divide by x^i.\n   */\n  poly operator>>(size_type __i) const noexcept\
    \ {\n    return poly(*this).operator>>=(__i);\n  }\n\n  poly operator+() const\
    \ noexcept { return *this; }\n\n  poly operator-() const noexcept {\n    poly\
    \ __x = *this;\n    for (auto __i = __x._M_impl._M_start; __i != __x._M_impl._M_finish;\
    \ ++__i)\n      *__i = -*__i;\n    return __x;\n  }\n\n  poly& operator+=(const\
    \ poly& __x) noexcept {\n    if (size() < __x.size()) vec::_M_default_append(__x.size()\
    \ - size());\n\n    for (auto __i = vec::_M_impl._M_start, __j = __x._M_impl._M_start;\n\
    \         __j != __x._M_impl._M_finish; ++__i, ++__j)\n      *__i += *__j;\n\n\
    \    _erase_leading_zeros();\n    return *this;\n  }\n\n  poly& operator+=(const\
    \ _Tp& __c) noexcept {\n    if (__c != static_cast<_Tp>(0)) {\n      if (vec::_M_impl._M_start\
    \ == vec::_M_impl._M_finish)\n        vec::emplace_back(__c);\n      else\n  \
    \      *vec::_M_impl._M_start += __c, _erase_leading_zeros();\n    }\n\n    return\
    \ *this;\n  }\n\n  poly& operator-=(const poly& __x) noexcept {\n    if (size()\
    \ < __x.size()) vec::_M_default_append(__x.size() - size());\n\n    for (auto\
    \ __i = vec::_M_impl._M_start, __j = __x._M_impl._M_start;\n         __j != __x._M_impl._M_finish;\
    \ ++__i, ++__j)\n      *__i -= *__j;\n\n    _erase_leading_zeros();\n    return\
    \ *this;\n  }\n\n  poly& operator-=(const _Tp& __c) noexcept {\n    if (__c !=\
    \ static_cast<_Tp>(0)) {\n      if (vec::_M_impl._M_start == vec::_M_impl._M_finish)\n\
    \        vec::emplace_back(-__c);\n      else\n        *vec::_M_impl._M_start\
    \ -= __c, _erase_leading_zeros();\n    }\n\n    return *this;\n  }\n\n  poly&\
    \ operator*=(const poly& __x) noexcept {\n    if (this == std::addressof(__x))\
    \  // with itself\n      return operator*=(poly(__x));\n\n    std::min(size(),\
    \ __x.size()) > _Conv_threshold ? _conv_dft(__x)\n                           \
    \                        : _conv_naive(__x);\n\n    return *this;\n  }\n\n  poly&\
    \ operator*=(poly&& __x) noexcept {\n    if (this == std::addressof(__x))  //\
    \ with itself\n      return operator*=(poly(__x));\n\n    std::min(size(), __x.size())\
    \ > _Conv_threshold\n        ? _conv_dft(std::move(__x))\n        : _conv_naive(std::move(__x));\n\
    \n    return *this;\n  }\n\n  poly& operator*=(const _Tp& __c) noexcept {\n  \
    \  if (__c == static_cast<_Tp>(0))\n      vec::_M_erase_at_end(vec::_M_impl._M_start);\n\
    \    else\n      for (auto __i = vec::_M_impl._M_start; __i != vec::_M_impl._M_finish;\n\
    \           ++__i)\n        *__i *= __c;\n\n    return *this;\n  }\n\n  poly&\
    \ operator/=(const _Tp& __c) noexcept {\n    assert(__c != static_cast<_Tp>(0));\n\
    \n    for (auto __i = vec::_M_impl._M_start; __i != vec::_M_impl._M_finish; ++__i)\n\
    \      *__i /= __c;\n\n    return *this;\n  }\n\n  poly pow(size_type __e) const\
    \ noexcept {\n    if (vec::empty()) return *this;\n\n    if (!__e) return {1};\n\
    \n    if (size() == 1) {\n      _Tp __x = vec::front(), __y = 1;\n      for (auto\
    \ __i = __e; __i; __i >>= 1, __x *= __x)\n        if (__i & 1) __y *= __x;\n \
    \     return {__y};\n    }\n\n    size_type __deg = (size() - 1) * __e;\n    assert(__deg\
    \ > 0);\n\n    poly __p(1 << (32 - __builtin_clz(__deg)));\n    std::copy(vec::_M_impl._M_start,\
    \ vec::_M_impl._M_finish,\n              __p._M_impl._M_start);\n\n    fft(__p._M_impl._M_start,\
    \ __p._M_impl._M_finish);\n\n    for (auto&& __x : __p) {\n      _Tp __y = 1;\n\
    \      for (auto __i = __e; __i; __i >>= 1, __x *= __x)\n        if (__i & 1)\
    \ __y *= __x;\n      __x = __y;\n    }\n\n    ifft(__p._M_impl._M_start, __p._M_impl._M_finish);\n\
    \n    __p.resize(__deg + 1);\n    return __p;\n  }\n\n  poly rev() const noexcept\
    \ { return rev(size()); }\n\n  poly rev(size_type __n) const noexcept {\n    poly\
    \ __r(__n);\n\n    auto __src = vec::_M_impl._M_start;\n    auto __dst = __r._M_impl._M_finish;\n\
    \    for (size_type __i = std::min(__n, size()); __i; --__i) *--__dst = *__src++;\n\
    \n    return __r;\n  }\n\n  poly inv() const noexcept { return inv(size()); }\n\
    \n  /**\n   * @brief Multiplicative inverse modulo x^n.\n   *\n   * @param __n\
    \ Degree of modulus\n   * @return\n   */\n  poly inv(size_type __n) const noexcept\
    \ {\n    if (!__n) return {};\n    assert(*vec::_M_impl._M_start != _Tp(0));\n\
    \n    size_type __len = 1;\n    while (__len < __n) __len <<= 1;\n\n    poly __y(__len);\n\
    \    auto __xp = new _Tp[__len], __yp = __y._M_impl._M_start,\n         __zp =\
    \ new _Tp[__len];\n\n    *__yp = _Tp(1) / *vec::_M_impl._M_start;\n\n    for (size_type\
    \ __i = 1; __i != __len; __i <<= 1) {\n      std::fill(std::copy_n(__yp, __i,\
    \ __zp), __zp + (__i << 1), _Tp(0));\n\n      _dft(__zp, __zp + (__i << 1));\n\
    \n      std::fill(\n          std::copy_n(vec::_M_impl._M_start, std::min(__i\
    \ << 1, size()), __xp),\n          __xp + (__i << 1), _Tp(0));\n\n      _dft(__xp,\
    \ __xp + (__i << 1));\n\n      for (size_type __j = 0; __j != (__i << 1); ++__j)\
    \ __xp[__j] *= -__zp[__j];\n\n      _idft(__xp, __xp + (__i << 1));\n\n      std::fill(std::move(__xp\
    \ + __i, __xp + (__i << 1), __xp),\n                __xp + (__i << 1), _Tp(0));\n\
    \n      _dft(__xp, __xp + (__i << 1));\n\n      for (size_type __j = 0; __j !=\
    \ (__i << 1); ++__j)\n        __xp[__j] *= static_cast<_Tp&&>(__zp[__j]);\n\n\
    \      _idft(__xp, __xp + (__i << 1));\n\n      std::move(__xp, __xp + __i, __yp\
    \ + __i);\n    }\n\n    delete[] __xp;\n    delete[] __zp;\n\n    __y._M_erase_at_end(__yp\
    \ + __n);\n    return __y;\n  }\n\n  poly& operator/=(const poly& __x) noexcept\
    \ {\n    if (__x.size() > _Conv_threshold)\n      _div_doubling(poly(__x));\n\
    \    else\n      _div_naive(__x);\n\n    return *this;\n  }\n\n  poly& operator/=(poly&&\
    \ __x) noexcept {\n    if (__x.size() > _Conv_threshold)\n      _div_doubling(std::move(__x));\n\
    \    else\n      _div_naive(__x);\n\n    return *this;\n  }\n\n  poly& operator%=(const\
    \ poly& __x) noexcept {\n    if (__x.size() > _Conv_threshold)\n      return operator-=(__x.operator*(operator/(__x)));\n\
    \n    vec::_M_erase_at_end(vec::_M_impl._M_start + _divmod_naive(__x));\n    return\
    \ *this;\n  }\n\n  template <class _T> poly operator+(_T&& __x) const noexcept\
    \ {\n    return poly(*this).operator+=(std::forward<_T>(__x));\n  }\n\n  template\
    \ <class _T> poly operator-(_T&& __x) const noexcept {\n    return poly(*this).operator-=(std::forward<_T>(__x));\n\
    \  }\n\n  template <class _T> poly operator*(_T&& __x) const noexcept {\n    return\
    \ poly(*this).operator*=(std::forward<_T>(__x));\n  }\n\n  template <class _T>\
    \ poly operator/(_T&& __x) const noexcept {\n    return poly(*this).operator/=(std::forward<_T>(__x));\n\
    \  }\n\n  template <class _T> poly operator%(_T&& __x) const noexcept {\n    return\
    \ poly(*this).operator%=(std::forward<_T>(__x));\n  }\n\n  std::pair<poly, poly>\
    \ divmod(const poly& __x) const {\n    if (__x.size() > _Conv_threshold) return\
    \ {operator/(__x), operator%(__x)};\n\n    poly __rem(*this);\n    auto __p =\
    \ __rem._M_impl._M_start + __rem._divmod_naive(__x);\n\n    poly __quot(__p, __rem._M_impl._M_finish);\n\
    \    __rem._M_erase_at_end(__p);\n\n    return {__quot, __rem};\n  }\n\n  /**\n\
    \   * @brief Differentiate.\n   *\n   * @return Derivative.\n   */\n  poly deriv()\
    \ const noexcept {\n    if (auto __s = vec::_M_impl._M_start, __f = vec::_M_impl._M_finish;\n\
    \        __s != __f) {\n      poly __der(++__s, __f);\n\n      __s = __der._M_impl._M_start,\
    \ __f = __der._M_impl._M_finish;\n      for (_Tp __i(1); __s != __f; ++__s, __i\
    \ += 1) *__s *= __i;\n\n      __der._erase_leading_zeros();\n      return __der;\n\
    \    }\n\n    return {};\n  }\n\n  /**\n   * @brief Differentiate at given point.\n\
    \   *\n   * @return Derivative coefficient.\n   */\n  _Tp deriv(const _Tp& __a)\
    \ const noexcept {\n    _Tp __der(0);\n\n    if (auto __s = vec::_M_impl._M_start,\
    \ __f = vec::_M_impl._M_finish;\n        __s != __f)\n      for (_Tp __i(1), __p(1);\
    \ ++__s != __f; __i += 1, __p *= __a)\n        __der += *__s * __i * __p;\n\n\
    \    return __der;\n  }\n\n  /**\n   * @brief Integrate.\n   *\n   * @return Integral\
    \ indefinite at the degrees divisible by the characteristic\n   * of `_Tp`. Coefficients\
    \ are set as 0 there.\n   */\n  poly integ() const noexcept {\n    if (auto __s\
    \ = vec::_M_impl._M_start, __f = vec::_M_impl._M_finish;\n        __s != __f)\
    \ {\n      poly __int(__f - __s + 1);\n\n      __f = std::copy(__s, __f, __int._M_impl._M_start\
    \ + 1);\n      __s = __int._M_impl._M_start + 1;\n      for (_Tp __i(1); __s !=\
    \ __f; ++__s, __i += 1)\n        __i == _Tp(0) ? assert(*__s == _Tp(0)) : void(*__s\
    \ /= __i);\n\n      return __int;\n    }\n\n    return {};\n  }\n\n  /**\n   *\
    \ @brief Integrate in given range.\n   *\n   * @return Definite integral over\
    \ [0, __a].\n   */\n  _Tp integ(const _Tp& __a) const noexcept {\n    _Tp __int(0);\n\
    \n    auto __s = vec::_M_impl._M_start, __f = vec::_M_impl._M_finish;\n    for\
    \ (_Tp __p(__a), __i(1); __s != __f; ++__s, __p *= __a, __i += 1)\n      __int\
    \ += *__s / __i * __p;\n\n    return __int;\n  }\n\n  /**\n   * @brief Integrate\
    \ in given range.\n   *\n   * @return Definite integral over [__a, __b].\n   */\n\
    \  _Tp integ(const _Tp& __a, const _Tp& __b) const noexcept {\n    _Tp __int(0);\n\
    \n    auto __s = vec::_M_impl._M_start, __f = vec::_M_impl._M_finish;\n    for\
    \ (_Tp __pa(__a), __pb(__b), __i(1); __s != __f;\n         ++__s, __pa *= __a,\
    \ __pb *= __b, __i += 1)\n      __int += *__s / __i * (__pb - __pa);\n\n    return\
    \ __int;\n  }\n\n  /**\n   * @brief\n   *\n   * @param __a\n   * @return f(x +\
    \ a)\n   */\n  poly shift(const _Tp& __a) const noexcept {\n    size_type __n\
    \ = size();\n    poly __s(*this), __e(__n);\n    _Tp __cs(1), __ce(1);\n\n   \
    \ for (size_type __i{0}; __i != __n;\n         __cs *= _Tp(++__i), __ce *= __a\
    \ / _Tp(__i))\n      __s[__i] *= __cs, __e[__n - 1 - __i] = __ce;\n\n    __s *=\
    \ std::move(__e);\n    __ce = 1;\n\n    for (size_type __i{0}; __i != __n; __ce\
    \ /= _Tp(++__i))\n      __e[__i] = __s[__n - 1 + __i] * __ce;\n\n    return __e;\n\
    \  }\n};\n\ntemplate <class _Tp, size_t _C>\nstd::vector<typename polynomial<_Tp,\
    \ _C>::field> polynomial<_Tp, _C>::__work1;\n\ntemplate <class _Tp, size_t _C>\n\
    std::vector<typename polynomial<_Tp, _C>::field> polynomial<_Tp, _C>::__work2;\n\
    \n/**\n * @brief Generating function of the sum of k-th powers of the first n\n\
    \ * non-negative integers. O(d \\\\log d) time in modulo x^d.\n *\n * @return\
    \ \\\\sum_{k=0}^{d-1} x^k \\\\sum_{i=0}^{n-1} i^k.\n */\ntemplate <class _Tp>\
    \ polynomial<_Tp> power_sum(_Tp __n, std::size_t __d) {\n  if (!__d) return {};\n\
    \n  polynomial<_Tp> __f(__d), __e(__d);\n  __f[0] = __n;\n  for (std::size_t __i\
    \ = 1; __i != __d; ++__i) __f[__i] = __f[__i - 1] * __n;\n\n  _Tp __c{1};\n  for\
    \ (std::size_t __i = 0; __i != __d; ++__i)\n    __c /= __i + 1, __f[__i] *= __c,\
    \ __e[__i] = __c;\n\n  (__f *= __e.inv(__d)).resize(__d);\n\n  __c = 1;\n  for\
    \ (std::size_t __i = 0; __i != __d; __c *= ++__i) __f[__i] *= __c;\n  return __f;\n\
    }\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/algebra/polynomial.hpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/algebra/polynomial.hpp
layout: document
redirect_from:
- /library/src/algebra/polynomial.hpp
- /library/src/algebra/polynomial.hpp.html
title: Polynomial
---
