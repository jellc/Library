#pragma once
#include "utils/sfinae.hpp"
template <class T> struct fraction {
  static_assert(is_integral_ext_v<T>);
  T num, den;
  constexpr fraction(const T &num = 0, const T &den = 1) : num(num), den(den) {}
  constexpr fraction operator-() const { return {-num, den}; }
  constexpr fraction operator-(const fraction &rhs) const {
    return {num * rhs.den - rhs.num * den, den * rhs.den};
  }
  constexpr bool operator<(const fraction &rhs) const {
    return operator-(rhs).num < 0;
  }

 private:
  constexpr void normalize();
};
