#pragma once

#include "sum.hpp"

namespace workspace {

// Product of all elements in given range.
template <class _Iterator,
          class _Operator = std::multiplies<
              typename std::iterator_traits<_Iterator>::value_type>>
typename std::iterator_traits<_Iterator>::value_type prod(
    _Iterator __first, _Iterator __last,
    _Operator __op = _Operator{}) noexcept {
  return sum(__first, __last, __op);
}

}  // namespace workspace
