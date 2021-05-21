#pragma once

/**
 * @file reference_list.hpp
 * @brief Reference List
 */

#include <vector>

namespace workspace {

/**
 * @brief Reference list.
 */
template <class _Tp>
class reference_list : public std::vector<std::reference_wrapper<_Tp>> {
 public:
  using container_type = std::vector<std::reference_wrapper<_Tp>>;

  reference_list() noexcept = default;

  template <class... _Args>
  reference_list(_Tp &__x, _Args &&...__args) noexcept
      : reference_list(private_ctor{}, __x, std::forward<_Args>(__args)...) {
    std::reverse(container_type::begin(), container_type::end());
  }

  class iterator : public container_type::iterator {
    using base_iterator = typename container_type::iterator;

   public:
    using reference = _Tp &;

    iterator() noexcept = default;
    iterator(const base_iterator &__x) noexcept : base_iterator(__x) {}

    decltype(auto) operator*() const noexcept {
      return base_iterator::operator*().get();
    }

    decltype(auto) operator->() const noexcept {
      return std::addressof(operator*());
    }
  };

  class const_iterator : public container_type::const_iterator {
    using base_iterator = typename container_type::const_iterator;

   public:
    using reference = const _Tp &;

    const_iterator() noexcept = default;
    const_iterator(const base_iterator &__x) noexcept : base_iterator(__x) {}

    decltype(auto) operator*() const noexcept {
      return base_iterator::operator*().get();
    }

    decltype(auto) operator->() const noexcept {
      return std::addressof(operator*());
    }
  };

  decltype(auto) begin() noexcept { return iterator(container_type::begin()); }
  decltype(auto) begin() const noexcept {
    return const_iterator(container_type::begin());
  }

  decltype(auto) end() noexcept { return iterator(container_type::end()); }
  decltype(auto) end() const noexcept {
    return const_iterator(container_type::end());
  }

  decltype(auto) front() noexcept { return container_type::front().get(); }

  decltype(auto) back() noexcept { return container_type::back().get(); }

  decltype(auto) operator[](typename container_type::size_type __i) noexcept {
    return container_type::operator[](__i).get();
  }

  using value_type = typename iterator::value_type;
  using reference = typename iterator::reference;

 private:
  struct private_ctor {};

  reference_list(private_ctor) noexcept {}

  template <class... _Args>
  reference_list(private_ctor __t, _Tp &__x, _Args &&...__args) noexcept
      : reference_list(__t, std::forward<_Args>(__args)...) {
    container_type::emplace_back(__x);
  }
};

}  // namespace workspace
