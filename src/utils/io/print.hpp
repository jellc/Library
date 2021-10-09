#pragma once

/**
 * @file print.hpp
 * @brief Print
 */

#include "ostream.hpp"

namespace workspace {

/**
 * @brief Print
 * @tparam _Sep
 * @tparam _End
 */
template <char _Sep = ' ', char _End = '\n', class _Tp, class... _Args>
void print(_Tp &&__x, _Args &&...__args) noexcept {
  if _CXX17_CONSTEXPR (sizeof...(_Args))
    cout << __x << _Sep, print(std::forward<_Args>(__args)...);
  else
    cout << __x << _End;
}

void flush() noexcept { cout << std::flush; }

}  // namespace workspace
