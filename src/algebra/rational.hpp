#pragma once

/**
 * @file rational.hpp
 * @brief Rational
 */

#include <cassert>

#include "system/operation.hpp"

namespace workspace {

/**
 * @brief Rational
 * @tparam _Tp Ring structure
 */
template <class _Tp> struct rational {
  _Tp __num{0}, __den{1};

  constexpr rational() noexcept = default;

  constexpr rational(const _Tp &__x) noexcept : __num(__x) {}

  constexpr rational(const _Tp &__x, const _Tp &__y) noexcept
      : __num(try_less<_Tp>{}(__y, _Tp(0)) ? -__x : __x),
        __den(try_less<_Tp>{}(__y, _Tp(0)) ? -__y : __y) {}

  constexpr operator bool() const noexcept { return __num != _Tp(0); }

  constexpr rational operator+() const noexcept { return *this; }

  constexpr rational operator-() const noexcept { return {-__num, __den}; }

  constexpr rational operator+(const rational &__x) const noexcept {
    return {__num * __x.__den + __x.__num * __den, __den * __x.__den};
  }

  constexpr rational operator-(const rational &__x) const noexcept {
    return {__num * __x.__den - __x.__num * __den, __den * __x.__den};
  }

  constexpr rational operator*(const rational &__x) noexcept {
    return {__num * __x.__num, __den * __x.__den};
  }

  constexpr rational operator/(const rational &__x) noexcept {
    assert(__x.__num != _Tp(0));
    return {__num * __x.__den, __den * __x.__num};
  }

  constexpr rational &operator+=(const rational &__x) noexcept {
    (__num *= __x.__den) += __den * __x.__num, __den *= __x.__den;
    return *this;
  }

  constexpr rational &operator-=(const rational &__x) noexcept {
    (__num *= __x.__den) -= __den * __x.__num, __den *= __x.__den;
    return *this;
  }

  constexpr rational &operator*=(const rational &__x) noexcept {
    __num *= __x.__num, __den *= __x.__den;
    return *this;
  }

  constexpr rational &operator/=(const rational &__x) noexcept {
    assert(__x.__num != _Tp(0));
    __num *= __x.__den, __den *= __x.__num;
    return *this;
  }

  constexpr bool operator==(const rational &__x) const noexcept {
    return __num == __x.__num && __den == __x.den;
  }

  constexpr bool operator!=(const rational &__x) const noexcept {
    return __num != __x.__num || __den != __x.den;
  }

  constexpr bool operator<(const rational &__x) const noexcept {
    return __num * __x.__den < __den * __x.__num;
  }

  constexpr bool operator>(const rational &__x) const noexcept {
    return __num * __x.__den > __den * __x.__num;
  }

  constexpr bool operator<=(const rational &__x) const noexcept {
    return __num * __x.__den <= __den * __x.__num;
  }

  constexpr bool operator>=(const rational &__x) const noexcept {
    return __num * __x.__den >= __den * __x.__num;
  }
};

}  // namespace workspace
