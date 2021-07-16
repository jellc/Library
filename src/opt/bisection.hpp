#pragma once

/**
 * @file bisection.hpp
 * @brief Bisection
 */

namespace workspace {

/**
 * @brief Bisection method.
 * @param __first
 * @param __last
 * @param __pred
 */
template <class _Iterator, class _Predicate>
_Iterator bisection(_Iterator __first, _Iterator __last, _Predicate &&__pred) {
  _Iterator __mid;
  for (decltype(__last - __first) __w = 0; __w < __last - __first;
       __w = __w << 1 | 1) {
    __mid = __first + __w;
    if (!__pred(__mid)) {
      __last = __mid;
      break;
    }
    __first = __mid;
  }
  while (1 < __last - __first) {
    __mid = __first + (__last - __first) / 2;
    (__pred(__mid) ? __first : __last) = __mid;
  }
  return __last;
}

/**
 * @brief Bisection method.
 * @param __first
 * @param __last
 * @param __pred
 * @param __eps
 */
template <class _Iterator, class _Predicate, class _Difference>
_Iterator bisection(_Iterator __first, _Iterator __last, _Predicate &&__pred,
                    _Difference __eps) {
  while (__eps < _Difference(__last - __first)) {
    _Iterator __mid = __first + (__last - __first) / 2;
    (__pred(__mid) ? __first : __last) = __mid;
  }
  return __last;
}

}  // namespace workspace
