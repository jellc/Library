#pragma once
#include "factorial.hpp"
#include "modulus/inverse.hpp"
#include "modulus/modint.hpp"
template <class, class = int> struct binomial;
template <class Modint>
struct binomial<Modint, decltype((void *)Modint::mod, 0)> {
  using value_type = Modint;
  struct mulinv_Op {
    value_type operator()(const value_type &f, const size_t &n) const {
      return f * inv(n);
    }
  };
  static inverse<value_type> inv;
  static factorial<value_type, mulinv_Op> fact_inv;
  static factorial<value_type> fact;
  value_type operator()(const int &n, const int &k) {
    return fact_inv(k) * fact_inv(n - k) * fact(n);
  }
};
template <class Modint>
inverse<Modint> binomial<Modint, decltype((void *)Modint::mod, 0)>::inv;
template <class Modint>
factorial<Modint,
          class binomial<Modint, decltype((void *)Modint::mod, 0)>::mulinv_Op>
    binomial<Modint, decltype((void *)Modint::mod, 0)>::fact_inv {
  1
};
template <class Modint>
factorial<Modint> binomial<Modint, decltype((void *)Modint::mod, 0)>::fact;
