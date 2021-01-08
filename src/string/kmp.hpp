/**
 * @file kmp.hpp
 * @brief Knuth-Morris-Pratt Algorithm
 * @date 2021-01-08
 */

#include <vector>

namespace workspace {

/**
 * @brief Knuth-Morris-Pratt algorithm.
 *
 * @param __s A string
 * @return The i-th element (1-indexed) describes the prefix of length i.
 */
template <class _Str> std::vector<size_t> kmp_algorithm(_Str const& __s) {
  std::vector<size_t> __k(std::size(__s));
  if (!__k.empty())
    for (size_t __p{}, __q{1}; __q != __k.size(); __k[__q++] = ++__p)
      while (__s[__p] != __s[__q]) {
        if (!__p--) break;
        __p = __k[__p];
      }
  return __k;
}

}  // namespace workspace
