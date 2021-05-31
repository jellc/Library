#pragma once

/**
 * @file set.hpp
 * @brief Set
 */

#include <set>

#include "lib/cxx17"
#include "src/utils/sfinae.hpp"

namespace workspace {

/**
 * @brief Wrapper class for std::set.
 */
template <class _Key, class _Compare>
class set : public std::set<_Key, _Compare> {
 public:
  using container_type = std::set<_Key, _Compare>;
  using container_type::container_type;

  set(const _Compare &__c) noexcept : container_type(__c) {}

  decltype(auto) front() noexcept { return *container_type::begin(); }
  decltype(auto) front() const noexcept { return *container_type::begin(); }

  decltype(auto) back() noexcept { return *std::prev(container_type::end()); }
  decltype(auto) back() const noexcept {
    return *std::prev(container_type::end());
  }

  decltype(auto) erase_front() noexcept {
    return container_type::erase(container_type::begin());
  }
  decltype(auto) erase_back() noexcept {
    return container_type::erase(std::prev(container_type::end()));
  }
};

template <class _Compare>
set(const _Compare &)
    -> set<std::decay_t<typename parse_compare<_Compare>::type>, _Compare>;

template <class _Key = void, class _Compare = std::less<_Key>>
decltype(auto) make_set(const _Compare &__c = _Compare{}) {
  if _CXX17_CONSTEXPR (std::is_void<_Key>::value)
    return set(__c);
  else
    return set<_Key, _Compare>(__c);
}

}  // namespace workspace
