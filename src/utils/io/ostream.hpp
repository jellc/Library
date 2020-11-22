#pragma once

/*
 * @file ostream.hpp
 * @brief Output Stream
 */

#include <iostream>
#include <tuple>

namespace workspace {

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
