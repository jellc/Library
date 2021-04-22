#pragma once

/**
 * @file rle.hpp
 * @brief Run-length Encoding
 */

#include <vector>

namespace workspace {

template <class _Iterator>
auto run_length_encoding(_Iterator __first, _Iterator __last) {
  std::vector<std::pair<typename std::iterator_traits<_Iterator>::value_type,
                        std::size_t>>
      __rle;

  while (__first != __last)
    for (__rle.emplace_back(*__first, 0);
         __first != __last && __rle.back().first == *__first; ++__first)
      ++__rle.back().second;

  return __rle;
}

}  // namespace workspace
