#pragma once

/**
 * @file enumerate.hpp
 * @brief Enumerate
 */

#include "range.hpp"
#include "zip.hpp"

#if __cplusplus >= 201703L

namespace workspace {

namespace _enumerate_impl {

constexpr size_t min_size() noexcept { return SIZE_MAX; }

template <class _Container, class... _Args>
constexpr size_t min_size(_Container const &__cont,
                          _Args &&... __args) noexcept {
  return std::min(std::size(__cont), min_size(std::forward<_Args>(__args)...));
}

}  // namespace _enumerate_impl

template <class... _Args>
constexpr decltype(auto) enumerate(_Args &&... __args) noexcept {
  return zip(range(_enumerate_impl::min_size(__args...)),
             std::forward<_Args>(__args)...);
}

template <class... _Args>
constexpr decltype(auto) enumerate(
    std::initializer_list<_Args> const &... __args) noexcept {
  return zip(range(_enumerate_impl::min_size(__args...)),
             std::vector(__args)...);
}

}  // namespace workspace

#endif
