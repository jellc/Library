#pragma once

/*
 * @file stream.hpp
 * @brief Stream
 */

#include <cxxabi.h>

#include <iostream>
#include <tuple>

#include "../sfinae.hpp"

namespace workspace {

/*
 * @class istream
 * @brief A wrapper class for std::istream.
 */
class istream : std::istream {
  template <class Tp,
            typename = decltype(std::istream::operator>>(std::declval<Tp &>()))>
  void read(Tp &x) {
    std::istream::operator>>(x);
  }

  template <class T1, class T2> void read(std::pair<T1, T2> &x) {
    read(x.first), read(x.second);
  }

  template <class Tp, size_t N = 0> void tuple_read(Tp &x) {
    if constexpr (N == std::tuple_size<Tp>::value)
      return;
    else
      read(std::get<N>(x)), tuple_read<Tp, N + 1>(x);
  }

  template <class... Tp> void read(istream &is, tuple<Tp...> &x) {
    tuple_read(x);
  }

  template <class Container, typename Value = element_type<Container>>
  typename std::enable_if<
      !is_same<typename decay<Container>::type, string>::value &&
          !is_same<typename decay<Container>::type, char *>::value,
      void>::type
  read(Container &x) {
    for (auto &&e : x) read(e);
  }

 public:
  template <typename Tp> istream &operator>>(Tp &x) {
    read(x);
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

// operator<< overloads

template <class T, class U>
ostream &operator<<(ostream &os, const pair<T, U> &p) {
  return os << p.first << ' ' << p.second;
}
template <class tuple_t, size_t index> struct tuple_os {
  static ostream &apply(ostream &os, const tuple_t &t) {
    tuple_os<tuple_t, index - 1>::apply(os, t);
    return os << ' ' << get<index>(t);
  }
};
template <class tuple_t> struct tuple_os<tuple_t, 0> {
  static ostream &apply(ostream &os, const tuple_t &t) {
    return os << get<0>(t);
  }
};
template <class tuple_t> struct tuple_os<tuple_t, SIZE_MAX> {
  static ostream &apply(ostream &os, const tuple_t &t) { return os; }
};

template <class... T>
std::ostream &operator<<(ostream &os, const tuple<T...> &t) {
  return tuple_os<tuple<T...>, tuple_size<tuple<T...>>::value - 1>::apply(os,
                                                                          t);
}

template <class Container, typename Value = element_type<Container>>
typename enable_if<!is_same<typename decay<Container>::type, string>::value &&
                       !is_same<typename decay<Container>::type, char *>::value,
                   ostream &>::type
operator<<(ostream &os, const Container &cont) {
  bool head = true;
  for (auto &&e : cont) head ? head = 0 : (os << ' ', 0), os << e;
  return os;
}

}  // namespace workspace
