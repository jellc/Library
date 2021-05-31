#pragma once

/**
 * @file cached.hpp
 * @brief Cached
 */

#include <map>
#include <memory>

#include "fixed_point.hpp"
#include "lib/cxx17"

namespace workspace {

namespace _cached_impl {

// Convert keys to tuple.
template <class... _Args> struct get_tuple {
  using type = decltype(std::tuple_cat(
      std::declval<std::tuple<std::conditional_t<
          std::is_convertible<std::decay_t<_Args>, _Args>::value,
          std::decay_t<_Args>, _Args>>>()...));
};

// Associative array.
template <class _Value, class... _Keys>
struct assoc
    : std::integral_constant<int, !std::is_void<_Value>::value>,
      std::conditional_t<std::is_void<_Value>::value,
                         std::set<typename get_tuple<_Keys...>::type>,
                         std::map<typename get_tuple<_Keys...>::type, _Value>> {
};

// Non-resursive lambda type.
template <class _F, class = void> struct is_recursive : std::false_type {};

// Resursive lambda type.
template <class _F>
struct is_recursive<
    _F, std::__void_t<decltype(&_F::template operator()<fixed_point<_F> &>)>>
    : std::true_type {};

// Recursive ver.
template <class _F> class _recursive {
  template <class...> struct _cache;

  template <class _G, class _R, class _H, class... _Args>
  struct _cache<_R (_G::*)(_H, _Args...)> : assoc<_R, _Args...> {};

  template <class _G, class _R, class _H, class... _Args>
  struct _cache<_R (_G::*)(_H, _Args...) const> : assoc<_R, _Args...> {};

 public:
  using cache = _cache<decltype(&_F::template operator()<_recursive<_F> &>)>;

  _recursive(_F __x) noexcept : __fn(__x), __cptr(new cache) {}

  /**
   * @brief Apply `*this` to 1st argument of the lambda.
   * @param __args Rest of arguments.
   */
  template <class... _Args> decltype(auto) operator()(_Args &&...__args) {
    typename cache::key_type __key{__args...};
    auto __i = __cptr->lower_bound(__key);

    if _CXX17_CONSTEXPR (cache::value) {
      if (__i != __cptr->end() && __i->first == __key)
        return __i->second;

      else
        return __cptr
            ->emplace_hint(__i, std::move(__key),
                           __fn(*this, std::forward<_Args>(__args)...))
            ->second;
    }

    else if (__i == __cptr->end() || *__i != __key)
      __cptr->emplace_hint(__i, std::move(__key)),
          __fn(*this, std::forward<_Args>(__args)...);
  }

 private:
  _F __fn;
  std::shared_ptr<cache> __cptr;
};

// Non-recursive ver.
template <class _F> class _non_recursive {
  template <class _T, class = void> struct _get_func { using type = _T; };

  template <class _T>
  struct _get_func<_T, std::__void_t<decltype(&_T::operator())>> {
    using type = decltype(&_T::operator());
  };

  template <class...> struct _cache;

  template <class _R, class... _Args>
  struct _cache<_R(_Args...)> : assoc<_R, _Args...> {};

  template <class _R, class... _Args>
  struct _cache<_R (*)(_Args...)> : assoc<_R, _Args...> {};

  template <class _G, class _R, class... _Args>
  struct _cache<_R (_G::*)(_Args...)> : assoc<_R, _Args...> {};

  template <class _G, class _R, class... _Args>
  struct _cache<_R (_G::*)(_Args...) const> : assoc<_R, _Args...> {};

 public:
  using cache = _cache<typename _get_func<_F>::type>;

  _non_recursive(_F __x) noexcept : __fn(__x), __cptr(new cache) {}

  /**
   * @param __args
   */
  template <class... _Args> decltype(auto) operator()(_Args &&...__args) {
    typename cache::key_type __key{__args...};
    auto __i = __cptr->lower_bound(__key);

    if _CXX17_CONSTEXPR (cache::value) {
      if (__i != __cptr->end() && __i->first == __key)
        return __i->second;

      else
        return __cptr
            ->emplace_hint(__i, std::move(__key),
                           __fn(std::forward<_Args>(__args)...))
            ->second;
    }

    else if (__i == __cptr->end() || *__i != __key)
      __cptr->emplace_hint(__i, std::move(__key)),
          __fn(std::forward<_Args>(__args)...);
  }

 private:
  _F __fn;
  std::shared_ptr<cache> __cptr;
};

template <class _F>
using _cached = std::conditional_t<is_recursive<_F>::value, _recursive<_F>,
                                   _non_recursive<_F>>;

}  // namespace _cached_impl

/**
 * @brief Cached caller of function
 */
template <class _F> class cached : public _cached_impl::_cached<_F> {
 public:
  /**
   * @brief Construct a new cached object
   */
  cached() noexcept : _cached_impl::_cached<_F>(_F{}) {}

  /**
   * @brief Construct a new cached object
   * @param __x Function
   */
  cached(_F __x) noexcept : _cached_impl::_cached<_F>(__x) {}
};

}  // namespace workspace
