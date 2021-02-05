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
   * @param __fn 1st argument callable with the rest of its arguments, and the
   * return type specified.
   */
  fixed_point(_F &&__fn) noexcept : __fn(std::forward<_F>(__fn)) {}

  /**
   * @brief Apply *this to 1st argument.
   * @param __args Rest of arguments.
   */
  template <class... _Args>
  decltype(auto) operator()(_Args &&... __args) const noexcept {
    return __fn(*this, std::forward<_Args>(__args)...);
  }
};

/**
 * @brief Cached version of Fixed Point Combinator
 */
template <class _F> class cached_fixed_point {
  template <class...> struct _cache;

  template <class _G, class _R, class _H, class... _Args>
  struct _cache<_R (_G::*)(_H, _Args...) const>
      : std::map<std::tuple<_Args...>, _R> {};

  using cache =
      _cache<decltype(&_F::template operator()<cached_fixed_point<_F> &>)>;

  _F __fn;
  static cache __ca;

 public:
  /**
   * @param __fn 1st argument callable with the rest of its arguments, and the
   * return type specified.
   */
  cached_fixed_point(_F &&__fn) noexcept : __fn(std::forward<_F>(__fn)) {}

  /**
   * @brief Apply *this to 1st argument.
   * @param __args Rest of arguments.
   */
  template <class... _Args>
  decltype(auto) operator()(_Args &&... __args) noexcept {
    typename cache::key_type __key(__args...);

    if (auto __i = __ca.lower_bound(__key);
        __i != __ca.end() && __i->first == __key)
      return __i->second;

    else
      return __ca
          .emplace_hint(__i, std::move(__key),
                        __fn(*this, std::forward<_Args>(__args)...))
          ->second;
  }
};

template <class _F>
typename cached_fixed_point<_F>::cache cached_fixed_point<_F>::__ca;

}  // namespace workspace
