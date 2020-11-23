#pragma once

/*
 * @file exponential_search.hpp
 * @brief Exponential Search
 */

#include "binary_search.hpp"

#if __cplusplus >= 201703L

namespace workspace {

/*
 * @fn exponential_search
 * @brief Exponential search on a discrete range.
 * @param range Range of search, exclusive
 * @param pred Predicate
 * @return The minimum non-negative integer where pred is false.
 */
template <class size_type, class pred_type>
std::enable_if_t<
    std::is_convertible_v<std::invoke_result_t<pred_type, size_type>, bool>,
    size_type>
exponential_search(size_type range, pred_type pred) {
  size_type step(1);
  while (step < range && pred(step)) step <<= 1;
  if (range < step) step = range;
  return binary_search(size_type(0), step, pred);
}

/*
 * @fn exponential_search
 * @brief Exponential search on the real number line.
 * @param range Range of search
 * @param eps Error tolerance
 * @param pred Predicate
 * @return The boundary point.
 */
template <class real_type, class pred_type>
std::enable_if_t<
    std::is_convertible_v<std::invoke_result_t<pred_type, real_type>, bool>,
    real_type>
exponential_search(real_type range, const real_type eps, pred_type pred) {
  real_type step(1);
  while (step < range && pred(step)) step += step;
  if (range < step) step = range;
  return binary_search(real_type(0), step, eps, pred);
}

}  // namespace workspace

#endif
