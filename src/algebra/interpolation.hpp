#pragma once

/**
 * @file interpolation.hpp
 * @brief Polynomial Interpolation
 */

#include <vector>

#include "polynomial.hpp"
#include "system/operation.hpp"

namespace workspace {

/**
 * @brief Lagrange interpolation on the points 0, 1, 2, ...
 * @param __x Point to evaluate at.
 * @param __first
 * @param __last
 */
template <class _Tp, class _InputIter,
          typename = std::_RequireInputIter<_InputIter>,
          typename = require_arithmetic<
              typename std::iterator_traits<_InputIter>::value_type>>
auto interpolate(_Tp __x, _InputIter __first, _InputIter __last) noexcept {
  using value_type = typename std::iterator_traits<_InputIter>::value_type;

  std::vector<value_type> __f(__first, __last);
  decltype(__f.size()) __k = 0;

  value_type __d = 1;
  while (__k != __f.size()) __k += 1, __d *= value_type{__k};

  __d = value_type{1} / __d;
  value_type __c = __k & 1 ? -__d : __d;
  auto __i = __f.begin();

  while (__i != __f.end()) {
    __c *= -value_type{__k}, __k -= 1;
    *__i++ *= __c;
    __c *= __x, __x -= 1;
  }

  __c = __d, __k = __f.size();
  value_type __y = 0;

  while (__i != __f.begin()) {
    __c *= value_type{__k}, __k -= 1;
    __y += *--__i * __c;
    __x += 1, __c *= __x;
  }

  return __y;
}

/**
 * @brief Polynomial interpolation in O(n log(n)^2) time.
 * @param __first
 * @param __last
 */
template <class _InputIter, typename = std::_RequireInputIter<_InputIter>>
auto interpolate(_InputIter __first, _InputIter __last) noexcept {
  size_t __n = std::distance(__first, __last);

  auto [__1, __2] = typename std::iterator_traits<_InputIter>::value_type{};

  using poly = polynomial<decltype(__1)>;

  if (!__n) return poly{};

  struct node {
    poly __all, __lack;
  };

  auto __tree = new node[__n << 1];
  auto __iter = __first;

  for (size_t __i = 0; __i != __n; ++__i) {
    auto&& [__a, __b] = *__iter++;
    __tree[__i + __n].__all = {-__a, 1}, __tree[__i + __n].__lack = {1};
  }

  for (size_t __i = __n; --__i;)
    __tree[__i].__all = __tree[__i << 1].__all * __tree[__i << 1 | 1].__all,
    __tree[__i].__lack =
        __tree[__i << 1].__all * std::move(__tree[__i << 1 | 1].__lack) +
        __tree[__i << 1 | 1].__all * std::move(__tree[__i << 1].__lack);

  for (size_t __i = 2; __i != __n << 1; __i += 2)
    __tree[__i].__lack = __tree[__i >> 1].__lack % __tree[__i].__all,
    __tree[__i | 1].__lack =
        std::move(__tree[__i >> 1].__lack %= __tree[__i | 1].__all);

  for (size_t __i = 0; __i != __n; ++__i) {
    auto&& [__a, __b] = *__first++;
    __tree[__i + __n].__lack[0] =
        std::move(__b) / std::move(__tree[__i + __n].__lack[0]);
  }

  for (size_t __i = __n; --__i;)
    __tree[__i].__lack = std::move(__tree[__i << 1].__all) *
                             std::move(__tree[__i << 1 | 1].__lack) +
                         std::move(__tree[__i << 1 | 1].__all) *
                             std::move(__tree[__i << 1].__lack);

  auto __result = std::move(__tree[1].__lack);

  delete[] __tree;

  return __result;
}

}  // namespace workspace
