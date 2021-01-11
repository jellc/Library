/**
 * @file kmp.hpp
 * @brief Knuth-Morris-Pratt Algorithm
 * @date 2021-01-08
 */

#include <vector>

namespace workspace {

/**
 * @brief Morris-Pratt algorithm.
 *
 * @param __s String
 * @return The border array of given string.
 */
template <class _Str> std::vector<size_t> mp_algorithm(_Str const& __s) {
  std::vector<size_t> __b(std::size(__s) + 1);
  for (size_t __p{__b[0] = -1}, __q{}; __q != __s.size(); __b[++__q] = ++__p)
    while (~__p && __s[__p] != __s[__q]) __p = __b[__p];
  return __b;
}

/**
 * @brief Knuth-Morris-Pratt algorithm.
 *
 * @param __s String
 * @return The strong-border array of given string.
 */
template <class _Str> std::vector<size_t> kmp_algorithm(_Str const& __s) {
  auto __b = mp_algorithm(__s);
  for (size_t __i{1}; __i != __s.size(); ++__i)
    if (__s[__i] == __s[__b[__i]]) __b[__i] = __b[__b[__i]];
  return __b;
}

}  // namespace workspace
