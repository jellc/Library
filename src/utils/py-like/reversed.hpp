#pragma once

/**
 * @file reversed.hpp
 * @brief Reversed
 */

#include <initializer_list>
#include <iterator>

namespace workspace {

namespace internal {

template <class Container> class reversed {
  Container cont;

 public:
  constexpr reversed(Container &&cont) : cont(cont) {}

  constexpr auto begin() { return std::rbegin(cont); }
  constexpr auto end() { return std::rend(cont); }
};

}  // namespace internal

template <class Container> constexpr auto reversed(Container &&cont) noexcept {
  return internal::reversed<Container>{std::forward<Container>(cont)};
}

template <class Tp>
constexpr auto reversed(std::initializer_list<Tp> &&cont) noexcept {
  return internal::reversed<std::initializer_list<Tp>>{
      std::forward<std::initializer_list<Tp>>(cont)};
}

}  // namespace workspace
