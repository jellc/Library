#pragma once

/*
 * @file exponential_search.hpp
 * @brief Exponential Search
 */

#include "binary_search.hpp"

namespace workspace {

/*
 * @fn exponential_search
 * @brief Exponential search on a discrete range.
 * @param range Range of search, exclusive
 * @param pred Predicate
 * @return Minimum non-negative integer where pred is false.
 */
template <class Index, class Pred>
typename std::enable_if<
    std::is_convertible<decltype(std::declval<Pred>()(std::declval<Index>())),
                        bool>::value,
    Index>::type
exponential_search(Index range, Pred pred) {
  Index step(1);
  while (step < range && pred(step)) step <<= 1;
  if (range < step) step = range;
  return binary_search(Index(0), step, pred);
}

/*
 * @fn exponential_search
 * @brief Exponential search on the real number line.
 * @param range Range of search
 * @param eps Error tolerance
 * @param pred Predicate
 * @return Boundary point.
 */
template <class Real, class Pred>
typename std::enable_if<
    std::is_convertible<decltype(std::declval<Pred>()(std::declval<Real>())),
                        bool>::value,
    Real>::type
exponential_search(Real range, Real const &eps, Pred pred) {
  Real step(1);
  while (step < range && pred(step)) step += step;
  if (range < step) step = range;
  return binary_search(Real(0), step, eps, pred);
}

}  // namespace workspace
