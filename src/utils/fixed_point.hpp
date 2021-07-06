#pragma once

/**
 * @file fixed_point.hpp
 * @brief Fixed Point Combinator
 */

#include <map>

namespace workspace {

/**
 * @brief Fixed Point Combinator.
 */
template <class _F> class fixed_point {
  struct _wrapper {
    _F &__ref;

    template <class... _Args>
    decltype(auto) operator()(_Args &&...__args) noexcept(
        noexcept(__ref(*this, std::forward<_Args>(__args)...))) {
      return __ref(*this, std::forward<_Args>(__args)...);
    }
  };

  _F __fn;

 public:
  // Construct a new fixed-point object.
  fixed_point(_F __x) noexcept : __fn(__x) {}

  // Function call.
  template <class... _Args>
  decltype(auto) operator()(_Args &&...__args) noexcept(noexcept(_wrapper{
      __fn}(std::forward<_Args>(__args)...))) {
    return _wrapper{__fn}(std::forward<_Args>(__args)...);
  }
};

}  // namespace workspace
