#pragma once

/*
 * @file xor_elimination.hpp
 * @brief XOR Elimination
 */

#include <vector>

namespace workspace {

template <class Expr> struct xor_elimination {
  std::vector<Expr> base;
  bool add(Expr e) {
    for (const Expr &b : base)
      if ((b ^ e) < e) e ^= b;
    if (e) base.emplace_back(e);
    return e;
  }
  size_t dim() const { return base.size(); }
};

}  // namespace workspace
