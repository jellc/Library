#pragma once

/**
 * @file input.hpp
 * @brief Input
 */

#include "../sfinae.hpp"
#include "istream.hpp"

namespace workspace {

template <class _Tp = int_least64_t, bool _Is_class = std::is_class<_Tp>::value>
class input {
  _Tp __value;

  template <class... _Args> struct is_convertible : std::false_type {};
  template <class _Arg>
  struct is_convertible<_Arg> : std::is_convertible<_Arg, _Tp> {};

 public:
  operator _Tp &() noexcept { return __value; }
  operator const _Tp &() const noexcept { return __value; }

  template <class... _Args>
  input(_Args &&...__args) noexcept : __value(std::forward<_Args>(__args)...) {
    if _CXX17_CONSTEXPR (not is_convertible<_Args...>::value) cin >> __value;
  }
};

template <class _Tp> class input<_Tp, true> : public _Tp {
  template <class... _Args> struct is_convertible : std::false_type {};
  template <class _Arg>
  struct is_convertible<_Arg> : std::is_convertible<_Arg, _Tp> {};

 public:
  operator _Tp &() noexcept { return *this; }
  operator const _Tp &() const noexcept { return *this; }

  template <class... _Args>
  input(_Args &&...__args) noexcept : _Tp(std::forward<_Args>(__args)...) {
    if _CXX17_CONSTEXPR (not is_convertible<_Args...>::value) cin >> *this;
  }

  template <class _E>
  input(std::initializer_list<_E> __l) noexcept : _Tp(__l) {}
};

// Integrality.
template <class _Tp>
struct is_integral_ext<input<_Tp>> : is_integral_ext<_Tp> {};

}  // namespace workspace
