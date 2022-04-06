#pragma once

/**
 * @file complex.hpp
 * @brief Complex Number
 */

namespace workspace {

// Complex number.
template <class _Tp> class complex {
  _Tp re, im;

  friend constexpr complex conj(const complex &x) noexcept {
    return {x.re, -x.im};
  }

  friend constexpr _Tp abs(const complex &x) noexcept {
    return hypot(x.re, x.im);
  }

  friend constexpr _Tp arg(const complex &x) noexcept {
    return atan2(x.re, x.im);
  }

  template <class _Is>
  friend constexpr _Is &operator>>(_Is &__is, complex &x) noexcept {
    return __is >> x.re >> x.im;
  }

  template <class _Os>
  friend constexpr _Os &operator<<(_Os &__os, const complex &x) noexcept {
    return __os << x.re << ' ' << x.im;
  }

 public:
  constexpr complex() noexcept : re{}, im{} {}
  constexpr complex(_Tp _re) noexcept : re{_re}, im{} {}
  constexpr complex(_Tp _re, _Tp _im) noexcept : re{_re}, im{_im} {}

  constexpr _Tp real() const noexcept { return re; }
  constexpr void real(_Tp _re) noexcept { re = _re; }

  constexpr _Tp imag() const noexcept { return im; }
  constexpr void imag(_Tp _im) noexcept { im = _im; }

  constexpr complex operator+() const noexcept { return *this; }
  constexpr complex operator-() const noexcept { return {-re, -im}; }

  constexpr complex &operator+=(const complex &x) noexcept {
    return re += x.re, im += x.im, *this;
  }
  constexpr complex &operator-=(const complex &x) noexcept {
    return re -= x.re, im -= x.im, *this;
  }
  constexpr complex &operator*=(const complex &x) noexcept {
    _Tp _re{re * x.re - im * x.im};
    return im = im * x.re + x.im * re, re = _re, *this;
  }
  constexpr complex &operator*=(_Tp x) noexcept {
    return re *= x, im *= x, *this;
  }
  constexpr complex &operator/=(const complex &x) noexcept {
    return (*this *= conj(x)) /= re * re + im * im;
  }
  constexpr complex &operator/=(_Tp x) noexcept {
    return re /= x, im /= x, *this;
  }

  constexpr complex operator+(const complex &x) const noexcept {
    return {re + x.re, im + x.im};
  }
  constexpr complex operator-(const complex &x) const noexcept {
    return {re - x.re, im - x.im};
  }

  constexpr complex operator*(const complex &x) const noexcept {
    return complex(*this) *= x;
  }

  constexpr complex operator*(_Tp x) const noexcept { return {re * x, im * x}; }

  constexpr complex operator/(const complex &x) const noexcept {
    return complex(*this) /= x;
  }

  constexpr complex operator/(_Tp x) const noexcept { return {re / x, im / x}; }
};

}  // namespace workspace
