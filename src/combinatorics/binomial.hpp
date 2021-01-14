#pragma once

/**
 * @file binomial.hpp
 * @brief Binomial Coefficient
 * @date 2021-01-15
 *
 *
 */

#include "../modular/modint.hpp"
#include "factorial.hpp"

namespace workspace {

/**
 * @brief Binomial coefficient for integer args.
 */
template <class Tp> Tp binomial(int_fast32_t __x, int_fast32_t __y) {
  if (!__y) return 1;
  if (__y < 0 || __x < __y) return 0;
  return factorial<Tp>(__x) * factorial_inverse<Tp>(__y) *
         factorial_inverse<Tp>(__x - __y);
}

}  // namespace workspace
