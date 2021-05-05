#pragma once

/**
 * @file fixed_point.hpp
 * @brief Fixed Point Combinator
 */

#include <map>

namespace workspace {

/**
 * @brief Fixed Point Combinator
 */
template <class _F> class fixed_point {
  _F __fn;

 public:
  /**
   * @brief Construct a new fixed point object
   *
   * @param __fn 1st argument callable with the rest of its arguments.
   * Return type specified.
   */
  fixed_point(_F __fn) noexcept : __fn(std::forward<_F>(__fn)) {}

  /**
   * @brief Apply *this to 1st argument.
   * @param __args Rest of arguments.
   */
  template <class... _Args> decltype(auto) operator()(_Args &&...__args) const {
    return __fn(*this, std::forward<_Args>(__args)...);
  }
};

}  // namespace workspace
