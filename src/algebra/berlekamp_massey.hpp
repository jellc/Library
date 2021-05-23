#pragma once

/**
 * @file berlekamp_massey.hpp
 * @brief Berlekamp-Massey Algorithm
 */

#include "polynomial.hpp"

namespace workspace {

template <class _Iterator>
auto Berlekamp_Massey(_Iterator __first, _Iterator __last) noexcept {
  using value_type = typename std::iterator_traits<_Iterator>::value_type;
  using size_type = typename polynomial<value_type>::size_type;

  polynomial<value_type> __c{1}, __b{1};

  for (size_type __z = 2; __first != __last; ++__z) {
    value_type __d{0};
    auto __s = ++__first;
    auto __i = __c.end();
    while (__i != __c.begin()) __d += *--__i * *--__s;

    if (__d == value_type(0)) continue;

    if (__c.size() < __z) {
      auto __tmp = __c / __d;
      __c <<= __z - __c.size();
      __c -= __b *= __d;
      __b = std::move(__tmp);
      __z = __b.size();
    } else
      for (size_type __i = 0; __i != __b.size(); ++__i)
        __c[__i + __c.size() - __z] -= __b[__i] * __d;
  }

  return __c;
}

}  // namespace workspace
