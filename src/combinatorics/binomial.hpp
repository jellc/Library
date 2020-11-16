#pragma once

/*
 * @file binomial.hpp
 * @brief Binomial Coefficient
 */

#include "../modular/inverse.hpp"
#include "../modular/modint.hpp"
#include "factorial.hpp"

namespace workspace {

template <class, class = int> struct binomial;
template <class Modint> struct binomial<Modint> {
  static_assert(std::is_same<std::nullptr_t,
                             decltype((void *)Modint::mod, nullptr)>::value);

  using value_type = Modint;
  struct mulinv_Op {
    value_type operator()(const value_type &f, const size_t &n) const {
      return f * inv(n);
    }
  };

  static inverse<value_type> inv;
  static factorial<value_type, mulinv_Op> fact_inv;
  static factorial<value_type> fact;

  value_type operator()(int_least32_t n, int_least32_t k) {
    return fact_inv(k) * fact_inv(n - k) * fact(n);
  }
};

template <class Modint> inverse<Modint> binomial<Modint>::inv;
template <class Modint>
factorial<Modint, class binomial<Modint>::mulinv_Op> binomial<Modint>::fact_inv;
template <class Modint> factorial<Modint> binomial<Modint>::fact;

}  // namespace workspace
