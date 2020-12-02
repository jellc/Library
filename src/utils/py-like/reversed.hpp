#pragma once

/*
 * @file reversed.hpp
 * @brief Reversed
 */

#include <initializer_list>
#include <iterator>

namespace workspace {

template <class Container> class reversal {
  Container cont;

 public:
  constexpr reversal(Container &&cont) : cont(cont) {}

  constexpr auto begin() { return std::rbegin(cont); }
  constexpr auto end() { return std::rend(cont); }
};

template <class Container> reversal<Container> reversed(Container &&cont) {
  return {std::forward<Container>(cont)};
}

template <class Tp>
reversal<std::initializer_list<Tp>> reversed(std::initializer_list<Tp> &&cont) {
  return {std::forward<std::initializer_list<Tp>>(cont)};
}

}  // namespace workspace
