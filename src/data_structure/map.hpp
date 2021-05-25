#pragma once

/**
 * @file map.hpp
 * @brief Map
 */

#include <map>

#include "set.hpp"

namespace workspace {

/**
 * @brief Wrapper class for std::map.
 */
template <class _Key, class _Value = void, class _Compare = std::less<_Key>>
class map : public std::map<_Key, _Value, _Compare> {
  _Value __init{};

 public:
  using container_type = std::map<_Key, _Value, _Compare>;
  using container_type::container_type;

  map(const _Value &__x) noexcept : __init(__x) {}
  map(const _Value &__x, const _Compare &__c) noexcept
      : container_type(__c), __init(__x) {}

  _Value &operator[](const _Key &__x) noexcept {
    auto __i = container_type::lower_bound(__x);

    if (__i == container_type::end() ||
        container_type::key_comp()(__x, __i->first))
      __i = container_type::emplace_hint(__i, __x, __init);

    return __i->second;
  }

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

template <class _Key, class _Compare>
class map<_Key, void, _Compare> : public set<_Key, _Compare> {
  using set<_Key, _Compare>::set;
};

template <class _Value, class _Compare>
map(const _Value &__x, const _Compare &)
    -> map<std::decay_t<typename parse_compare<_Compare>::type>, _Value,
           _Compare>;

template <class _Compare>
map(const _Compare &)
    -> map<std::decay_t<typename parse_compare<_Compare>::type>, void,
           _Compare>;

template <class _Key = void, class _Value, class _Compare = std::less<_Key>>
decltype(auto) make_map(const _Value &__x, const _Compare &__c = _Compare{}) {
  if constexpr (std::is_void<_Key>::value)
    return map(__x, __c);
  else
    return map<_Key, _Value, _Compare>(__x, __c);
}

template <class _Key, class _Value, class _Compare = std::less<_Key>>
decltype(auto) make_map(const _Compare &__c = _Compare{}) {
  if constexpr (std::is_void<_Value>::value)
    return make_set(__c);
  else
    return map(_Value{}, __c);
}

}  // namespace workspace
