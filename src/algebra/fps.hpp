#pragma once

/**
 * @file fps.hpp
 * @brief Formal Power Series
 */

#include "polynomial.hpp"

namespace workspace {

namespace _fps_impl {

template <class _Tp> decltype(auto) _exp(_Tp __x) { return exp(__x); }

template <class _Tp> decltype(auto) _log(_Tp __x) { return log(__x); }

template <class _Tp, class _Tp2> decltype(auto) _pow(_Tp __x, _Tp2 __y) {
  return pow(__x, __y);
}

template <class _Tp> decltype(auto) _sqrt(_Tp __x) { return sqrt(__x); }

template <class _Tp, typename = void> struct has_exp : std::false_type {};

template <class _Tp>
struct has_exp<_Tp, std::enable_if_t<std::is_same<
                        _Tp, decltype(exp(std::declval<_Tp>()))>::value>>
    : std::true_type {};

template <class _Tp, typename = void> struct has_log : std::false_type {};

template <class _Tp>
struct has_log<_Tp, std::enable_if_t<std::is_same<
                        _Tp, decltype(log(std::declval<_Tp>()))>::value>>
    : std::true_type {};

template <class _T1, class _T2, typename = void>
struct has_pow : std::false_type {};

template <class _T1, class _T2>
struct has_pow<
    _T1, _T2,
    std::enable_if_t<std::is_same<
        _T1, decltype(pow(std::declval<_T1>(), std::declval<_T2>()))>::value>>
    : std::true_type {};

template <class _Tp, typename = void> struct has_sqrt : std::false_type {};

template <class _Tp>
struct has_sqrt<_Tp, std::enable_if_t<std::is_same<
                         _Tp, decltype(sqrt(std::declval<_Tp>()))>::value>>
    : std::true_type {};

}  // namespace _fps_impl

/**
 * @brief Formal Power Series.
 * @tparam _Tp Field structure
 */
template <class _Tp> class formal_power_series : public polynomial<_Tp> {
  using poly = polynomial<_Tp>;
  using fps = formal_power_series;

 public:
  using poly::poly;
  using typename poly::size_type;

  formal_power_series(const poly& __x) noexcept : poly(__x) {}
  formal_power_series(poly&& __x) noexcept : poly(std::move(__x)) {}

  fps& operator=(const poly& __x) noexcept {
    poly::operator=(__x);
    return *this;
  }
  fps& operator=(poly&& __x) noexcept {
    poly::operator=(std::move(__x));
    return *this;
  }

  fps& operator<<=(size_type __n) noexcept {
    for (auto __i = std::move_backward(
             poly::_M_impl._M_start,
             poly::_M_impl._M_finish - std::min(__n, poly::size()),
             poly::_M_impl._M_finish);
         __i != poly::_M_impl._M_start;) {
      *--__i = _Tp();
    }
    return *this;
  }

  fps& operator>>=(size_type __n) noexcept {
    for (auto __i =
             std::move(poly::_M_impl._M_start + std::min(__n, poly::size()),
                       poly::_M_impl._M_finish, poly::_M_impl._M_start);
         __i != poly::_M_impl._M_finish; ++__i) {
      *__i = _Tp();
    }
    return *this;
  }

  fps operator<<(size_type __n) const noexcept {
    return fps(*this).operator<<=(__n);
  }

  fps operator>>(size_type __n) const noexcept {
    return fps(*this).operator>>=(__n);
  }

  fps operator+() const noexcept { return *this; }

  fps operator-() const noexcept {
    fps __x = *this;
    for (auto __i = __x._M_impl._M_start; __i != __x._M_impl._M_finish; ++__i)
      *__i = -*__i;
    return __x;
  }

  fps& operator+=(const fps& __x) noexcept {
    if (poly::size() < __x.size()) poly::resize(__x.size());
    for (size_type __i = 0; __i != __x.size(); ++__i)
      poly::operator[](__i) += __x[__i];
    return *this;
  }

  fps& operator-=(const fps& __x) noexcept {
    if (poly::size() < __x.size()) poly::resize(__x.size());
    for (size_type __i = 0; __i != __x.size(); ++__i)
      poly::operator[](__i) -= __x[__i];
    return *this;
  }

  fps& operator*=(const _Tp& __c) noexcept {
    for (auto __i = poly::begin(); __i != poly::end(); ++__i) *__i *= __c;
    return *this;
  }

  fps& operator*=(const fps& __x) noexcept {
    auto __n = std::max(poly::size(), __x.size());
    poly::operator*=(__x);
    poly::resize(__n);
    return *this;
  }

  fps& operator/=(const _Tp& __c) noexcept {
    poly::operator/=(__c);
    return *this;
  }

  fps& operator/=(const fps& __x) noexcept {
    auto __n = std::max(poly::size(), __x.size());
    poly::operator*=(__x.inv(__n));
    poly::resize(__n);
    return *this;
  }

  template <class _T> fps operator+(_T&& __x) const noexcept {
    return fps(*this).operator+=(std::forward<_T>(__x));
  }

  template <class _T> fps operator-(_T&& __x) const noexcept {
    return fps(*this).operator-=(std::forward<_T>(__x));
  }

  template <class _T> fps operator*(_T&& __x) const noexcept {
    return fps(*this).operator*=(std::forward<_T>(__x));
  }

  template <class _T> fps operator/(_T&& __x) const noexcept {
    return fps(*this).operator/=(std::forward<_T>(__x));
  }

  friend fps operator*(const _Tp& __c, const fps& __x) noexcept {
    return __x * __c;
  }

 protected:
  using poly::_dft;
  using poly::_idft;

  fps _exp(size_type __n) const noexcept {
    if (__n == 1) return {1};
    size_type __len = 2;
    while (__len < __n) __len <<= 1;

    fps __w(__len);
    auto __wp = __w.data(), __xp = new _Tp[__len], __yp = new _Tp[__len]{},
         __zp = new _Tp[__len];

    *__wp = 1, *(__wp + (__len >> 1)) = 1;

    for (size_type __i = 1;; __i <<= 1) {
      std::copy_n(__wp, __i, __xp);

      std::copy_n(__wp + (__len >> 1), __i, __yp);

      std::fill(std::copy_n(poly::_M_impl._M_start + 1,
                            std::min(__i << 1, poly::size()) - 1, __zp),
                __zp + (__i << 1), _Tp(0));

      for (size_type __j = 1; __j != (__i << 1); ++__j) __zp[__j - 1] *= __j;

      _dft(__xp, __xp + (__i << 1));

      _dft(__yp, __yp + (__i << 1));

      _dft(__zp, __zp + (__i << 1));

      for (size_type __j = 0; __j != (__i << 1); ++__j) __zp[__j] *= __xp[__j];

      _idft(__zp, __zp + (__i << 1));

      std::fill(std::move(__zp + __i - 1, __zp + (__i << 1) - 1, __zp),
                __zp + (__i << 1), _Tp(0));

      _dft(__zp, __zp + (__i << 1));

      for (size_type __j = 0; __j != (__i << 1); ++__j) __zp[__j] *= __yp[__j];

      _idft(__zp, __zp + (__i << 1));

      for (size_type __j = 0; __j != __i; ++__j)
        __zp[__j] /= __j + __i, __zp[__j + __i] = 0;

      _dft(__zp, __zp + (__i << 1));

      for (size_type __j = 0; __j != (__i << 1); ++__j)
        __zp[__j] *= static_cast<_Tp&&>(__xp[__j]);

      _idft(__zp, __zp + (__i << 1));

      std::move(__zp, __zp + __i, __wp + __i);

      if (__i << 1 == __len) break;

      std::copy_n(__wp, __i << 1, __zp);

      _dft(__zp, __zp + (__i << 1));

      for (size_type __j = 0; __j != (__i << 1); ++__j) __zp[__j] *= -__yp[__j];

      _idft(__zp, __zp + (__i << 1));

      std::fill(std::move(__zp + __i, __zp + (__i << 1), __zp),
                __zp + (__i << 1), _Tp(0));

      _dft(__zp, __zp + (__i << 1));

      for (size_type __j = 0; __j != (__i << 1); ++__j)
        __zp[__j] *= static_cast<_Tp&&>(__yp[__j]);

      _idft(__zp, __zp + (__i << 1));

      std::move(__zp, __zp + __i, __wp + (__len >> 1) + __i);
    }

    delete[] __xp;
    delete[] __yp;
    delete[] __zp;

    __w.resize(__n);
    return __w;
  }

  fps _sqrt(size_type __n) const noexcept {
    if (!__n) return {};

    size_type __len = 1;
    while (__len < __n) __len <<= 1;

    poly __x(__len);
    auto __xp = __x.data(), __yp = new _Tp[__len], __zp = new _Tp[__len]{},
         __wp = new _Tp[__len]{};

    *__yp = (*__xp = 1) / 2;

    for (size_type __i = 1; __i != __len; __i <<= 1) {
      std::copy_n(__xp, __i, __zp);

      _dft(__zp, __zp + (__i << 1));

      for (size_type __j = 0; __j != (__i << 1); ++__j) __zp[__j] *= -__zp[__j];

      _idft(__zp, __zp + (__i << 1));

      std::fill(std::move(__zp + __i, __zp + (__i << 1), __zp),
                __zp + (__i << 1), _Tp(0));

      for (size_type __j = 0; __j != __i && __i + __j < poly::size(); ++__j)
        __zp[__j] += *(poly::_M_impl._M_start + __i + __j);

      _dft(__zp, __zp + (__i << 1));

      std::copy_n(__yp, __i, __wp);

      _dft(__wp, __wp + (__i << 1));

      for (size_type __j = 0; __j != (__i << 1); ++__j) __zp[__j] *= __wp[__j];

      _idft(__zp, __zp + (__i << 1));

      if (__i << 1 == __len)
        std::move(__zp, __zp + __i, __xp + __i);

      else {  // update inv of x, y
        std::copy(__zp, __zp + __i, __xp + __i);
        std::move(__zp, __zp + __i, __zp + __i);
        std::copy_n(__xp, __i, __zp);

        _dft(__zp, __zp + (__i << 1));

        for (size_type __j = 0; __j != (__i << 1); ++__j)
          __zp[__j] *= __wp[__j] * -2;

        _idft(__zp, __zp + (__i << 1));

        std::fill(std::move(__zp + __i, __zp + (__i << 1), __zp),
                  __zp + (__i << 1), _Tp(0));

        _dft(__zp, __zp + (__i << 1));

        for (size_type __j = 0; __j != (__i << 1); ++__j)
          __zp[__j] *= static_cast<_Tp&&>(__wp[__j]);

        _idft(__zp, __zp + (__i << 1));

        std::move(__zp, __zp + __i, __yp + __i);
      }
    }

    delete[] __yp;
    delete[] __zp;
    delete[] __wp;

    __x.resize(__n);
    return __x;
  }

 public:
  /**
   * @brief Exponential.
   */
  fps exp() const noexcept { return exp(poly::size()); }

  /**
   * @brief Exponential modulo x^n.
   *
   * @param __n Degree of modulus
   * @return
   */
  fps exp(size_type __n) const noexcept {
    if (!__n) return {};
    if (poly::empty()) return {1};

    if _CXX17_CONSTEXPR (_fps_impl::has_exp<_Tp>::value) {
      auto __x = _exp(__n);
      __x *= _fps_impl::_exp(*poly::_M_impl._M_start);
      return __x;
    }

    assert(*poly::_M_impl._M_start == _Tp(0));
    return _exp(__n);
  }

  /**
   * @brief Logarithm.
   */
  fps log() const noexcept { return log(poly::size()); }

  /**
   * @brief Logarithm modulo x^n.
   *
   * @param __n Degree of modulus
   * @return
   */
  fps log(size_type __n) const noexcept {
    assert(!poly::empty());

    if _CXX17_CONSTEXPR (_fps_impl::has_log<_Tp>::value) {
      assert(*poly::_M_impl._M_start != _Tp(0));
      if (!__n) return {};
      if (__n == 1) return {0};

      auto __x = *this;
      auto __c = *poly::_M_impl._M_start;
      for (auto&& __a : __x) __a /= __c;

      __x = __x.inv(__n - 1) * __x.deriv();
      __x.resize(__n);
      std::move_backward(__x.begin(), __x.begin() + __n - 1, __x.begin() + __n);
      for (size_type __i = 1; __i != __n; ++__i) __x[__i] /= __i;

      __x[0] = _fps_impl::_log(__c);
      return __x;
    }

    assert(*poly::_M_impl._M_start == _Tp(1));
    if (!__n) return {};
    if (__n == 1) return {0};

    auto __x = poly::inv(__n - 1).operator*(poly::deriv());
    __x.resize(__n);
    std::move_backward(__x.begin(), __x.begin() + __n - 1, __x.begin() + __n);
    for (size_type __i = 1; __i != __n; ++__i) __x[__i] /= __i;

    __x[0] = 0;
    return __x;
  }

  template <class _Tp2> fps pow(_Tp2 __e) const noexcept {
    return pow(__e, poly::size());
  }

  template <class _Tp2> fps pow(_Tp2 __e, size_type __n) const noexcept {
    if (!__n) return {};

    if (__e == _Tp2(0)) {
      fps __x(__n, 0);
      __x[0] = 1;
      return __x;
    }

    auto __first = poly::_M_impl._M_start;

    if _CXX17_CONSTEXPR (is_integral_ext<_Tp2>::value) {
      if (__e > 0) {
        size_type __o = 0;
        while (__first != poly::_M_impl._M_finish && *__first == _Tp(0))
          ++__first, ++__o;

        if ((__n - 1) / __e < __o || __first == poly::_M_impl._M_finish)
          return fps(__n, 0);

        __o *= __e;
        fps __x(__first, poly::_M_impl._M_finish);

        if _CXX17_CONSTEXPR (_fps_impl::has_pow<_Tp, _Tp2>::value) {
          assert(*__first != _Tp(0));
          auto __c = *__first;
          for (auto&& __a : __x) __a /= __c;

          __x = __x.log(__n - __o);
          __x *= __e;
          __x = __x.exp(__n - __o);

          __c = _fps_impl::_pow(__c, __e);
          for (auto&& __a : __x) __a *= __c;

          __x.insert(__x.begin(), __o, _Tp(0));
          return __x;
        }

        assert(*__first == _Tp(1));

        __x = __x.log(__n - __o);
        __x *= __e;
        __x = __x.exp(__n - __o);

        __x.insert(__x.begin(), __o, _Tp(0));
        return __x;
      }
    }

    if _CXX17_CONSTEXPR (_fps_impl::has_pow<_Tp, _Tp2>::value) {
      assert(*__first != _Tp(0));

      fps __x(__first, poly::_M_impl._M_finish);

      auto __c = *__first;
      for (auto&& __a : __x) __a /= __c;

      __x = __x.log(__n);
      __x *= __e;
      __x = __x.exp(__n);

      __c = _fps_impl::_pow(__c, __e);
      for (auto&& __a : __x) __a *= __c;

      return __x;
    }

    assert(*__first == _Tp(1));

    auto __x = log(__n);
    __x *= __e;
    return __x.exp(__n);
  }

  /**
   * @brief Square root.
   *
   * @return Square root of the %fps if exists. Otherwise an empty object.
   */
  fps sqrt() const noexcept { return sqrt(poly::size()); }

  /**
   * @brief Square root.
   *
   * @param __n
   * @return Square root of the %fps if exists. Otherwise an empty object.
   */
  fps sqrt(size_type __n) const noexcept {
    auto __first = poly::_M_impl._M_start, __last = poly::_M_impl._M_finish;

    size_type __o = 0;
    while (__first != __last && *__first == _Tp(0)) ++__first, ++__o;

    if (__first == __last) return fps(__n);

    if (__o & 1) return {};
    __o >>= 1;
    __n -= __o;

    if _CXX17_CONSTEXPR (_fps_impl::has_sqrt<_Tp>::value) {
      auto __c = *__first;
      fps __x(__first, __last);

      for (auto&& __a : __x) __a /= __c;
      __x = __x._sqrt(__n);

      __c = _fps_impl::_sqrt(__c);
      if (__c < 0) return {};  // No solution.

      for (auto&& __a : __x) __a *= __c;

      return __x <<= __o;
    }

    assert(*__first == _Tp(1));
    return _sqrt(__n) <<= __o;
  }
};

}  // namespace workspace
