#pragma once

/**
 * @file polynomial.hpp
 * @brief Polynomial
 */

#include <algorithm>
#include <cassert>
#include <vector>

#include "lib/cxx17"
#include "ntt.hpp"
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
  using vec::vec;
  using size_type = typename vec::size_type;

 protected:
  void _erase_leading_zeros() noexcept {
    auto __i = vec::_M_impl._M_finish;
    while (__i != vec::_M_impl._M_start && *(__i - 1) == _Tp(0)) --__i;
    vec::_M_erase_at_end(__i);
  }

  template <class _Iter> void _dft(_Iter __first, _Iter __last) const noexcept {
    if _CXX17_CONSTEXPR (has_mod<_Tp>::value)
      ntt(__first, __last);
    else {
      // fft(__first, __last);
      assert(0);  // Not implemented!
    }
  }

  template <class _Iter>
  void _idft(_Iter __first, _Iter __last) const noexcept {
    if _CXX17_CONSTEXPR (has_mod<_Tp>::value)
      intt(__first, __last);
    else {
      // ifft(__first, __last);
      assert(0);  // Not implemented!
    }
  }

  void _conv_naive(const poly& __x) noexcept {
    if (vec::_M_impl._M_start == vec::_M_impl._M_finish) return;

    if (__x._M_impl._M_start == __x._M_impl._M_finish) {
      vec::_M_erase_at_end(vec::_M_impl._M_start);
      return;
    }

    vec::_M_default_append(__x._M_impl._M_finish - __x._M_impl._M_start - 1);

    for (auto __i = vec::_M_impl._M_finish; __i-- != vec::_M_impl._M_start;) {
      auto __j = __i, __k = __x._M_impl._M_start;
      *__i *= *__k++;

      while (__j != vec::_M_impl._M_start && __k != __x._M_impl._M_finish)
        *__i += *--__j * *__k++;
    }
  }

  void _conv_dft(poly&& __x) noexcept {
    if _CXX17_CONSTEXPR (has_mod<_Tp>::value)
      _conv_ntt(std::move(__x));
    else {
      // _conv_fft(std::move(__x));
      assert(0);  // Not implemented!
    }
  }

  void _conv_fft(poly&& __x) noexcept;

  void _conv_ntt(poly&& __x) noexcept {
    size_type __n = vec::_M_impl._M_finish - vec::_M_impl._M_start,
              __m = __x._M_impl._M_finish - __x._M_impl._M_start,
              __len = 1 << (32 - __builtin_clz(__n + __m - 1));

    vec::_M_default_append(__len - __n);
    __x._M_default_append(__len - __m);

    ntt(vec::_M_impl._M_start, vec::_M_impl._M_finish);
    ntt(__x._M_impl._M_start, __x._M_impl._M_finish);

    for (auto __i = vec::_M_impl._M_start, __j = __x._M_impl._M_start;
         __i != vec::_M_impl._M_finish; ++__i, ++__j)
      *__i *= std::move(*__j);

    intt(vec::_M_impl._M_start, vec::_M_impl._M_finish);

    vec::_M_erase_at_end(vec::_M_impl._M_start + __n + __m - 1);
  }

  /**
   * @brief
   *
   * @param __x
   * @return Degree of __x.
   */
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
  size_type deg() const noexcept { return vec::size() - 1; }

  /**
   * @param __i Not exceeding the degree.
   * @return Coefficient of x^i.
   */
  typename vec::reference operator[](size_type __i) noexcept {
    assert(__i < vec::size());
    return *(vec::_M_impl._M_start + __i);
  }

  /**
   * @param __i Not exceeding the degree.
   * @return Coefficient of x^i.
   */
  typename vec::const_reference operator[](size_type __i) const noexcept {
    assert(__i < vec::size());
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
   * @brief Conversion to bool.
   *
   * @return Whether the %polynomial is not zero.
   */
  operator bool() const noexcept {
    auto __first = vec::_M_impl._M_start, __last = vec::_M_impl._M_finish;

    while (__first != __last)
      if (*__first++ != _Tp(0)) return true;

    return false;
  }

  bool operator==(const poly& __x) const noexcept {
    auto __first1 = vec::_M_impl._M_start, __last1 = vec::_M_impl._M_finish;

    auto __first2 = __x._M_impl._M_start, __last2 = __x._M_impl._M_finish;

    if (__last1 - __first1 < __last2 - __first2) {
      while (__first1 != __last1)
        if (*__first1++ != *__first2++) return false;

      while (__first2 != __last2)
        if (*__first2++ != _Tp(0)) return false;
    }

    else {
      while (__first2 != __last2)
        if (*__first1++ != *__first2++) return false;

      while (__first1 != __last1)
        if (*__first1++ != _Tp(0)) return false;
    }

    return true;
  }

  bool operator!=(const poly& __x) const noexcept { return !operator==(__x); }

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
        std::move(vec::_M_impl._M_start + std::min(__i, vec::size()),
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
    if (vec::size() < __x.size())
      vec::_M_default_append(__x.size() - vec::size());

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
    if (vec::size() < __x.size())
      vec::_M_default_append(__x.size() - vec::size());

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
    std::min(vec::size(), __x.size()) > _Conv_threshold
        ? _conv_dft(poly(__x))
        : _conv_naive(this == std::addressof(__x) ? poly(__x) : __x);

    return *this;
  }

  poly& operator*=(poly&& __x) noexcept {
    std::min(vec::size(), __x.size()) > _Conv_threshold
        ? _conv_dft(std::move(__x))
        : _conv_naive(__x);

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

  poly rev() const noexcept { return rev(vec::size()); }

  poly rev(size_type __n) const noexcept {
    poly __r(__n);

    auto __src = vec::_M_impl._M_start;
    auto __dst = __r._M_impl._M_finish;
    for (size_type __i = std::min(__n, vec::size()); __i; --__i)
      *--__dst = *__src++;

    return __r;
  }

  poly inv() const noexcept { return inv(vec::size()); }

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

      std::fill(std::copy_n(vec::_M_impl._M_start,
                            std::min(__i << 1, vec::size()), __xp),
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
};

/**
 * @brief Polynomial interpolation in O(n log(n)^2) time.
 *
 * @param __first
 * @param __last
 * @return
 */
template <class _InputIter, typename = std::_RequireInputIter<_InputIter>>
auto interpolate(_InputIter __first, _InputIter __last) {
  size_t __n = std::distance(__first, __last);

  auto [__1, __2] =
      typename std::iterator_traits<decltype(__first)>::value_type{};

  using poly = polynomial<decltype(__1)>;

  if (!__n) return poly{};

  struct node {
    poly __all, __lack;
  };

  auto __tree = new node[__n << 1];
  auto __iter = __first;

  for (size_t __i = 0; __i != __n; ++__i) {
    auto&& [__a, __b] = *__iter++;
    __tree[__i + __n].__all = {-__a, 1}, __tree[__i + __n].__lack = {1};
  }

  for (size_t __i = __n; --__i;)
    __tree[__i].__all = __tree[__i << 1].__all * __tree[__i << 1 | 1].__all,
    __tree[__i].__lack =
        __tree[__i << 1].__all * std::move(__tree[__i << 1 | 1].__lack) +
        __tree[__i << 1 | 1].__all * std::move(__tree[__i << 1].__lack);

  for (size_t __i = 2; __i != __n << 1; __i += 2)
    __tree[__i].__lack = __tree[__i >> 1].__lack % __tree[__i].__all,
    __tree[__i | 1].__lack =
        std::move(__tree[__i >> 1].__lack %= __tree[__i | 1].__all);

  for (size_t __i = 0; __i != __n; ++__i) {
    auto&& [__a, __b] = *__first++;
    __tree[__i + __n].__lack[0] =
        std::move(__b) / std::move(__tree[__i + __n].__lack[0]);
  }

  for (size_t __i = __n; --__i;)
    __tree[__i].__lack = std::move(__tree[__i << 1].__all) *
                             std::move(__tree[__i << 1 | 1].__lack) +
                         std::move(__tree[__i << 1 | 1].__all) *
                             std::move(__tree[__i << 1].__lack);

  auto __result = std::move(__tree[1].__lack);

  delete[] __tree;

  return __result;
}

// /**
//  * @brief \\prod_{i=0}^{n-1} (x+i) \\bmod x^d.
//  */
// template <class _Tp> auto rising_factorial(_Tp __n, std::size_t __d) {}

// /**
//  * @brief \\prod_{i=0}^{n-1} (x+i).
//  */
// template <class _Tp> auto rising_factorial(_Tp __n) {
//   return rising_factorial(__n, __n);
// }

// /**
//  * @brief \\prod_{i=0}^{n-1} (x-i) \\bmod x^d.
//  */
// template <class _Tp> auto falling_factorial(_Tp __n, std::size_t __d) {
//   auto __f = rising_factorial(__n, __d);
//   for (std::size_t __i = (__n & 1) ^ 1; __i < __d; __i += 2)
//     __f[__i] = -__f[__i];
//   return __f;
// }

// /**
//  * @brief \\prod_{i=0}^{n-1} (x-i).
//  */
// template <class _Tp> auto falling_factorial(_Tp __n) {
//   return falling_factorial(__n, __n);
// }

/**
 * @brief \\sum_{j=0}^{d-1} x^j \\sum_{i=0}^{n-1} i^j.
 */
template <class _Tp> auto power_sums(_Tp __n, std::size_t __d) {
  using return_type = polynomial<_Tp>;
  if (!__d) return return_type{};
  return_type __f(__d), __e(__d);
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
