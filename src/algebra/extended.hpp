#pragma once

/**
 * @file extended.hpp
 * @brief Extended Numeric Type
 */

#include <cstdint>
#include <type_traits>

namespace workspace {

template <class _Tp> constexpr auto sign_of(const _Tp &__x) noexcept {
  return __x != _Tp(0) ? (__x > _Tp(0) ? +1 : -1) : 0;
}

// Extended numeric type.
template <class _Tp> class extended {
  bool infinite{};
  int_least8_t sign{};  // in {0, +1, -1}
  _Tp value{};          // is 0 if infinite

  template <class _Os>
  friend _Os &operator<<(_Os &__os, const extended &__x) noexcept {
    return __x.infinite ? __os << (__x.sign > 0 ? '+' : '-') << "infinity"
                        : __os << __x.value;
  }

  template <class _Is>
  friend _Is &operator>>(_Is &__is, extended &__x) noexcept {
    __x.infinite = false;
    __is >> __x.value;
    __x.sign = sign_of(__x.value);
    return __is;
  }

  constexpr extended(bool __x, int_least8_t __y, const _Tp &__z) noexcept
      : infinite(__x), sign(__y), value(__z) {}

 public:
  constexpr static extended infinity{true, +1, 0};

  constexpr extended() noexcept {}

  constexpr extended(const _Tp &__x) noexcept
      : sign(sign_of(__x)), value(__x) {}

  constexpr std::enable_if_t<std::is_swappable<_Tp>::value> swap(
      extended &__x) noexcept {
    std::swap(infinite, __x.infinite);
    std::swap(sign, __x.sign);
    std::swap(value, __x.value);
  }

  // constexpr operator _Tp &() noexcept { return value; }

  constexpr operator _Tp const &() const noexcept { return value; }

  constexpr operator bool() const noexcept { return sign; }

  constexpr extended operator+() const noexcept { return *this; }

  constexpr extended operator-() const noexcept {
    return extended(infinite, -sign, -value);
  }

  constexpr extended &operator+=(const extended &__x) noexcept {
    if (!infinite) {
      if (__x.infinite)
        infinite = true, sign = __x.sign, value = 0;
      else
        value += __x.value;
    }
    return *this;
  }

  constexpr extended &operator+=(const _Tp &__x) noexcept {
    if (!infinite) value += __x;
    return *this;
  }

  constexpr extended &operator-=(const extended &__x) noexcept {
    return operator+=(-__x);
  }

  constexpr extended &operator-=(const _Tp &__x) noexcept {
    return operator+=(-__x);
  }

  constexpr extended &operator*=(const extended &__x) noexcept {
    if (sign *= __x.sign)
      infinite = infinite || __x.infinite, value *= __x.value;
    else
      infinite = false, value = 0;
    return *this;
  }

  constexpr extended &operator*=(const _Tp &__x) noexcept {
    if (sign *= sign_of(__x))
      value *= __x;
    else
      infinite = false, value = 0;
    return *this;
  }

  constexpr extended &operator/=(const extended &__x) noexcept {
    if (__x.infinite)
      infinite = false, sign = 0, value = 0;
    else if (__x.sign)
      sign *= __x.sign, value /= __x.value;
    else
      infinite = true, value = 0;
    return *this;
  }

  constexpr extended &operator/=(const _Tp &__x) noexcept {
    auto __s = sign_of(__x);
    if (__s)
      sign *= __s, value /= __x;
    else
      infinite = true, value = 0;
    return *this;
  }

  constexpr extended operator+(const extended &__x) const noexcept {
    return extended(*this) += __x;
  }

  constexpr extended operator-(const extended &__x) const noexcept {
    return extended(*this) -= __x;
  }

  constexpr extended operator*(const extended &__x) const noexcept {
    return extended(*this) *= __x;
  }

  constexpr extended operator/(const extended &__x) const noexcept {
    return extended(*this) /= __x;
  }

  constexpr extended operator+(const _Tp &__x) const noexcept {
    return extended(*this) += __x;
  }

  constexpr extended operator-(const _Tp &__x) const noexcept {
    return extended(*this) -= __x;
  }

  constexpr extended operator*(const _Tp &__x) const noexcept {
    return extended(*this) *= __x;
  }

  constexpr extended operator/(const _Tp &__x) const noexcept {
    return extended(*this) /= __x;
  }

  constexpr friend extended operator+(const _Tp &__x,
                                      const extended &__y) noexcept {
    return extended(__x) += __y;
  }

  constexpr friend extended operator-(const _Tp &__x,
                                      const extended &__y) noexcept {
    return extended(__x) -= __y;
  }

  constexpr friend extended operator*(const _Tp &__x,
                                      const extended &__y) noexcept {
    return extended(__x) *= __y;
  }

  constexpr friend extended operator/(const _Tp &__x,
                                      const extended &__y) noexcept {
    return extended(__x) /= __y;
  }

  constexpr bool operator==(const extended &__x) const noexcept {
    return infinite == __x.infinite && sign == __x.sign && value == __x.value;
  }

  constexpr bool operator==(const _Tp &__x) const noexcept {
    return !infinite && value == __x;
  }

  constexpr friend bool operator==(const _Tp &__x,
                                   const extended &__y) noexcept {
    return __y.operator==(__x);
  }

  constexpr bool operator!=(const extended &__x) const noexcept {
    return !operator==(__x);
  }

  constexpr bool operator!=(const _Tp &__x) const noexcept {
    return !operator==(__x);
  }

  constexpr friend bool operator!=(const _Tp &__x,
                                   const extended &__y) noexcept {
    return __y.operator!=(__x);
  }

  constexpr bool operator<(const extended &__x) const noexcept {
    auto __l = sign * infinite, __r = __x.sign * __x.infinite;
    return __l != __r ? __l < __r : value < __x.value;
  }

  constexpr bool operator<=(const extended &__x) const noexcept {
    auto __l = sign * infinite, __r = __x.sign * __x.infinite;
    return __l != __r ? __l < __r : value <= __x.value;
  }

  constexpr bool operator<(const _Tp &__x) const noexcept {
    return infinite ? sign < 0 : value < __x;
  }

  constexpr bool operator<=(const _Tp &__x) const noexcept {
    return infinite ? sign < 0 : value <= __x;
  }

  constexpr bool operator>(const extended &__x) const noexcept {
    return __x.operator<(*this);
  }

  constexpr bool operator>=(const extended &__x) const noexcept {
    return __x.operator<=(*this);
  }

  constexpr bool operator>(const _Tp &__x) const noexcept {
    return infinite ? sign > 0 : value > __x;
  }

  constexpr bool operator>=(const _Tp &__x) const noexcept {
    return infinite ? sign > 0 : value >= __x;
  }

  constexpr friend bool operator<(const _Tp &__x,
                                  const extended &__y) noexcept {
    return __y.operator>(__x);
  }

  constexpr friend bool operator>(const _Tp &__x,
                                  const extended &__y) noexcept {
    return __y.operator<(__x);
  }

  constexpr friend bool operator<=(const _Tp &__x,
                                   const extended &__y) noexcept {
    return __y.operator>=(__x);
  }

  constexpr friend bool operator>=(const _Tp &__x,
                                   const extended &__y) noexcept {
    return __y.operator<=(__x);
  }
};

}  // namespace workspace
