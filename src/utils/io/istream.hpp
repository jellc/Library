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

namespace internal {

template <class Tp, typename = std::nullptr_t> struct istream_helper {
  istream_helper(std::istream &is, Tp &x) {
    if constexpr (has_begin<Tp>::value)
      for (auto &&e : x)
        istream_helper<typename std::decay<decltype(e)>::type>(is, e);
    else
      static_assert(has_begin<Tp>::value, "istream unsupported type.");
  }
};

template <class Tp>
struct istream_helper<
    Tp,
    decltype(std::declval<std::decay<decltype(std::declval<std::istream &>() >>
                                              std::declval<Tp &>())>>(),
             nullptr)> {
  istream_helper(std::istream &is, Tp &x) { is >> x; }
};

#ifdef __SIZEOF_INT128__

template <> struct istream_helper<__int128_t, std::nullptr_t> {
  istream_helper(std::istream &is, __int128_t &x) {
    std::string s;
    is >> s;
    bool negative = s.front() == '-' ? s.erase(s.begin()), true : false;
    x = 0;
    for (char e : s) x = x * 10 + e - '0';
    if (negative) x = -x;
  }
};

template <> struct istream_helper<__uint128_t, std::nullptr_t> {
  istream_helper(std::istream &is, __uint128_t &x) {
    std::string s;
    is >> s;
    bool negative = s.front() == '-' ? s.erase(s.begin()), true : false;
    x = 0;
    for (char e : s) x = x * 10 + e - '0';
    if (negative) x = -x;
  }
};

#endif  // INT128

template <class T1, class T2> struct istream_helper<std::pair<T1, T2>> {
  istream_helper(std::istream &is, std::pair<T1, T2> &x) {
    istream_helper<T1>(is, x.first), istream_helper<T2>(is, x.second);
  }
};

template <class... Tps> struct istream_helper<std::tuple<Tps...>> {
  istream_helper(std::istream &is, std::tuple<Tps...> &x) { iterate(is, x); }

 private:
  template <class Tp, size_t N = 0> void iterate(std::istream &is, Tp &x) {
    if constexpr (N == std::tuple_size<Tp>::value)
      return;
    else
      istream_helper<typename std::tuple_element<N, Tp>::type>(is,
                                                               std::get<N>(x)),
          iterate<Tp, N + 1>(is, x);
  }
};

}  // namespace internal

/**
 * @brief A wrapper class for std::istream.
 */
class istream : public std::istream {
 public:
  /**
   * @brief Wrapped operator.
   */
  template <typename Tp> istream &operator>>(Tp &x) {
    internal::istream_helper<Tp>(*this, x);
    if (std::istream::fail()) {
      static auto once = atexit([] {
        std::cerr << "\n\033[43m\033[30mwarning: failed to read \'"
                  << abi::__cxa_demangle(typeid(Tp).name(), 0, 0, 0)
                  << "\'.\033[0m\n\n";
      });
      assert(!once);
    }
    return *this;
  }
};

namespace internal {
auto *const cin_ptr = (istream *)&std::cin;
}
auto &cin = *internal::cin_ptr;

}  // namespace workspace
