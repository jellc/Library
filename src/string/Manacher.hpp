#pragma once

/**
 * @file Manacher.hpp
 * @brief Manacher's Algorithm
 */

#include <vector>

namespace workspace {

/**
 * @brief Manacher's Algorithm.
 *
 * @param __s String
 * @return Radiuses of the longest palindromic substring with each fixed center.
 */
template <class _Str> std::vector<size_t> Manacher(_Str const &__s) {
  const auto __n = std::size(__s);
  std::vector<size_t> __r(__n);
  for (size_t __i = 0, __c = 0; __i != __n; ++__i)
    if (auto __j = __c * 2 - __i; __j < __n && __c + __r[__c] > __i + __r[__j])
      __r[__i] = __r[__j];
    else {
      __j = __c + __r[__c] - __i;
      while (__i >= __j && __i + __j != __n && __s[__i - __j] == __s[__i + __j])
        ++__j;
      __r[__c = __i] = __j;
    }
  return __r;
}

}  // namespace workspace
