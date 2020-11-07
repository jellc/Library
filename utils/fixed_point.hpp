#pragma once

/*
 * @file fixed_point.hpp
 * @brief Fixed point combinator
 */

#include <utility>

namespace workspace {

/*
 * @class fixed_point
 * @brief recursive calling of lambda expression
 */
template <class lambda_type> class fixed_point {
  lambda_type func;

 public:
  /*
   * @param func 1st arg callable with the rest of args, and the return type
   * specified
   */
  fixed_point(lambda_type &&func) : func(std::move(func)) {}

  /*
   * @brief recursively apply *this to 1st arg of func
   * @param args arguments of the recursive method
   */
  template <class... Args> auto operator()(Args &&... args) const {
    return func(*this, std::forward<Args>(args)...);
  }
};

}  // namespace workspace
