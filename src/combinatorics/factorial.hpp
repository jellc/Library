#pragma once

/*
 * @brief Factorial
 */

#include <functional>
#include <vector>

namespace workspace {

template <class Tp, class Op = std::multiplies<Tp>> class factorial {
  std::vector<Tp> fact;
  Op op;

 public:
  factorial(Tp init = 1, Op op = Op()) : fact{init}, op{op} {}

  Tp operator()(int_least32_t n) {
    if (n < 0) return 0;
    for (int_least32_t m(fact.size()); m <= n; ++m)
      fact.emplace_back(op(fact.back(), m));
    return fact[n];
  }
};

}  // namespace workspace
