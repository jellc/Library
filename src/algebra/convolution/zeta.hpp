#pragma once

/**
 * @file zeta.hpp
 * @brief Fast Zeta Transform
 */

#include <cstddef>

#include "lib/bit"

namespace workspace {

/**
 * @brief Fast zeta transform on a lattice.
 * @param f Value list of the function
 * @param n Number of join-irreducible elements, bit-width of indices
 * @return Value list of resulting function.
 */
template <class A> A fast_zeta(A f, size_t n) {
  while (n--)
    for (size_t s = 0; s != std::size(f); ++s)
      if (s >> n & 1) f[s] += f[s ^ 1 << n];
  return f;
}

/**
 * @brief Fast zeta transform on a lattice.
 * @param f Value list of the function
 * @return Value list of resulting function.
 */
template <class A> A fast_zeta(A const &f) {
  return fast_zeta(f, __countr_zero(__bit_floor(std::size(f))));
}

/**
 * @brief Inverse of fast zeta transform.
 * @param f Value list of the function
 * @param n Number of join-irreducible elements, bit-width of indices
 * @return Value list of resulting function.
 */
template <class A> A fast_mobius(A f, size_t n) {
  while (n--)
    for (size_t s = 0; s != std::size(f); ++s)
      if (s >> n & 1) f[s] -= f[s ^ 1 << n];
  return f;
}

/**
 * @brief Inverse of fast zeta transform.
 * @param f Value list of the function
 * @return Value list of resulting function.
 */
template <class A> A fast_mobius(A const &f) {
  return fast_mobius(f, __countr_zero(__bit_floor(std::size(f))));
}

}  // namespace workspace
