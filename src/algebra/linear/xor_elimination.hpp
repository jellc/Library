#pragma once

/**
 * @file xor_elimination.hpp
 * @brief XOR Elimination
 */

#include <vector>

namespace workspace {

template <class Expr> class xor_elimination : std::vector<Expr> {
  using base = std::vector<Expr>;
 public:
  using base::begin;
  using base::end;
  using base::size;

  bool add(Expr __e) {
    for (auto __i = begin(); __i != end(); ++__i)
      if ((*__i ^ __e) < __e) __e ^= *__i;
    if (__e) base::emplace_back(__e);
    return __e;
  }
};

}  // namespace workspace
