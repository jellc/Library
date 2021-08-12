#pragma once

#include <iterator>
#include <vector>

namespace workspace {

// Sum of all elements in given range.
template <class _Iterator,
          class _Operator =
              std::plus<typename std::iterator_traits<_Iterator>::value_type>>
typename std::iterator_traits<_Iterator>::value_type sum(
    _Iterator __first, _Iterator __last,
    _Operator __op = _Operator{}) noexcept {
  using value_type = typename std::iterator_traits<_Iterator>::value_type;

  if (__first == __last) return value_type{};

  auto __b = new value_type[std::distance(__first, __last)],
       __e = std::copy(__first, __last, __b);

  while (__b + 1 != __e)
    for (auto __t = __e, __s = __e = __b; __s != __t; ++__s, ++__e)
      if (__t - __s == 1)
        *__e = std::move(*__s);
      else
        *__e = __op(*__s, *(__s + 1)), ++__s;

  value_type __tmp = std::move(*__b);
  delete[] __b;
  return __tmp;
}

}  // namespace workspace
