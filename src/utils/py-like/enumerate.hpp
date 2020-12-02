#pragma once

/*
 * @file enumerate.hpp
 * @brief Enumerate
 */

#include "range.hpp"
#include "zip.hpp"

#if __cplusplus >= 201703L

namespace workspace {

template <class... Args> constexpr auto enumerate(Args &&... args) {
  return zipped<range<size_t>, Args...>(range<size_t>(SIZE_MAX),
                                        std::forward<Args>(args)...);
}

template <class... Args>
constexpr auto enumerate(std::initializer_list<Args> &&... args) {
  return zipped<range<size_t>, std::initializer_list<Args>...>(
      range<size_t>(SIZE_MAX),
      std::forward<std::initializer_list<Args>>(args)...);
}

}  // namespace workspace

#endif
