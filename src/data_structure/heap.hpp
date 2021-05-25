#pragma once

/**
 * @file heap.hpp
 * @brief Heap
 */

#include <queue>

#include "src/utils/sfinae.hpp"

namespace workspace {

/**
 * @brief Wrapper class for std::priority_queue.
 */
template <class _Tp, class _Compare = std::less<_Tp>>
class heap : public std::priority_queue<_Tp, std::vector<_Tp>, _Compare> {
 public:
  using container_type = std::priority_queue<_Tp, std::vector<_Tp>, _Compare>;
  using container_type::container_type;

  heap(const _Compare &__c) noexcept : container_type(__c) {}
};

template <class _Compare>
heap(const _Compare &)
    -> heap<std::decay_t<typename parse_compare<_Compare>::type>, _Compare>;

template <class _Tp = void, class _Compare = std::less<_Tp>>
decltype(auto) make_heap(const _Compare &__c = _Compare{}) {
  if constexpr (std::is_void<_Tp>::value)
    return heap(__c);
  else
    return heap<_Tp, _Compare>(__c);
}

}  // namespace workspace
