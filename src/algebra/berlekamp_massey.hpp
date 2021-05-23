#pragma once

/**
 * @file berlekamp_massey.hpp
 * @brief Berlekamp-Massey Algorithm
 */

#include <numeric>

#include "polynomial.hpp"

namespace workspace {

template <class _Iterator>
auto Berlekamp_Massey(_Iterator __first, _Iterator __last) noexcept {
  using value_type = typename std::iterator_traits<_Iterator>::value_type;

  std::vector<value_type> __a(__first, __last);
  polynomial<value_type> __c{1}, __b{1};

  typename decltype(__c)::size_type __z = 1;

  for (auto __s = __a.begin(); __s != __a.end(); ++__s) {
    ++__z;

    auto __d = std::inner_product(__c.begin(), __c.end(), __s + 1 - __c.size(),
                                  value_type(0));
    if (__d == value_type(0)) continue;

    if (__c.size() < __z) {
      auto __tmp = __c;
      __c <<= __z - __c.size();
      __c -= __b *= __d;
      __b = std::move(__tmp);
      __b /= __d;
      __z = __b.size();
    } else {
      for (auto __i = __c.end() - __z, __j = __b.begin(); __j != __b.end();
           ++__i, ++__j)
        *__i -= *__j * __d;
    }
  }

  return __c;
}

}  // namespace workspace
