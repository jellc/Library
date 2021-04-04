#pragma once

/**
 * @file istream.hpp
 * @brief Input Stream
 */

#include <cxxabi.h>

#include <cassert>
#include <iostream>
#include <tuple>

#include "src/utils/sfinae.hpp"

namespace workspace {

namespace _istream_impl {

template <class _Tp, typename = std::nullptr_t> struct istream_helper {
  istream_helper(std::istream &__is, _Tp &__x) {
    if constexpr (has_begin<_Tp>::value)
      for (auto &&__e : __x)
        istream_helper<std::__decay_t<decltype(__e)>>(__is, __e);
    else
      static_assert(has_begin<_Tp>::value, "istream unsupported type.");
  }
};

template <class _Tp>
struct istream_helper<
    _Tp,
    decltype(std::declval<std::__decay_t<decltype(
                 std::declval<std::istream &>() >> std::declval<_Tp &>())>>(),
             nullptr)> {
  istream_helper(std::istream &__is, _Tp &__x) { __is >> __x; }
};

#ifdef __SIZEOF_INT128__

template <> struct istream_helper<__uint128_t, std::nullptr_t> {
  istream_helper(std::istream &__is, __uint128_t &__x) {
    std::string __s;
    __is >> __s;
    bool __neg = false;
    if (__s.front() == '-') __neg = true, __s.erase(__s.begin());
    __x = 0;
    for (char __d : __s) {
      __x *= 10;
      __d -= '0';
      if (__neg)
        __x -= __d;
      else
        __x += __d;
    }
  }
};

template <> struct istream_helper<__int128_t, std::nullptr_t> {
  istream_helper(std::istream &__is, __int128_t &__x) {
    std::string __s;
    __is >> __s;
    bool __neg = false;
    if (__s.front() == '-') __neg = true, __s.erase(__s.begin());
    __x = 0;
    for (char __d : __s) {
      __x *= 10;
      __d -= '0';
      if (__neg)
        __x -= __d;
      else
        __x += __d;
    }
  }
};

#endif  // INT128

template <class T1, class T2> struct istream_helper<std::pair<T1, T2>> {
  istream_helper(std::istream &__is, std::pair<T1, T2> &__x) {
    istream_helper<T1>(__is, __x.first), istream_helper<T2>(__is, __x.second);
  }
};

template <class... Tps> struct istream_helper<std::tuple<Tps...>> {
  istream_helper(std::istream &__is, std::tuple<Tps...> &__x) {
    iterate(__is, __x);
  }

 private:
  template <class _Tp, size_t N = 0>
  void iterate(std::istream &__is, _Tp &__x) {
    if constexpr (N == std::tuple_size<_Tp>::value)
      return;
    else
      istream_helper<typename std::tuple_element<N, _Tp>::type>(
          __is, std::get<N>(__x)),
          iterate<_Tp, N + 1>(__is, __x);
  }
};

}  // namespace _istream_impl

/**
 * @brief A wrapper class for std::istream.
 */
class istream : public std::istream {
 public:
  /**
   * @brief Wrapped operator.
   */
  template <typename _Tp> istream &operator>>(_Tp &__x) {
    _istream_impl::istream_helper<_Tp>(*this, __x);
    if (std::istream::fail()) {
      static auto once = atexit([] {
        std::cerr << "\n\033[43m\033[30mwarning: failed to read \'"
                  << abi::__cxa_demangle(typeid(_Tp).name(), 0, 0, 0)
                  << "\'.\033[0m\n\n";
      });
      assert(!once);
    }
    return *this;
  }
};

decltype(auto) cin = static_cast<istream &>(std::cin);

}  // namespace workspace
