#pragma once

/**
 * @file point.hpp
 * @brief Point
 */

#include <tuple>

namespace workspace {

// Point class as position vector.
template <class _Scalar, std::size_t _Dimension = 2>
struct point : std::array<_Scalar, _Dimension> {
  using container_type = std::array<_Scalar, _Dimension>;

  using typename container_type::size_type;
  using typename container_type::value_type;

 protected:
  using container_type::_M_elems;

 public:
  // Itself.
  constexpr point operator+() const noexcept { return *this; }

  // Vector negation.
  constexpr point operator-() const noexcept {
    point __p;
    for (size_type __i = 0; __i != _Dimension; ++__i) __p[__i] = -_M_elems[__i];
    return __p;
  }

  // Vector sum.
  constexpr point &operator+=(const point &__p) noexcept {
    for (size_type __i = 0; __i != _Dimension; ++__i) _M_elems[__i] += __p[__i];
    return *this;
  }

  // Vector sum.
  constexpr point operator+(const point &__p) const noexcept {
    return point(*this) += __p;
  }

  // Vector difference.
  constexpr point &operator-=(const point &__p) noexcept {
    for (size_type __i = 0; __i != _Dimension; ++__i) _M_elems[__i] -= __p[__i];
    return *this;
  }

  // Vector difference.
  constexpr point operator-(const point &__p) const noexcept {
    return point(*this) -= __p;
  }

  // Scalar multiplication.
  constexpr point &operator*=(value_type __c) noexcept {
    for (size_type __i = 0; __i != _Dimension; ++__i) _M_elems[__i] *= __c;
    return *this;
  }

  // Scalar multiplication.
  constexpr point operator*(value_type __c) const noexcept {
    return point(*this) *= __c;
  }

  // Scalar division.
  constexpr point &operator/=(value_type __c) noexcept {
    for (size_type __i = 0; __i != _Dimension; ++__i) _M_elems[__i] /= __c;
    return *this;
  }

  // Scalar division.
  constexpr point operator/(value_type __c) const noexcept {
    return point(*this) /= __c;
  }

  // Dot product.
  constexpr value_type dot(const point &__p) const noexcept {
    value_type __ret = 0;
    for (size_type __i = 0; __i != _Dimension; ++__i)
      __ret += _M_elems[__i] * __p[__i];
    return __ret;
  }

  // Euclidian norm.
  constexpr value_type norm() const noexcept {
    value_type __ret = 0;
    for (size_type __i = 0; __i != _Dimension; ++__i)
      __ret += _M_elems[__i] * _M_elems[__i];
    return sqrt(__ret);
  }

  // Euclidian distance.
  constexpr value_type distance(const point &__p) const noexcept {
    return operator-(__p).norm();
  }

  constexpr auto arg() const noexcept {
    return atan2(_M_elems[1], _M_elems[0]);
  }

  // Cross product.
  constexpr auto cross(const point &__p) const noexcept {
    if constexpr (_Dimension == 2)
      return _M_elems[0] * __p[1] - _M_elems[1] * __p[0];
    else if constexpr (_Dimension == 3)
      return point{_M_elems[1] * __p[2] - _M_elems[2] * __p[1],
                   _M_elems[2] * __p[0] - _M_elems[0] * __p[2],
                   _M_elems[0] * __p[1] - _M_elems[1] * __p[0]};
  }

  /**
   * @brief Counter-clockwise.
   * @param __p
   * @param __q
   * @return Whether __p is in the counter-clockwise direction of __q around
   this.
   */
  constexpr bool ccw(const point &__p, const point &__q) const noexcept {
    return value_type(0) < operator-(__p).cross(operator-(__q));
  }
};

#if __cpp_deduction_guides >= 201606
template <typename _Tp, typename... _Up>
point(_Tp, _Up...)
    -> point<std::enable_if_t<(std::is_same_v<_Tp, _Up> && ...), _Tp>,
             1 + sizeof...(_Up)>;
#endif

}  // namespace workspace

namespace std {

template <class _Scalar, size_t _Dimension>
struct tuple_size<workspace::point<_Scalar, _Dimension>>
    : tuple_size<array<_Scalar, _Dimension>> {};

template <size_t _Nm, class _Scalar, size_t _Dimension>
struct tuple_element<_Nm, workspace::point<_Scalar, _Dimension>>
    : tuple_element<_Nm, array<_Scalar, _Dimension>> {};

}  // namespace std
