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

  std::vector<value_type> __v(__first, __last);

  for (auto __b = __v.begin(), __e = __v.end(); __e - __b != 1;)
    for (std::move_iterator<typename decltype(__v)::iterator> __t(__e),
         __s(__e = __v.begin());
         __s != __t; ++__s, ++__e)
      if (__t - __s == 1)
        *__e = *__s;
      else
        *__e = __op(*__s, *(__s + 1)), ++__s;

  return __v.front();
}

}  // namespace workspace
