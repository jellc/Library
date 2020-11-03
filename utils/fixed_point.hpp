#pragma once
#include <utility>
namespace workspace {

// specify the return type of lambda.
/*
 * @class fixed_point
 * @brief fixed point combinator.
 */
template <class lambda_type> class fixed_point {
  lambda_type func;

 public:
  /*
   * @brief
   * @param func 1st arg is callable with the rest of args
   */
  fixed_point(lambda_type &&func) : func(std::move(func)) {}

  /*
   * @brief recursively apply *this to 1st arg of func.
   * @param args arguments of the recursive method
   */
  template <class... Args> auto operator()(Args &&... args) const {
    return func(*this, std::forward<Args>(args)...);
  }
};

}  // namespace workspace
