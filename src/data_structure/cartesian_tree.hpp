#pragma once

/**
 * @file cartesian_tree.hpp
 * @brief Cartesian Tree
 */

#include <vector>

namespace workspace {

/**
 * @brief Cartesian Tree.
 */
template <class _Iterator>
auto Cartesian_tree(_Iterator __first, _Iterator __last) noexcept {
  std::vector<std::size_t> __p;
  std::vector<_Iterator> __it;

  for (std::size_t __i = 0, __j = -1; __first != __last;
       __p.emplace_back(__j), __j = __i++, __it.emplace_back(__first++)) {
    std::size_t __k = -1;
    while (~__j && *__first < *__it[__j]) __k = __j, __j = __p[__j];
    if (~__k) __p[__k] = __i;
  }

  return __p;
}

/**
 * @brief Cartesian Tree.
 */
template <class _Iterator, class _Compare>
auto Cartesian_tree(_Iterator __first, _Iterator __last,
                    _Compare __comp) noexcept {
  std::vector<std::size_t> __p;
  std::vector<_Iterator> __it;

  for (std::size_t __i = 0, __j = -1; __first != __last;
       __p.emplace_back(__j), __j = __i++, __it.emplace_back(__first++)) {
    std::size_t __k = -1;
    while (~__j && __comp(*__first, *__it[__j])) __k = __j, __j = __p[__j];
    if (~__k) __p[__k] = __i;
  }

  return __p;
}

}  // namespace workspace
