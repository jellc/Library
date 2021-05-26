#pragma once

/**
 * @file kmp.hpp
 * @brief Knuth-Morris-Pratt Algorithm
 */

#include <vector>

namespace workspace {

/**
 * @brief Morris-Pratt algorithm.
 *
 * @param __s String
 * @return Border array of given string.
 */
template <class _String> auto mp_algorithm(const _String& __s) {
  std::vector<size_t> __b(__s.size() + 1);
  for (size_t __p{__b[0] = -1}, __q{}; __q != __s.size(); __b[++__q] = ++__p)
    while (~__p && __s[__p] != __s[__q]) __p = __b[__p];
  return __b;
}

/**
 * @brief Knuth-Morris-Pratt algorithm.
 *
 * @param __s String
 * @return Strong-border array of given string.
 */
template <class _String> auto kmp_algorithm(const _String& __s) {
  auto __b = mp_algorithm(__s);
  for (size_t __i{1}; __i != __s.size(); ++__i)
    if (__s[__i] == __s[__b[__i]]) __b[__i] = __b[__b[__i]];
  return __b;
}

}  // namespace workspace
