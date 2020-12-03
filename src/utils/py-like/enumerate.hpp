#pragma once

/*
 * @file enumerate.hpp
 * @brief Enumerate
 */

#include "range.hpp"
#include "zip.hpp"

#if __cplusplus >= 201703L

namespace workspace {

constexpr size_t min_size() noexcept { return SIZE_MAX; }

template <class Container, class... Args>
constexpr size_t min_size(Container const &cont, Args &&... args) noexcept {
  return std::min(std::size(cont), min_size(std::forward<Args>(args)...));
}

template <class Tp, class... Args>
constexpr size_t min_size(Tp const (&cont)[], Args &&... args) noexcept {
  return std::min(std::size(cont), min_size(std::forward<Args>(args)...));
}

template <class... Args> constexpr auto enumerate(Args &&... args) noexcept {
  return zipped<range<size_t>, Args...>(range(min_size(args...)),
                                        std::forward<Args>(args)...);
}

template <class... Args>
constexpr auto enumerate(std::initializer_list<Args> &&... args) noexcept {
  return zipped<range<size_t>, std::initializer_list<Args>...>(
      range<size_t>(SIZE_MAX),
      std::forward<std::initializer_list<Args>>(args)...);
}

}  // namespace workspace

#endif
