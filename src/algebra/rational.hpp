#pragma once

/**
 * @file rational.hpp
 * @brief Rational
 */

#include <cassert>

#include "lib/cxx17"
#include "system/operation.hpp"

namespace workspace {

/**
 * @brief Rational.
 * @tparam _Tp Ring structure
 */
template <class _Tp> class rational {
  _Tp __num, __den;

 public:
  _CXX14_CONSTEXPR rational(const _Tp &__x, const _Tp &__y) noexcept
      : __num(__x), __den(__y) {}

  _CXX14_CONSTEXPR rational(const _Tp &__x, _Tp &&__y) noexcept
      : __num(__x), __den(std::move(__y)) {}

  _CXX14_CONSTEXPR rational(_Tp &&__x, const _Tp &__y) noexcept
      : __num(std::move(__x)), __den(__y) {}

  _CXX14_CONSTEXPR rational(_Tp &&__x = 0, _Tp &&__y = 1) noexcept
      : __num(std::move(__x)), __den(std::move(__y)) {}

  _CXX14_CONSTEXPR rational(std::initializer_list<_Tp> __x) noexcept
      : __num(__x.size() > 0 ? *__x.begin() : _Tp(0)),
        __den(__x.size() > 1 ? *std::next(__x.begin()) : _Tp(1)) {}

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

  _CXX14_CONSTEXPR rational operator*(const rational &__x) const noexcept {
    return {__num * __x.__num, __den * __x.__den};
  }

  _CXX14_CONSTEXPR rational operator/(const rational &__x) const noexcept {
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
    __num *= __x.__den, __den *= __x.__num;
    return *this;
  }

  _CXX14_CONSTEXPR bool operator==(const rational &__x) const noexcept {
    return __num * __x.__den == __den * __x.__num;
  }

  _CXX14_CONSTEXPR bool operator!=(const rational &__x) const noexcept {
    return __num * __x.__den != __den * __x.__num;
  }

  _CXX14_CONSTEXPR bool operator<(const rational &__x) const noexcept {
    return (__den > 0) ^ (__x.__den > 0)
               ? __num * __x.__den > __den * __x.__num
               : __num * __x.__den < __den * __x.__num;
  }

  _CXX14_CONSTEXPR bool operator>(const rational &__x) const noexcept {
    return (__den > 0) ^ (__x.__den > 0)
               ? __num * __x.__den < __den * __x.__num
               : __num * __x.__den > __den * __x.__num;
  }

  _CXX14_CONSTEXPR bool operator<=(const rational &__x) const noexcept {
    return !operator>(__x);
  }

  _CXX14_CONSTEXPR bool operator>=(const rational &__x) const noexcept {
    return !operator<(__x);
  }

  _CXX14_CONSTEXPR
  std::enable_if_t<std::is_swappable<_Tp>::value> swap(rational &__x) noexcept {
    std::swap(__num, __x.__num), std::swap(__den, __x.__den);
  }

  template <size_t _Nm> friend constexpr auto &get(rational &__x) noexcept {
    static_assert(_Nm < 2);
    if _CXX17_CONSTEXPR (_Nm) return __x.__den;
    return __x.__num;
  }

  template <size_t _Nm>
  friend constexpr const auto &get(const rational &__x) noexcept {
    static_assert(_Nm < 2);
    if _CXX17_CONSTEXPR (_Nm) return __x.__den;
    return __x.__num;
  }

  template <size_t _Nm> friend constexpr auto &&get(rational &&__x) noexcept {
    static_assert(_Nm < 2);
    if _CXX17_CONSTEXPR (_Nm) return std::move(__x.__den);
    return std::move(__x.__num);
  }
};

}  // namespace workspace

namespace std {

template <class _Tp>
struct tuple_size<workspace::rational<_Tp>> : integral_constant<size_t, 2> {};

template <class _Tp, size_t _Nm>
struct tuple_element<_Nm, workspace::rational<_Tp>> {
  using type = _Tp;
};

}  // namespace std
