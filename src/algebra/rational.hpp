#pragma once

/**
 * @file rational.hpp
 * @brief Rational
 */

#include <cassert>

#include "lib/cxx14"
#include "system/operation.hpp"

namespace workspace {

/**
 * @brief Rational
 * @tparam _Tp Ring structure
 */
template <class _Tp> struct rational {
  _Tp __num{0}, __den{1};

  _CXX14_CONSTEXPR rational() noexcept = default;

  _CXX14_CONSTEXPR rational(const _Tp &__x) noexcept : __num(__x) {}

  _CXX14_CONSTEXPR rational(const _Tp &__x, const _Tp &__y) noexcept
      : __num(try_less<_Tp>{}(__y, _Tp(0)) ? -__x : __x),
        __den(try_less<_Tp>{}(__y, _Tp(0)) ? -__y : __y) {}

  _CXX14_CONSTEXPR operator bool() const noexcept { return __num != _Tp(0); }

  _CXX14_CONSTEXPR rational operator+() const noexcept { return *this; }

  _CXX14_CONSTEXPR rational operator-() const noexcept {
    return {-__num, __den};
  }

  _CXX14_CONSTEXPR rational operator+(const rational &__x) const noexcept {
    return {__num * __x.__den + __x.__num * __den, __den * __x.__den};
  }

  _CXX14_CONSTEXPR rational operator-(const rational &__x) const noexcept {
    return {__num * __x.__den - __x.__num * __den, __den * __x.__den};
  }

  _CXX14_CONSTEXPR rational operator*(const rational &__x) noexcept {
    return {__num * __x.__num, __den * __x.__den};
  }

  _CXX14_CONSTEXPR rational operator/(const rational &__x) noexcept {
    assert(__x.__num != _Tp(0));
    return {__num * __x.__den, __den * __x.__num};
  }

  _CXX14_CONSTEXPR rational &operator+=(const rational &__x) noexcept {
    (__num *= __x.__den) += __den * __x.__num, __den *= __x.__den;
    return *this;
  }

  _CXX14_CONSTEXPR rational &operator-=(const rational &__x) noexcept {
    (__num *= __x.__den) -= __den * __x.__num, __den *= __x.__den;
    return *this;
  }

  _CXX14_CONSTEXPR rational &operator*=(const rational &__x) noexcept {
    __num *= __x.__num, __den *= __x.__den;
    return *this;
  }

  _CXX14_CONSTEXPR rational &operator/=(const rational &__x) noexcept {
    assert(__x.__num != _Tp(0));
    __num *= __x.__den, __den *= __x.__num;
    return *this;
  }

  _CXX14_CONSTEXPR bool operator==(const rational &__x) const noexcept {
    return __num == __x.__num && __den == __x.den;
  }

  _CXX14_CONSTEXPR bool operator!=(const rational &__x) const noexcept {
    return __num != __x.__num || __den != __x.den;
  }

  _CXX14_CONSTEXPR bool operator<(const rational &__x) const noexcept {
    return __num * __x.__den < __den * __x.__num;
  }

  _CXX14_CONSTEXPR bool operator>(const rational &__x) const noexcept {
    return __num * __x.__den > __den * __x.__num;
  }

  _CXX14_CONSTEXPR bool operator<=(const rational &__x) const noexcept {
    return __num * __x.__den <= __den * __x.__num;
  }

  _CXX14_CONSTEXPR bool operator>=(const rational &__x) const noexcept {
    return __num * __x.__den >= __den * __x.__num;
  }
};

}  // namespace workspace
