#pragma once

/**
 * @file polynomial.hpp
 * @brief Polynomial
 */

#include <algorithm>
#include <cassert>
#include <vector>

#include "fft.hpp"
#include "lib/cxx17"
#include "src/utils/sfinae.hpp"

namespace workspace {

/**
 * @brief Polynomial.
 *
 * @tparam _Tp Ring structure
 * @tparam _Conv_threshold Threshold for convolution method
 */
template <class _Tp, std::size_t _Conv_threshold = 64>
class polynomial : public std::vector<_Tp> {
  using vec = std::vector<_Tp>;
  using poly = polynomial;

  template <class _Os> friend _Os& operator<<(_Os& __os, const poly& __x) {
    bool __head = true;
    for (const auto& __a : __x) {
      if (!__head) __os << ' ';
      __head = false;
      __os << __a;
    }
    return __os;
  }

 public:
  using typename vec::size_type;
  using typename vec::value_type;
  using vec::size;
  using vec::vec;

  using field = typename _fft_impl::field<_Tp>::type;

 protected:
  constexpr static _fft_impl::coef<field> __coef{};
  static std::vector<field> __work1, __work2;

  void _erase_leading_zeros() noexcept {
    auto __i = vec::_M_impl._M_finish;
    while (__i != vec::_M_impl._M_start && *(__i - 1) == _Tp(0)) --__i;
    vec::_M_erase_at_end(__i);
  }

  template <class _Iter> void _dft(_Iter __first, _Iter __last) const noexcept {
    fft<false>(__first, __last);
  }

  template <class _Iter>
  void _idft(_Iter __first, _Iter __last) const noexcept {
    fft<true>(__first, __last);
  }

  void _conv_naive(const poly& __x) noexcept {
    auto __n = vec::_M_impl._M_finish - vec::_M_impl._M_start;

    if (__n == 0) return;

    if (__x._M_impl._M_start == __x._M_impl._M_finish) {
      vec::_M_erase_at_end(vec::_M_impl._M_start);  // clear
      return;
    }

    vec::_M_default_append(__x._M_impl._M_finish - __x._M_impl._M_start - 1);

    for (auto __h = vec::_M_impl._M_start + __n, __i = vec::_M_impl._M_finish;
         __i != vec::_M_impl._M_start;) {
      auto __k = __x._M_impl._M_start;

      if (__i != __h) {
        __k += __i - __h;
        --__i;
      } else {
        --__i, --__h;
        *__i *= *__k++;
      }

      for (auto __j = __h;
           __j != vec::_M_impl._M_start && __k != __x._M_impl._M_finish;)
        *__i += *--__j * *__k++;
    }
  }

  template <class _Poly> void _conv_dft(_Poly&& __x) noexcept {
    size_type __n = vec::_M_impl._M_finish - vec::_M_impl._M_start,
              __m = __x._M_impl._M_finish - __x._M_impl._M_start,
              __len = 1 << (32 - __builtin_clz(__n + __m - 1));

    if (__work1.size() < __len) __work1.resize(__len);
    if (__work2.size() < __len) __work2.resize(__len);

    vec::_M_default_append(__m - 1);

    if _CXX17_CONSTEXPR (std::is_same<_Tp, field>::value) {
      std::fill(std::move(vec::_M_impl._M_start, vec::_M_impl._M_finish,
                          __work1.data()),
                __work1.data() + __len, _Tp(0));

      std::fill(std::move(__x._M_impl._M_start, __x._M_impl._M_finish,
                          __work2.data()),
                __work2.data() + __len, _Tp(0));

      fft(__work1.data(), __len);
      fft(__work2.data(), __len);

      for (size_type __i = 0; __i < __len; ++__i)
        __work1[__i] *= std::move(__work2[__i]);

      ifft(__work1.data(), __len);

      std::move(__work1.data(), __work1.data() + __n + __m - 1,
                vec::_M_impl._M_start);
    }

    else {
      std::fill_n(__work1.data(), __len, _Tp(0));
      std::fill_n(__work2.data(), __len, _Tp(0));

      for (size_type __i = 0; __i < __n; ++__i)
        __work1[__i].real(vec::_M_impl._M_start[__i]);

      for (size_type __i = 0; __i < __m; ++__i)
        __work1[__i].imag(__x._M_impl._M_start[__i]);

      fft(__work1.data(), __len);

      __work2[0].imag(__work1[0].real() * __work1[0].imag());

      for (size_type __b = 1; __b != __len; __b <<= 1)
        for (size_type __i = __b, __j = __b << 1; __j-- != __b; ++__i)
          __work2[__i] = (__work1[__i] + conj(__work1[__j])) *
                         (__work1[__i] - conj(__work1[__j])) / 4;

      ifft(__work2.data(), __len);

      for (size_type __i = 0; __i < __n + __m - 1; ++__i)
        if _CXX17_CONSTEXPR (std::is_floating_point<_Tp>::value)
          vec::_M_impl._M_start[__i] = __work2[__i].imag();
        else
          vec::_M_impl._M_start[__i] = roundl(__work2[__i].imag());
    }
  }

  size_type _divmod_naive(const poly& __x) {
    auto __xfin = __x._M_impl._M_finish;
    auto __xlen = __x.size();
    while (__xfin != __x._M_impl._M_start && *(__xfin - 1) == _Tp(0))
      --__xfin, --__xlen;

    assert(__xlen != 0);
    _erase_leading_zeros();

    auto __p = vec::_M_impl._M_finish;

    while (size_type(__p - vec::_M_impl._M_start) >= __xlen) {
      --__p;

      auto __src = __xfin;
      auto __dst = __p;

      *__dst /= *--__src;
      while (__src != __x._M_impl._M_start) *--__dst -= *--__src * *__p;
    }

    return std::min<size_type>(__xlen - 1, __p - vec::_M_impl._M_start);
  }

  void _div_naive(const poly& __x) { operator>>=(_divmod_naive(__x)); }

  void _div_doubling(poly&& __x) noexcept {
    _erase_leading_zeros();
    __x._erase_leading_zeros();

    auto __n = vec::_M_impl._M_finish - vec::_M_impl._M_start;
    auto __m = __x._M_impl._M_finish - __x._M_impl._M_start;

    if (__n < __m)
      vec::clear();
    else {
      assert(__m != 0);

      std::reverse(__x._M_impl._M_start, __x._M_impl._M_finish);
      __x = __x.inv(__n - __m + 1);

      std::reverse(vec::_M_impl._M_start, vec::_M_impl._M_finish);
      vec::_M_erase_at_end(vec::_M_impl._M_finish - (__m - 1));

      operator*=(__x).resize(__n - __m + 1);
      std::reverse(vec::_M_impl._M_start, vec::_M_impl._M_finish);
    }
  }

 public:
  /**
   * @return Degree of %polynomial. Return -1 if it equals zero.
   */
  size_type deg() const noexcept { return size() - 1; }

  /**
   * @param __i Not exceeding the degree.
   * @return Coefficient of x^i.
   */
  typename vec::reference operator[](size_type __i) noexcept {
    assert(__i < size());
    return *(vec::_M_impl._M_start + __i);
  }

  /**
   * @param __i Not exceeding the degree.
   * @return Coefficient of x^i.
   */
  typename vec::const_reference operator[](size_type __i) const noexcept {
    assert(__i < size());
    return *(vec::_M_impl._M_start + __i);
  }

  /**
   * @brief Evaluate at given point.
   */
  _Tp eval(const _Tp& __a) const noexcept {
    _Tp __v(0), __p(1);

    for (auto __i = vec::_M_impl._M_start; __i != vec::_M_impl._M_finish;
         ++__i, __p *= __a)
      __v += *__i * __p;

    return __v;
  }

  /**
   * @brief In-place multipoint evaluation.
   */
  template <class _Iter, typename = std::_RequireInputIter<_Iter>>
  _Iter eval(_Iter __first, _Iter __last) const noexcept {
    return eval(__first, __last, __first);
  }

  /**
   * @brief Multipoint evaluation.
   */
  template <class _InputIter, class _OutputIter,
            typename = std::_RequireInputIter<_InputIter>>
  _OutputIter eval(_InputIter __first, _InputIter __last,
                   _OutputIter __result) const noexcept {
    size_type __n = std::distance(__first, __last);
    if (!__n) return __result;

    auto __tree = new poly[__n << 1];

    for (auto __p = __tree + __n; __first != __last; ++__p, ++__first)
      *__p = {-*__first, 1};

    for (size_type __i = __n; --__i;)
      __tree[__i] = __tree[__i << 1] * __tree[__i << 1 | 1];

    __tree[1] = operator%(std::move(__tree[1]));

    for (size_type __i = 2; __i != __n << 1; __i += 2)
      __tree[__i] = __tree[__i >> 1] % std::move(__tree[__i]),
      __tree[__i | 1] =
          std::move(__tree[__i >> 1] %= std::move(__tree[__i | 1]));

    for (size_type __i = 0; __i != __n; ++__i)
      *__result++ = std::move(*__tree[__n + __i]._M_impl._M_start);

    delete[] __tree;

    return __result;
  }

  /**
   * @brief Multiply by x^i.
   */
  poly& operator<<=(size_type __i) noexcept {
    vec::insert(vec::begin(), __i, _Tp(0));
    return *this;
  }

  /**
   * @brief Divide by x^i.
   */
  poly& operator>>=(size_type __i) noexcept {
    vec::_M_erase_at_end(
        std::move(vec::_M_impl._M_start + std::min(__i, size()),
                  vec::_M_impl._M_finish, vec::_M_impl._M_start));

    return *this;
  }

  /**
   * @brief Multiply by x^i.
   */
  poly operator<<(size_type __i) const noexcept {
    return poly(*this).operator<<=(__i);
  }

  /**
   * @brief Divide by x^i.
   */
  poly operator>>(size_type __i) const noexcept {
    return poly(*this).operator>>=(__i);
  }

  poly operator+() const noexcept { return *this; }

  poly operator-() const noexcept {
    poly __x = *this;
    for (auto __i = __x._M_impl._M_start; __i != __x._M_impl._M_finish; ++__i)
      *__i = -*__i;
    return __x;
  }

  poly& operator+=(const poly& __x) noexcept {
    if (size() < __x.size()) vec::_M_default_append(__x.size() - size());

    for (auto __i = vec::_M_impl._M_start, __j = __x._M_impl._M_start;
         __j != __x._M_impl._M_finish; ++__i, ++__j)
      *__i += *__j;

    _erase_leading_zeros();
    return *this;
  }

  poly& operator+=(const _Tp& __c) noexcept {
    if (__c != static_cast<_Tp>(0)) {
      if (vec::_M_impl._M_start == vec::_M_impl._M_finish)
        vec::emplace_back(__c);
      else
        *vec::_M_impl._M_start += __c, _erase_leading_zeros();
    }

    return *this;
  }

  poly& operator-=(const poly& __x) noexcept {
    if (size() < __x.size()) vec::_M_default_append(__x.size() - size());

    for (auto __i = vec::_M_impl._M_start, __j = __x._M_impl._M_start;
         __j != __x._M_impl._M_finish; ++__i, ++__j)
      *__i -= *__j;

    _erase_leading_zeros();
    return *this;
  }

  poly& operator-=(const _Tp& __c) noexcept {
    if (__c != static_cast<_Tp>(0)) {
      if (vec::_M_impl._M_start == vec::_M_impl._M_finish)
        vec::emplace_back(-__c);
      else
        *vec::_M_impl._M_start -= __c, _erase_leading_zeros();
    }

    return *this;
  }

  poly& operator*=(const poly& __x) noexcept {
    if (this == std::addressof(__x))  // with itself
      return operator*=(poly(__x));

    std::min(size(), __x.size()) > _Conv_threshold ? _conv_dft(__x)
                                                   : _conv_naive(__x);

    return *this;
  }

  poly& operator*=(poly&& __x) noexcept {
    if (this == std::addressof(__x))  // with itself
      return operator*=(poly(__x));

    std::min(size(), __x.size()) > _Conv_threshold
        ? _conv_dft(std::move(__x))
        : _conv_naive(std::move(__x));

    return *this;
  }

  poly& operator*=(const _Tp& __c) noexcept {
    if (__c == static_cast<_Tp>(0))
      vec::_M_erase_at_end(vec::_M_impl._M_start);
    else
      for (auto __i = vec::_M_impl._M_start; __i != vec::_M_impl._M_finish;
           ++__i)
        *__i *= __c;

    return *this;
  }

  poly& operator/=(const _Tp& __c) noexcept {
    assert(__c != static_cast<_Tp>(0));

    for (auto __i = vec::_M_impl._M_start; __i != vec::_M_impl._M_finish; ++__i)
      *__i /= __c;

    return *this;
  }

  poly pow(size_type __e) const noexcept {
    if (vec::empty()) return *this;

    if (!__e) return {1};

    if (size() == 1) {
      _Tp __x = vec::front(), __y = 1;
      for (auto __i = __e; __i; __i >>= 1, __x *= __x)
        if (__i & 1) __y *= __x;
      return {__y};
    }

    size_type __deg = (size() - 1) * __e;
    assert(__deg > 0);

    poly __p(1 << (32 - __builtin_clz(__deg)));
    std::copy(vec::_M_impl._M_start, vec::_M_impl._M_finish,
              __p._M_impl._M_start);

    fft(__p._M_impl._M_start, __p._M_impl._M_finish);

    for (auto&& __x : __p) {
      _Tp __y = 1;
      for (auto __i = __e; __i; __i >>= 1, __x *= __x)
        if (__i & 1) __y *= __x;
      __x = __y;
    }

    ifft(__p._M_impl._M_start, __p._M_impl._M_finish);

    __p.resize(__deg + 1);
    return __p;
  }

  poly rev() const noexcept { return rev(size()); }

  poly rev(size_type __n) const noexcept {
    poly __r(__n);

    auto __src = vec::_M_impl._M_start;
    auto __dst = __r._M_impl._M_finish;
    for (size_type __i = std::min(__n, size()); __i; --__i) *--__dst = *__src++;

    return __r;
  }

  poly inv() const noexcept { return inv(size()); }

  /**
   * @brief Multiplicative inverse modulo x^n.
   *
   * @param __n Degree of modulus
   * @return
   */
  poly inv(size_type __n) const noexcept {
    if (!__n) return {};
    assert(*vec::_M_impl._M_start != _Tp(0));

    size_type __len = 1;
    while (__len < __n) __len <<= 1;

    poly __y(__len);
    auto __xp = new _Tp[__len], __yp = __y._M_impl._M_start,
         __zp = new _Tp[__len];

    *__yp = _Tp(1) / *vec::_M_impl._M_start;

    for (size_type __i = 1; __i != __len; __i <<= 1) {
      std::fill(std::copy_n(__yp, __i, __zp), __zp + (__i << 1), _Tp(0));

      _dft(__zp, __zp + (__i << 1));

      std::fill(
          std::copy_n(vec::_M_impl._M_start, std::min(__i << 1, size()), __xp),
          __xp + (__i << 1), _Tp(0));

      _dft(__xp, __xp + (__i << 1));

      for (size_type __j = 0; __j != (__i << 1); ++__j) __xp[__j] *= -__zp[__j];

      _idft(__xp, __xp + (__i << 1));

      std::fill(std::move(__xp + __i, __xp + (__i << 1), __xp),
                __xp + (__i << 1), _Tp(0));

      _dft(__xp, __xp + (__i << 1));

      for (size_type __j = 0; __j != (__i << 1); ++__j)
        __xp[__j] *= static_cast<_Tp&&>(__zp[__j]);

      _idft(__xp, __xp + (__i << 1));

      std::move(__xp, __xp + __i, __yp + __i);
    }

    delete[] __xp;
    delete[] __zp;

    __y._M_erase_at_end(__yp + __n);
    return __y;
  }

  poly& operator/=(const poly& __x) noexcept {
    if (__x.size() > _Conv_threshold)
      _div_doubling(poly(__x));
    else
      _div_naive(__x);

    return *this;
  }

  poly& operator/=(poly&& __x) noexcept {
    if (__x.size() > _Conv_threshold)
      _div_doubling(std::move(__x));
    else
      _div_naive(__x);

    return *this;
  }

  poly& operator%=(const poly& __x) noexcept {
    if (__x.size() > _Conv_threshold)
      return operator-=(__x.operator*(operator/(__x)));

    vec::_M_erase_at_end(vec::_M_impl._M_start + _divmod_naive(__x));
    return *this;
  }

  template <class _T> poly operator+(_T&& __x) const noexcept {
    return poly(*this).operator+=(std::forward<_T>(__x));
  }

  template <class _T> poly operator-(_T&& __x) const noexcept {
    return poly(*this).operator-=(std::forward<_T>(__x));
  }

  template <class _T> poly operator*(_T&& __x) const noexcept {
    return poly(*this).operator*=(std::forward<_T>(__x));
  }

  template <class _T> poly operator/(_T&& __x) const noexcept {
    return poly(*this).operator/=(std::forward<_T>(__x));
  }

  template <class _T> poly operator%(_T&& __x) const noexcept {
    return poly(*this).operator%=(std::forward<_T>(__x));
  }

  std::pair<poly, poly> divmod(const poly& __x) const {
    if (__x.size() > _Conv_threshold) return {operator/(__x), operator%(__x)};

    poly __rem(*this);
    auto __p = __rem._M_impl._M_start + __rem._divmod_naive(__x);

    poly __quot(__p, __rem._M_impl._M_finish);
    __rem._M_erase_at_end(__p);

    return {__quot, __rem};
  }

  /**
   * @brief Differentiate.
   *
   * @return Derivative.
   */
  poly deriv() const noexcept {
    if (auto __s = vec::_M_impl._M_start, __f = vec::_M_impl._M_finish;
        __s != __f) {
      poly __der(++__s, __f);

      __s = __der._M_impl._M_start, __f = __der._M_impl._M_finish;
      for (_Tp __i(1); __s != __f; ++__s, __i += 1) *__s *= __i;

      __der._erase_leading_zeros();
      return __der;
    }

    return {};
  }

  /**
   * @brief Differentiate at given point.
   *
   * @return Derivative coefficient.
   */
  _Tp deriv(const _Tp& __a) const noexcept {
    _Tp __der(0);

    if (auto __s = vec::_M_impl._M_start, __f = vec::_M_impl._M_finish;
        __s != __f)
      for (_Tp __i(1), __p(1); ++__s != __f; __i += 1, __p *= __a)
        __der += *__s * __i * __p;

    return __der;
  }

  /**
   * @brief Integrate.
   *
   * @return Integral indefinite at the degrees divisible by the characteristic
   * of `_Tp`. Coefficients are set as 0 there.
   */
  poly integ() const noexcept {
    if (auto __s = vec::_M_impl._M_start, __f = vec::_M_impl._M_finish;
        __s != __f) {
      poly __int(__f - __s + 1);

      __f = std::copy(__s, __f, __int._M_impl._M_start + 1);
      __s = __int._M_impl._M_start + 1;
      for (_Tp __i(1); __s != __f; ++__s, __i += 1)
        __i == _Tp(0) ? assert(*__s == _Tp(0)) : void(*__s /= __i);

      return __int;
    }

    return {};
  }

  /**
   * @brief Integrate in given range.
   *
   * @return Definite integral over [0, __a].
   */
  _Tp integ(const _Tp& __a) const noexcept {
    _Tp __int(0);

    auto __s = vec::_M_impl._M_start, __f = vec::_M_impl._M_finish;
    for (_Tp __p(__a), __i(1); __s != __f; ++__s, __p *= __a, __i += 1)
      __int += *__s / __i * __p;

    return __int;
  }

  /**
   * @brief Integrate in given range.
   *
   * @return Definite integral over [__a, __b].
   */
  _Tp integ(const _Tp& __a, const _Tp& __b) const noexcept {
    _Tp __int(0);

    auto __s = vec::_M_impl._M_start, __f = vec::_M_impl._M_finish;
    for (_Tp __pa(__a), __pb(__b), __i(1); __s != __f;
         ++__s, __pa *= __a, __pb *= __b, __i += 1)
      __int += *__s / __i * (__pb - __pa);

    return __int;
  }

  /**
   * @brief
   *
   * @param __a
   * @return f(x + a)
   */
  poly shift(const _Tp& __a) const noexcept {
    size_type __n = size();
    poly __s(*this), __e(__n);
    _Tp __cs(1), __ce(1);

    for (size_type __i{0}; __i != __n;
         __cs *= _Tp(++__i), __ce *= __a / _Tp(__i))
      __s[__i] *= __cs, __e[__n - 1 - __i] = __ce;

    __s *= std::move(__e);
    __ce = 1;

    for (size_type __i{0}; __i != __n; __ce /= _Tp(++__i))
      __e[__i] = __s[__n - 1 + __i] * __ce;

    return __e;
  }
};

template <class _Tp, size_t _C>
std::vector<typename polynomial<_Tp, _C>::field> polynomial<_Tp, _C>::__work1;

template <class _Tp, size_t _C>
std::vector<typename polynomial<_Tp, _C>::field> polynomial<_Tp, _C>::__work2;

/**
 * @brief Generating function of the sum of k-th powers of the first n
 * non-negative integers. O(d \\log d) time in modulo x^d.
 *
 * @return \\sum_{k=0}^{d-1} x^k \\sum_{i=0}^{n-1} i^k.
 */
template <class _Tp> polynomial<_Tp> power_sum(_Tp __n, std::size_t __d) {
  if (!__d) return {};

  polynomial<_Tp> __f(__d), __e(__d);
  __f[0] = __n;
  for (std::size_t __i = 1; __i != __d; ++__i) __f[__i] = __f[__i - 1] * __n;

  _Tp __c{1};
  for (std::size_t __i = 0; __i != __d; ++__i)
    __c /= __i + 1, __f[__i] *= __c, __e[__i] = __c;

  (__f *= __e.inv(__d)).resize(__d);

  __c = 1;
  for (std::size_t __i = 0; __i != __d; __c *= ++__i) __f[__i] *= __c;
  return __f;
}

}  // namespace workspace
