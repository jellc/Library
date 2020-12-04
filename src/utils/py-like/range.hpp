#pragma once

/*
 * @file range.hpp
 * @brief Range
 */

#include <iterator>

#include "../iterator/reverse.hpp"

namespace workspace {

template <class Index> class range {
  Index first, last;

 public:
  class iterator {
    Index iter;

   public:
    using difference_type = std::ptrdiff_t;
    using value_type = Index;
    using reference = typename std::add_const<Index>::type &;
    using pointer = iterator;
    using iterator_category = std::bidirectional_iterator_tag;

    constexpr iterator(Index iter = Index()) noexcept : iter(iter) {}

    constexpr bool operator==(iterator const &rhs) const noexcept {
      return iter == rhs.iter;
    }
    constexpr bool operator!=(iterator const &rhs) const noexcept {
      return iter != rhs.iter;
    }

    constexpr iterator &operator++() noexcept {
      ++iter;
      return *this;
    }
    constexpr iterator &operator--() noexcept {
      --iter;
      return *this;
    }

    constexpr reference operator*() const noexcept { return iter; }
  };

  constexpr range(Index first, Index last) noexcept
      : first(first), last(last) {}
  constexpr range(Index last) noexcept : first(), last(last) {}

  constexpr iterator begin() const noexcept { return iterator{first}; }
  constexpr iterator end() const noexcept { return iterator{last}; }

  constexpr reverse_iterator<iterator> rbegin() const noexcept {
    return reverse_iterator<iterator>(end());
  }
  constexpr reverse_iterator<iterator> rend() const noexcept {
    return reverse_iterator<iterator>(begin());
  }
};

}  // namespace workspace
