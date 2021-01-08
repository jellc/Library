#pragma once

/**
 * @file z_algorithm.hpp
 * @brief Z-Algorithm
 * @date 2021-01-08
 */

#include <string>
#include <vector>

namespace workspace {

/**
 * @brief Construct Z-array in linear time.
 * @param __s A string
 * @return The i-th element (0-indexed) is the length of the Longest Common
 * Prefix between __s and __s[i:].
 */
template <class _Str> std::vector<size_t> z_algorithm(_Str const &__s) {
  std::vector<size_t> __z;
  if (!__s.empty()) {
    for (size_t __i{1}, __j{0}; __i != __s.size(); ++__i) {
      if (__z[__i - __j] + __i < __z[__j] + __j) {
        __z[__i] = __z[__i - __j];
      } else {
        size_t __k{__z[__j] + __j > __i ? __z[__j] + __j - __i : 0};
        while (__k + __i < __s.size() && __s[__k] == __s[__k + __i]) ++__k;
        __z[__i] = __k;
        __j = __i;
      }
    }
    __z.front() = __s.size();
  }
  return __z;
}

}  // namespace workspace
