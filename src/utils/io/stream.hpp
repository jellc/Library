#pragma once

/*
 * @file stream.hpp
 * @brief Stream
 */

#include <cxxabi.h>

#include <cassert>
#include <iostream>
#include <tuple>

namespace workspace {

/*
 * @class istream
 * @brief A wrapper class for std::istream.
 */
class istream : std::istream {
  template <class Tp, typename = std::nullptr_t> struct helper {
    helper(std::istream &is, Tp &x) {
      for (auto &&e : x) helper<decltype(e)>(is, e);
    }
  };

  template <class Tp>
  struct helper<
      Tp,
      decltype(std::declval<std::decay<decltype(
                   std::declval<std::istream &>() >> std::declval<Tp &>())>>(),
               nullptr)> {
    helper(std::istream &is, Tp &x) { is >> x; }
  };

  template <class T1, class T2> struct helper<std::pair<T1, T2>> {
    helper(std::istream &is, std::pair<T1, T2> &x) {
      helper<T1>(is, x.first), helper<T2>(is, x.second);
    }
  };

  template <class... Tps> struct helper<std::tuple<Tps...>> {
    helper(std::istream &is, std::tuple<Tps...> &x) { iterate(is, x); }

   private:
    template <class Tp, size_t N = 0> void iterate(std::istream &is, Tp &x) {
      if constexpr (N == std::tuple_size<Tp>::value)
        return;
      else
        helper<typename std::tuple_element<N, Tp>::type>(is, std::get<N>(x)),
            iterate<Tp, N + 1>(is, x);
    }
  };

 public:
  template <typename Tp> istream &operator>>(Tp &x) {
    helper<Tp>(*this, x);
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
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p) {
  return os << p.first << ' ' << p.second;
}
template <class tuple_t, size_t index> struct tuple_os {
  static std::ostream &apply(std::ostream &os, const tuple_t &t) {
    tuple_os<tuple_t, index - 1>::apply(os, t);
    return os << ' ' << std::get<index>(t);
  }
};
template <class tuple_t> struct tuple_os<tuple_t, 0> {
  static std::ostream &apply(std::ostream &os, const tuple_t &t) {
    return os << std::get<0>(t);
  }
};
template <class tuple_t> struct tuple_os<tuple_t, SIZE_MAX> {
  static std::ostream &apply(std::ostream &os, const tuple_t &t) { return os; }
};

template <class... T>
std::ostream &operator<<(std::ostream &os, const std::tuple<T...> &t) {
  return tuple_os<std::tuple<T...>,
                  std::tuple_size<std::tuple<T...>>::value - 1>::apply(os, t);
}

template <class Container,
          typename = decltype(std::begin(std::declval<Container>()))>
typename std::enable_if<
    !std::is_same<typename std::decay<Container>::type, std::string>::value &&
        !std::is_same<typename std::decay<Container>::type, char *>::value,
    std::ostream &>::type
operator<<(std::ostream &os, const Container &cont) {
  bool head = true;
  for (auto &&e : cont) head ? head = 0 : (os << ' ', 0), os << e;
  return os;
}

}  // namespace workspace
