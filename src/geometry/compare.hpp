#pragma once

/**
 * @file comp_arg.hpp
 * @brief Compare Argument
 */

#include "point.hpp"

namespace workspace {

// Compare by value of `atan2`.
template <class _Scalar> struct less_arg {
  using value_type = point<_Scalar, 2>;
  using first_argument_type = value_type;
  using second_argument_type = value_type;
  using result_type = bool;

  value_type origin;

  constexpr less_arg() noexcept : origin() {}
  constexpr less_arg(const value_type &__o) noexcept : origin(__o) {}

  constexpr bool operator()(const value_type &__p,
                            const value_type &__q) const noexcept {
    if (__p[1] == origin[1])
      return origin[0] <= __p[0] &&
             (origin[1] < __q[1] ||
              (__q[1] == origin[1] && __q[0] < origin[0]));

    return origin[1] < __p[1] ? origin[1] <= __q[1] && origin.ccw(__p, __q)
                              : origin[1] <= __q[1] || origin.ccw(__p, __q);
  }
};

// Compare by value of `atan2`.
template <class _Scalar> struct greater_arg : less_arg<_Scalar> {
  using typename less_arg<_Scalar>::value_type;
  using less_arg<_Scalar>::less_arg;

  constexpr bool operator()(const value_type &__p,
                            const value_type &__q) const noexcept {
    return less_arg<_Scalar>::operator()(__q, __p);
  }
};

// Compare by value of `atan2`.
template <class _Scalar> struct equal_arg : less_arg<_Scalar> {
  using typename less_arg<_Scalar>::value_type;
  using less_arg<_Scalar>::less_arg;

  constexpr bool operator()(const value_type &__p,
                            const value_type &__q) const noexcept {
    return !less_arg<_Scalar>::operator()(__p, __q) &&
           !less_arg<_Scalar>::operator()(__q, __p);
  }
};

}  // namespace workspace
