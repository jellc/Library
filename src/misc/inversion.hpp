#pragma once

/**
 * @file inversion.hpp
 * @brief Inversion
 */

#include <algorithm>
#include <vector>

namespace workspace {

template <class _Iterator>
auto left_inversion(_Iterator __first, _Iterator __last) noexcept {
  std::vector<typename std::iterator_traits<_Iterator>::value_type> __v(__first,
                                                                        __last);
  std::sort(__v.begin(), __v.end(), std::greater<void>{});
  std::vector<size_t> __inv, __sum(__v.size() + 1);
  while (__first != __last) {
    auto& __c = __inv.emplace_back();
    size_t __e = std::distance(
        __v.begin(), std::lower_bound(__v.begin(), __v.end(), *__first++,
                                      std::greater<void>{}));
    for (auto __i = __e; __i; __i &= __i - 1) __c += __sum[__i];
    for (++__e; __e < __sum.size(); __e += __e & -__e) ++__sum[__e];
  }
  return __inv;
}

template <class _Iterator>
auto right_inversion(_Iterator __first, _Iterator __last) noexcept {
  std::vector<typename std::iterator_traits<_Iterator>::value_type> __v(__first,
                                                                        __last);
  std::sort(__v.begin(), __v.end());
  std::vector<size_t> __inv, __sum(__v.size() + 1);
  while (__first != __last) {
    auto& __c = __inv.emplace_back();
    size_t __e = std::distance(
        __v.begin(), std::lower_bound(__v.begin(), __v.end(), *--__last));
    for (auto __i = __e; __i; __i &= __i - 1) __c += __sum[__i];
    for (++__e; __e < __sum.size(); __e += __e & -__e) ++__sum[__e];
  }
  std::reverse(__inv.begin(), __inv.end());
  return __inv;
}

template <class _Iterator>
auto inversion(_Iterator __first, _Iterator __last) noexcept {
  size_t __res = 0;
  for (auto __x : left_inversion(__first, __last)) __res += __x;
  return __res;
}

}  // namespace workspace
